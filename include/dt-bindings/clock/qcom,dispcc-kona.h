/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2022, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _DT_BINDINGS_CLK_QCOM_DISP_CC_KONA_H
#define _DT_BINDINGS_CLK_QCOM_DISP_CC_KONA_H

/* DISP_CC clocks */
#define DISP_CC_MDSS_AHB_CLK					0
#define DISP_CC_MDSS_AHB_CLK_SRC				1
#define DISP_CC_MDSS_BYTE0_CLK					2
#define DISP_CC_MDSS_BYTE0_CLK_SRC				3
#define DISP_CC_MDSS_BYTE0_DIV_CLK_SRC				4
#define DISP_CC_MDSS_BYTE0_INTF_CLK				5
#define DISP_CC_MDSS_BYTE1_CLK					6
#define DISP_CC_MDSS_BYTE1_CLK_SRC				7
#define DISP_CC_MDSS_BYTE1_DIV_CLK_SRC				8
#define DISP_CC_MDSS_BYTE1_INTF_CLK				9
#define DISP_CC_MDSS_DP_AUX1_CLK				10
#define DISP_CC_MDSS_DP_AUX1_CLK_SRC				11
#define DISP_CC_MDSS_DP_AUX_CLK					12
#define DISP_CC_MDSS_DP_AUX_CLK_SRC				13
#define DISP_CC_MDSS_DP_LINK1_CLK				14
#define DISP_CC_MDSS_DP_LINK1_CLK_SRC				15
#define DISP_CC_MDSS_DP_LINK1_DIV_CLK_SRC			16
#define DISP_CC_MDSS_DP_LINK1_INTF_CLK				17
#define DISP_CC_MDSS_DP_LINK_CLK				18
#define DISP_CC_MDSS_DP_LINK_CLK_SRC				19
#define DISP_CC_MDSS_DP_LINK_DIV_CLK_SRC			20
#define DISP_CC_MDSS_DP_LINK_INTF_CLK				21
#define DISP_CC_MDSS_DP_PIXEL1_CLK				22
#define DISP_CC_MDSS_DP_PIXEL1_CLK_SRC				23
#define DISP_CC_MDSS_DP_PIXEL2_CLK				24
#define DISP_CC_MDSS_DP_PIXEL2_CLK_SRC				25
#define DISP_CC_MDSS_DP_PIXEL_CLK				26
#define DISP_CC_MDSS_DP_PIXEL_CLK_SRC				27
#define DISP_CC_MDSS_EDP_AUX_CLK				28
#define DISP_CC_MDSS_EDP_AUX_CLK_SRC				29
#define DISP_CC_MDSS_EDP_GTC_CLK				30
#define DISP_CC_MDSS_EDP_GTC_CLK_SRC				31
#define DISP_CC_MDSS_EDP_LINK_CLK				32
#define DISP_CC_MDSS_EDP_LINK_CLK_SRC				33
#define DISP_CC_MDSS_EDP_LINK_DIV_CLK_SRC			34
#define DISP_CC_MDSS_EDP_LINK_INTF_CLK				35
#define DISP_CC_MDSS_EDP_PIXEL_CLK				36
#define DISP_CC_MDSS_EDP_PIXEL_CLK_SRC				37
#define DISP_CC_MDSS_ESC0_CLK					38
#define DISP_CC_MDSS_ESC0_CLK_SRC				39
#define DISP_CC_MDSS_ESC1_CLK					40
#define DISP_CC_MDSS_ESC1_CLK_SRC				41
#define DISP_CC_MDSS_MDP_CLK					42
#define DISP_CC_MDSS_MDP_CLK_SRC				43
#define DISP_CC_MDSS_MDP_LUT_CLK				44
#define DISP_CC_MDSS_NON_GDSC_AHB_CLK				45
#define DISP_CC_MDSS_PCLK0_CLK					46
#define DISP_CC_MDSS_PCLK0_CLK_SRC				47
#define DISP_CC_MDSS_PCLK1_CLK					48
#define DISP_CC_MDSS_PCLK1_CLK_SRC				49
#define DISP_CC_MDSS_ROT_CLK					50
#define DISP_CC_MDSS_ROT_CLK_SRC				51
#define DISP_CC_MDSS_RSCC_AHB_CLK				52
#define DISP_CC_MDSS_RSCC_VSYNC_CLK				53
#define DISP_CC_MDSS_VSYNC_CLK					54
#define DISP_CC_MDSS_VSYNC_CLK_SRC				55
#define DISP_CC_PLL0						56
#define DISP_CC_PLL1						57
#define DISP_CC_SLEEP_CLK					58
#define DISP_CC_SLEEP_CLK_SRC					59
#define DISP_CC_XO_CLK						60

/* DISP_CC resets */
#define DISP_CC_MDSS_CORE_BCR					0
#define DISP_CC_MDSS_RSCC_BCR					1

#endif