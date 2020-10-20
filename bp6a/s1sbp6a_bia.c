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
#include "s1sbp6a_bia.h"

/* ========================================================================== */
/*          F U N C T I O N S                                                 */
/* ========================================================================== */

void bp6a_bia_set_tx_lpf(bia_tx_lpf_t val)
{
    putreg32(&BP_AFE_BIA->BIA_TX_FIL, (uint32_t)val);
}

void bp6a_bia_set_tx_freq(uint32_t val)
{
    putreg32(&BP_AFE_BIA->BIA_TX_FREQ, (uint32_t)val);
}

void bp6a_bia_set_tx_amp(uint32_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_TX_AMPL, BIA_TX_AMP_DAC_MASK, BIA_TX_AMP_DAC(val));
}

void bp6a_bia_set_tx_volt_range(bia_tx_range_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_TX_AMPL, BIA_TX_AMP_DACI_MASK, BIA_TX_AMP_DACI(val));
}

void bp6a_bia_set_tx_volt(uint8_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_TX_AMPL, BIA_TX_AMP_DAC_MASK, BIA_TX_AMP_DAC(val));
}

void bp6a_bia_enable_tx_amp_cur_up(bool enable)
{
    modifyreg32(&BP_AFE_BIA->BIA_TX_CUR, BIA_TX_CUR_ICONT_MASK, BIA_TX_CUR_ICONT(enable));
}

void bp6a_bia_enable_tx_drv_cur_up(bool enable)
{
    modifyreg32(&BP_AFE_BIA->BIA_TX_CUR, BIA_TX_CUR_IDUP_MASK, BIA_TX_CUR_IDUP(enable));
}

void bp6a_bia_set_tx_switch(bia_tx_rn_path_t txChN, bia_tx_rp_path_t txChP, bia_tx_i_path_t txChI)
{
    modifyreg32(&BP_AFE_BIA->BIA_TX_SW, BIA_TX_SW_DACSI_MASK |
                BIA_TX_SW_DACSRP_MASK | BIA_TX_SW_DACSRN_MASK,
                BIA_TX_SW_DACSI(txChI) | BIA_TX_SW_DACSRP(txChP) |
                BIA_TX_SW_DACSRN(txChN));
}

void bp6a_bia_set_rx_switch(bia_rx_path_t rxChN, bia_rx_path_t rxChP)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_INPUT,
                BIA_RX_INPUT_VSENCTRP_MASK |
                BIA_RX_INPUT_VSENCTRN_MASK,
                BIA_RX_INPUT_VSENCTRP((uint32_t)rxChP) | BIA_RX_INPUT_VSENCTRN((uint32_t)rxChN));

}

void bp6a_bia_set_path(bia_imp_path_t sel)
{
    switch (sel) {
        case BIA_CALIBRATION_PATH0:
            /* TX switch set to RN0/RP0 measure */
            bp6a_bia_set_tx_switch(BIA_TX_RN0, BIA_TX_RP0, BIA_TX_BODY_UNUSED);

            /* RX switch set to RN0/RP0 measure */
            bp6a_bia_set_rx_switch(BIA_RX_OFFSET_OUTER_REG0, BIA_RX_OFFSET_OUTER_REG0);
            break;

        case BIA_CALIBRATION_PATH1:
            /* TX switch set to RN0/RP0 measure */
            bp6a_bia_set_tx_switch(BIA_TX_RN1, BIA_TX_RP1, BIA_TX_BODY_UNUSED);

            /* RX switch set to RN0/RP0 measure */
            bp6a_bia_set_rx_switch(BIA_RX_OFFSET_OUTER_REG1, BIA_RX_OFFSET_OUTER_REG1);
            break;

        case BIA_BODY_PATH:
            /* TX switch set to Body measure */
            bp6a_bia_set_tx_switch(BIA_TX_RN_UNUSED, BIA_TX_RP_UNUSED, BIA_TX_BODY);

            /* RX switch set to Body measure */
            bp6a_bia_set_rx_switch(BIA_RX_BODY, BIA_RX_BODY);
            break;

        default:
            break;
    }

}

