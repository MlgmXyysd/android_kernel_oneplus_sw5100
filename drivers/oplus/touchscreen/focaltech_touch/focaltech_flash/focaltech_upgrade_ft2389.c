/*
 *
 * FocalTech fts TouchScreen driver.
 *
 * Copyright (c) 2012-2020, Focaltech Ltd. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*****************************************************************************
*
* File Name: focaltech_upgrade_ft2389.c
*
* Author: Focaltech Driver Team
*
* Created: 2020-11-06
*
* Abstract:
*
* Reference:
*
*****************************************************************************/

/*****************************************************************************
* 1.Included header files
*****************************************************************************/
#include "../focaltech_flash.h"

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/
u8 pb_file_ft2389[] = {
#include "../include/pramboot/FT2389_Pramboot_V1.0_20210926.i"
};

/*****************************************************************************
* Private constant and macro definitions using #define
*****************************************************************************/

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/
static int fts_ft2389_upgrade(u8 *buf, u32 len)
{
    int ret = 0;
    u32 start_addr = 0;
    u8 cmd[4] = { 0 };
    u32 delay = 0;
    int ecc_in_host = 0;
    int ecc_in_tp = 0;

    if ((NULL == buf) || (len < FTS_MIN_LEN)) {
        FTS_ERROR("buffer/len(%x) is invalid", len);
        return -EINVAL;
    }

    /* enter into upgrade environment */
    ret = fts_fwupg_enter_into_boot();
    if (ret < 0) {
        FTS_ERROR("enter into pramboot/bootloader fail,ret=%d", ret);
        goto fw_reset;
    }

    cmd[0] = FTS_CMD_FLASH_MODE;
    cmd[1] = FLASH_MODE_UPGRADE_VALUE;
    if (upgrade_func_ft2389.appoff_handle_in_ic) {
        start_addr = 0; /* offset handle in pramboot */
    } else {
        start_addr = upgrade_func_ft2389.appoff;
    }
    FTS_INFO("flash mode:0x%02x, start addr=0x%04x", cmd[1], start_addr);

    ret = fts_write(cmd, 2);
    if (ret < 0) {
        FTS_ERROR("upgrade mode(09) cmd write fail");
        goto fw_reset;
    }

    cmd[0] = FTS_CMD_APP_DATA_LEN_INCELL;
    cmd[1] = BYTE_OFF_16(len);
    cmd[2] = BYTE_OFF_8(len);
    cmd[3] = BYTE_OFF_0(len);
    ret = fts_write(cmd, FTS_CMD_DATA_LEN_LEN);
    if (ret < 0) {
        FTS_ERROR("data len cmd write fail");
        goto fw_reset;
    }

    delay = FTS_ERASE_SECTOR_DELAY * (len / FTS_MAX_LEN_SECTOR);
    ret = fts_fwupg_erase(delay);
    if (ret < 0) {
        FTS_ERROR("erase cmd write fail");
        goto fw_reset;
    }

    /* write app */
    ecc_in_host = fts_flash_write_buf(start_addr, buf, len, 1);
    if (ecc_in_host < 0 ) {
        FTS_ERROR("flash write fail");
        goto fw_reset;
    }

    /* ecc */
    ecc_in_tp = fts_fwupg_ecc_cal(start_addr, len);
    if (ecc_in_tp < 0 ) {
        FTS_ERROR("ecc read fail");
        goto fw_reset;
    }

    FTS_INFO("ecc in tp:%x, host:%x", ecc_in_tp, ecc_in_host);
    if (ecc_in_tp != ecc_in_host) {
        FTS_ERROR("ecc check fail");
        goto fw_reset;
    }

    FTS_INFO("upgrade success, reset to normal boot");
    ret = fts_fwupg_reset_in_boot();
    if (ret < 0) {
        FTS_ERROR("reset to normal boot fail");
    }

    msleep(400);
    return 0;

fw_reset:
    return -EIO;
}

/************************************************************************
* Name: fts_ft2389_upgrade
* Brief:
* Input:
* Output:
* Return: return 0 if success, otherwise return error code
***********************************************************************/
struct upgrade_func upgrade_func_ft2389 = {
    .ctype = {0x27},
    .fwveroff = 0x10E,
    .fwcfgoff = 0x0F80,
    .appoff = 0x1000,
    .appoff_handle_in_ic = true,
    .upgspec_version = UPGRADE_SPEC_V_1_1,
    .pramboot_supported = true,
    .pramboot = pb_file_ft2389,
    .pb_length = sizeof(pb_file_ft2389),
    .upgrade = fts_ft2389_upgrade,
};
