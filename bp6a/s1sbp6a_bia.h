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

#ifndef _S1SBP6A_BIA_H_
#define _S1SBP6A_BIA_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define BIA_TX_AMP_DAC_SHIFT                0
#define BIA_TX_AMP_DACI_SHIFT               6
#define BIA_TX_AMP_DFSGAIN_SHIFT            8

#define BIA_TX_AMP_DAC_MASK                 ((0x3F) << BIA_TX_AMP_DAC_SHIFT)
#define BIA_TX_AMP_DACI_MASK                ((0x03) << BIA_TX_AMP_DACI_SHIFT)
#define BIA_TX_AMP_DFSGAIN_MASK             ((0x03) << BIA_TX_AMP_DFSGAIN_SHIFT)
#define BIA_TX_AMP_DAC(c)                   ((c) << BIA_TX_AMP_DAC_SHIFT)
#define BIA_TX_AMP_DACI(c)                  ((c) << BIA_TX_AMP_DACI_SHIFT)
#define BIA_TX_AMP_DFSGAIN(c)               ((c) << BIA_TX_AMP_DFSGAIN_SHIFT)

#define BIA_TX_CUR_IAMPUP_SHIFT             (0)
#define BIA_TX_CUR_ITOPUP_SHIFT             (1)
#define BIA_TX_CUR_ICONT_SHIFT              (2)
#define BIA_TX_CUR_IDUP_SHIFT               (3)
#define BIA_TX_CUR_IAMPUP_MASK              ((0x01) << BIA_TX_CUR_IAMPUP_SHIFT)
#define BIA_TX_CUR_ITOPUP_MASK              ((0x01) << BIA_TX_CUR_ITOPUP_SHIFT)
#define BIA_TX_CUR_ICONT_MASK               ((0x01) << BIA_TX_CUR_ICONT_SHIFT)
#define BIA_TX_CUR_IDUP_MASK                ((0x01) << BIA_TX_CUR_IDUP_SHIFT)
#define BIA_TX_CUR_IAMPUP(c)                ((c) << BIA_TX_CUR_IAMPUP_SHIFT)
#define BIA_TX_CUR_ITOPUP(c)                ((c) << BIA_TX_CUR_ITOPUP_SHIFT)
#define BIA_TX_CUR_ICONT(c)                 ((c) << BIA_TX_CUR_ICONT_SHIFT)
#define BIA_TX_CUR_IDUP(c)                  ((c) << BIA_TX_CUR_IDUP_SHIFT)

#define BIA_TX_SW_DACSI_SHIFT               (0)
#define BIA_TX_SW_DACSRP_SHIFT              (2)
#define BIA_TX_SW_DACSRN_SHIFT              (4)
#define BIA_TX_SW_DACSI_MASK                ((0x03) << BIA_TX_SW_DACSI_SHIFT)
#define BIA_TX_SW_DACSRP_MASK               ((0x03) << BIA_TX_SW_DACSRP_SHIFT)
#define BIA_TX_SW_DACSRN_MASK               ((0x03) << BIA_TX_SW_DACSRN_SHIFT)
#define BIA_TX_SW_DACSI(c)                  ((c) << BIA_TX_SW_DACSI_SHIFT)
#define BIA_TX_SW_DACSRP(c)                 ((c) << BIA_TX_SW_DACSRP_SHIFT)
#define BIA_TX_SW_DACSRN(c)                 ((c) << BIA_TX_SW_DACSRN_SHIFT)


#define BIA_RX_INPUT_VSENCTRN_SHIFT         (0)
#define BIA_RX_INPUT_VSENCTRP_SHIFT         (2)

#define BIA_RX_INPUT_VSENCTRN_MASK          ((0x03) << BIA_RX_INPUT_VSENCTRN_SHIFT)
#define BIA_RX_INPUT_VSENCTRP_MASK          ((0x03) << BIA_RX_INPUT_VSENCTRP_SHIFT)

#define BIA_RX_INPUT_VSENCTRN(c)            ((c) << BIA_RX_INPUT_VSENCTRN_SHIFT)
#define BIA_RX_INPUT_VSENCTRP(c)            ((c) << BIA_RX_INPUT_VSENCTRP_SHIFT)

#define BIA_RX_AMP1_AMPCTRL_SHIFT           (0)
#define BIA_RX_AMP1_IQ_MODE_SEL_SHIFT       (4)
#define BIA_RX_AMP1_AMPCTRL_MASK            ((0x07) << BIA_RX_AMP1_AMPCTRL_SHIFT)
#define BIA_RX_AMP1_IQ_MODE_SEL_MASK        ((0x01) << BIA_RX_AMP1_IQ_MODE_SEL_SHIFT)
#define BIA_RX_AMP1_AMPCTRL(c)              ((c) << BIA_RX_AMP1_AMPCTRL_SHIFT)
#define BIA_RX_AMP1_IQ_MODE_SEL(c)          ((c) << BIA_RX_AMP1_IQ_MODE_SEL_SHIFT)

