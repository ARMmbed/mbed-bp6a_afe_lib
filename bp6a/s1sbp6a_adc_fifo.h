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
#ifndef __S1SBP6A_ADC_FIFO_H
#define __S1SBP6A_ADC_FIFO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* ========================================================================== */
/*          D E F I N E S                                                     */
/* ========================================================================== */
#define ADC_FIFO_INTMASK_NONE       (0)
#define ADC_FIFO_INTMASK_READY      (1 << 0)
#define ADC_FIFO_INTMASK_EMPTY      (1 << 1)
#define ADC_FIFO_INTMASK_FULL       (1 << 2)
#define ADC_FIFO_INTMASK_ALL        (ADC_FIFO_INTMASK_READY|ADC_FIFO_INTMASK_EMPTY|ADC_FIFO_INTMASK_FULL)

#define ADC_FIFO_STATUS_READY       (1)
#define ADC_FIFO_STATUS_EMPTY       (2)
#define ADC_FIFO_STATUS_FULL        (4)

#define ADC_FIFO_LENGTH_SAR         (16)
#define ADC_FIFO_LENGTH_ID          (64)
#define ADC_FIFO_LENGTH_SD          (16)

/* ========================================================================== */
/*          T Y P E S                                                         */
/* ========================================================================== */

typedef enum _adc_fifo_id_t {
    ADC_FIFO_SARADC_ID0 = 0,    // BIA I Channel
    ADC_FIFO_SARADC_ID1 = 1,    // ECG
    ADC_FIFO_SARADC_ID2 = 2,    // BIA Q Channel
    ADC_FIFO_SARADC_ID3 = 3,    // Not Used
    ADC_FIFO_SARADC_ID4 = 4,    // General Purpose 0
    ADC_FIFO_SARADC_ID5 = 5,    // General Purpose 1
    ADC_FIFO_ISDADC_ID6 = 6,    // PPG Channel 0
    ADC_FIFO_ISDADC_ID7 = 7,    // PPG Channel 1
    ADC_FIFO_SDADC_ID8 = 8,     // GSR or General Purpose 2
    ADC_FIFO_MAX_ID = 9,
} adc_fifo_id_t;

