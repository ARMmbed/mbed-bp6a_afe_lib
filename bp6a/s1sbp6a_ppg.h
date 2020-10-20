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

#ifndef _S1SBP6A_PPG_H_
#define _S1SBP6A_PPG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PPG_GEN_SHIELD_BUF_BYPASS_SHIFT                  (0)
#define PPG_GEN_SHIELD_DRV_EN_SHIFT                      (1)
#define PPG_GEN_IDC_EN_LDO_SHIFT                         (2)
#define PPG_GEN_AGCTS0EN_SHIFT                           (3)
#define PPG_GEN_AGCTS1EN_SHIFT                           (4)
#define PPG_GEN_AGCTS2EN_SHIFT                           (5)
#define PPG_GEN_AGCTS3EN_SHIFT                           (6)
#define PPG_GEN_AGCTS0SYNC_SHIFT                         (7)
#define PPG_GEN_AGCTS1SYNC_SHIFT                         (8)
#define PPG_GEN_AGCTS2SYNC_SHIFT                         (9)
#define PPG_GEN_AGCTS3SYNC_SHIFT                         (10)
#define PPG_GEN_TMUXSEL_SHIFT                            (11)
#define PPG_GEN_AFE_BYPASS_SHIFT                         (14)
#define PPG_GEN_IDC_VREF_EX_MODE_SHIFT                   (15)
#define PPG_GEN_IDC_EXT_REG_MODE_SHIFT                   (16)
#define PPG_GEN_IDC_BIASx2_SHIFT                         (17)
#define PPG_GEN_IDC_CLK_DLY_SHIFT                        (18)
#define PPG_GEN_LED_DCC_SYNC_SHIFT                       (19)
#define PPG_GEN_IDC_BUF_TEST_SHIFT                       (20)

#define PPG_GEN_ALL_MASK                                 (0x1FFFFF)
#define PPG_GEN_SHIELD_BUF_BYPASS_MASK                   (0x01 << PPG_GEN_SHIELD_BUF_BYPASS_SHIFT)
#define PPG_GEN_SHIELD_DRV_EN_MASK                       (0x01 << PPG_GEN_SHIELD_DRV_EN_SHIFT)
#define PPG_GEN_IDC_EN_LDO_MASK                          (0x01 << PPG_GEN_IDC_EN_LDO_SHIFT)
#define PPG_GEN_AGCTS0EN_MASK                            (0x01 << PPG_GEN_AGCTS0EN_SHIFT)
#define PPG_GEN_AGCTS1EN_MASK                            (0x01 << PPG_GEN_AGCTS1EN_SHIFT)
#define PPG_GEN_AGCTS2EN_MASK                            (0x01 << PPG_GEN_AGCTS2EN_SHIFT)
#define PPG_GEN_AGCTS3EN_MASK                            (0x01 << PPG_GEN_AGCTS3EN_SHIFT)
#define PPG_GEN_AGCTS0SYNC_MASK                          (0x01 << PPG_GEN_AGCTS0SYNC_SHIFT)
#define PPG_GEN_AGCTS1SYNC_MASK                          (0x01 << PPG_GEN_AGCTS1SYNC_SHIFT)
#define PPG_GEN_AGCTS2SYNC_MASK                          (0x01 << PPG_GEN_AGCTS2SYNC_SHIFT)
#define PPG_GEN_AGCTS3SYNC_MASK                          (0x01 << PPG_GEN_AGCTS3SYNC_SHIFT)
#define PPG_GEN_TMUXSEL_MASK                             (0x07 << PPG_GEN_TMUXSEL_SHIFT)
#define PPG_GEN_AFE_BYPASS_MASK                          (0x01 << PPG_GEN_AFE_BYPASS_SHIFT)
#define PPG_GEN_IDC_VREF_EX_MODE_MASK                    (0x01 << PPG_GEN_IDC_VREF_EX_MODE_SHIFT)
#define PPG_GEN_IDC_EXT_REG_MODE_MASK                    (0x01 << PPG_GEN_IDC_EXT_REG_MODE_SHIFT)
#define PPG_GEN_IDC_BIASx2_MASK                          (0x01 << PPG_GEN_IDC_BIASx2_SHIFT)
#define PPG_GEN_IDC_CLK_DLY_MASK                         (0x01 << PPG_GEN_IDC_CLK_DLY_SHIFT)
#define PPG_GEN_LED_DCC_SYNC_MASK                        (0x01 << PPG_GEN_LED_DCC_SYNC_SHIFT)
#define PPG_GEN_IDC_BUF_TEST_MASK                        (0x01 << PPG_GEN_IDC_BUF_TEST_SHIFT)

