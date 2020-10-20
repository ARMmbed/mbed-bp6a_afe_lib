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
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "mbed_assert.h"
#include "s1sbp6a.h"
#include "s1sbp6a_type.h"
#include "s1sbp6a_dma.h"
#include "s1sbp6a_adc_fifo.h"

typedef struct {
    DMA_cycle_t prim_cycle_ctr;
    DMA_cycle_t alt_cycle_ctr;

    uint16_t  prim_nMinus1;
    uint16_t  alt_nMinus1;
} DMA_ch_config_t;

/* ========================================================================== */
/*          V A R I A B L E S                                                 */
/* ========================================================================== */

static __attribute__((aligned(1024))) DMA_ch_descript_t g_DMAdata;
static DMA_ch_config_t g_DMACfgTable[DMA_CH_MAX] = {0,};
static dma_callback_func_t g_DmaCallback[DMA_CH_MAX] = {NULL,};
static dma_error_callback_func_t g_DmaErrorCallback = NULL;
static bool dma_initailize = false;

/* ========================================================================== */
/*          F U N C T I O N S                                                 */
/* ========================================================================== */

void DMA_ERROR_Handler(void)
{
    NVIC_DisableIRQ((IRQn_Type)DMA_ERROR_IRQn);

    if (NULL != g_DmaErrorCallback) {
        g_DmaErrorCallback();
    }

    if ((BP_DMA->ERR_CLR & 0x1) == 0x1) {
        BP_DMA->ERR_CLR = 0x1;
    } else {
        MBED_ASSERT(false);
    }

    NVIC_ClearPendingIRQ((IRQn_Type)DMA_ERROR_IRQn);
    NVIC_EnableIRQ((IRQn_Type)DMA_ERROR_IRQn);

    return;
}

static void bp6a_dma_ctrl_enable(bool enable)
{
    modifyreg32(&BP_DMA->DMA_CFG, DMA_CFG_MASTER_EN_MASK, DMA_CFG_MASTER_EN(enable));
}

static void bp6a_dma_set_discriptor(uint32_t addr)
{
    putreg32(&BP_DMA->CTRL_BASE_PTR, addr);
}

static void bp6a_dma_set_sw_req(dma_ch_t ch)
{
    modifyreg32(&BP_DMA->CHNL_SW_REQUEST, 1 << ch, 1 << ch);
}

static void bp6a_use_burst(dma_ch_t ch, bool enable)
{
    if (enable) {
        modifyreg32(&BP_DMA->CHNL_USEBURST_SET, (1 << ch), (1 << ch));
    } else {
        modifyreg32(&BP_DMA->CHNL_USEBURST_CLR, (1 << ch), (1 << ch));
    }
}

static void bp6a_set_ch_priority(dma_ch_t ch, bool enable)
{
    if (enable) {
        modifyreg32(&BP_DMA->CHNL_PRIORITY_SET, (1 << ch), (1 << ch));
    } else {
        modifyreg32(&BP_DMA->CHNL_PRIORITY_CLR, (1 << ch), (1 << ch));
    }
}

static void bp6a_dma_ch_enable(dma_ch_t ch, bool enable)
{
    if (enable) {
        putreg32(&BP_DMA->CHNL_ENABLE_SET, (1 << ch));
        putreg32(&BP_DMA->CHNL_REQ_MASK_CLR, (1 << ch));

    } else {
        putreg32(&BP_DMA->CHNL_ENABLE_CLR, (1 << ch));
        putreg32(&BP_DMA->CHNL_REQ_MASK_SET, (1 << ch));
    }

    modifyreg32(&BP_DMA->DMA_REQ_GATE, 0x01 << ch, (enable) << ch);
}

static int bp6a_dma_reload_pingpong(dma_ch_t ch)
{
    uint32_t temp   = 0;
    uint32_t bufSel = 0;
    uint32_t size   = 0;

    if (DMA_CH_MAX <= ch) {
        return -1;
    }

    bufSel = bp6a_dma_get_ch_conf_set(ch);

    if (bufSel == 0) {    /* 0: primary data structure */
        temp = g_DMAdata.alternate[ch].control;
        size = g_DMACfgTable[ch].alt_nMinus1;
        g_DMAdata.alternate[ch].control = temp |
                                          DMA_CH_CFG_N_MINUS_1(size - 1) |
                                          DMA_CH_CFG_CYCLE_CTR(DMA_CYCLE_PING_PONG);
    } else  {              /* 1: alternate data structure */
        temp = g_DMAdata.primary[ch].control;
        size = g_DMACfgTable[ch].prim_nMinus1;
        g_DMAdata.primary[ch].control = temp |
                                        DMA_CH_CFG_N_MINUS_1(size - 1) |
                                        DMA_CH_CFG_CYCLE_CTR(DMA_CYCLE_PING_PONG);
    }

    return 0;
}

