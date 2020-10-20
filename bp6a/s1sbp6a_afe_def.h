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
#ifndef _S1SBP6A_AFE_DEF_H_
#define _S1SBP6A_AFE_DEF_H_

#define AFE_CLK_CTRL_ECG_CLK_EN_SHIFT            0
#define AFE_CLK_CTRL_BIA_CLK_EN_SHIFT            1
#define AFE_CLK_CTRL_PPG_CLK_EN_SHIFT            2
#define AFE_CLK_CTRL_AFE_CLK_SRC_SHIFT           3
#define AFE_CLK_CTRL_GSR_CLK_EN_SHIFT            4
#define AFE_CLK_CTRL_SAR_ADC0_CLK_EN_SHIFT       5
#define AFE_CLK_CTRL_SAR_ADC1_CLK_EN_SHIFT       6
#define AFE_CLK_CTRL_SAR_ADC2_CLK_EN_SHIFT       7
#define AFE_CLK_CTRL_SEL_SAMPLE_CLK_SHIFT        8

#define AFE_CLK_CTRL_ECG_CLK_EN_MASK            (0x01 << AFE_CLK_CTRL_ECG_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_BIA_CLK_EN_MASK            (0x01 << AFE_CLK_CTRL_BIA_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_PPG_CLK_EN_MASK            (0x01 << AFE_CLK_CTRL_PPG_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_AFE_CLK_SRC_MASK           (0x01 << AFE_CLK_CTRL_AFE_CLK_SRC_SHIFT)
#define AFE_CLK_CTRL_GSR_CLK_EN_MASK            (0x01 << AFE_CLK_CTRL_GSR_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SAR_ADC0_CLK_EN_MASK       (0x01 << AFE_CLK_CTRL_SAR_ADC0_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SAR_ADC1_CLK_EN_MASK       (0x01 << AFE_CLK_CTRL_SAR_ADC1_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SAR_ADC2_CLK_EN_MASK       (0x01 << AFE_CLK_CTRL_SAR_ADC2_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SEL_SAMPLE_CLK_MASK        (0x01 << AFE_CLK_CTRL_SEL_SAMPLE_CLK_SHIFT)

#define AFE_CLK_CTRL_ECG_CLK_EN(c)              ((c) << AFE_CLK_CTRL_ECG_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_BIA_CLK_EN(c)              ((c) << AFE_CLK_CTRL_BIA_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_PPG_CLK_EN(c)              ((c) << AFE_CLK_CTRL_PPG_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_AFE_CLK_SRC(c)             ((c) << AFE_CLK_CTRL_AFE_CLK_SRC_SHIFT)
#define AFE_CLK_CTRL_GSR_CLK_EN(c)              ((c) << AFE_CLK_CTRL_GSR_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SAR_ADC0_CLK_EN(c)         ((c) << AFE_CLK_CTRL_SAR_ADC0_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SAR_ADC1_CLK_EN(c)         ((c) << AFE_CLK_CTRL_SAR_ADC1_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SAR_ADC2_CLK_EN(c)         ((c) << AFE_CLK_CTRL_SAR_ADC2_CLK_EN_SHIFT)
#define AFE_CLK_CTRL_SEL_SAMPLE_CLK(c)          ((c) << AFE_CLK_CTRL_SEL_SAMPLE_CLK_SHIFT)

#define AFE_CLK_CTRL_SAMPLE_CLK_16K             (0x01)
#define AFE_CLK_CTRL_SAMPLE_CLK_2K              (0x00)


#define AFE_RESET_CTRL_PPG_RESET_SHIFT           1
#define AFE_RESET_CTRL_BIA_RESET_SHIFT           2
#define AFE_RESET_CTRL_GSR_RESET_SHIFT           3

#define AFE_RESET_CTRL_PPG_RESET_MASK            (0x01 << AFE_RESET_CTRL_PPG_RESET_SHIFT)
#define AFE_RESET_CTRL_BIA_RESET_MASK            (0x01 << AFE_RESET_CTRL_BIA_RESET_SHIFT)
#define AFE_RESET_CTRL_GSR_RESET_MASK            (0x01 << AFE_RESET_CTRL_GSR_RESET_SHIFT)

#define GPIO_TMUX_SEL_SHIFT                      0
#define GPIO_TMUX_SEL_MASK                       (0x7UL << GPIO_TMUX_SEL_SHIFT)

#define GP_DAC0_ENABLE_SHIFT                     0
#define GP_DAC0_ITOPUP_SHIFT                     1
#define GP_DAC0_INPUT_CODE_SHIFT                 4

#define GP_DAC0_ENABLE_MASK                      (0x01 << GP_DAC0_ENABLE_SHIFT)
#define GP_DAC0_ITOPUP_MASK                      (0x01 << GP_DAC0_ITOPUP_SHIFT)
#define GP_DAC0_INPUT_CODE_MASK                  (0x3FF << GP_DAC0_INPUT_CODE_SHIFT)