#define PPG_GEN_SHIELD_BUF_BYPASS(c)                     ((c) << PPG_GEN_SHIELD_BUF_BYPASS_SHIFT)
#define PPG_GEN_SHIELD_DRV_EN(c)                         ((c) << PPG_GEN_SHIELD_DRV_EN_SHIFT)
#define PPG_GEN_IDC_EN_LDO(c)                            ((c) << PPG_GEN_IDC_EN_LDO_SHIFT)
#define PPG_GEN_AGCTS0EN(c)                              ((c) << PPG_GEN_AGCTS0EN_SHIFT)
#define PPG_GEN_AGCTS1EN(c)                              ((c) << PPG_GEN_AGCTS1EN_SHIFT)
#define PPG_GEN_AGCTS2EN(c)                              ((c) << PPG_GEN_AGCTS2EN_SHIFT)
#define PPG_GEN_AGCTS3EN(c)                              ((c) << PPG_GEN_AGCTS3EN_SHIFT)
#define PPG_GEN_AGCTS0SYNC(c)                            ((c) << PPG_GEN_AGCTS0SYNC_SHIFT)
#define PPG_GEN_AGCTS1SYNC(c)                            ((c) << PPG_GEN_AGCTS1SYNC_SHIFT)
#define PPG_GEN_AGCTS2SYNC(c)                            ((c) << PPG_GEN_AGCTS2SYNC_SHIFT)
#define PPG_GEN_AGCTS3SYNC(c)                            ((c) << PPG_GEN_AGCTS3SYNC_SHIFT)
#define PPG_GEN_TMUXSEL(c)                               ((c) << PPG_GEN_TMUXSEL_SHIFT)
#define PPG_GEN_AFE_BYPASS(c)                            ((c) << PPG_GEN_AFE_BYPASS_SHIFT)
#define PPG_GEN_IDC_VREF_EX_MODE(c)                      ((c) << PPG_GEN_IDC_VREF_EX_MODE_SHIFT)
#define PPG_GEN_IDC_EXT_REG_MODE(c)                      ((c) << PPG_GEN_IDC_EXT_REG_MODE_SHIFT)
#define PPG_GEN_IDC_BIASx2(c)                            ((c) << PPG_GEN_IDC_BIASx2_SHIFT)
#define PPG_GEN_IDC_CLK_DLY(c)                           ((c) << PPG_GEN_IDC_CLK_DLY_SHIFT)
#define PPG_GEN_LED_DCC_SYNC(c)                          ((c) << PPG_GEN_LED_DCC_SYNC_SHIFT)
#define PPG_GEN_IDC_BUF_TEST(c)                          ((c) << PPG_GEN_IDC_BUF_TEST_SHIFT)


#define PPG_FUNC_AFE_PDN_EN_SHIFT                        (0)
#define PPG_FUNC_SNH_BYPASS_EN_SHIFT                     (1)
#define PPG_FUNC_DCC_EN_SHIFT                            (2)
#define PPG_FUNC_DCC_TEST_EN_SHIFT                       (3)
#define PPG_FUNC_IDC_EN_BUF_SHIFT                        (4)
#define PPG_FUNC_IDC_EN_CHOP_SHIFT                       (5)
#define PPG_FUNC_IDC_EN_DWA_SHIFT                        (6)
#define PPG_FUNC_IDC_EN_SHIFT                            (7)
#define PPG_FUNC_IDC_PDB_EN_SHIFT                        (8)
#define PPG_FUNC_IDC_BUF_BYPASS_SHIFT                    (9)
#define PPG_FUNC_INPUT_SHORT_SHIFT                       (10)
#define PPG_FUNC_TIA_EN_SHIFT                            (11)