static inline void bp6a_dma_handler(uint32_t ch)
{
    NVIC_DisableIRQ((IRQn_Type)DMA0_IRQn + ch);
    NVIC_ClearPendingIRQ((IRQn_Type)DMA0_IRQn + ch);
    if ((g_DMACfgTable[ch].prim_cycle_ctr == DMA_CYCLE_PING_PONG) ||
            (g_DMACfgTable[ch].alt_cycle_ctr == DMA_CYCLE_PING_PONG)) {
        bp6a_dma_reload_pingpong(ch);
    }

    if (g_DmaCallback[ch]) {
        g_DmaCallback[ch](ch);
    }

    NVIC_EnableIRQ((IRQn_Type)DMA0_IRQn + ch);
}


static uint32_t bp6a_dma_get_mux(bool is_mux)
{
    if (is_mux) {
        return getreg32(&BP_DMA->DMA_MUX);
    } else {
        return (getreg32(&BP_DMA->DMA_NOT_MUX) & 0xff);
    }
}

static dma_ch_t get_i2c_spi_dma_ch(dma_peri_type_t periType, uint32_t periCh)
{
    uint32_t dmaMux = 0x0;
    uint32_t i;
    uint32_t ch;

    dma_ch_t  dmaCh = DMA_CH_MAX;

    dma_ch_t spiDmaCh[5]    = {DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN};
    dma_ch_t i2cDmaCh[5]    = {DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN, DMA_CH_NOT_ASSIGN};

    dmaMux = bp6a_dma_get_mux(true);
    for (i = 0; i < 4; i++) {
        ch = (dma_ch_t)((dmaMux >> i * 4) & 0x7);
        i2cDmaCh[ch] = DMA_CH_10 + 2;

        ch = (dma_ch_t)((dmaMux >> (i + 4) * 4) & 0x7);
        spiDmaCh[ch] = DMA_CH_0 + 2 * i;
    }

    if (periType == DMA_PERI_TYPE_SPI_RX) {
        dmaCh = (dma_ch_t)spiDmaCh[periCh];
    } else if (periType == DMA_PERI_TYPE_SPI_TX) {
        dmaCh = (dma_ch_t)(spiDmaCh[periCh] + 1);
    } else if (periType == DMA_PERI_TYPE_I2C_RX) {
        dmaCh = (dma_ch_t)i2cDmaCh[periCh];
    } else if (periType == DMA_PERI_TYPE_I2C_TX) {
        dmaCh = (dma_ch_t)(i2cDmaCh[periCh] + 1);
    }

    return dmaCh;
}

uint32_t bp6a_dma_get_free_chs(void)
{
    return ((getreg32(&(BP_DMA->DMA_STATUS)) >> 16) & 0x1F) + 1; /* Number of available DMA channels minus one */
}

uint32_t bp6a_dma_get_status(void)
{
    return ((getreg32(&(BP_DMA->DMA_STATUS)) >> DMA_STATUS_STATE_SHIFT) & DMA_STATUS_STATE_MASK);
}

uint32_t bp6a_dma_get_ch_conf_set(dma_ch_t ch)
{
    return ((getreg32(&BP_DMA->CHNL_PRI_ALT_SET) >> ch) & 0x01);
}

int bp6a_dma_init(void)
{
    uint32_t ch;

    if (dma_initailize) {
        return  -1;
    }

    dma_initailize = true;

    for (ch = 0; ch < DMA_CH_MAX; ch++) {
        bp6a_dma_ch_enable((dma_ch_t)ch, false);
        g_DmaCallback[ch] = NULL;
    }

    bp6a_dma_ctrl_enable(true);
    bp6a_dma_set_discriptor((uint32_t)&g_DMAdata);

    return 0;
}