#define GP_DAC1_ENABLE_SHIFT                     0
#define GP_DAC1_ITOPUP_SHIFT                     1
#define GP_DAC1_INPUT_CODE_SHIFT                 4

#define GP_DAC1_ENABLE_MASK                      (0x01 << GP_DAC1_ENABLE_SHIFT)
#define GP_DAC1_ITOPUP_MASK                      (0x01 << GP_DAC1_ITOPUP_SHIFT)
#define GP_DAC1_INPUT_CODE_MASK                  (0x3FF << GP_DAC1_INPUT_CODE_SHIFT)

#define GP_ADC0_AMP0_EN_SHIFT                    0
#define GP_ADC0_AMP1_EN_SHIFT                    1
#define GP_ADC0_R1_CTRL_SHIFT                    4
#define GP_ADC0_R2_CTRL_SHIFT                    6
#define GP_ADC0_R2_300K_EN_SHIFT                 8
#define GP_ADC0_C1_CTRL_SHIFT                    12
#define GP_ADC0_SW_SEL_SHIFT                     16

#define GP_ADC0_AMP0_EN_MASK                    (0x01 << GP_ADC0_AMP0_EN_SHIFT)
#define GP_ADC0_AMP1_EN_MASK                    (0x01 << GP_ADC0_AMP1_EN_SHIFT)
#define GP_ADC0_R1_CTRL_MASK                    (0x03 << GP_ADC0_R1_CTRL_SHIFT)
#define GP_ADC0_R2_CTRL_MASK                    (0x03 << GP_ADC0_R2_CTRL_SHIFT)
#define GP_ADC0_R2_300K_EN_MASK                 (0x01 << GP_ADC0_R2_300K_EN_SHIFT)
#define GP_ADC0_C1_CTRL_MASK                    (0x03 << GP_ADC0_C1_CTRL_SHIFT)
#define GP_ADC0_SW_SEL_MASK                     (0xFFF << GP_ADC0_SW_SEL_SHIFT)

#define GP_ADC0_R1_0_35M                        0
#define GP_ADC0_R1_0_75M                        1
#define GP_ADC0_R1_1_75M                        2
#define GP_ADC0_R1_5_25M                        3
#define GP_ADC0_R2_0_63M                        0
#define GP_ADC0_R2_1_31M                        1
#define GP_ADC0_R2_2_63M                        2
#define GP_ADC0_R2_5_25M                        3
#define GP_ADC0_C1_15P                          0
#define GP_ADC0_C1_20P                          1
#define GP_ADC0_C1_25P                          2
#define GP_ADC0_C1_30P                          3

#define GP_ADC1_ENABLE_SHIFT                    0
#define GP_ADC1_TEST_EN_SHIFT                   1
#define GP_ADC1_CCOM_CTRL_SHIFT                 2
#define GP_ADC1_CDIFF_CTRL_SHIFT                3
#define GP_ADC1_SW_SEL_SHIFT                    4

#define GP_ADC1_ENABLE_MASK                     (0x01 << GP_ADC1_ENABLE_SHIFT)
#define GP_ADC1_TEST_EN_MASK                    (0x01 << GP_ADC1_TEST_EN_SHIFT)
#define GP_ADC1_CCOM_CTRL_MASK                  (0x01 << GP_ADC1_CCOM_CTRL_SHIFT)
#define GP_ADC1_CDIFF_CTRL_MASK                 (0x01 << GP_ADC1_CDIFF_CTRL_SHIFT)
#define GP_ADC1_SW_SEL_MASK                     (0x1FF << GP_ADC1_SW_SEL_SHIFT)

#define GP_ADC1_CCOM_2_5P                       0
#define GP_ADC1_CCOM_5P                         1
#define GP_ADC1_CDIFF_2_5P                      0
#define GP_ADC1_CDIFF_5P                        1

#define REF_CTRL_CH_RBTRIM_SHIFT                0
#define REF_CTRL_V1P25_RBTRIM_SHIFT             8
#define REF_CTRL_V0P7_RBTRIM_SHIFT              16
#define REF_CTRL_V1P25_LPFRTRIM_SHIFT           20
#define REF_CTRL_RB_SEL_SHIFT                   24
#define REF_CTRL_CH_EN_SHIFT                    25
#define REF_CTRL_TEST_EN_SHIFT                  26
#define REF_CTRL_LED_EN_SHIFT                   27
#define REF_CTRL_FLASH_EN_SHIFT                 28
#define REF_CTRL_FLASH_BUF_EN_SHIFT             29
#define REF_CTRL_V1P25_INTR_EN_SHIFT            30
#define REF_CTRL_V1P25_INTR_BYPASS_SHIFT        31

