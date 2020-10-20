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
#include "ppg_api.h"
#include "bp6a/s1sbp6a_type.h"
#include "bp6a/s1sbp6a_ppg.h"
#include "bp6a/s1sbp6a_adc.h"
#include "bp6a/s1sbp6a_dma.h"
#include "bp6a/s1sbp6a_adc_fifo.h"
#include "bp6a/s1sbp6a_afe.h"

#define MAX_NUM_PD          2
#define MAX_NUM_LED         4
#define MAX_TIME_SLOT       4
#define PPG_BUF_LEN         1024
#define PPG_ADC_CH0_FIFO_ID ADC_FIFO_ISDADC_ID6
#define PPG_DMA_R_POWER     5

typedef struct {
	uint8_t prt;                  /*2, 4, 10ms */
	uint8_t led_on_time;          /* 1/2048 ms */
	uint8_t led_drv_current[MAX_NUM_LED];
	uint8_t pd_t_slot[MAX_NUM_PD];
	uint8_t n_ch;
} ppg_set_params_t;

static ppg_set_params_t ppg_params;
static ppg_callback_t usr_cb[MAX_NUM_PD] = {NULL, NULL};
static dma_callback_func_t ppg_dma_cb[MAX_NUM_PD];

void bp6a_ppg_led_enable(bool enable);
static uint32_t *g_ppg_buf[MAX_NUM_PD] = { NULL, NULL};
static uint32_t g_ppg_cnv[MAX_NUM_PD][MAX_TIME_SLOT * PPG_BUF_LEN / 2];


static void ppg_data_parse(int32_t *dest,  uint32_t *src, uint32_t len)
{
    uint32_t index;
    uint32_t slot_start[4] = {0, len / 4, len / 4 * 2, len / 4 * 3};

    for (index = 0; index < len; index++) {
        uint32_t dst_idx = slot_start[src[index] >> 24] + (index >> 2);
        dest[dst_idx] = ((((int32_t)src[index]) << 8) >> 8);
    }
}

static void ppg0_dma_cb(dma_ch_t ch)
{
    uint32_t len = 0;
    uint32_t buf_sel = 0;;

    if (usr_cb[0]) {
        buf_sel = bp6a_dma_get_ch_conf_set(ch);

        if (buf_sel) {
            len = PPG_BUF_LEN / 2;
        }
        ppg_data_parse((int32_t *)g_ppg_cnv[0], (int32_t *)((g_ppg_buf[0]) + len), PPG_BUF_LEN / 2);
        (usr_cb[0])();
    }
}

static void ppg1_dma_cb(dma_ch_t ch)
{
    uint32_t len = 0;
    uint32_t buf_sel = 0;;

    if (usr_cb[1]) {
        buf_sel = bp6a_dma_get_ch_conf_set(ch);

        if (buf_sel) {
            len = PPG_BUF_LEN / 2;
        }

        ppg_data_parse(g_ppg_cnv[1], (g_ppg_buf[0]) + len, len);
        (usr_cb[1])();

    }
}

static int ppg_dma_set_config(uint8_t ch, uint32_t dma_ch, uint32_t dma_size)
{
    DMA_cfg_desc_t prim;
    DMA_cfg_desc_t alt;

    uint32_t *ppg_fifo_addr = bp6a_adc_fifo_get_address(PPG_ADC_CH0_FIFO_ID + ch);

    prim.srcAddr = ppg_fifo_addr;
    prim.dstAddr = (uint32_t *)&g_ppg_buf[ch][0];
    prim.dstInc = 2;
    prim.srcInc = 3;
    prim.dstsize = 2;
    prim.srcsize = 2;
    prim.r_pwr = PPG_DMA_R_POWER;
    prim.cycle_ctr = DMA_CYCLE_PING_PONG;
    prim.nMinus1 = dma_size;

    alt.srcAddr = ppg_fifo_addr;
    alt.dstAddr = (uint32_t *)&g_ppg_buf[ch][dma_size];
    alt.dstInc = 2;
    alt.srcInc = 3;
    alt.dstsize = 2;
    alt.srcsize = 2;
    alt.r_pwr = PPG_DMA_R_POWER;
    alt.cycle_ctr = DMA_CYCLE_PING_PONG;
    alt.nMinus1 = dma_size;

    return bp6a_dma_open(dma_ch, &prim, &alt);
}

uint32_t *ppg_get_data(int ch, int time_slot, uint32_t *len)
{
    *len = (PPG_BUF_LEN /2 /4);
    return &g_ppg_cnv[ch][time_slot * (PPG_BUF_LEN /2 /4)];
}