void bp6a_dma_set_desc(uint32_t ch, bool primary, DMA_cfg_desc_t *pCfg)
{
    DMA_descript_t *DMA_desc;

    if (primary) {
        DMA_desc = (DMA_descript_t *)&g_DMAdata.primary[ch];
    } else {
        DMA_desc = (DMA_descript_t *)&g_DMAdata.alternate[ch];
    }

    DMA_desc->srcEndPointer = (uint32_t)pCfg->srcAddr;
    DMA_desc->dstEndPointer = (uint32_t)pCfg->dstAddr;

    if (pCfg->srcInc != DMA_NO_INCREMENT) {
        DMA_desc->srcEndPointer += ((1 << pCfg->srcInc) * (pCfg->nMinus1 - 1));
    }
    if (pCfg->dstInc != DMA_NO_INCREMENT) {
        DMA_desc->dstEndPointer += ((1 << pCfg->dstInc) * (pCfg->nMinus1 - 1));
    }


    DMA_desc->control = DMA_CH_CFG_DST_INC(pCfg->dstInc) |
                        DMA_CH_CFG_DST_SIZE(pCfg->dstsize) |
                        DMA_CH_CFG_SRC_INC(pCfg->srcInc) |
                        DMA_CH_CFG_SRC_SIZE(pCfg->srcsize) |
                        DMA_CH_CFG_DST_PROT_CTR(0) |
                        DMA_CH_CFG_SRC_PROT_CTR(0) |
                        DMA_CH_CFG_R_PWR(pCfg->r_pwr) |
                        DMA_CH_CFG_N_MINUS_1(pCfg->nMinus1 - 1) |
                        DMA_CH_CFG_USEBURST(0) |
                        DMA_CH_CFG_CYCLE_CTR(pCfg->cycle_ctr);
}

int bp6a_dma_open(dma_ch_t ch, DMA_cfg_desc_t *prim, DMA_cfg_desc_t *alt)
{
    if (ch >= DMA_CH_MAX) {
        return -1;
    }

    bp6a_dma_ch_enable(ch, false);

    g_DMACfgTable[ch].prim_cycle_ctr = prim->cycle_ctr;
    g_DMACfgTable[ch].alt_cycle_ctr = alt->cycle_ctr;
    g_DMACfgTable[ch].prim_nMinus1 = prim->nMinus1;
    g_DMACfgTable[ch].alt_nMinus1 = alt->nMinus1;
    bp6a_dma_set_desc(ch, true, prim);
    bp6a_dma_set_desc(ch, false, alt);

    return 0;
}

int bp6a_dma_start(dma_ch_t ch)
{
    bp6a_dma_ch_enable(ch, true);
    NVIC_EnableIRQ((IRQn_Type)(DMA0_IRQn + (IRQn_Type)ch));

    return 0;
}

int bp6a_dma_stop(dma_ch_t ch)
{
    bp6a_dma_ch_enable(ch, false);

    NVIC_ClearPendingIRQ((IRQn_Type)(DMA0_IRQn + (IRQn_Type)ch));

    return 0;
}

int bp6a_dma_close(dma_ch_t ch)
{
    bp6a_dma_ch_enable(ch, false);

    g_DmaCallback[ch] = NULL;

    NVIC_ClearPendingIRQ((IRQn_Type)(DMA0_IRQn + (IRQn_Type)ch));

    modifyreg32(&BP_DMA->CHNL_PRI_ALT_CLR, 0x1 << ch, 0x1 << ch);    /* Select the default primary data sructure for the channel */

    memset((void *)&g_DMAdata.primary[ch], 0x00, sizeof(g_DMAdata.primary[ch]));
    memset((void *)&g_DMAdata.alternate[ch], 0x00, sizeof(g_DMAdata.alternate[ch]));

    return 0;
}

dma_ch_t bp6a_get_dma_ch(dma_peri_type_t periType, uint32_t periCh)
{
    dma_ch_t dmaCh = DMA_CH_MAX;

    if (((periType <= DMA_PERI_TYPE_I2C_TX) && (periCh > 4)) ||
            ((periType <= DMA_PERI_TYPE_UART_TX) && (periCh > 2)) ||
            ((periType <= DMA_PERI_TYPE_AFE_FIFO) && (periCh > 8))) {
        return DMA_CH_NOT_ASSIGN;
    }

    if (periType == DMA_PERI_TYPE_UART_RX) {
        dmaCh = (dma_ch_t)(DMA_CH_20 + (periCh * 2));
    } else if (periType == DMA_PERI_TYPE_UART_TX) {
        dmaCh = (dma_ch_t)(DMA_CH_21 + (periCh * 2));
    } else if (periType == DMA_PERI_TYPE_AFE_FIFO) {
        if ((periCh == ADC_FIFO_ISDADC_ID6) || (periCh == ADC_FIFO_ISDADC_ID7)) {
            dmaCh = DMA_CH_8 + periCh - ADC_FIFO_ISDADC_ID6;
        } else if (periCh == ADC_FIFO_SDADC_ID8) {
            dmaCh = DMA_CH_18;
        } else {
            dmaCh = (dma_ch_t)(DMA_CH_26 + periCh);
        }
    } else {
        dmaCh = get_i2c_spi_dma_ch(periType, periCh);
    }

    return dmaCh;
}