#define REF_CTRL_CH_RBTRIM_MASK                (0x3F << REF_CTRL_CH_RBTRIM_SHIFT)
#define REF_CTRL_V1P25_RBTRIM_MASK             (0x7F << REF_CTRL_V1P25_RBTRIM_SHIFT)
#define REF_CTRL_V0P7_RBTRIM_MASK              (0x0F << REF_CTRL_V0P7_RBTRIM_SHIFT)
#define REF_CTRL_V1P25_LPFRTRIM_MASK           (0x0F << REF_CTRL_V1P25_LPFRTRIM_SHIFT)
#define REF_CTRL_RB_SEL_MASK                   (0x01 << REF_CTRL_RB_SEL_SHIFT)
#define REF_CTRL_CH_EN_MASK                    (0x01 << REF_CTRL_CH_EN_SHIFT)
#define REF_CTRL_TEST_EN_MASK                  (0x01 << REF_CTRL_TEST_EN_SHIFT)
#define REF_CTRL_LED_EN_MASK                   (0x01 << REF_CTRL_LED_EN_SHIFT)
#define REF_CTRL_FLASH_EN_MASK                 (0x01 << REF_CTRL_FLASH_EN_SHIFT)
#define REF_CTRL_FLASH_BUF_EN_MASK             (0x01 << REF_CTRL_FLASH_BUF_EN_SHIFT)
#define REF_CTRL_V1P25_INTR_EN_MASK            (0x01 << REF_CTRL_V1P25_INTR_EN_SHIFT)
#define REF_CTRL_V1P25_INTR_BYPASS_MASK        (0x01 << REF_CTRL_V1P25_INTR_BYPASS_SHIFT)

#define REF_CTRL_RB_EXT_REG                    0
#define REF_CTRL_RB_INT_REG                    1

#define REGULATOR_CTRL0_ALDO_VCTRL_SHIFT        0
#define REGULATOR_CTRL0_PLDO_VCTRL_SHIFT        8
#define REGULATOR_CTRL0_CLDO_VCTRL_SHIFT        16

#define REGULATOR_CTRL0_ALDO_VCTRL_MASK        (0x1F << REGULATOR_CTRL0_ALDO_VCTRL_SHIFT)
#define REGULATOR_CTRL0_PLDO_VCTRL_MASK        (0x1F << REGULATOR_CTRL0_PLDO_VCTRL_SHIFT)
#define REGULATOR_CTRL0_CLDO_VCTRL_MASK        (0x1F << REGULATOR_CTRL0_CLDO_VCTRL_SHIFT)

#define REGULATOR_CTRL1_MLDO_VCTRL_SHIFT        0
#define REGULATOR_CTRL1_V0P8_RBTRIM_SHIFT       8
#define REGULATOR_CTRL1_PBOR_RBTRIM_SHIFT       12

#define REGULATOR_CTRL1_MLDO_VCTRL_MASK         (0x1F << REGULATOR_CTRL1_MLDO_VCTRL_SHIFT)
#define REGULATOR_CTRL1_V0P8_RBTRIM_MASK        (0x1F << REGULATOR_CTRL1_V0P8_RBTRIM_SHIFT)
#define REGULATOR_CTRL1_PBOR_RBTRIM_MASK        (0x0F << REGULATOR_CTRL1_PBOR_RBTRIM_SHIFT)

#define TMPX_ENP_SHIFT                           0
#define TMPX_ENN_SHIFT                           1
#define TMPX_BUFP_BYPASS_SHIFT                   2
#define TMPX_BUFN_BYPASS_SHIFT                   3
#define TMPX_SELP_SHIFT                          4
#define TMPX_SELN_SHIFT                          8


#define TMPX_ENP_MASK                            (0x01 << TMPX_ENP_SHIFT)
#define TMPX_ENN_MASK                            (0x01 << TMPX_ENN_SHIFT)
#define TMPX_BUFP_BYPASS_MASK                    (0x01 << TMPX_BUFP_BYPASS_SHIFT)
#define TMPX_BUFN_BYPASS_MASK                    (0x01 << TMPX_BUFN_BYPASS_SHIFT)
#define TMPX_SELP_MASK                           (0x0F << TMPX_SELP_SHIFT)
#define TMPX_SELN_MASK                           (0x0F << TMPX_SELN_SHIFT)

#define V11_RSV0_PPG_IDC_BUF_ENA_SHIFT            0
#define V11_RSV0_PPG0_IDC_BUF_VCM_CTRL_SHIFT      1
#define V11_RSV0_PPG1_IDC_BUF_VCM_CTRL_SHIFT      4

