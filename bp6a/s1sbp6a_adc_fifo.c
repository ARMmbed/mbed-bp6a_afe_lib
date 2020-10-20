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

#include <stdint.h>
#include <stddef.h>
#include "s1sbp6a.h"
#include "s1sbp6a_type.h"
#include "s1sbp6a_adc_fifo.h"
#include "mbed_wait_api.h"

/* ========================================================================== */
/*          D E F I N E S                                                     */
/* ========================================================================== */
#define ADC_FIFO_STATUS_SAR0_ALL    (0x00000007)
#define ADC_FIFO_STATUS_SAR1_ALL    (ADC_FIFO_STATUS_SAR0_ALL << 3)
#define ADC_FIFO_STATUS_SAR2_ALL    (ADC_FIFO_STATUS_SAR0_ALL << 6)
#define ADC_FIFO_STATUS_SAR3_ALL    (ADC_FIFO_STATUS_SAR0_ALL << 9)
#define ADC_FIFO_STATUS_SAR4_ALL    (ADC_FIFO_STATUS_SAR0_ALL << 12)
#define ADC_FIFO_STATUS_SAR5_ALL    (ADC_FIFO_STATUS_SAR0_ALL << 15)
#define ADC_FIFO_STATUS_ID0_ALL     (ADC_FIFO_STATUS_SAR0_ALL << 18)
#define ADC_FIFO_STATUS_ID1_ALL     (ADC_FIFO_STATUS_SAR0_ALL << 21)
#define ADC_FIFO_STATUS_SD_ALL      (ADC_FIFO_STATUS_SAR0_ALL << 24)

/* ========================================================================== */
/*          T Y P E S                                                         */
/* ========================================================================== */

typedef struct _adc_fifo_control_t {
    uint8_t is_use;
    adc_fifo_mode_t mode;
    uint8_t mask;
    adc_fifo_interrupt_callback_func_t CallBack;
    adc_fifo_ready_size_t readySize;
} adc_fifo_control_t;

/* ========================================================================== */
/*          V A R I A B L E S                                                 */
/* ========================================================================== */

static adc_fifo_control_t g_AdcFifoControl[ADC_FIFO_MAX_ID] = {
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
    {0, ADC_FIFO_MODE_INVALID, ADC_FIFO_INTMASK_NONE, NULL, ADC_FIFO_READY_SIZE_MAX},
};


/* ========================================================================== */
/*          F U N C T I O N S                                                 */
/* ========================================================================== */

void AFECON_Handler(void);


static void bp6a_adc_fifo_reset(adc_fifo_id_t id)
{
    modifyreg32(&(BP_ADC_FIFO->FIFO_SW_RESET), (0x1 << id), 0x01 << id);
    wait_us(100);
    modifyreg32(&(BP_ADC_FIFO->FIFO_SW_RESET), (0x1 << id), 0x0 << id);

}

static void bp6a_adc_fifo_set_dma_ready_size(adc_fifo_id_t id, adc_fifo_ready_size_t readySize)
{
    uint32_t reg = (uint32_t)(&(BP_ADC_FIFO->FIFO_DMA_SIZE0));
    uint32_t mask = 0x0F;
    uint32_t shift = id * 4;

    if (id >= ADC_FIFO_ISDADC_ID6) {
        id = (adc_fifo_id_t)(id - ADC_FIFO_ISDADC_ID6);
        reg = (uint32_t)(&(BP_ADC_FIFO->FIFO_DMA_SIZE1));
        if (id !=  ADC_FIFO_SDADC_ID8) {
            mask = 0x3F;
        }
        shift = id * 8;
    }

    modifyreg32(reg, (mask << shift), readySize << shift);
}

static void bp6a_adc_fifo_set_ready_size(adc_fifo_id_t id, adc_fifo_ready_size_t readySize)
{
    uint32_t reg = (uint32_t)(&(BP_ADC_FIFO->FIFO_READY_SIZE0));
    uint32_t mask = 0x0F;
    uint32_t shift = id * 4;

    if (id >= ADC_FIFO_ISDADC_ID6) {
        id = (adc_fifo_id_t)(id - ADC_FIFO_ISDADC_ID6);
        reg = (uint32_t)(&(BP_ADC_FIFO->FIFO_READY_SIZE1));
        if (id !=  ADC_FIFO_SDADC_ID8) {
            mask = 0x3F;
        }
        shift = id * 8;
    }

    modifyreg32(reg, (mask << shift), readySize << shift);
}

