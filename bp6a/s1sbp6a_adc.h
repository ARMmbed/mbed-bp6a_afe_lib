/*******************************************************************************
 *
 * Copyright 2020 Samsung Electronics All Rights Reserved.
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
 ******************************************************************************/
#ifndef __S1SBP6A_ADC_H
#define __S1SBP6A_ADC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* ========================================================================== */
/*          D E F I N E S                                                     */
/* ========================================================================== */
#define SAR_SEL_OFFSET_OFFSET                 (0x0600)
#define SAR_DC_COMPEN_ADC0_OFFSET             (0x0604)
#define SAR_DC_COMPEN_ADC1_OFFSET             (0x0608)
#define SAR_DC_COMPEN_ADC2_OFFSET             (0x060C)
#define SAR_ADC0_CH0_DATA_OFFSET              (0x061C)
#define SAR_ADC0_CH1_DATA_OFFSET              (0x0620)
#define SAR_ADC1_CH0_DATA_OFFSET              (0x0624)
#define SAR_ADC1_CH1_DATA_OFFSET              (0x0628)
#define SAR_ADC2_CH0_DATA_OFFSET              (0x062C)
#define SAR_ADC2_CH1_DATA_OFFSET              (0x0630)
#define SD_ADC0_DATA_OFFSET                   (0x0634)
#define SD_ADC1_DATA_OFFSET                   (0x0638)
#define SD_ADC2_DATA_OFFSET                   (0x063C)
#define SAR_ADC_CON_OFFSET                    (0x0644)
#define SAR_ADC_CTRL_OFFSET                   (0x0648)


#define SDADC_CTRL1_OFFSET                    (0x0700)
#define SDADC_CTRL2_OFFSET                    (0x0704)
#define SDADC_CTRL3_OFFSET                    (0x0708)
#define SDADC_LDO_CTRL_OFFSET                 (0x0714)


/* SAR_ADC_CON */
#define SAR_ADC_CON_OSR_MODE0_SHIFT           (0)
#define SAR_ADC_CON_CLK_COUNT_RST0_SHIFT      (3)
#define SAR_ADC_CON_OSR_MODE1_SHIFT           (4)
#define SAR_ADC_CON_CLK_COUNT_RST1_SHIFT      (7)
#define SAR_ADC_CON_OSR_MIDE2_SHIFT           (8)
#define SAR_ADC_CON_CLK_COUNT2_RST_SHIFT      (11)
#define SAR_ADC_CON_SIGN_MODE_SHIFT           (12)

#define SAR_ADC_CON_OSR_MODE0_MASK            ((0x07) << SAR_ADC_CON_OSR_MODE0_SHIFT)
#define SAR_ADC_CON_CLK_COUNT_RST0_MASK       ((0x01) << SAR_ADC_CON_CLK_COUNT_RST0_SHIFT)
#define SAR_ADC_CON_OSR_MODE1_MASK            ((0x07) << SAR_ADC_CON_OSR_MODE1_SHIFT)
#define SAR_ADC_CON_CLK_COUNT_RST1_MASK       ((0x01) << SAR_ADC_CON_CLK_COUNT_RST1_SHIFT)
#define SAR_ADC_CON_OSR_MIDE2_MASK            ((0x07) << SAR_ADC_CON_OSR_MIDE2_SHIFT)
#define SAR_ADC_CON_CLK_COUNT2_RST_MASK       ((0x01) << SAR_ADC_CON_CLK_COUNT2_RST_SHIFT)
#define SAR_ADC_CON_SIGN_MODE_MASK            ((0x01) << SAR_ADC_CON_SIGN_MODE_SHIFT)

