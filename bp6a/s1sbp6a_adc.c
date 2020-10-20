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
#include "mbed_wait_api.h"

#define get_SARADC_DATA_REG(c, p)  ((uint32_t)c << 3 | (uint32_t)p << 2)
#define get_SDADC_DATA_REG(c)      ((uint32_t)c << 2)

void bp6a_saradc_init(saradc_ch_t ch)
{
    uint32_t mask = 0x01 << (ch + SAR_ADC_CTRL_EN_ADC_SHIFT);

    modifyreg32(&BP_ADC_CON->SAR_ADC_CTRL, SAR_ADC_CTRL_EN_MASK |
                mask,
                SAR_ADC_CTRL_EN(1) |
                mask);
}

void bp6a_saradc_stop(saradc_ch_t ch)
{
    uint32_t mask = 0x01 << (ch + SAR_ADC_CTRL_EN_ADC_SHIFT);

    modifyreg32(&BP_ADC_CON->SAR_ADC_CTRL, SAR_ADC_CTRL_EN_MASK |
                mask,
                SAR_ADC_CTRL_EN(1) |
                0);
}


uint32_t bp6a_saradc_read(saradc_ch_t ch, saradc_port_t port)
{

    uint32_t reg = get_SARADC_DATA_REG(ch, port);
    reg += (uint32_t)(&BP_ADC_CON->SAR_ADC0_CH0_DATA);

    return getreg32(reg);
}

void bp6a_saradc_set_OSR(saradc_ch_t ch, saradc_osr_mode_t osrMode)
{
    uint32_t mask = 0x07 << (ch << 2);
    uint32_t val = osrMode << (ch << 2);

    modifyreg32(&(BP_ADC_CON->SAR_ADC_CON), mask, val);
}

uint32_t bp6a_saradc_get_OSR(saradc_ch_t ch)
{
    uint32_t shift = (ch << 2);
    uint32_t mask = 0x07;

    return getreg32(&BP_ADC_CON->SAR_ADC_CON) >> shift & mask;
}

void bp6a_saradc_reset_dm_cnt(saradc_ch_t ch)
{
    uint32_t shift = (ch << 2) + 3;
    uint32_t mask = 0x01 << shift;
    uint32_t val = 0x1 << shift;

    modifyreg32(&(BP_ADC_CON->SAR_ADC_CON), mask, val);
}

static void bp6a_sdadc_enable(bool enable)
{
    modifyreg32(&BP_SDADC_CON->SDADC_CTRL1, SDADC_CTRL1_SEL_INPUT_MASK |
                SDADC_CTRL1_DFILTER_MASK |
                SDADC_CTRL1_START_MASK |
                SDADC_CTRL1_ENALBE_MASK |
                SDADC_CTRL1_ENABLE_BUF_MASK,
                SDADC_CTRL1_SEL_INPUT(1) |
                SDADC_CTRL1_DFILTER(1) |
                SDADC_CTRL1_START(enable) |
                SDADC_CTRL1_ENALBE(enable) |
                SDADC_CTRL1_ENABLE_BUF(enable));

    modifyreg32(&BP_SDADC_CON->SDADC_CTRL3, SDADC_CTRL3_EN_CHOP_DSM_MASK |
                SDADC_CTRL3_EN_CHOP_BUF_MASK |
                SDADC_CTRL3_EN_DEM_MASK |
                SDADC_CTRL3_ENBUF_BYPASS_MASK,
                SDADC_CTRL3_EN_CHOP_DSM(0) |
                SDADC_CTRL3_EN_CHOP_BUF(1) |
                SDADC_CTRL3_EN_DEM(enable) |
                SDADC_CTRL3_ENBUF_BYPASS(1));

}

static void bp6a_sdadc_reset(bool reset)
{
    modifyreg32(&BP_SDADC_CON->SDADC_CTRL1, SDADC_CTRL1_RESET_MASK,
                SDADC_CTRL1_RESET(1));
    if (reset) {
        wait_us(1000);
        modifyreg32(&BP_SDADC_CON->SDADC_CTRL1, SDADC_CTRL1_RESET_MASK,
                    SDADC_CTRL1_RESET(0));
    }
}

void bp6a_sdadc_set_VCM_level(sdadc_sel_vcm_level_t vcm)
{
    modifyreg32(&BP_SDADC_CON->SDADC_CTRL2, SDADC_CTRL2_SEL_VCM_MASK,
                SDADC_CTRL2_SEL_VCM(vcm));
}

void bp6a_sdadc_LDO_enable(bool enable)
{
    modifyreg32(&BP_SDADC_CON->GPADC_LDO_CTRL, SDADC_LDO_CTRL_ENABLE_MASK,
                SDADC_LDO_CTRL_ENABLE(enable));
    wait_us(10000);
}

void bp6a_sdadc_init(sdadc_ch_t ch)
{
    bp6a_sdadc_LDO_enable(true);
    bp6a_sdadc_enable(true);
    bp6a_sdadc_reset(true);
}

void bp6a_sdadc_stop(sdadc_ch_t ch)
{
    bp6a_sdadc_enable(false);
    bp6a_sdadc_reset(false);
    bp6a_sdadc_LDO_enable(false);
}

void bp6a_sdadc_set_input_mode(sdadc_sel_input_mux_t mux)
{
    modifyreg32(&BP_SDADC_CON->SDADC_CTRL1, SDADC_CTRL1_SEL_INPUT_MASK,
                SDADC_CTRL1_SEL_INPUT(mux));
}

uint32_t bp6a_sdadc_read(sdadc_ch_t ch)
{
    return  getreg32(&(BP_ADC_CON->SD_ADC2_DATA));
}

uint32_t bp6a_sdad_read_isdac(isdadc_ch_t ch)
{
    uint32_t reg = (uint32_t)(&(BP_ADC_CON->SD_ADC0_DATA));
    reg += get_SDADC_DATA_REG(ch);

    return getreg32(reg);
}
