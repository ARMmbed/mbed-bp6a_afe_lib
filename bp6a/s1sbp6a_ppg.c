/****************************************************************************
 *
 * Copyright 2020 Samsung Electronics All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
#include "s1sbp6a.h"
#include "s1sbp6a_type.h"
#include "s1sbp6a_adc.h"
#include "s1sbp6a_afe.h"
#include "s1sbp6a_ppg.h"

/* ========================================================================== */
/*          F U N C T I O N S                                                 */
/* ========================================================================== */
static bool is_ppg_enable = false;

static void bp6a_ppg_set_global_enable(ppg_ch_t ch, bool enable)
{
    modifyreg32(&BP_AFE_PPG->PPG_GLOBALEN, 1 << ch, enable << ch);
}

static void bp6a_init_ppg_gen_reg(void)
{
    modifyreg32(&BP_AFE_PPG->PPG_GENERAL, PPG_GEN_ALL_MASK,
                PPG_GEN_SHIELD_DRV_EN(1) | PPG_GEN_IDC_EN_LDO(1) | PPG_GEN_AFE_BYPASS(1) |
                PPG_GEN_IDC_CLK_DLY(1));
}

static void bp6a_ppg_ch_func_enable(ppg_ch_t ch, bool enable)
{
    modifyreg32(&BP_AFE_PPG->PPG0_FUNCEN + ch * 0x10, PPG_FUNC_ALL_MASK,
                PPG_FUNC_IDC_PDB_EN(enable) |
                PPG_FUNC_AFE_PDN_EN(enable) |
                PPG_FUNC_DCC_EN(enable) |
                PPG_FUNC_IDC_EN_CHOP(enable) |
                PPG_FUNC_IDC_EN_DWA(enable) |
                PPG_FUNC_TIA_EN(enable));
}

static void bp6a_ppg_ldo_enable(bool enable)
{
    modifyreg32(&BP_AFE_PPG->PPG_GENERAL, PPG_GEN_IDC_EN_LDO_MASK,
                PPG_GEN_IDC_EN_LDO(enable));
}

static void bp6a_ppg_led_on_time(uint32_t on_time_ms)
{

    putreg32(&BP_AFE_PPG->PPG0_LEDONT, on_time_ms);
}


static void bp6a_ppg_set_led_drv_current(uint8_t led, uint8_t val)
{
    if (led > 3) {
        return;
    }

    uint32_t addr = &BP_AFE_PPG->LED_CDAC0 + led;
    putreg32(addr, (uint32_t)val);
}

static void bp6a_ppg_adc_enable(ppg_ch_t ch, bool enable)
{
    modifyreg32(&BP_AFE_PPG->PPG0_FUNCEN + ch * 0x10,
                PPG_FUNC_IDC_EN_BUF_MASK | PPG_FUNC_IDC_EN_MASK | PPG_FUNC_IDC_PDB_EN_MASK,
                PPG_FUNC_IDC_EN_BUF(enable) | PPG_FUNC_IDC_EN(enable) | PPG_FUNC_IDC_PDB_EN(enable));
}


static void bp6a_set_tia(ppg_ch_t ch, uint8_t rp, uint8_t rn, uint8_t cp, uint8_t cn)
{
    modifyreg32(&BP_AFE_PPG->PPG0_TIA + ch * 0x10,
                PPG_RFP_MASK | PPG_RFN_MASK |
                PPG_CFP_MASK | PPG_CFN_MASK,
                PPG_RFP(rp) | PPG_RFN(rn) |
                PPG_CFP(cp) | PPG_CFN(cn));

}

void bp6a_ppg_dcc_ctrl(ppg_ch_t ch, uint8_t dccp, uint8_t dccn)
{
    modifyreg32(&BP_AFE_PPG->PPG0_DCCCTRL + ch * 0x10,
                PPG_DCCP_MASK | PPG_DCCN_MASK,
                PPG_DCCP(dccp) | PPG_DCCN(dccn));
}