#define BIA_RX_AMP2_QAMPCTRL_SHIFT          (0)
#define BIA_RX_AMP2_IAMPCTRL_SHIFT          (4)
#define BIA_RX_AMP2_QAMPCTRL_MASK           ((0x07) << BIA_RX_AMP2_QAMPCTRL_SHIFT)
#define BIA_RX_AMP2_IAMPCTRL_MASK           ((0x07) << BIA_RX_AMP2_IAMPCTRL_SHIFT)
#define BIA_RX_AMP2_QAMPCTRL(c)             ((c) << BIA_RX_AMP2_QAMPCTRL_SHIFT)
#define BIA_RX_AMP2_IAMPCTRL(c)             ((c) << BIA_RX_AMP2_IAMPCTRL_SHIFT)

#define BIA_RX_FIL_FBANDCTRL_SHIFT          (0)
#define BIA_RX_FIL_FBANDCTRL_MASK           ((0x07) << BIA_RX_FIL_FBANDCTRL_SHIFT)
#define BIA_RX_FIL_FBANDCTRL(c)             ((c) << BIA_RX_FIL_FBANDCTRL_SHIFT)

#define BIA_RX_AMP3_DC_AMP_CTRL_SHIFT       (0)
#define BIA_RX_AMP3_DC_AMP_CTRL_EN_SHIFT    (4)
#define BIA_RX_AMP3_BIA_RXBIAS_CTRL_SHIFT   (5)
#define BIA_RX_AMP3_DC_AMP_CTRL_MASK        ((0x07) << BIA_RX_AMP3_DC_AMP_CTRL_SHIFT)
#define BIA_RX_AMP3_DC_AMP_CTRL_EN_MASK     ((0x01) << BIA_RX_AMP3_DC_AMP_CTRL_EN_SHIFT)
#define BIA_RX_AMP3_BIA_RXBIAS_CTRL_MASK    ((0x03) << BIA_RX_AMP3_BIA_RXBIAS_CTRL_SHIFT)
#define BIA_RX_AMP3_DC_AMP_CTRL(c)          ((c) << BIA_RX_AMP3_DC_AMP_CTRL_SHIFT)
#define BIA_RX_AMP3_DC_AMP_CTRL_EN(c)       ((c) << BIA_RX_AMP3_DC_AMP_CTRL_EN_SHIFT)
#define BIA_RX_AMP3_BIA_RXBIAS_CTRL(c)      ((c) << BIA_RX_AMP3_BIA_RXBIAS_CTRL_SHIFT)

#define BIA_RX_COMP_HYS_RES_CONTROL_SHIFT   (0)
#define BIA_RX_COMP_HYS_ON_SHIFT            (3)
#define BIA_RX_COMAMPCTRL_SHIFT             (4)
#define BIA_RX_COMP_HYS_RES_CONTROL_MASK    ((0x07) << BIA_RX_COMP_HYS_RES_CONTROL_SHIFT)
#define BIA_RX_COMP_HYS_ON_MASK             ((0x01) << BIA_RX_COMP_HYS_ON_SHIFT)
#define BIA_RX_COMAMPCTRL_MASK              ((0x07) << BIA_RX_COMAMPCTRL_SHIFT)
#define BIA_RX_COMP_HYS_RES_CONTROL(c)      ((c) << BIA_RX_COMP_HYS_RES_CONTROL_SHIFT)
#define BIA_RX_COMP_HYS_ON(c)               ((c) << BIA_RX_COMP_HYS_ON_SHIFT)
#define BIA_RX_COMAMPCTRL(c)                ((c) << BIA_RX_COMAMPCTRL_SHIFT)

#define BIA_DCTRL1_DACIN_SEL_SHIFT          (5)
#define BIA_DCTRL1_DACIN_SEL_MASK           ((0x03) << BIA_DCTRL1_DACIN_SEL_SHIFT)
#define BIA_DCTRL1_DACIN_SEL(c)             ((c) << BIA_DCTRL1_DACIN_SEL_SHIFT)

#define BIA_IQ_GEN_SHIFT_SEL_SHIFT          (0)
#define BIA_IQ_GEN_PHASE_SFT_EN_SHIFT       (10)
#define BIA_IQ_GEN_MASK_SEL_MASK            ((0x3FF) << BIA_IQ_GEN_SHIFT_SEL_SHIFT)
#define BIA_IQ_GEN_PHASE_SFT_EN_MASK        ((0x01) << BIA_IQ_GEN_PHASE_SFT_EN_SHIFT)
#define BIA_IQ_GEN_SEL(c)                   ((c) << BIA_IQ_GEN_SHIFT_SEL_SHIFT)
#define BIA_IQ_GEN_PHASE_SFT_EN(c)          ((c) << BIA_IQ_GEN_PHASE_SFT_EN_SHIFT)

