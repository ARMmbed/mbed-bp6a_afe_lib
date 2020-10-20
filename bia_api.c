/*******************************************************************************
 *
 * Copyright 2020 Samsung Electronics All Rights Reserved.
 *
 * * Licensed under the Apache License, Version 2.0 (the "License");
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
#include <stdlib.h>
#include "bp6a/s1sbp6a_type.h"
#include "bp6a/s1sbp6a_bia.h"
#include "bp6a/s1sbp6a_adc.h"
#include "bp6a/s1sbp6a_dma.h"
#include "bp6a/s1sbp6a_adc_fifo.h"
#include "bp6a/s1sbp6a_afe.h"
#include "bia_api.h"

#define BIA_ADC_CH                    (SARADC_CH0)
#define BIA_ADC_FIFO_CH_I             (ADC_FIFO_SARADC_ID0)
#define BIA_ADC_FIFO_CH_Q             (ADC_FIFO_SARADC_ID2)
#define BIA_SETTLING_TIME_MS          (200)
#define BIA_SAMPLING_PERIOD_MS        (2)
#define BIA_DMA_R_POWER               (3)
#define BIA_SAMPLE_AVERAGE_NUM        (100)
#define BIA_SARADC_CENTER             (2048)
#define BIA_EXTERNAL_R_OHM            (51000)

#define BIA_CALIB_R0_OHM              (1500)
#define BIA_CALIB_R1_OHM              (750)
#define BIA_DMA_SIZE                  (256)
#define BIA_DMA_BUFF_SIZE             (BIA_DMA_SIZE * 2)

#define CAL_R0                         (1/((float)1/BIA_EXTERNAL_R_OHM + (float)1/BIA_CALIB_R0_OHM))
#define CAL_R1                         (1/((float)1/BIA_EXTERNAL_R_OHM + (float)1/BIA_CALIB_R1_OHM))

static uint16_t *bia_buffer = NULL;
static dma_ch_t bia_dma_ch;
static uint32_t g_BiaCalibCodeR0 = 0;   // 1500
static uint32_t g_BiaCalibCodeR1 = 0;   // 750
static bia_callback_t usr_cb = NULL;


static int bia_conv_adc_code(uint16_t *pData, uint32_t len)
{
    uint32_t osrMode      = 0;
    uint32_t i            = 0;
    uint32_t mean;

    osrMode = bp6a_saradc_get_OSR(SARADC_CH0);

    mean = (BIA_SARADC_CENTER << osrMode);

    for (i = 0; i < len; i++) {
        pData[i] = mean - (int16_t)pData[i];

        if ((int16_t)pData[i] < 0) {
            pData[i] *= (-1);
        }
    }
    return 0;
}

static int32_t bia_cal_ohm(uint16_t code)
{
    int32_t r0     = 0;
    int32_t r1     = 0;
    int32_t v0     = 0;
    int32_t v1     = 0;
    int32_t bodyR  = 0;
    int32_t retVal = 0;

    float slope    = 0.0f;

    r0 = CAL_R0;
    r1 = CAL_R1;

    v0 = g_BiaCalibCodeR0;
    v1 = g_BiaCalibCodeR1;

    slope = (float)(r0 - r1) / (v0 - v1);
    bodyR = (int32_t)(slope * (code - v1) + r1);

    retVal = (int32_t)((float)1 / (((float)1 / bodyR) - ((float)1 / BIA_EXTERNAL_R_OHM)));

    return retVal;
}

uint32_t bia_cal_impedance(uint16_t *pdata, uint32_t len)
{

    uint32_t imp = 0;
    uint32_t i;

    bia_conv_adc_code(pdata, len);

    for (i = 0; i < len; i++) {

        imp += bia_cal_ohm(pdata[i]);
    }

    return (uint32_t)(imp / len);
}

static void bia_dma_callback(dma_ch_t ch)
{
    uint32_t len = 0;
    uint32_t buf_sel = 0;;

    if (usr_cb) {
        buf_sel = bp6a_dma_get_ch_conf_set(ch);

        if (buf_sel) {
            len = BIA_DMA_SIZE;
        }

        usr_cb(&bia_buffer[len], BIA_DMA_SIZE);
    }
}

static int bia_dma_set_config(dma_ch_t ch, uint32_t dma_size)
{
    DMA_cfg_desc_t prim;
    DMA_cfg_desc_t alt;

    uint32_t *bia_fifo_addr = bp6a_adc_fifo_get_address(BIA_ADC_FIFO_CH_I);

    prim.srcAddr = bia_fifo_addr;
    prim.dstAddr = (uint32_t *)&bia_buffer[0];
    prim.dstInc = 1;
    prim.srcInc = 3;
    prim.dstsize = 1;
    prim.srcsize = 1;
    prim.r_pwr = BIA_DMA_R_POWER;
    prim.cycle_ctr = DMA_CYCLE_PING_PONG;
    prim.nMinus1 = dma_size;

    alt.srcAddr = bia_fifo_addr;
    alt.dstAddr = (uint32_t *)&bia_buffer[dma_size];
    alt.dstInc = 1;
    alt.srcInc = 3;
    alt.dstsize = 1;
    alt.srcsize = 1;
    alt.r_pwr = BIA_DMA_R_POWER;
    alt.cycle_ctr = DMA_CYCLE_PING_PONG;
    alt.nMinus1 = dma_size;

    return bp6a_dma_open(ch, &prim, &alt);
}

int bia_init(void)
{

    bp6a_dma_init();
    bp6a_bia_init();

    bp6a_saradc_init(BIA_ADC_CH);

    bp6a_bia_enable_tx(true);
    bp6a_bia_enable_rx(true);
    bp6a_bia_set_mode(BIA_I_MODE);

    adc_fifo_config_t stFifoConfigEntry;

    stFifoConfigEntry.mode = ADC_FIFO_MODE_DMA;
    stFifoConfigEntry.mask = ADC_FIFO_INTMASK_NONE;
    stFifoConfigEntry.readySize = ADC_FIFO_READY_SIZE_08;

    if (bp6a_adc_fifo_open(BIA_ADC_FIFO_CH_I, &stFifoConfigEntry, NULL)) {
        goto error_return1;
    }


    bia_buffer = (uint16_t *)malloc(sizeof(uint16_t) * BIA_DMA_BUFF_SIZE);

    if (!bia_buffer) {
        goto error_return0;
    }
    return 0;

error_return0 :
    bp6a_adc_fifo_close(BIA_ADC_FIFO_CH_I);
error_return1 :
    bp6a_saradc_stop(BIA_ADC_CH);
    bp6a_bia_deinit();

    return -1;
}

int bia_conf(uint16_t tx_freq, uint8_t tx_amp)
{
    bp6a_saradc_set_OSR(SARADC_CH0, SARADC_OSR_2_DECIMATION);
    bp6a_bia_set_tx_volt(tx_amp);
    bp6a_bia_set_tx_freq(tx_freq);

    return 0;
}

int bia_start(void)
{

    bia_dma_ch = bp6a_get_dma_ch(DMA_PERI_TYPE_AFE_FIFO, (uint32_t)BIA_ADC_FIFO_CH_I);
    bia_dma_set_config(bia_dma_ch, BIA_DMA_SIZE);
    bp6a_dma_set_callback(bia_dma_ch, bia_dma_callback);


    if (bp6a_dma_start(bia_dma_ch)) {
        return -1;
    }

    if (bp6a_adc_fifo_start(BIA_ADC_FIFO_CH_I)) {
        return -1;
    }

    return 0;
}

int bia_stop(void)
{
    bp6a_dma_stop(bia_dma_ch);
    bp6a_adc_fifo_stop(BIA_ADC_FIFO_CH_I);
    return 0;
}

int bia_close(void)
{
    bp6a_adc_fifo_close(BIA_ADC_FIFO_CH_I);
    usr_cb = NULL;
    bp6a_bia_deinit();
    free(bia_buffer);
    return 0;
}

int bia_set_callback(bia_callback_t cb)
{
    if (usr_cb != NULL || cb == NULL) {
        return -1;
    }

    usr_cb = cb;

    return 0;
}

void bia_calibration(void)
{
    uint32_t i            = 0;
    uint32_t sum          = 0;
    uint16_t ich          = 0;
    int j;

    printf("Calibration Start\r\n");
    bia_imp_path_t cal_path[2] = {BIA_CALIBRATION_PATH0, BIA_CALIBRATION_PATH1};
    uint32_t *pCalcode[2] = {&g_BiaCalibCodeR0, &g_BiaCalibCodeR1};

    for (j = 0; j < 2; j++) {
        bp6a_bia_set_path(cal_path[j]);
        wait_us(BIA_SETTLING_TIME_MS * 1000);

        sum = 0;
        bp6a_adc_fifo_start(BIA_ADC_FIFO_CH_I);

        for (i = 0; i < BIA_SAMPLE_AVERAGE_NUM; i++) {
            while (!bp6a_adc_fifo_get_data_data_cnt(BIA_ADC_FIFO_CH_I));

            bp6a_adc_fifo_get_data_16bit(BIA_ADC_FIFO_CH_I, (uint16_t *)&ich);
            bia_conv_adc_code(&ich, 1);
            sum += ich;

            wait_us(BIA_SAMPLING_PERIOD_MS * 1000);
        }

        bp6a_adc_fifo_stop(BIA_ADC_FIFO_CH_I);

        // calib point r0
        *pCalcode[j] = sum / BIA_SAMPLE_AVERAGE_NUM;
        printf("calibration r: %d, code: %d \r\n", j, *pCalcode[j]);

    }
    bp6a_bia_set_path(BIA_BODY_PATH);

}