void bp6a_ppg_conf_ch(ppg_ch_t ch, uint32_t prt)
{
    bp6a_ppg_set_global_enable(ch, true);
    bp6a_ppg_ch_func_enable(ch, true);
    bp6a_ppg_adc_enable(ch, true);


    bp6a_set_tia(ch, PPG_TIA_REGISTER_25K, PPG_TIA_REGISTER_25K,
                    PPG_TIA_CAPACITOR_18P, PPG_TIA_CAPACITOR_18P);

    bp6a_ppg_dcc_ctrl(ch, 0x3F, 0x3F);

    // bp6a_ppg_dcc_ctrl(ch, 0, 0);


    modifyreg32(&BP_AFE_PPG->PPG0_IDC + ch * 0x10,
                PPG_IDC_BUF_PWR_SEL_MASK | PPG_IDC_BUF_EN_CHOP_MASK |
                PPG_IDC_BUF_I_CTRL_MASK  | PPG_IDC_BUF_CMO_CTRL_MASK |
                PPG_IDC_CHOPCLK_SEL_MASK,
                PPG_IDC_BUF_PWR_SEL(1) | PPG_IDC_BUF_EN_CHOP(1) |
                PPG_IDC_BUF_I_CTRL(1) | PPG_IDC_BUF_CMO_CTRL(1) |
                PPG_IDC_CHOPCLK_SEL(2));

    putreg32(&BP_AFE_PPG->PPG0_PRT + ch * 0x10, prt);

    modifyreg32(&BP_AFE_PPG->PPG0_CONVT + ch * 0x10,
                PPG_CONVT_MASK | PPG_DECISCALE_MASK | PPG_DECIRSTDLY_MASK,
                PPG_CONVT(0x200) | PPG_DECISCALE(8) | PPG_DECIRSTDLY(0));

    putreg32(&BP_AFE_PPG->PPG0_IDCRSTT + ch * 0x10, 0x21);

    putreg32(&BP_AFE_PPG->PPG0_AFESETT + ch * 0x10, 0x14);
    modifyreg32(&BP_AFE_PPG->PPG0_PDNTCTRL + ch * 0x10,
                PPG_PDNWAIT_MASK | PPG_AFEAGE_MASK,
                PPG_PDNWAIT(41) | PPG_AFEAGE(0));
}

void bp6a_ppg_led_enable(bool enable)
{
    modifyreg32(&BP_AFE_PPG->LED_FUNCEN, PPG_LED_EN_MASK, PPG_LED_EN(enable));
}

void bp6a_ppg_conf_leddrv(uint32_t led_ontime, uint8_t *drv_cur)
{
    int i;

    /*LED On time*/
    bp6a_ppg_led_on_time(led_ontime);

    /*Enable Time Slot */
    for (i = 0; i < PPG_MAX_TIME_SLOT; i++) {
        bp6a_ppg_set_led_drv_current(i, drv_cur[i]);
    }

    bp6a_ppg_led_enable(true);
}

void bp6a_ppg_led_time_slot_enable(uint32_t val)
{
    modifyreg32(&BP_AFE_PPG->PPG0_LEDTSCTRL, 0x0F, val);

}
int bp6a_ppg_init(void)
{
    if (is_ppg_enable) {
        return -1;
    }

    /* AFE CTRL Clock */
    bp6a_set_afe_smp_clk_div(125);
    bp6a_set_afe_con_clock(CMU_SRC_CLK_LSOSC);
    bp6a_set_afe_smp_clk_src(CMU_SELECT_EXTERNAL_XTAL_32768_CLK);

    bp6a_afe_ppg_clk_enable(true);
    bp6a_ppg_ldo_enable(true);
    bp6a_init_ppg_gen_reg();
    bp6a_afe_ppg_buf_enable();

    is_ppg_enable = true;
    putreg32(&BP_AFE_PPG->LED_TRIM, 7);

    return 0;
}

void bp6a_ppg_deinit(void)
{
    int ch;

    bp6a_ppg_led_enable(false);

    for (ch = 0; ch < PPG_MAX_PD; ch++) {
        bp6a_ppg_adc_enable(ch, false);
        bp6a_ppg_ch_func_enable(ch, false);
        bp6a_ppg_set_global_enable(ch, false);
    }

    bp6a_ppg_ldo_enable(false);
    bp6a_afe_ppg_clk_enable(false);

    is_ppg_enable = false;
}