#define SAR_ADC_CON_OSR_MODE0(c)              ((c) << SAR_ADC_CON_OSR_MODE0_SHIFT)
#define SAR_ADC_CON_CLK_COUNT_RST0(c)         ((c) << SAR_ADC_CON_CLK_COUNT_RST0_SHIFT)
#define SAR_ADC_CON_OSR_MODE1(c)              ((c) << SAR_ADC_CON_OSR_MODE1_SHIFT)
#define SAR_ADC_CON_CLK_COUNT_RST1(c)         ((c) << SAR_ADC_CON_CLK_COUNT_RST1_SHIFT)
#define SAR_ADC_CON_OSR_MIDE2(c)              ((c) << SAR_ADC_CON_OSR_MIDE2_SHIFT)
#define SAR_ADC_CON_CLK_COUNT2_RST(c)         ((c) << SAR_ADC_CON_CLK_COUNT2_RST_SHIFT)
#define SAR_ADC_CON_SIGN_MODE(c)              ((c) << SAR_ADC_CON_SIGN_MODE_SHIFT)

/* SAR_ADC_CTRL */
#define SAR_ADC_CTRL_EN_SHIFT                (0)
#define SAR_ADC_CTRL_EN_ADC_SHIFT             (1)
#define SAR_ADC_CTRL_CAP_CTRL0_SHIFT          (5)
#define SAR_ADC_CTRL_VCM_CTRL1_SHIFT          (8)
#define SAR_ADC_CTRL_CAP_CTRL2_SHIFT          (12)
#define SAR_ADC_CTRL_CVCM_CTRL_SHIFT          (16)

#define SAR_ADC_CTRL_EN_MASK                 ((0x01) << SAR_ADC_CTRL_EN_SHIFT)
#define SAR_ADC_CTRL_EN_ADC_MASK             ((0x07) << SAR_ADC_CTRL_EN_ADC_SHIFT)
#define SAR_ADC_CTRL_CAP_CTRL0_MASK          ((0x07) << SAR_ADC_CTRL_CAP_CTRL0_SHIFT)
#define SAR_ADC_CTRL_VCM_CTRL1_MASK          ((0x07) << SAR_ADC_CTRL_VCM_CTRL1_SHIFT)
#define SAR_ADC_CTRL_CAP_CTRL2_MASK          ((0x07) << SAR_ADC_CTRL_CAP_CTRL2_SHIFT)
#define SAR_ADC_CTRL_CVCM_CTRL_MASK          ((0x0F) << SAR_ADC_CTRL_CVCM_CTRL_SHIFT)

#define SAR_ADC_CTRL_EN(c)                   ((c) << SAR_ADC_CTRL_EN_SHIFT)
#define SAR_ADC_CTRL_EN_ADC(c)               ((c) << SAR_ADC_CTRL_EN_ADC_SHIFT)
#define SAR_ADC_CTRL_CAP_CTRL0(c)            ((c) << SAR_ADC_CTRL_CAP_CTRL0_SHIFT)
#define SAR_ADC_CTRL_VCM_CTRL1(c)            ((c) << SAR_ADC_CTRL_VCM_CTRL1_SHIFT)
#define SAR_ADC_CTRL_CAP_CTRL2(c)            ((c) << SAR_ADC_CTRL_CAP_CTRL2_SHIFT)
#define SAR_ADC_CTRL_CVCM_CTRL(c)            ((c) << SAR_ADC_CTRL_CVCM_CTRL_SHIFT)

/* SDADC_CTRL1 */

#define SDADC_CTRL1_SEL_INPUT_SHIFT           (0)
#define SDADC_CTRL1_DFILTER_SHIFT             (2)
#define SDADC_CTRL1_START_SHIFT               (4)
#define SDADC_CTRL1_ENALBE_SHIFT              (5)
#define SDADC_CTRL1_ENABLE_BUF_SHIFT          (6)
#define SDADC_CTRL1_RESET_SHIFT               (7)

#define SDADC_CTRL1_SEL_INPUT_MASK           ((0x03) << SDADC_CTRL1_SEL_INPUT_SHIFT)
#define SDADC_CTRL1_DFILTER_MASK             ((0x03) << SDADC_CTRL1_DFILTER_SHIFT)
#define SDADC_CTRL1_START_MASK               ((0x01) << SDADC_CTRL1_START_SHIFT)
#define SDADC_CTRL1_ENALBE_MASK              ((0x01) << SDADC_CTRL1_ENALBE_SHIFT)
#define SDADC_CTRL1_ENABLE_BUF_MASK          ((0x01) << SDADC_CTRL1_ENABLE_BUF_SHIFT)
#define SDADC_CTRL1_RESET_MASK               ((0x01) << SDADC_CTRL1_RESET_SHIFT)