#define BIA_TX_EN_SHIFT                     (0)
#define BIA_RX_EN_SHIFT                     (1)
#define BIA_TX_EN_MASK                      ((0x01) << BIA_TX_EN_SHIFT)
#define BIA_RX_EN_MASK                      ((0x01) << BIA_RX_EN_SHIFT)
#define BIA_TX_EN(c)                        ((c) << BIA_TX_EN_SHIFT)
#define BIA_RX_EN(c)                        ((c) << BIA_RX_EN_SHIFT)

#define BIA_TX_IDOWN_SHIFT                  (0)
#define BIA_RX_IUP_SHIFT                    (1)
#define BIA_RECT_IUP_SHIFT                  (2)
#define BIA_TX_IDOWN_MASK                   ((0x01) << BIA_TX_IDOWN_SHIFT)
#define BIA_RX_IUP_MASK                     ((0x01) << BIA_RX_IUP_SHIFT)
#define BIA_RECT_IUP_MASK                   ((0x01) << BIA_RECT_IUP_SHIFT)
#define BIA_TX_IDOWN(c)                     ((c) << BIA_TX_IDOWN_SHIFT)
#define BIA_RX_IUP(c)                       ((c) << BIA_RX_IUP_SHIFT)
#define BIA_RECT_IUP(c)                     ((c) << BIA_RECT_IUP_SHIFT)


typedef enum {
    BIA_TX_LPF_125KHZ = 0,
    BIA_TX_LPF_500KHZ,
    BIA_TX_LPF_1000KHZ,
    BIA_TX_LPF_2000KHZ,

    BIA_TX_LPF_MAX,
} bia_tx_lpf_t;


typedef enum _bia_tx_range_t {
    BIA_TX_RANGE_300MV = 0,     /* 300mV */
    BIA_TX_RANGE_400MV,         /* 400mV */
    BIA_TX_RANGE_500MV,         /* 500mV */
    BIA_TX_RANGE_600MV,         /* 600mV */

    BIA_TX_RANGE_MAX
} bia_tx_range_t;

typedef enum _bia_imp_path_t {
    BIA_CALIBRATION_PATH0 = 0,
    BIA_CALIBRATION_PATH1,
    BIA_BODY_PATH,

    BIA_PATH_MAX
} bia_imp_path_t;

typedef enum _bia_tx_rn_path_t {
    BIA_TX_RN_UNUSED = 0,
    BIA_TX_RN0,
    BIA_TX_RN1,

    BIA_TX_RN_MAX
} bia_tx_rn_path_t;


typedef enum _bia_tx_rp_path_t {
    BIA_TX_RP_UNUSED = 0,
    BIA_TX_RP0,
    BIA_TX_RP1,

    BIA_TX_RP_MAX
} bia_tx_rp_path_t;


typedef enum _bia_tx_i_path_t {
    BIA_TX_BODY_UNUSED = 0,
    BIA_TX_BODY,
    BIA_TX_BODY_MAX
} bia_tx_i_path_t;


typedef enum _bia_rx_path_t {
    BIA_RX_BODY = 0,
    BIA_RX_BODY_REVERSE_DIR,
    BIA_RX_OFFSET_OUTER_REG0,
    BIA_RX_OFFSET_OUTER_REG1,

    BIA_RX_MAX
} bia_rx_path_t;

typedef enum _bia_amp_t {
    BIA_AMP_0_5X = 0,
    BIA_AMP_1X,
    BIA_AMP_RESERVED,
    BIA_AMP_2X,

    BIA_AMP_MAX
} bia_amp_t;


typedef enum _bia_dc_amp_t {
    BIA_DC_AMP_1X = 0,
    BIA_DC_AMP_1_5X,
    BIA_DC_AMP_2X,

    BIA_DC_AMP_MAX
} bia_dc_amp_t;


typedef enum _bia_comp_amp_t {
    BIA_COMP_AMP_1X = 0,
    BIA_COMP_AMP_2X,
    BIA_COMP_AMP_3X,

    BIA_COMP_AMP_MAX
} bia_comp_amp_t;


typedef enum _bia_current_t {
    BIA_CURRENT_150NA = 0,      /* 150nA */
    BIA_CURRENT_175NA,          /* 175nA */
    BIA_CURRENT_250NA,          /* 250nA */
    BIA_CURRENT_350NA,          /* 350nA */

    BIA_CURRENT_MAX
} bia_current_t;

typedef enum _bia_mode_t {
    BIA_I_MODE = 0x0,
    BIA_IQ_MODE,

    BIA_MODE_MAX
} bia_mode_t;



void bp6a_bia_init(void);
void bp6a_bia_deinit(void);
void bp6a_bia_set_mode(bia_mode_t val);
void bp6a_bia_enable_tx(bool enable);
void bp6a_bia_enable_rx(bool enable);
void bp6a_bia_set_tx_freq(uint32_t val);
void bp6a_bia_set_tx_amp(uint32_t val);
void bp6a_bia_set_tx_volt(uint8_t val);
void bp6a_bia_set_path(bia_imp_path_t sel);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _S1SBP6A_BIA_H_ */