void bp6a_bia_set_mode(bia_mode_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_AMP1, BIA_RX_AMP1_IQ_MODE_SEL_MASK, BIA_RX_AMP1_IQ_MODE_SEL(val));
}

void bp6a_bia_set_rx_buff_gain(bia_amp_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_AMP1, BIA_RX_AMP1_AMPCTRL_MASK, BIA_RX_AMP1_AMPCTRL(val));
}

void bp6a_bia_set_rx_I_amp_gain(bia_amp_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_AMP2, BIA_RX_AMP2_IAMPCTRL_MASK, BIA_RX_AMP2_IAMPCTRL(val));
}

void bp6a_bia_set_rx_Q_amp_gain(bia_amp_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_AMP2, BIA_RX_AMP2_QAMPCTRL_MASK, BIA_RX_AMP2_QAMPCTRL(val));
}

void bp6a_bia_enable_hysteresis(bool enable)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_COMP, BIA_RX_COMP_HYS_ON_MASK, BIA_RX_COMP_HYS_ON(enable));
}

void bp6a_bia_set_comp_gain(bia_comp_amp_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_COMP, BIA_RX_COMAMPCTRL_MASK, BIA_RX_COMAMPCTRL(0x01 << val));
}

void bp6a_bia_set_comp_delay(uint32_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_COMP, BIA_RX_COMP_HYS_RES_CONTROL_MASK,
                BIA_RX_COMP_HYS_RES_CONTROL(val));
}

void bp6a_bia_set_dc_amp_gain(bia_dc_amp_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_AMP3, BIA_RX_AMP3_DC_AMP_CTRL_MASK,
                BIA_RX_AMP3_DC_AMP_CTRL(0x1 << val));
}

void bp6a_bia_enable_dc_amp(bool enable)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_AMP3, BIA_RX_AMP3_DC_AMP_CTRL_EN_MASK,
                BIA_RX_AMP3_DC_AMP_CTRL_EN(!enable));

}

void bp6a_bia_set_current_ctrl(bia_current_t val)
{
    modifyreg32(&BP_AFE_BIA->BIA_RX_AMP3, BIA_RX_AMP3_BIA_RXBIAS_CTRL_MASK,
                BIA_RX_AMP3_BIA_RXBIAS_CTRL(val));
}

void bp6a_bia_enable_tx(bool enable)
{
    modifyreg32(&BP_AFE_BIA->BIA_TRX_EN, BIA_TX_EN_MASK, BIA_TX_EN(enable));
}

void bp6a_bia_enable_rx(bool enable)
{
    modifyreg32(&BP_AFE_BIA->BIA_TRX_EN, BIA_RX_EN_MASK, BIA_RX_EN(enable));
}

void bp6a_bia_init(void)
{
    bp6a_afe_bia_clk_enable(true);

    bp6a_bia_set_tx_lpf(BIA_TX_LPF_2000KHZ);
    bp6a_bia_set_tx_volt(0x20);
    bp6a_bia_set_tx_volt_range(BIA_TX_RANGE_400MV);
    bp6a_bia_set_tx_freq(0x32);

    /* tx current up */
    bp6a_bia_enable_tx_amp_cur_up(true);
    bp6a_bia_enable_tx_drv_cur_up(true);

    /* set impednace path*/
    bp6a_bia_set_path(BIA_BODY_PATH);

    /* set rx gain */
    bp6a_bia_set_rx_buff_gain(BIA_AMP_2X);
    bp6a_bia_set_rx_I_amp_gain(BIA_AMP_1X);
    bp6a_bia_set_rx_Q_amp_gain(BIA_AMP_1X);

    /*set rx comparater */
    bp6a_bia_enable_hysteresis(true);
    bp6a_bia_set_comp_gain(BIA_COMP_AMP_1X);
    bp6a_bia_set_comp_delay(1);

    /* set dc amp */
    bp6a_bia_enable_dc_amp(true);
    bp6a_bia_set_dc_amp_gain(BIA_DC_AMP_2X);
    bp6a_bia_set_current_ctrl(BIA_CURRENT_350NA);
}

void bp6a_bia_deinit(void)
{
    bp6a_afe_bia_clk_enable(false);
}