typedef enum _adc_fifo_ready_size_t {
    ADC_FIFO_READY_SIZE_02 = 0,
    ADC_FIFO_READY_SIZE_03 = 1,
    ADC_FIFO_READY_SIZE_04 = 2,
    ADC_FIFO_READY_SIZE_05 = 3,
    ADC_FIFO_READY_SIZE_06 = 4,
    ADC_FIFO_READY_SIZE_07 = 5,
    ADC_FIFO_READY_SIZE_08 = 6,
    ADC_FIFO_READY_SIZE_09 = 7,
    ADC_FIFO_READY_SIZE_10 = 8,
    ADC_FIFO_READY_SIZE_11 = 9,
    ADC_FIFO_READY_SIZE_12 = 10,
    ADC_FIFO_READY_SIZE_13 = 11,
    ADC_FIFO_READY_SIZE_14 = 12,
    ADC_FIFO_READY_SIZE_15 = 13,
    ADC_FIFO_READY_SIZE_16 = 14,
    /* !! below level only use IDADC FIFO */
    ADC_FIFO_READY_SIZE_17 = 15,
    ADC_FIFO_READY_SIZE_18 = 16,
    ADC_FIFO_READY_SIZE_19 = 17,
    ADC_FIFO_READY_SIZE_20 = 18,
    ADC_FIFO_READY_SIZE_21 = 19,
    ADC_FIFO_READY_SIZE_22 = 20,
    ADC_FIFO_READY_SIZE_23 = 21,
    ADC_FIFO_READY_SIZE_24 = 22,
    ADC_FIFO_READY_SIZE_25 = 23,
    ADC_FIFO_READY_SIZE_26 = 24,
    ADC_FIFO_READY_SIZE_27 = 25,
    ADC_FIFO_READY_SIZE_28 = 26,
    ADC_FIFO_READY_SIZE_29 = 27,
    ADC_FIFO_READY_SIZE_30 = 28,
    ADC_FIFO_READY_SIZE_31 = 29,
    ADC_FIFO_READY_SIZE_32 = 30,
    ADC_FIFO_READY_SIZE_33 = 31,
    ADC_FIFO_READY_SIZE_34 = 32,
    ADC_FIFO_READY_SIZE_35 = 33,
    ADC_FIFO_READY_SIZE_36 = 34,
    ADC_FIFO_READY_SIZE_37 = 35,
    ADC_FIFO_READY_SIZE_38 = 36,
    ADC_FIFO_READY_SIZE_39 = 37,
    ADC_FIFO_READY_SIZE_40 = 38,
    ADC_FIFO_READY_SIZE_41 = 39,
    ADC_FIFO_READY_SIZE_42 = 40,
    ADC_FIFO_READY_SIZE_43 = 41,
    ADC_FIFO_READY_SIZE_44 = 42,
    ADC_FIFO_READY_SIZE_45 = 43,
    ADC_FIFO_READY_SIZE_46 = 44,
    ADC_FIFO_READY_SIZE_47 = 45,
    ADC_FIFO_READY_SIZE_48 = 46,
    ADC_FIFO_READY_SIZE_49 = 47,
    ADC_FIFO_READY_SIZE_50 = 48,
    ADC_FIFO_READY_SIZE_51 = 49,
    ADC_FIFO_READY_SIZE_52 = 50,
    ADC_FIFO_READY_SIZE_53 = 51,
    ADC_FIFO_READY_SIZE_54 = 52,
    ADC_FIFO_READY_SIZE_55 = 53,
    ADC_FIFO_READY_SIZE_56 = 54,
    ADC_FIFO_READY_SIZE_57 = 55,
    ADC_FIFO_READY_SIZE_58 = 56,
    ADC_FIFO_READY_SIZE_59 = 57,
    ADC_FIFO_READY_SIZE_60 = 58,
    ADC_FIFO_READY_SIZE_61 = 59,
    ADC_FIFO_READY_SIZE_62 = 60,
    ADC_FIFO_READY_SIZE_63 = 61,
    ADC_FIFO_READY_SIZE_64 = 62,
    ADC_FIFO_READY_SIZE_MAX,
} adc_fifo_ready_size_t;

typedef enum _adc_fifo_mode_t {
    ADC_FIFO_MODE_POLLING,
    ADC_FIFO_MODE_INTERRUPT,
    ADC_FIFO_MODE_DMA,
    ADC_FIFO_MODE_INVALID,
} adc_fifo_mode_t;

typedef void (*adc_fifo_interrupt_callback_func_t)(uint8_t ucIntStatus, adc_fifo_id_t id);

typedef struct _adc_fifo_config_t {
    adc_fifo_mode_t mode;
    uint8_t mask;
    adc_fifo_ready_size_t readySize;
} adc_fifo_config_t;


int32_t bp6a_adc_fifo_open(adc_fifo_id_t id, adc_fifo_config_t *pstFifoConfigEntry, adc_fifo_interrupt_callback_func_t func);
uint32_t *bp6a_adc_fifo_get_address(adc_fifo_id_t id);
int32_t bp6a_adc_fifo_start(adc_fifo_id_t id);
int32_t bp6a_adc_fifo_stop(adc_fifo_id_t id);
int32_t bp6a_adc_fifo_close(adc_fifo_id_t id);
uint8_t bp6a_adc_fifo_get_data_data_cnt(adc_fifo_id_t id);
int32_t bp6a_adc_fifo_get_data_16bit(adc_fifo_id_t id, uint16_t *pData);
int32_t bp6a_adc_fifo_multi_start(adc_fifo_id_t *pId, uint8_t num);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __S1SBP6A_ADC_FIFO_H */