static void bp6a_adc_fifo_set_dma_enable(adc_fifo_id_t id, bool en)
{

    modifyreg32(&(BP_ADC_FIFO->FIFO_DMA_ENABLE), (0x1 << id), (en << id));

}

static void bp6a_fifo_set_enable(adc_fifo_id_t id, bool en)
{
    modifyreg32(&(BP_ADC_FIFO->FIFO_ENABLE), 0x01 << id, en << id);
}

static void bp6a_adc_fifo_set_multi_enable(adc_fifo_id_t *pId, uint8_t num, bool en)
{
    uint32_t fifo_mask = 0x0;
    uint32_t en_mask = 0x0;
    adc_fifo_id_t fifo_id = ADC_FIFO_MAX_ID;
    uint8_t i = 0;

    for (i = 0; i  < num; i++) {
        fifo_id = pId[i];
        fifo_mask |= (0x1 << fifo_id);
        en_mask |= ((en) << fifo_id);
    }

    modifyreg32(&(BP_ADC_FIFO->FIFO_ENABLE), fifo_mask, en_mask);
}
#if 1
static uint32_t bp6a_adc_fifo_get_status(void)
{
    return getreg32(&(BP_ADC_FIFO->FIFO_STATUS));
}
#else
static uint8_t bp6a_adc_fifo_get_status(adc_fifo_id_t id)
{
    return (uint8_t)((getreg32(&(BP_ADC_FIFO->FIFO_STATUS)) >> (id * 3)) & 0x07);
}
#endif
static void bp6a_adc_fifo_int_clear(void)
{
    modifyreg32(&(BP_ADC_FIFO->FIFO_INT_CLEAR), 0x0, 0x01);
    __NOP();
    modifyreg32(&(BP_ADC_FIFO->FIFO_INT_CLEAR), 0x01, 0x0);

}

static void bp6a_adc_fifo_set_intmask(adc_fifo_id_t id, uint8_t ucVal)
{
    uint32_t mask;
    uint32_t val;

    mask = (uint32_t)((0x07) << (id * 3));
    val = (uint32_t)(ucVal << (id * 3));

    modifyreg32(&(BP_ADC_FIFO->FIFO_INTR_MASK), mask, val);
}

void AFECON_Handler(void)
{
    uint32_t unStatus = 0x0;

    NVIC_DisableIRQ(AFECON_IRQn);

    unStatus = bp6a_adc_fifo_get_status();

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_SAR0_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_SARADC_ID0].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_SAR0_ALL)) >> (ADC_FIFO_SARADC_ID0 * 3));
            g_AdcFifoControl[ADC_FIFO_SARADC_ID0].CallBack((uint8_t) unStatus, ADC_FIFO_SARADC_ID0);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_SAR1_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_SARADC_ID1].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_SAR1_ALL)) >> (ADC_FIFO_SARADC_ID1 * 3));
            g_AdcFifoControl[ADC_FIFO_SARADC_ID1].CallBack((uint8_t) unStatus, ADC_FIFO_SARADC_ID1);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_SAR2_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_SARADC_ID2].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_SAR2_ALL)) >> (ADC_FIFO_SARADC_ID2 * 3));
            g_AdcFifoControl[ADC_FIFO_SARADC_ID2].CallBack((uint8_t) unStatus, ADC_FIFO_SARADC_ID2);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_SAR3_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_SARADC_ID3].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_SAR3_ALL)) >> (ADC_FIFO_SARADC_ID3 * 3));
            g_AdcFifoControl[ADC_FIFO_SARADC_ID3].CallBack((uint8_t) unStatus, ADC_FIFO_SARADC_ID3);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_SAR4_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_SARADC_ID4].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_SAR4_ALL)) >> (ADC_FIFO_SARADC_ID4 * 3));
            g_AdcFifoControl[ADC_FIFO_SARADC_ID4].CallBack((uint8_t) unStatus, ADC_FIFO_SARADC_ID4);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_SAR5_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_SARADC_ID5].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_SAR5_ALL)) >> (ADC_FIFO_SARADC_ID5 * 3));
            g_AdcFifoControl[ADC_FIFO_SARADC_ID5].CallBack((uint8_t) unStatus, ADC_FIFO_SARADC_ID5);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_ID0_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_ISDADC_ID6].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_ID0_ALL)) >> (ADC_FIFO_ISDADC_ID6 * 3));
            g_AdcFifoControl[ADC_FIFO_ISDADC_ID6].CallBack((uint8_t) unStatus, ADC_FIFO_ISDADC_ID6);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_ID1_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_ISDADC_ID7].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_ID1_ALL)) >> (ADC_FIFO_ISDADC_ID7 * 3));
            g_AdcFifoControl[ADC_FIFO_ISDADC_ID7].CallBack((uint8_t) unStatus, ADC_FIFO_ISDADC_ID7);
        }
    }

    if (unStatus & (uint32_t) ADC_FIFO_STATUS_SD_ALL) {
        if (g_AdcFifoControl[ADC_FIFO_SDADC_ID8].CallBack !=  NULL) {
            unStatus = ((unStatus & (uint32_t)(ADC_FIFO_STATUS_SD_ALL)) >> (ADC_FIFO_SDADC_ID8 * 3));
            g_AdcFifoControl[ADC_FIFO_SDADC_ID8].CallBack((uint8_t) unStatus, ADC_FIFO_SDADC_ID8);
        }
    }

    bp6a_adc_fifo_int_clear();

    NVIC_ClearPendingIRQ(AFECON_IRQn);
    NVIC_EnableIRQ(AFECON_IRQn);

    return;
}