#define SDADC_CTRL1_SEL_INPUT(c)           ((c) << SDADC_CTRL1_SEL_INPUT_SHIFT)
#define SDADC_CTRL1_DFILTER(c)             ((c) << SDADC_CTRL1_DFILTER_SHIFT)
#define SDADC_CTRL1_START(c)               ((c) << SDADC_CTRL1_START_SHIFT)
#define SDADC_CTRL1_ENALBE(c)              ((c) << SDADC_CTRL1_ENALBE_SHIFT)
#define SDADC_CTRL1_ENABLE_BUF(c)          ((c) << SDADC_CTRL1_ENABLE_BUF_SHIFT)
#define SDADC_CTRL1_RESET(c)               ((c) << SDADC_CTRL1_RESET_SHIFT)
#define SDADC_INPUT_DIFFERENTIAL            (0)
#define SDADC_INPUT_SINGLE                  (1)
#define SDADC_FILTER_1KHZ                   (0)
#define SDADC_FILTER_500HZ                  (1)
#define SDADC_FILTER_250HZ                  (2)
#define SDADC_FILTER_125HZ                  (3)

/* SDADC_CTRL2 */

#define SDADC_CTRL2_SEL_VCM_SHIFT           (0)
#define SDADC_CTRL2_SEL_VCM_MASK            ((0x07) << SDADC_CTRL2_SEL_VCM_SHIFT)
#define SDADC_CTRL2_SEL_VCM(c)              ((c) << SDADC_CTRL2_SEL_VCM_SHIFT)

#define SDAC_SEL_VCM_0_31V                  (0)
#define SDAC_SEL_VCM_0_55V                  (1)
#define SDAC_SEL_VCM_0_78V                  (2)
#define SDAC_SEL_VCM_1_02V                  (3)
#define SDAC_SEL_VCM_1_24V                  (4)
#define SDAC_SEL_VCM_1_48V                  (5)
#define SDAC_SEL_VCM_1_72V                  (6)
#define SDAC_SEL_VCM_1_95V                  (7)

/* SDADC_CTRL3 */
#define SDADC_CTRL3_EN_CHOP_DSM_SHIFT        (0)
#define SDADC_CTRL3_EN_CHOP_BUF_SHIFT        (1)
#define SDADC_CTRL3_EN_DEM_SHIFT             (2)
#define SDADC_CTRL3_ENBUF_BYPASS_SHIFT       (3)

#define SDADC_CTRL3_EN_CHOP_DSM_MASK         ((0x01) << SDADC_CTRL3_EN_CHOP_DSM_SHIFT)
#define SDADC_CTRL3_EN_CHOP_BUF_MASK         ((0x01) << SDADC_CTRL3_EN_CHOP_BUF_SHIFT)
#define SDADC_CTRL3_EN_DEM_MASK              ((0x01) << SDADC_CTRL3_EN_DEM_SHIFT)
#define SDADC_CTRL3_ENBUF_BYPASS_MASK        ((0x01) << SDADC_CTRL3_ENBUF_BYPASS_SHIFT)

#define SDADC_CTRL3_EN_CHOP_DSM(c)           ((c) << SDADC_CTRL3_EN_CHOP_DSM_SHIFT)
#define SDADC_CTRL3_EN_CHOP_BUF(c)           ((c) << SDADC_CTRL3_EN_CHOP_BUF_SHIFT)
#define SDADC_CTRL3_EN_DEM(c)                ((c) << SDADC_CTRL3_EN_DEM_SHIFT)
#define SDADC_CTRL3_ENBUF_BYPASS(c)          ((c) << SDADC_CTRL3_ENBUF_BYPASS_SHIFT)