#define PPG_FUNC_ALL_MASK                                (0xFFF)
#define PPG_FUNC_AFE_PDN_EN_MASK                         (1 << PPG_FUNC_AFE_PDN_EN_SHIFT)
#define PPG_FUNC_SNH_BYPASS_EN_MASK                      (1 << PPG_FUNC_SNH_BYPASS_EN_SHIFT)
#define PPG_FUNC_DCC_EN_MASK                             (1 << PPG_FUNC_DCC_EN_SHIFT)
#define PPG_FUNC_DCC_TEST_EN_MASK                        (1 << PPG_FUNC_DCC_TEST_EN_SHIFT)
#define PPG_FUNC_IDC_EN_BUF_MASK                         (1 << PPG_FUNC_IDC_EN_BUF_SHIFT)
#define PPG_FUNC_IDC_EN_CHOP_MASK                        (1 << PPG_FUNC_IDC_EN_CHOP_SHIFT)
#define PPG_FUNC_IDC_EN_DWA_MASK                         (1 << PPG_FUNC_IDC_EN_DWA_SHIFT)
#define PPG_FUNC_IDC_EN_MASK                             (1 << PPG_FUNC_IDC_EN_SHIFT)
#define PPG_FUNC_IDC_PDB_EN_MASK                         (1 << PPG_FUNC_IDC_PDB_EN_SHIFT)
#define PPG_FUNC_IDC_BUF_BYPASS_MASK                     (1 << PPG_FUNC_IDC_BUF_BYPASS_SHIFT)
#define PPG_FUNC_INPUT_SHORT_MASK                        (1 << PPG_FUNC_INPUT_SHORT_SHIFT)
#define PPG_FUNC_TIA_EN_MASK                             (1 << PPG_FUNC_TIA_EN_SHIFT)

#define PPG_FUNC_AFE_PDN_EN(c)                           ((c) << PPG_FUNC_AFE_PDN_EN_SHIFT)
#define PPG_FUNC_SNH_BYPASS_EN(c)                        ((c) << PPG_FUNC_SNH_BYPASS_EN_SHIFT)
#define PPG_FUNC_DCC_EN(c)                               ((c) << PPG_FUNC_DCC_EN_SHIFT)
#define PPG_FUNC_DCC_TEST_EN(c)                          ((c) << PPG_FUNC_DCC_TEST_EN_SHIFT)
#define PPG_FUNC_IDC_EN_BUF(c)                           ((c) << PPG_FUNC_IDC_EN_BUF_SHIFT)
#define PPG_FUNC_IDC_EN_CHOP(c)                          ((c) << PPG_FUNC_IDC_EN_CHOP_SHIFT)
#define PPG_FUNC_IDC_EN_DWA(c)                           ((c) << PPG_FUNC_IDC_EN_DWA_SHIFT)
#define PPG_FUNC_IDC_EN(c)                               ((c) << PPG_FUNC_IDC_EN_SHIFT)
#define PPG_FUNC_IDC_PDB_EN(c)                           ((c) << PPG_FUNC_IDC_PDB_EN_SHIFT)
#define PPG_FUNC_IDC_BUF_BYPASS(c)                       ((c) << PPG_FUNC_IDC_BUF_BYPASS_SHIFT)
#define PPG_FUNC_INPUT_SHORT(c)                          ((c) << PPG_FUNC_INPUT_SHORT_SHIFT)
#define PPG_FUNC_TIA_EN(c)                               ((c) << PPG_FUNC_TIA_EN_SHIFT)

#define PPG_CONVT_SHIFT                                  (0)
#define PPG_DECISCALE_SHIFT                              (13)
#define PPG_DECIRSTDLY_SHIFT                             (18)

#define PPG_CONVT_MASK                                   (0x1FFF  << PPG_CONVT_SHIFT)
#define PPG_DECISCALE_MASK                               (0x1F << PPG_DECISCALE_SHIFT)
#define PPG_DECIRSTDLY_MASK                              (0x02 << PPG_DECIRSTDLY_SHIFT)

#define PPG_CONVT(c)                                     ((c)<< PPG_CONVT_SHIFT)
#define PPG_DECISCALE(c)                                 ((c)<< PPG_DECISCALE_SHIFT)
#define PPG_DECIRSTDLY(c)                                ((c)<< PPG_DECIRSTDLY_SHIFT)

#define PPG_PDNWAIT_SHIFT                                (0)
#define PPG_AFEAGE_SHIFT                                 (9)

#define PPG_PDNWAIT_MASK                                 (0x1FF << PPG_PDNWAIT_SHIFT)
#define PPG_AFEAGE_MASK                                  (0x1FF << PPG_AFEAGE_SHIFT)

#define PPG_PDNWAIT(c)                                   ((c) << PPG_PDNWAIT_SHIFT)
#define PPG_AFEAGE(c)                                    ((c) << PPG_AFEAGE_SHIFT)

