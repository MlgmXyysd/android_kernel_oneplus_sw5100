// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2010-2015, 2017, 2019, 2021 The Linux Foundation. All rights reserved.
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/rq_stats.h>
#include <linux/module.h>

#define MAX_LONG_SIZE 24
#define DEFAULT_DEF_TIMER_JIFFIES 5

struct rq_data rq_info;
struct workqueue_struct *rq_wq;
spinlock_t rq_lock;

static void def_work_fn(struct work_struct *work)
{
	/* Notify polling threads on change of value */
	sysfs_notify(rq_info.kobj, NULL, "def_timer_ms");
}

static ssize_t show_def_timer_ms(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	int64_t diff;
	u64 udiff;

	diff = ktime_to_ns(ktime_get()) - rq_info.def_start_time;
	udiff = (u64)diff;
	do_div(udiff, 1000 * 1000);

	return snprintf(buf, MAX_LONG_SIZE, "%u\n", udiff);
}

static ssize_t store_def_timer_ms(struct kobject *kobj,
		struct kobj_attribute *attr, const char *buf, size_t count)
{
	unsigned int val = 0;

	if (kstrtouint(buf, 0, &val))
		return -EINVAL;

	rq_info.def_timer_jiffies = msecs_to_jiffies(val);

	rq_info.def_start_time = ktime_to_ns(ktime_get());
	return count;
}

static struct kobj_attribute def_timer_ms_attr =
	__ATTR(def_timer_ms, 0600, show_def_timer_ms,
			store_def_timer_ms);

static struct attribute *rq_attrs[] = {
	&def_timer_ms_attr.attr,
	NULL,
};

static struct attribute_group rq_attr_group = {
	.attrs = rq_attrs,
};

static int init_rq_attribs(void)
{
	int err;

	rq_info.attr_group = &rq_attr_group;

	/* Create /sys/devices/system/cpu/cpu0/rq-stats/... */
	rq_info.kobj = kobject_create_and_add("rq-stats",
			&get_cpu_device(0)->kobj);
	if (!rq_info.kobj)
		return -ENOMEM;

	err = sysfs_create_group(rq_info.kobj, rq_info.attr_group);
	if (err)
		kobject_put(rq_info.kobj);
	else
		kobject_uevent(rq_info.kobj, KOBJ_ADD);

	return err;
}

static int __init msm_rq_stats_init(void)
{
	int ret;

#ifndef CONFIG_SMP
	/* Bail out if this is not an SMP Target */
	rq_info.init = 0;
	return -EPERM;
#endif

	rq_wq = create_singlethread_workqueue("rq_stats");
	WARN_ON(!rq_wq);
	INIT_WORK(&rq_info.def_timer_work, def_work_fn);
	spin_lock_init(&rq_lock);
	rq_info.def_timer_jiffies = DEFAULT_DEF_TIMER_JIFFIES;
	rq_info.def_timer_last_jiffy = 0;
	ret = init_rq_attribs();

	rq_info.init = 1;

	return ret;
}
late_initcall(msm_rq_stats_init);

static __exit void msm_rq_stats_exit(void)
{
	destroy_workqueue(rq_wq);
	kobject_del(rq_info.kobj);
}
module_exit(msm_rq_stats_exit);

MODULE_DESCRIPTION("QCOM Run Queue Stats");
MODULE_LICENSE("GPL v2");