uint32_t DMA_GetPeriChannel(dma_ch_t ch)
{
    uint32_t periCh = 0x0;
    uint32_t dmaMux = 0x0;

    if (ch >= DMA_CH_26) {
        periCh = (ch - DMA_CH_26);
    } else if (ch >= DMA_CH_20) {
        periCh = (uint32_t)((ch - DMA_CH_20) / 2);
    } else if (ch == DMA_CH_18) {
        periCh = 8;
    } else if (ch == DMA_CH_9) {
        periCh = 7;
    } else if (ch == DMA_CH_8) {
        periCh = 6;
    } else {
        dmaMux = bp6a_dma_get_mux(true);

        if (ch <= DMA_CH_7) {
            periCh = (uint32_t)((dmaMux >> ((ch / 2) * 4)) & 0x7);
        } else if (ch <= DMA_CH_17) {
            periCh = (uint32_t)((dmaMux >> (((ch / 2) - 1) * 4)) & 0x7);
        } else {
            MBED_ASSERT(false);
        }
    }

    return periCh;
}

int bp6a_dma_set_callback(dma_ch_t ch, dma_callback_func_t func)
{
    if (ch >= DMA_CH_MAX) {
        return -1;
    }

    g_DmaCallback[ch] = func;

    return 0;
}

int bp6a_dma_release_callback(dma_ch_t ch)
{
    if (ch >= DMA_CH_MAX) {
        return -1;
    }

    g_DmaCallback[ch] = NULL;

    return 0;
}

void bp6a_set_error_callback(dma_error_callback_func_t func)
{
    g_DmaErrorCallback = func;

    NVIC_EnableIRQ(DMA_ERROR_IRQn);
}

void bp6a_dma_release_error_callback(void)
{
    NVIC_DisableIRQ(DMA_ERROR_IRQn);

    g_DmaErrorCallback = NULL;
}

void DMA0_Handler(void)
{
    bp6a_dma_handler(0);
}

void DMA1_Handler(void)
{
    bp6a_dma_handler(1);
}

void DMA2_Handler(void)
{
    bp6a_dma_handler(2);
}

void DMA3_Handler(void)
{
    bp6a_dma_handler(3);
}

void DMA4_Handler(void)
{
    bp6a_dma_handler(4);
}

void DMA5_Handler(void)
{
    bp6a_dma_handler(5);
}

void DMA6_Handler(void)
{
    bp6a_dma_handler(6);
}

void DMA7_Handler(void)
{
    bp6a_dma_handler(7);
}

void DMA8_Handler(void)
{
    bp6a_dma_handler(8);
}

void DMA9_Handler(void)
{
    bp6a_dma_handler(9);
}

void DMA10_Handler(void)
{
    bp6a_dma_handler(10);
}

void DMA11_Handler(void)
{
    bp6a_dma_handler(11);
}

void DMA12_Handler(void)
{
    bp6a_dma_handler(12);
}

void DMA13_Handler(void)
{
    bp6a_dma_handler(13);
}

void DMA14_Handler(void)
{
    bp6a_dma_handler(14);
}

void DMA15_Handler(void)
{
    bp6a_dma_handler(15);
}

void DMA16_Handler(void)
{
    bp6a_dma_handler(16);
}

void DMA17_Handler(void)
{
    bp6a_dma_handler(17);
}

void DMA18_Handler(void)
{
    bp6a_dma_handler(18);
}

void DMA19_Handler(void)
{
    bp6a_dma_handler(19);
}

void DMA20_Handler(void)
{
    bp6a_dma_handler(20);
}

void DMA21_Handler(void)
{
    bp6a_dma_handler(21);
}

void DMA22_Handler(void)
{
    bp6a_dma_handler(22);
}

void DMA23_Handler(void)
{
    bp6a_dma_handler(23);
}

void DMA24_Handler(void)
{
    bp6a_dma_handler(24);
}

void DMA25_Handler(void)
{
    bp6a_dma_handler(25);
}

void DMA26_Handler(void)
{
    bp6a_dma_handler(26);
}

void DMA27_Handler(void)
{
    bp6a_dma_handler(27);
}

void DMA28_Handler(void)
{
    bp6a_dma_handler(28);
}

void DMA29_Handler(void)
{
    bp6a_dma_handler(29);
}

void DMA30_Handler(void)
{
    bp6a_dma_handler(30);
}

void DMA31_Handler(void)
{
    bp6a_dma_handler(31);
}