#define V11_RSV0_PPG_IDC_BUF_ENA_MASK            (0x01 << V11_RSV0_PPG_IDC_BUF_ENA_SHIFT)
#define V11_RSV0_PPG0_IDC_BUF_VCM_CTR_MASK       (0x07 << V11_RSV0_PPG0_IDC_BUF_VCM_CTRL_SHIFT)
#define V11_RSV0_PPG1_IDC_BUF_VCM_CTR_MASK       (0x07 << V11_RSV0_PPG1_IDC_BUF_VCM_CTRL_SHIFT)

#define V11_RSV0_PPG_IDC_BUF_ENA(c)              ((c) << V11_RSV0_PPG_IDC_BUF_ENA_SHIFT)
#define V11_RSV0_PPG0_IDC_BUF_VCM_CTR(c)         ((c) << V11_RSV0_PPG0_IDC_BUF_VCM_CTRL_SHIFT)
#define V11_RSV0_PPG1_IDC_BUF_VCM_CTR(c)         ((c) << V11_RSV0_PPG1_IDC_BUF_VCM_CTRL_SHIFT)


#define TRIM_SELB_SAR0_CDAC_SHIFT                0
#define TRIM_SELB_SAR1_CDAC_SHIFT                1
#define TRIM_SELB_SAR2_CDAC_SHIFT                2
#define TRIM_SELB_LED_COARSE_SHIFT               3
#define TRIM_SELB_ALDO_VOUT_SHIFT                4
#define TRIM_SELB_PLDO_VOUT_SHIFT                5
#define TRIM_SELB_CLDO_VOUT_SHIFT                6
#define TRIM_SELB_MLDO_VOUT_SHIFT                7
#define TRIM_SELB_POR_BOR_HYS_REF_SHIFT          8
#define TRIM_SELB_CH_REF_CURRENT_SHIFT           9
#define TRIM_SELB_REF_V1P25_SHIFT                10
#define TRIM_SELB_REF_V0P7_SHIFT                 11
#define TRIM_SELB_LSOSC_SHIFT                    12
#define TRIM_SELB_HSOSC_SHIFT                    13
#define TRIM_SELB_PBOR_RBTRIM_SHIFT              14

#define TRIM_SELB_SAR0_CDAC_MASK                (0x01 << TRIM_SELB_SAR0_CDAC_SHIFT)
#define TRIM_SELB_SAR1_CDAC_MASK                (0x01 << TRIM_SELB_SAR1_CDAC_SHIFT)
#define TRIM_SELB_SAR2_CDAC_MASK                (0x01 << TRIM_SELB_SAR2_CDAC_SHIFT)
#define TRIM_SELB_LED_COARSEC_MASK              (0x01 << TRIM_SELB_LED_COARSE_SHIFT)
#define TRIM_SELB_ALDO_VOUT_MASK                (0x01 << TRIM_SELB_ALDO_VOUT_SHIFT)
#define TRIM_SELB_PLDO_VOUT_MASK                (0x01 << TRIM_SELB_PLDO_VOUT_SHIFT)
#define TRIM_SELB_CLDO_VOUT_MASK                (0x01 << TRIM_SELB_CLDO_VOUT_SHIFT)
#define TRIM_SELB_MLDO_VOUT_MASK                (0x01 << TRIM_SELB_MLDO_VOUT_SHIFT)
#define TRIM_SELB_POR_BOR_HYS_REF_MASK          (0x01 << TRIM_SELB_POR_BOR_HYS_REF_SHIFT)
#define TRIM_SELB_CH_REF_CURRENT_MASK           (0x01 << TRIM_SELB_CH_REF_CURRENT_SHIFT)
#define TRIM_SELB_REF_V1P25_MASK                (0x01 << TRIM_SELB_REF_V1P25_SHIFT)
#define TRIM_SELB_REF_V0P7_MASK                 (0x01 << TRIM_SELB_REF_V0P7_SHIFT)
#define TRIM_SELB_LSOSC_MASK                    (0x01 << TRIM_SELB_LSOSC_SHIFT)
#define TRIM_SELB_HSOSC_MASK                    (0x01 << TRIM_SELB_HSOSC_SHIFT)
#define TRIM_SELB_PBOR_RBTRIM_MASK              (0x01 << TRIM_SELB_PBOR_RBTRIM_SHIFT)

#define FM_SEL_SHIFT                            0
#define FM_SEL_MASK                             (0x7 << FM_SEL_SHIFT)

#define FM_SEL_ALL_DISCONNECT                   0
#define FM_SEL_V1P25                            1
#define FM_SEL_V0P7V                            2
#define FM_SEL_CLDO_OUT                         3
#define FM_SEL_MLDO_OUT                         4
#define FM_SEL_PLDO_OUT                         5
#define FM_SEL_ALDO_OUT                         6

#endif /* _S1SBP6A_AFE_DEF_H_ */
