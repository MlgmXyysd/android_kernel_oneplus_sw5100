/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2022, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __DRIVERS_CLK_QCOM_VDD_LEVEL_SDX55_H
#define __DRIVERS_CLK_QCOM_VDD_LEVEL_SDX55_H

#include <linux/regulator/consumer.h>
#include <dt-bindings/regulator/qcom,rpmh-regulator-levels.h>

enum vdd_levels {
	VDD_NONE,
	VDD_MIN,		/* MIN SVS */
	VDD_LOWER,		/* SVS2 */
	VDD_LOW,		/* SVS */
	VDD_LOW_L1,		/* SVSL1 */
	VDD_NOMINAL,		/* NOM */
	VDD_HIGH,		/* TURBO */
	VDD_NUM,
};

static int vdd_corner[] = {
	0,					/* VDD_NONE */
	RPMH_REGULATOR_LEVEL_MIN_SVS,		/* VDD_MIN */
	RPMH_REGULATOR_LEVEL_LOW_SVS,		/* VDD_LOWER */
	RPMH_REGULATOR_LEVEL_SVS,		/* VDD_LOW */
	RPMH_REGULATOR_LEVEL_SVS_L1,		/* VDD_LOW_L1 */
	RPMH_REGULATOR_LEVEL_NOM,		/* VDD_NOMINAL */
	RPMH_REGULATOR_LEVEL_TURBO,		/* VDD_HIGH */
};

#endif