int ppg_init(uint32_t prt_ms, uint8_t n_ch)
{
    int i = 0;

    if (n_ch > MAX_NUM_PD)
        return -1;

    bp6a_dma_init();
    bp6a_ppg_init();

    ppg_dma_cb[0] = ppg0_dma_cb;
    ppg_dma_cb[1] = ppg1_dma_cb;

    ppg_params.prt = prt_ms;
    ppg_params.n_ch = n_ch;

    adc_fifo_config_t stFifoConfigEntry;


    stFifoConfigEntry.mode = ADC_FIFO_MODE_DMA;
    stFifoConfigEntry.mask = ADC_FIFO_INTMASK_NONE;
    stFifoConfigEntry.readySize = ADC_FIFO_READY_SIZE_32;

    for (i  = 0; i < n_ch; i++) {
        g_ppg_buf[i] = (uint32_t *)malloc(sizeof(uint32_t) * PPG_BUF_LEN);
        memset(g_ppg_buf[i], 0, sizeof(uint32_t)*PPG_BUF_LEN);
        bp6a_adc_fifo_open(PPG_ADC_CH0_FIFO_ID + i, &stFifoConfigEntry, NULL);
    }

    return 0;
}

int ppg_conf_ch(int ch, bool t0, bool t1, bool t2, bool t3)
{
    if (ch > ppg_params.n_ch)
        return -1;

    ppg_params.pd_t_slot[ch] = t0 | t1 << 1 | t2 << 2 | t3 << 3;

    return 0;
}

int ppg_set_led_drv(uint8_t ontime, uint8_t *drv_cur)
{
    ppg_params.led_on_time = ontime;
    memcpy(ppg_params.led_drv_current, drv_cur, MAX_NUM_LED);

    return 0;
}

void ppg_set_cb(ppg_callback_t cb0,  ppg_callback_t cb1)
{
    usr_cb[0] = cb0;
    usr_cb[1] = cb1;
}

int ppg_start(void)
{
    int i;
    uint32_t ppg_dma_ch;

    adc_fifo_id_t adc_ch[2] = {PPG_ADC_CH0_FIFO_ID, PPG_ADC_CH0_FIFO_ID + 1};

    for (i = 0; i < ppg_params.n_ch; i++) {
        ppg_dma_ch = bp6a_get_dma_ch(DMA_PERI_TYPE_AFE_FIFO, PPG_ADC_CH0_FIFO_ID + i);
        bp6a_ppg_conf_ch(i, (uint32_t)ppg_params.prt * 2048);
        ppg_dma_set_config(i, ppg_dma_ch, PPG_BUF_LEN / 2);
        bp6a_dma_set_callback(ppg_dma_ch, ppg_dma_cb[i]);
        bp6a_dma_start(ppg_dma_ch);
    }

    bp6a_ppg_conf_leddrv(ppg_params.led_on_time, ppg_params.led_drv_current);
    bp6a_ppg_led_time_slot_enable(ppg_params.pd_t_slot[0] | ppg_params.pd_t_slot[1]);

    bp6a_ppg_led_enable(true);
    bp6a_adc_fifo_multi_start(adc_ch, ppg_params.n_ch);
    return 0;
}

int ppg_stop(void)
{
    int i;
    uint32_t dma_ch;

    for (i = 0; i < ppg_params.n_ch; i++ ) {
        bp6a_adc_fifo_stop(PPG_ADC_CH0_FIFO_ID + i);
        dma_ch = bp6a_get_dma_ch(DMA_PERI_TYPE_AFE_FIFO, PPG_ADC_CH0_FIFO_ID + i);
        bp6a_dma_stop(dma_ch);
    }

    return 0;
}

int ppg_close(void)
{
    int i;
    uint32_t dma_ch;

    bp6a_ppg_deinit();

    for (i = 0; i < ppg_params.n_ch; i++ ) {
        dma_ch = bp6a_get_dma_ch(DMA_PERI_TYPE_AFE_FIFO, PPG_ADC_CH0_FIFO_ID + i);
        bp6a_dma_close(dma_ch + i);
        bp6a_adc_fifo_stop(PPG_ADC_CH0_FIFO_ID + i);
        bp6a_adc_fifo_close(PPG_ADC_CH0_FIFO_ID + i);
        if (g_ppg_buf[i] != NULL)
            free(g_ppg_buf[i]);
    }

    return 0;
}