int32_t bp6a_adc_fifo_get_data_16bit(adc_fifo_id_t id, uint16_t *pData)
{
    if (id >= ADC_FIFO_ISDADC_ID6) {
        return -1;
    }

    *pData = (uint16_t)getreg32(&(BP_ADC_FIFO->FIFO0_READ_DATA) + id);

    return 0;
}

int32_t bp6a_adc_fifo_get_data_32bit(adc_fifo_id_t id, uint32_t *pData)
{
    if (id >= ADC_FIFO_MAX_ID || id <= ADC_FIFO_SARADC_ID5) {
        return -1;
    }

    // *pData = getreg32(&(BP_ADC_FIFO->FIFO6_READ_DATA) +
    //                   (ADC_FIFO_ISDADC_ID6 - id) * 4);
    *pData = getreg32(&(BP_ADC_FIFO->FIFO6_READ_DATA) +
                      (ADC_FIFO_ISDADC_ID6 - id));
    return 0;
}

uint8_t bp6a_adc_fifo_get_data_data_cnt(adc_fifo_id_t id)
{
    uint32_t reg = (uint32_t)(&(BP_ADC_FIFO->FIFO_DATA_CNT_SAR));
    uint32_t mask = 0x1F;
    uint32_t shift = id * 5;

    if ((id == ADC_FIFO_ISDADC_ID6) || (id == ADC_FIFO_ISDADC_ID7)) {
        mask = 0x7f;
        shift = (id - ADC_FIFO_ISDADC_ID6) * 7;
        reg = (uint32_t)(&(BP_ADC_FIFO->FIFO_DATA_CNT_IDC));
    }  else if (id == ADC_FIFO_SDADC_ID8) {
        mask = 0x1f;
        reg = (uint32_t)(&(BP_ADC_FIFO->FIFO_DATA_CNT_SDC));
        shift = 0;
    }

    return (uint8_t)((getreg32(reg) >> shift) & mask);
}


uint32_t *bp6a_adc_fifo_get_address(adc_fifo_id_t id)
{
    if (id >= ADC_FIFO_MAX_ID) {
        return NULL;
    }

    return ((uint32_t *) & (BP_ADC_FIFO->FIFO0_READ_DATA) + (id));
}

int32_t bp6a_adc_fifo_start(adc_fifo_id_t id)
{
    if ((g_AdcFifoControl[id].is_use == 0) || (id >= ADC_FIFO_MAX_ID)) {
        return -1;
    }

    bp6a_adc_fifo_reset(id);

    bp6a_fifo_set_enable(id, true);

    return 0;
}

int32_t bp6a_adc_fifo_multi_start(adc_fifo_id_t *pId, uint8_t num)
{
    uint8_t i = 0;

    if ((pId == NULL) || (num == 0) || (num > ADC_FIFO_MAX_ID)) {
        return -1;
    }

    for (i = 0; i < num; i++) {
        if (g_AdcFifoControl[pId[i]].is_use == 0) {
            return -1;
        }
        bp6a_adc_fifo_reset(pId[i]);
    }

    bp6a_adc_fifo_set_multi_enable(pId, num, true);

    return 0;
}

