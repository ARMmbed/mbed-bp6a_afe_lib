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

#ifndef _S1SBP6A_ECG_H_
#define _S1SBP6A_ECG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


//ECG_EN
#define ECG_EN_SHIFT                      (0)
#define ECG_EN_MASK                       (0x01 << ECG_EN_SHIFT)
#define ECG_EN(c)                         ((c) << ECG_EN_SHIFT)

#define ECG_GAIN_SHIFT                    (0)
#define ECG_GAIN_MASK                     (0x07 << ECG_GAIN_SHIFT)
#define ECG_GAIN(c)                       ((c) << ECG_GAIN_SHIFT)

#define ECG_BW_SHIFT                      (0)
#define ECG_BW_MASK                       (0x07 << ECG_BW_SHIFT)
#define ECG_BW(c)                         ((c) << ECG_BW_SHIFT)


//ECG_SET
#define ECG_LPF_BP_ON_SHIFT               (0)
#define ECG_PHASE_CTRL_SHIFT              (1)
#define ECG_EN_READ_TEST_BUF_SHIFT        (2)
#define ECG_EN_OVRSMP_SHIFT               (3)

#define ECG_LPF_BP_ON_MASK                (0x01 << ECG_LPF_BP_ON_SHIFT)
#define ECG_PHASE_CTRL_MASK               (0x01 << ECG_PHASE_CTRL_SHIFT)
#define ECG_EN_READ_TEST_BUF_MASK         (0x01 << ECG_EN_READ_TEST_BUF_SHIFT)
#define ECG_EN_OVRSMP_MASK                (0x01 << ECG_EN_OVRSMP_SHIFT)

#define ECG_LPF_BP_ON(c)                  ((c) << ECG_LPF_BP_ON_SHIFT)
#define ECG_PHASE_CTRL(c)                 ((c) << ECG_PHASE_CTRL_SHIFT)
#define ECG_EN_READ_TEST_BUF(c)           ((c) << ECG_EN_READ_TEST_BUF_SHIFT)
#define ECG_EN_OVRSMP(c)                  ((c) << ECG_EN_OVRSMP_SHIFT)


//ECG_INIT
#define ECG_INIT_SC_HPF_SHIFT             (0)
#define ECG_INIT_SC_HPF_MASK              (0x01 << ECG_INIT_SC_HPF_SHIFT)
#define ECG_INIT_SC_HPF(c)                ((c) << ECG_INIT_SC_HPF_SHIFT)

//ECG_HPF
#define ECG_HPF_BYPASS_EN_SHIFT           (0)
#define ECG_EXT_HPF_EN_SHIFT              (1)
#define ECG_HPF2_EN_SHIFT                 (2)

#define ECG_HPF_BYPASS_EN_MASK            (0x01 << ECG_HPF_BYPASS_EN_SHIFT)
#define ECG_EXT_HPF_EN_MASK               (0x01 << ECG_EXT_HPF_EN_SHIFT)
#define ECG_HPF2_EN_MASK                  (0x01 << ECG_HPF2_EN_SHIFT)


#define ECG_HPF_BYPASS_EN(c)              ((c) << ECG_HPF_BYPASS_EN_SHIFT)
#define ECG_EXT_HPF_EN(c)                 ((c) << ECG_EXT_HPF_EN_SHIFT)
#define ECG_HPF2_EN(c)                    ((c) << ECG_HPF2_EN_SHIFT)

//ECG_CONT
#define ECG_VB_IA_CONT1_SHIFT             (0)
#define ECG_IA_TEST_EN_SHIFT              (3)
#define ECG_IN_SHORTT_CTRL_SHIFT          (4)
#define ECG_RLD_EN_SHIFT                  (5)
#define ECG_TEST_PATT_GEN_EN_SHIFT        (6)
#define ECG_CHOP_CLK_EN_SHIFT             (7)

#define ECG_VB_IA_CONT1_MASK              (0x07 << ECG_VB_IA_CONT1_SHIFT)
#define ECG_IA_TEST_EN_MASK               (0x01 << ECG_IA_TEST_EN_SHIFT)
#define ECG_IN_SHORTT_CTRL_MASK           (0x01 << ECG_IN_SHORTT_CTRL_SHIFT)
#define ECG_RLD_EN_MASK                   (0x01 << ECG_RLD_EN_SHIFT)
#define ECG_TEST_PATT_GEN_EN_MASK         (0x01 << ECG_TEST_PATT_GEN_EN_SHIFT)
#define ECG_CHOP_CLK_EN_MASK              (0x01 << ECG_CHOP_CLK_EN_SHIFT)

#define ECG_VB_IA_CONT1(c)                ((c) << ECG_VB_IA_CONT1_SHIFT)
#define ECG_IA_TEST_EN(c)                 ((c) << ECG_IA_TEST_EN_SHIFT)
#define ECG_IN_SHORTT_CTRL(c)             ((c) << ECG_IN_SHORTT_CTRL_SHIFT)
#define ECG_RLD_EN(c)                     ((c) << ECG_RLD_EN_SHIFT)
#define ECG_TEST_PATT_GEN_EN(c)           ((c) << ECG_TEST_PATT_GEN_EN_SHIFT)
#define ECG_CHOP_CLK_EN(c)                ((c) << ECG_CHOP_CLK_EN_SHIFT)
/* ========================================================================== */
/*          T Y P E S                                                         */
/* ========================================================================== */
typedef enum _ecg_pga_gain_t {
    ECG_PGA_GAIN_X1_0 = 0,
    ECG_PGA_GAIN_X1_2 = 1,
    ECG_PGA_GAIN_X1_6 = 2,
    ECG_PGA_GAIN_X2 = 3,
    ECG_PGA_GAIN_X3 = 4,
    ECG_PGA_GAIN_X4 = 5,
    ECG_PGA_GAIN_X5 = 6,
    ECG_PGA_GAIN_X6 = 7,
    ECG_PGA_GAIN_INVALID = 8,
} ecg_pga_gain_t;

typedef enum _ecg_lpf_bw_t {
    ECG_LPF_BW_250Hz = 0,
    ECG_LPF_BW_225Hz = 1,
    ECG_LPF_BW_200Hz = 2,
    ECG_LPF_BW_180Hz = 3,
    ECG_LPF_BW_150Hz = 4,
    ECG_LPF_BW_125Hz = 5,
    ECG_LPF_BW_100Hz = 6,
    ECG_LPF_BW_75Hz = 7,
    ECG_LPF_BW_INVALID = 8,
} ecg_lpf_bw_t;

typedef enum _ecg_vcm_level_t {
    ECG_VCM_LEVEL_0_33V = 0,
    ECG_VCM_LEVEL_0_385V = 1,
    ECG_VCM_LEVEL_0_44V = 2,
    ECG_VCM_LEVEL_0_495V = 3,
    ECG_VCM_LEVEL_0_55V = 4,
    ECG_VCM_LEVEL_0_605V = 5,
    ECG_VCM_LEVEL_0_66V = 6,
    ECG_VCM_LEVEL_0_715V = 7,
    ECG_VCM_LEVEL_INVALID = 8,
} ecg_vcm_level_t;

void bp6a_ecg_init(ecg_pga_gain_t gain);
void bp6a_ecg_deinit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _S1SBP6A_ECG_H_ */