/* SDADC_LDO_CTRL */
#define SDADC_LDO_CTRL_ENABLE_SHIFT          (0)
#define SDADC_LDO_CTRL_VREF_EX_MODE_SHIFT    (1)
#define SDADC_LDO_CTRL_EXT_REG_MODE_SHIFT    (2)
#define SDADC_LDO_CTRL_BIAS_CURX2_SHIFT      (3)

#define SDADC_LDO_CTRL_ENABLE_MASK          ((0x01) << SDADC_LDO_CTRL_ENABLE_SHIFT)
#define SDADC_LDO_CTRL_VREF_EX_MODE_MASK    ((0x01) << SDADC_LDO_CTRL_VREF_EX_MODE_SHIFT)
#define SDADC_LDO_CTRL_EXT_REG_MODE_MASK    ((0x01) << SDADC_LDO_CTRL_EXT_REG_MODE_SHIFT)
#define SDADC_LDO_CTRL_BIAS_CURX2_MASK      ((0x01) << SDADC_LDO_CTRL_BIAS_CURX2_SHIFT)

#define SDADC_LDO_CTRL_ENABLE(c)            ((c) << SDADC_LDO_CTRL_ENABLE_SHIFT)
#define SDADC_LDO_CTRL_VREF_EX_MODE(c)      ((c) << SDADC_LDO_CTRL_VREF_EX_MODE_SHIFT)
#define SDADC_LDO_CTRL_EXT_REG_MODE(c)      ((c) << SDADC_LDO_CTRL_EXT_REG_MODE_SHIFT)
#define SDADC_LDO_CTRL_BIAS_CURX2(c)        ((c) << SDADC_LDO_CTRL_BIAS_CURX2_SHIFT)


// SAR_ADC_CTRL
#define SARADC_EN_3SARADC_SHIFT             (0U)
#define SARADC_EN_3SARADC_MASK              (0x1UL << SARADC_EN_3SARADC_SHIFT)

// SDADC_CTRL1
#define SDADC_SEL_INPUT_SHIFT               (0U)
#define SDADC_SEL_INPUT_MASK                (0x3UL << SDADC_SEL_INPUT_SHIFT)
#define SDADC_DFILTER_SHIFT                 (2U)
#define SDADC_DFILTER_MASK                  (0x3UL << SDADC_DFILTER_SHIFT)
#define SDADC_START_SHIFT                   (4U)
#define SDADC_START_MASK                    (0x1UL << SDADC_START_SHIFT)
#define SDADC_EN_SHIFT                      (5U)
#define SDADC_EN_MASK                       (0x1UL << SDADC_EN_SHIFT)
#define SDADC_EN_BUF_SHIFT                  (6U)
#define SDADC_EN_BUF_MASK                   (0x1UL << SDADC_EN_BUF_SHIFT)
#define SDADC_RESET_SHIFT                   (7U)
#define SDADC_RESET_MASK                    (0x1UL << SDADC_RESET_SHIFT)

// SDADC_CTRL2
#define SDADC_SEL_VCM_SHIFT                 (0U)
#define SDADC_SEL_VCM_MASK                  (0x7UL << SDADC_SEL_VCM_SHIFT)

// SDADC_CTRL3
#define SDADC_EN_CHOP_DSM_SHIFT             (0U)
#define SDADC_EN_CHOP_DSM_MASK              (0x1UL << SDADC_EN_CHOP_DSM_SHIFT)
#define SDADC_EN_CHOP_BUF_SHIFT             (1U)
#define SDADC_EN_CHOP_BUF_MASK              (0x1UL << SDADC_EN_CHOP_BUF_SHIFT)
#define SDADC_EN_DEM_SHIFT                  (2U)
#define SDADC_EN_DEM_MASK                   (0x1UL << SDADC_EN_DEM_SHIFT)
#define SDADC_BUF_BYPASS_SHIFT              (3U)
#define SDADC_BUF_BYPASS_MASK               (0x1UL << SDADC_BUF_BYPASS_SHIFT)