#define PPG_LED_EN_SHIFT                                 (0)
#define LED_SEL_IBIAS_SHIFT                              (1)

#define PPG_LED_EN_MASK                                  (1 << PPG_LED_EN_SHIFT)
#define LED_SEL_IBIAS_MASK                               (1 << LED_SEL_IBIAS_SHIFT)

#define PPG_LED_EN(c)                                    ((c) << PPG_LED_EN_SHIFT)
#define LED_SEL_IBIAS(c)                                 ((c) << LED_SEL_IBIAS_SHIFT)


#define PPG_RFP_SHIFT                                    (0)
#define PPG_RFN_SHIFT                                    (3)
#define PPG_CFP_SHIFT                                    (6)
#define PPG_CFN_SHIFT                                    (9)
#define PPG_VCM_SHIFT                                    (12)
#define PPG_TIARST_SHIFT                                 (15)

#define PPG_RFP_MASK                                     ((0x07) << PPG_RFP_SHIFT)
#define PPG_RFN_MASK                                     ((0x07) << PPG_RFN_SHIFT)
#define PPG_CFP_MASK                                     ((0x07) << PPG_CFP_SHIFT)
#define PPG_CFN_MASK                                     ((0x07) << PPG_CFN_SHIFT)
#define PPG_VCM_MASK                                     ((0x07) << PPG_VCM_SHIFT)
#define PPG_TIARST_MASK                                  ((0x01) << PPG_TIARST_SHIFT)

#define PPG_RFP(c)                                       ((c) << PPG_RFP_SHIFT)
#define PPG_RFN(c)                                       ((c) << PPG_RFN_SHIFT)
#define PPG_CFP(c)                                       ((c) << PPG_CFP_SHIFT)
#define PPG_CFN(c)                                       ((c) << PPG_CFN_SHIFT)
#define PPG_VCM(c)                                       ((c) << PPG_VCM_SHIFT)
#define PPG_TIARST(c)                                    ((c) << PPG_TIARST_SHIFT)

#define PPG_IDC_ICTRL_INT1_SHIFT                         (0)
#define PPG_IDC_ICTRL_INT2_SHIFT                         (4)
#define PPG_IDC_ICTRL_INT3_SHIFT                         (8)
#define PPG_IDC_ICTRL_QUANT_SHIFT                        (12)
#define PPG_IDC_BUF_PWR_SEL_SHIFT                        (14)
#define PPG_IDC_BUF_EN_CHOP_SHIFT                        (15)
#define PPG_IDC_BUF_I_CTRL_SHIFT                         (16)
#define PPG_IDC_BUF_CMO_CTRL_SHIFT                       (18)
#define PPG_IDC_DATA_LAT_POL_SHIFT                       (19)
#define PPG_IDC_MCLK_POL_SHIFT                           (20)
#define PPG_IDC_CHOPCLK_POL_SHIFT                        (21)
#define PPG_IDC_CHOPCLK_SEL_SHIFT                        (22)

#define PPG_IDC_ICTRL_INT1_MASK                          ((0x0F) << PPG_IDC_ICTRL_INT1_SHIFT)
#define PPG_IDC_ICTRL_INT2_MASK                          ((0x0F) << PPG_IDC_ICTRL_INT2_SHIFT)
#define PPG_IDC_ICTRL_INT3_MASK                          ((0x0F) << PPG_IDC_ICTRL_INT3_SHIFT)
#define PPG_IDC_ICTRL_QUANT_MASK                         ((3) << PPG_IDC_ICTRL_QUANT_SHIFT)
#define PPG_IDC_BUF_PWR_SEL_MASK                         ((1) << PPG_IDC_BUF_PWR_SEL_SHIFT)
#define PPG_IDC_BUF_EN_CHOP_MASK                         ((1) << PPG_IDC_BUF_EN_CHOP_SHIFT)
#define PPG_IDC_BUF_I_CTRL_MASK                          ((3) << PPG_IDC_BUF_I_CTRL_SHIFT)
#define PPG_IDC_BUF_CMO_CTRL_MASK                        ((1) << PPG_IDC_BUF_CMO_CTRL_SHIFT)
#define PPG_IDC_DATA_LAT_POL_MASK                        ((1) << PPG_IDC_DATA_LAT_POL_SHIFT)
#define PPG_IDC_MCLK_POL_MASK                            ((1) << PPG_IDC_MCLK_POL_SHIFT)
#define PPG_IDC_CHOPCLK_POL_MASK                         ((1) << PPG_IDC_CHOPCLK_POL_SHIFT)
#define PPG_IDC_CHOPCLK_SEL_MASK                         ((7) << PPG_IDC_CHOPCLK_SEL_SHIFT)

