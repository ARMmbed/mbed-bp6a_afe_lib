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
#include "s1sbp6a_afe_def.h"
#include "s1sbp6a_cmu_def.h"
#include "s1sbp6a_afe.h"

void bp6a_afe_ecg_clk_enable(bool enable)
{

    modifyreg32(&BP_AFE_TOP->AFE_CLK_CTRL, AFE_CLK_CTRL_ECG_CLK_EN_MASK |
                AFE_CLK_CTRL_SAR_ADC0_CLK_EN_MASK,
                AFE_CLK_CTRL_SAR_ADC0_CLK_EN(enable) |
                AFE_CLK_CTRL_ECG_CLK_EN(enable));
}

void bp6a_afe_bia_clk_enable(bool enable)
{
    modifyreg32(&BP_AFE_TOP->AFE_CLK_CTRL, AFE_CLK_CTRL_BIA_CLK_EN_MASK |
                AFE_CLK_CTRL_SAR_ADC0_CLK_EN_MASK |
                AFE_CLK_CTRL_SAR_ADC1_CLK_EN_MASK,
                AFE_CLK_CTRL_BIA_CLK_EN(enable) |
                AFE_CLK_CTRL_SAR_ADC0_CLK_EN(enable) |
                AFE_CLK_CTRL_SAR_ADC1_CLK_EN(enable));
}

void bp6a_afe_ppg_clk_enable(bool enable)
{
    modifyreg32(&BP_AFE_TOP->AFE_CLK_CTRL, AFE_CLK_CTRL_PPG_CLK_EN_MASK,
                AFE_CLK_CTRL_PPG_CLK_EN(enable) | 0x08);
}

void bp6a_afe_ppg_buf_enable(void)
{
    modifyreg32(&BP_AFE_TOP->V11_RESERVED0, V11_RSV0_PPG_IDC_BUF_ENA_MASK |
                V11_RSV0_PPG0_IDC_BUF_VCM_CTR_MASK |
                V11_RSV0_PPG1_IDC_BUF_VCM_CTR_MASK,
                V11_RSV0_PPG_IDC_BUF_ENA(1) |
                V11_RSV0_PPG0_IDC_BUF_VCM_CTR(4) |
                V11_RSV0_PPG1_IDC_BUF_VCM_CTR(4));
}

void bp6a_set_afe_con_clock(cmu_src_clk_t clock)
{
    modifyreg32(&BP_SYSCON->AFE_CLK_CTRL, CMU_AFE_CLK_CTRL_SEL_SRC_MASK,
                CMU_AFE_CLK_CTRL_SEL_SRC(clock));
}

void bp6a_set_afe_smp_clk_div(uint32_t div)
{
    modifyreg32(&BP_SYSCON->AFE_CLK_CTRL, CMU_AFE_CLK_CTRL_SMP_CLK_DIV_MASK |
                CMU_AFE_CLK_CTRL_AFE_DIV_ON_MASK,
                CMU_AFE_CLK_CTRL_AFE_DIV_ON(1) |
                CMU_AFE_CLK_CTRL_SMP_CLK_DIV(div));
}

void bp6a_set_afe_smp_clk_src(cmu_sel_smp_clk_t src)
{
    modifyreg32(&BP_SYSCON->AFE_CLK_CTRL, AFE_CLK_CTRL_AFE_CLK_SRC_MASK,
                AFE_CLK_CTRL_AFE_CLK_SRC(src));
}