// GAPADC_LDO_CTRL
#define SDADC_LDO_EN_SHIFT                   (0U)
#define SDADC_LDO_EN_MASK                    (0x1UL << SDADC_LDO_EN_SHIFT)
#define SDADC_VREF_EX_MODE_SHIFT             (1U)
#define SDADC_VREF_EX_MODE_MASK              (0x1UL << SDADC_VREF_EX_MODE_SHIFT)
#define SDADC_BIAS_CURX2_SHIFT               (2U)
#define SDADC_BIAS_CURX2_MASK                (0x1UL << SDADC_BIAS_CURX2_SHIFT)
#define SDADC_EXT_REG_MODE_SHIFT             (3U)
#define SDADC_EXT_REG_MODE_MASK              (0x1UL << SDADC_EXT_REG_MODE_SHIFT)



/* ========================================================================== */
/*          T Y P E S                                                         */
/* ========================================================================== */
typedef enum _saradc_ch_t {
    SARADC_CH0 = 0,
    SARADC_CH1 = 1,
    SARADC_CH2 = 2,
    SARADC_CH_MAX = 3,
} saradc_ch_t;

typedef enum _saradc_port_t {
    SARADC_PORT0 = 0,
    SARADC_PORT1 = 1,
    SARADC_PORT_MAX = 2,
} saradc_port_t;

typedef enum _adc_sdadc_ch_t {
    SDADC_CH0 = 0,
    SDADC_CH_MAX = 1,
} sdadc_ch_t;

typedef enum _isdadc_ch_t {
    ISDADC_CH0 = 0,
    ISDADC_CH1 = 1,
    ISDADC_CH_MAX = 2,
} isdadc_ch_t;

typedef enum _saradc_osr_mode_t {
    SARADC_OSR_NO_DECIMATION = 0,
    SARADC_OSR_2_DECIMATION = 1,
    SARADC_OSR_4_DECIMATION = 2,
    SARADC_OSR_8_DECIMATION = 3,
    SARADC_OSR_16_DECIMATION = 4,
    SARADC_OSR_INVALID = 5,
} saradc_osr_mode_t;

typedef enum _adc_sdadc_sel_input_mux_t {
    SDADC_SEL_INPUT_MUX_DIFFERENTIAL = 0,
    SDADC_SEL_INPUT_MUX_SINGLE_ENDED = 1,
    SDADC_SEL_INPUT_MUX_INVALID = 2,
} sdadc_sel_input_mux_t;

typedef enum _adc_sdadc_sel_vcm_level_t {
    SDADC_SEL_VCM_0_31V = 0,
    SDADC_SEL_VCM_0_55V = 1,
    SDADC_SEL_VCM_0_78V = 2,
    SDADC_SEL_VCM_1_02V = 3,
    SDADC_SEL_VCM_1_25V = 4,
    SDADC_SEL_VCM_1_48V = 5,
    SDADC_SEL_VCM_1_72V = 6,
    SDADC_SEL_VCM_1_95V = 7,
    SDADC_SEL_VCM_MAX = 8,
} sdadc_sel_vcm_level_t;

void bp6a_saradc_init(saradc_ch_t ch);
void bp6a_saradc_stop(saradc_ch_t ch);
uint32_t bp6a_saradc_read(saradc_ch_t ch, saradc_port_t port);
void bp6a_saradc_set_OSR(saradc_ch_t ch, saradc_osr_mode_t osrMode);
uint32_t bp6a_saradc_get_OSR(saradc_ch_t ch);
void bp6a_saradc_reset_dm_cnt(saradc_ch_t ch);
void bp6a_sdadc_init(sdadc_ch_t ch);
void bp6a_sdadc_stop(sdadc_ch_t ch);
void bp6a_sdadc_set_input_mode(sdadc_sel_input_mux_t mux);
uint32_t bp6a_sdadc_read(sdadc_ch_t ch);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DRV_ADC_H_ */