#define PPG_IDC_ICTRL_INT1(c)                            ((c) << PPG_IDC_ICTRL_INT1_SHIFT)
#define PPG_IDC_ICTRL_INT2(c)                            ((c) << PPG_IDC_ICTRL_INT2_SHIFT)
#define PPG_IDC_ICTRL_INT3(c)                            ((c) << PPG_IDC_ICTRL_INT3_SHIFT)
#define PPG_IDC_ICTRL_QUANT(c)                           ((c) << PPG_IDC_ICTRL_QUANT_SHIFT)
#define PPG_IDC_BUF_PWR_SEL(c)                           ((c) << PPG_IDC_BUF_PWR_SEL_SHIFT)
#define PPG_IDC_BUF_EN_CHOP(c)                           ((c) << PPG_IDC_BUF_EN_CHOP_SHIFT)
#define PPG_IDC_BUF_I_CTRL(c)                            ((c) << PPG_IDC_BUF_I_CTRL_SHIFT)
#define PPG_IDC_BUF_CMO_CTRL(c)                          ((c) << PPG_IDC_BUF_CMO_CTRL_SHIFT)
#define PPG_IDC_DATA_LAT_POL(c)                          ((c) << PPG_IDC_DATA_LAT_POL_SHIFT)
#define PPG_IDC_MCLK_POL(c)                              ((c) << PPG_IDC_MCLK_POL_SHIFT)
#define PPG_IDC_CHOPCLK_POL(c)                           ((c) << PPG_IDC_CHOPCLK_POL_SHIFT)
#define PPG_IDC_CHOPCLK_SEL(c)                           ((c) << PPG_IDC_CHOPCLK_SEL_SHIFT)

#define PPG_DCCP_SHIFT                                   (0)
#define PPG_DCCN_SHIFT                                   (6)

#define PPG_DCCP_MASK                                    (0x3F << PPG_DCCP_SHIFT)
#define PPG_DCCN_MASK                                    (0x3F << PPG_DCCN_SHIFT)

#define PPG_DCCP(c)                                      ((c) << PPG_DCCP_SHIFT)
#define PPG_DCCN(c)                                      ((c) << PPG_DCCN_SHIFT)


#define PPG_MAX_TIME_SLOT                                 4
#define PPG_MAX_PD                                        2

typedef enum _ppg_tia_reg_t {
    PPG_TIA_REGISTER_10K,
    PPG_TIA_REGISTER_25K,
    PPG_TIA_REGISTER_50K,
    PPG_TIA_REGISTER_100K,
    PPG_TIA_REGISTER_250K,
    PPG_TIA_REGISTER_500K,
    PPG_TIA_REGISTER_1M,
    PPG_TIA_REGISTER_2M,
} ppg_tia_reg_t;

typedef enum _ppg_tia_cap_t {
    PPG_TIA_CAPACITOR_2P,
    PPG_TIA_CAPACITOR_4P,
    PPG_TIA_CAPACITOR_6P,
    PPG_TIA_CAPACITOR_8P,
    PPG_TIA_CAPACITOR_10P,
    PPG_TIA_CAPACITOR_14P,
    PPG_TIA_CAPACITOR_18P,
    PPG_TIA_CAPACITOR_22P,
} ppg_tia_cap_t;

typedef enum _ppg_ch_t {
    PPG_CH_0 = 0x0,
    PPG_CH_1,
} ppg_ch_t;


int bp6a_ppg_init(void);
void bp6a_ppg_deinit(void);

void bp6a_ppg_conf_leddrv(uint32_t led_ontime, uint8_t *drv_cur);
void bp6a_ppg_led_enable(bool enable);

void bp6a_ppg_conf_ch(ppg_ch_t ch, uint32_t prt);
void bp6a_ppg_dcc_ctrl(ppg_ch_t ch, uint8_t dccp, uint8_t dccn);
void bp6a_ppg_led_time_slot_enable(uint32_t val);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _S1SBP6A_PPG_H_ */