int32_t bp6a_adc_fifo_stop(adc_fifo_id_t id)
{
    if (g_AdcFifoControl[id].is_use == 0) {
        return -1;
    }

    bp6a_fifo_set_enable(id, false);

    bp6a_adc_fifo_reset(id);

    return 0;
}

int32_t bp6a_adc_fifo_multi_stop(adc_fifo_id_t *pId, uint8_t num)
{
    uint8_t i = 0;

    if ((pId == NULL) || (num == 0) || (num > ADC_FIFO_MAX_ID)) {
        return -1;
    }

    for (i = 0; i < num; i++) {
        if (g_AdcFifoControl[pId[i]].is_use == 0) {
            return -1;
        }
    }

    bp6a_adc_fifo_set_multi_enable(pId, num, false);

    for (i = 0; i < num; i++) {
        bp6a_adc_fifo_reset(pId[i]);
    }

    return 0;
}

int32_t bp6a_adc_fifo_open(adc_fifo_id_t id, adc_fifo_config_t *pstFifoConfigEntry, adc_fifo_interrupt_callback_func_t func)
{
    if ((id >= ADC_FIFO_MAX_ID) || (g_AdcFifoControl[id].is_use)) {
        return -1;
    }

    bp6a_fifo_set_enable(id, false);

    g_AdcFifoControl[id].CallBack = NULL;

    if (pstFifoConfigEntry->mode == ADC_FIFO_MODE_INTERRUPT) {
        bp6a_adc_fifo_set_ready_size(id, pstFifoConfigEntry->readySize);
        if (func != NULL) {
            g_AdcFifoControl[id].CallBack  = func;
        }
    } else {
        bp6a_adc_fifo_set_ready_size(id, ADC_FIFO_READY_SIZE_02);
        g_AdcFifoControl[id].CallBack = NULL;
    }

    bp6a_adc_fifo_set_intmask(id, ADC_FIFO_INTMASK_NONE);
    bp6a_adc_fifo_int_clear();

    if ((pstFifoConfigEntry->mode == ADC_FIFO_MODE_INTERRUPT) && (func != NULL)) {
        g_AdcFifoControl[id].CallBack  = func;
    } else {
        g_AdcFifoControl[id].CallBack = NULL;
    }


    if (pstFifoConfigEntry->mode == ADC_FIFO_MODE_INTERRUPT) {
        bp6a_adc_fifo_set_intmask(id, pstFifoConfigEntry->mask);
        NVIC_SetVector((IRQn_Type)AFECON_IRQn, (uint32_t)&AFECON_Handler);
        NVIC_EnableIRQ((IRQn_Type)AFECON_IRQn);
    } else {
        NVIC_ClearPendingIRQ((IRQn_Type)AFECON_IRQn);
        NVIC_DisableIRQ((IRQn_Type)AFECON_IRQn);
    }

    if (pstFifoConfigEntry->mode == ADC_FIFO_MODE_DMA) {
        bp6a_adc_fifo_set_dma_ready_size(id, pstFifoConfigEntry->readySize);
        bp6a_adc_fifo_set_dma_enable(id, true);
    } else {
        bp6a_adc_fifo_set_dma_ready_size(id, ADC_FIFO_READY_SIZE_02);
        bp6a_adc_fifo_set_dma_enable(id, false);
    }


    g_AdcFifoControl[id].is_use = 1;
    g_AdcFifoControl[id].mode = pstFifoConfigEntry->mode;
    g_AdcFifoControl[id].mask = pstFifoConfigEntry->mask;
    g_AdcFifoControl[id].readySize = pstFifoConfigEntry->readySize;

    return 0;
}

int32_t bp6a_adc_fifo_close(adc_fifo_id_t id)
{
    if ((id >= ADC_FIFO_MAX_ID) || (g_AdcFifoControl[id].is_use == 0)) {
        return -1;
    }

    bp6a_fifo_set_enable(id, false);

    NVIC_DisableIRQ(AFECON_IRQn);
    bp6a_adc_fifo_set_intmask(id, ADC_FIFO_INTMASK_NONE);

    g_AdcFifoControl[id].is_use = 0;
    g_AdcFifoControl[id].mode = ADC_FIFO_MODE_INVALID;
    g_AdcFifoControl[id].mask = ADC_FIFO_INTMASK_NONE;
    g_AdcFifoControl[id].CallBack = NULL;
    g_AdcFifoControl[id].readySize = ADC_FIFO_READY_SIZE_MAX;

    return 0;
}
