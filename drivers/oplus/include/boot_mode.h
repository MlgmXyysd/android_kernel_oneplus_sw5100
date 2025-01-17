/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2018-2021 Oplus. All rights reserved.
 */
#ifndef _BOOT_MODE_H
#define _BOOT_MODE_H
enum{
	MSM_BOOT_MODE__NORMAL,
	MSM_BOOT_MODE__FASTBOOT,
	MSM_BOOT_MODE__RECOVERY,
	MSM_BOOT_MODE__FACTORY,
	MSM_BOOT_MODE__RF,
	MSM_BOOT_MODE__WLAN,
	MSM_BOOT_MODE__MOS,
	MSM_BOOT_MODE__CHARGE,
	MSM_BOOT_MODE__SILENCE,
	MSM_BOOT_MODE__SAU,
	MSM_BOOT_MODE__AGING = 998,
	MSM_BOOT_MODE__SAFE = 999,
};

extern int get_boot_mode(void);
#ifdef OPLUS_BUG_STABILITY
/*add for charge*/
extern bool qpnp_is_power_off_charging(void);
#endif
#ifdef OPLUS_BUG_STABILITY
/*add for detect charger when reboot */
extern bool qpnp_is_charger_reboot(void);
#endif /*OPLUS_BUG_STABILITY*/
#endif  /*_BOOT_MODE_H*/

#ifdef OPLUS_BUG_STABILITY
/*Add for kernel monitor whole bootup*/
#ifdef PHOENIX_PROJECT
extern bool op_is_monitorable_boot(void);
#endif
#endif

