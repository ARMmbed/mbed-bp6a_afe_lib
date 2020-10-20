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
#include "s1sbp6a_ecg.h"

/* ========================================================================== */
/*          F U N C T I O N S                                                 */
/* ========================================================================== */

static void  bp6a_ecg_enable(bool enable)
{
    putreg32(&BP_AFE_ECG->ECG_EN, ECG_EN(enable));
}

static void  bp6a_ecg_set_gain(ecg_pga_gain_t gain)
{
    putreg32(&BP_AFE_ECG->ECG_GAIN, ECG_GAIN(gain));
}

static ecg_pga_gain_t bp6a_ecg_get_gain(ecg_pga_gain_t *pGain)
{
    return (ecg_pga_gain_t)(getreg32(&BP_AFE_ECG->ECG_GAIN) & ECG_GAIN_MASK);
}

static void  bp6a_ecg_set_LPF_BW(ecg_lpf_bw_t bw)
{
    putreg32(&BP_AFE_ECG->ECG_BW, ECG_BW(bw));
}

static void  bp6a_ecg_LPF_disable(bool disable)
{
    modifyreg32(&BP_AFE_ECG->ECG_SET, ECG_LPF_BP_ON_MASK, ECG_LPF_BP_ON(disable));
}

static void  bp6a_ecg_set_input_polarity(bool enable)
{
    modifyreg32(&BP_AFE_ECG->ECG_SET, ECG_PHASE_CTRL_MASK, ECG_PHASE_CTRL(enable));
}

static void  bp6a_ecg_buf_bw_ctrl(bool enable)
{
    modifyreg32(&BP_AFE_ECG->ECG_SET, ECG_EN_OVRSMP_MASK, ECG_EN_OVRSMP(enable));
}

static void  bp6a_ecg_HPF_init(bool enable)
{
    modifyreg32(&BP_AFE_ECG->ECG_INIT, ECG_INIT_SC_HPF_MASK, ECG_INIT_SC_HPF(enable));
}

static void  bp6a_ecg_HPF_disable(bool disable)
{
    modifyreg32(&BP_AFE_ECG->ECG_HPF, ECG_HPF_BYPASS_EN_MASK, ECG_HPF_BYPASS_EN(disable));
}

static void  bp6a_ecg_ext_HPF_enable(bool enable)
{
    modifyreg32(&BP_AFE_ECG->ECG_HPF, ECG_EXT_HPF_EN_MASK, ECG_EXT_HPF_EN(enable));
}

static void  bp6a_ecg_2ndHPF_enable(bool enable)
{
    modifyreg32(&BP_AFE_ECG->ECG_HPF, ECG_HPF2_EN_MASK, ECG_HPF2_EN(enable));
}

static void  bp6a_ecg_set_VCMlevel(ecg_vcm_level_t level)
{
    modifyreg32(&BP_AFE_ECG->ECG_CONT, ECG_VB_IA_CONT1_MASK, ECG_VB_IA_CONT1(level));
}

static void  bp6a_ecg_set_input_short(bool enable)
{

    modifyreg32(&BP_AFE_ECG->ECG_CONT, ECG_IN_SHORTT_CTRL_MASK, ECG_IN_SHORTT_CTRL(enable));
}

static void  bp6a_ecg_RLD_enable(bool enable)
{
    modifyreg32(&BP_AFE_ECG->ECG_CONT, ECG_RLD_EN_MASK, ECG_RLD_EN(enable));
}

static void bp6a_ecg_chop_clk_enable(bool enable)
{
    modifyreg32(&BP_AFE_ECG->ECG_CONT, ECG_CHOP_CLK_EN_MASK, ECG_CHOP_CLK_EN(enable));
}

bool bp6a_ecg_get_input_polarity(void)
{
    return (!!(getreg32(&BP_AFE_ECG->ECG_SET) & ECG_PHASE_CTRL_MASK));
}

void bp6a_ecg_init(ecg_pga_gain_t gain)
{
    bp6a_afe_ecg_clk_enable(true);
    // bp6a_set_afe_con_clock(CMU_SRC_CLK_EXT_4M);

    bp6a_set_afe_con_clock(CMU_SRC_CLK_LSOSC);
    // bp6a_set_afe_smp_clk_div(125);
    // bp6a_set_afe_smp_clk_src(CMU_SELECT_INTERNAL_CLK);
    bp6a_set_afe_smp_clk_src(CMU_SELECT_EXTERNAL_XTAL_32768_CLK);
    bp6a_ecg_enable(true);
    bp6a_ecg_set_gain(gain);
    bp6a_ecg_set_LPF_BW(ECG_LPF_BW_250Hz);
    bp6a_ecg_2ndHPF_enable(false);
    bp6a_ecg_ext_HPF_enable(false);
    bp6a_ecg_HPF_disable(true);
    bp6a_ecg_RLD_enable(true);
    bp6a_ecg_set_input_polarity(true);
}

void bp6a_ecg_deinit(void)
{
    bp6a_ecg_enable(false);
    bp6a_afe_ecg_clk_enable(false);
}
