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

#ifndef __S1SBP6A_DMA_H
#define __S1SBP6A_DMA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* ==========================================================================*/
/*                    D E F I N E S                                          */
/* ==========================================================================*/

#define DMA_CH_CFG_DST_INC_SHIFT                       (30)
#define DMA_CH_CFG_DST_INC_MASK                        ((0x03) << DMA_CH_CFG_DST_INC_SHIFT)
#define DMA_CH_CFG_DST_INC(c)                          ((c) << DMA_CH_CFG_DST_INC_SHIFT)

#define DMA_CH_CFG_DST_SIZE_SHIFT                      (28)
#define DMA_CH_CFG_DST_SIZE_MASK                       ((0x03) << DMA_CH_CFG_DST_SIZE_SHIFT)
#define DMA_CH_CFG_DST_SIZE(c)                         ((c) << DMA_CH_CFG_DST_SIZE_SHIFT)

#define DMA_CH_CFG_SRC_INC_SHIFT                       (26)
#define DMA_CH_CFG_SRC_INC_MASK                        ((0x03) << DMA_CH_CFG_SRC_INC_SHIFT)
#define DMA_CH_CFG_SRC_INC(c)                          ((c) << DMA_CH_CFG_SRC_INC_SHIFT)

#define DMA_CH_CFG_SRC_SIZE_SHIFT                      (24)
#define DMA_CH_CFG_SRC_SIZE_MASK                       ((0x03) << DMA_CH_CFG_SRC_SIZE_SHIFT)
#define DMA_CH_CFG_SRC_SIZE(c)                         ((c) << DMA_CH_CFG_SRC_SIZE_SHIFT)

#define DMA_CH_CFG_DST_PROT_CTR_SHIFT                  (21)
#define DMA_CH_CFG_DST_PROT_CTR_MASK                   ((0x07) << DMA_CH_CFG_DST_PROT_CTR_SHIFT)
#define DMA_CH_CFG_DST_PROT_CTR(c)                     ((c) << DMA_CH_CFG_DST_PROT_CTR_SHIFT)

#define DMA_CH_CFG_SRC_PROT_CTR_SHIFT                  (18)
#define DMA_CH_CFG_SRC_PROT_CTR_MASK                   ((0x07) << DMA_CH_CFG_SRC_PROT_CTR_SHIFT)
#define DMA_CH_CFG_SRC_PROT_CTR(c)                     ((c) << DMA_CH_CFG_SRC_PROT_CTR_SHIFT)

#define DMA_CH_CFG_R_PWR_SHIFT                         (14)
#define DMA_CH_CFG_R_PWR_MASK                          ((0x0F) << DMA_CH_CFG_R_PWR_SHIFT)
#define DMA_CH_CFG_R_PWR(c)                            ((c) << DMA_CH_CFG_R_PWR_SHIFT)

#define DMA_CH_CFG_N_MINUS_1_SHIFT                     (4)
#define DMA_CH_CFG_N_MINUS_1_MASK                      ((0x3FF) << DMA_CH_CFG_N_MINUS_1_SHIFT)
#define DMA_CH_CFG_N_MINUS_1(c)                        ((c) << DMA_CH_CFG_N_MINUS_1_SHIFT)

#define DMA_CH_CFG_USEBURST_SHIFT                      (3)
#define DMA_CH_CFG_USEBURST_MASK                       ((0x01) << DMA_CH_CFG_USEBURST_SHIFT)
#define DMA_CH_CFG_USEBURST(c)                         ((c) << DMA_CH_CFG_USEBURST_SHIFT)

#define DMA_CH_CFG_CYCLE_CTR_SHIFT                     (0)
#define DMA_CH_CFG_CYCLE_CTR_MASK                      ((0x07) << DMA_CH_CFG_CYCLE_CTR_SHIFT)
#define DMA_CH_CFG_CYCLE_CTR(c)                        ((c) << DMA_CH_CFG_CYCLE_CTR_SHIFT)

#define DMA_CFG_CHNLPROT_CTR_SHIFT                     (5)
#define DMA_CFG_CHNLPROT_CTR_MASK                      ((0x07) << DMA_CFG_CHNLPROT_CTR_SHIFT)
#define DMA_CFG_CHNLPROT_CTR(c)                        ((c) << DMA_CFG_CHNLPROT_CTR_SHIFT)

#define DMA_CFG_MASTER_EN_SHIFT                        (0)
#define DMA_CFG_MASTER_EN_MASK                         ((0x01) << DMA_CFG_MASTER_EN_SHIFT)
#define DMA_CFG_MASTER_EN(c)                           ((c) << DMA_CFG_MASTER_EN_SHIFT)

#define DMA_STATUS_CH_N_MINUS_1_SHIFT                  (16)
#define DMA_STATUS_CH_N_MINUS_1_MASK                   ((0x1F) << DMA_STATUS_CH_N_MINUS_1_SHIFT)
#define DMA_STATUS_CH_N_MINUS_1(c)                     ((c) << DMA_STATUS_CH_N_MINUS_1_SHIFT)

#define DMA_STATUS_STATE_SHIFT                         (4)
#define DMA_STATUS_STATE_MASK                          ((0x0F) << DMA_STATUS_STATE_SHIFT)
#define DMA_STATUS_STATE(c)                            ((c) << DMA_STATUS_STATE_SHIFT)

#define DMA_STATUS_MASTER_EN_SHIFT                     (0)
#define DMA_STATUS_MASTER_EN_MASK                      ((0x03) << DMA_STATUS_MASTER_EN_SHIFT)
#define DMA_STATUS_MASTER_EN(c)                        ((c) << DMA_STATUS_MASTER_EN_SHIFT)


/* ==========================================================================*/
/*                    T Y P E S                                              */
/* ==========================================================================*/

typedef enum _dma_ch_t {
    DMA_CH_0 = 0,    /* SPI(0-4) RX */
    DMA_CH_1,        /* SPI(0-4) TX */
    DMA_CH_2,        /* SPI(0-4) RX */
    DMA_CH_3,        /* SPI(0-4) TX */
    DMA_CH_4,        /* SPI(0-4) RX */
    DMA_CH_5,        /* SPI(0-4) TX */
    DMA_CH_6,        /* SPI(0-4) RX */
    DMA_CH_7,        /* SPI(0-4) TX */
    DMA_CH_8,        /* AFE FIFO 6  */
    DMA_CH_9,        /* AFE FIFO 7  */
    DMA_CH_10,        /* I2C(0-4) RX */
    DMA_CH_11,        /* I2C(0-4) TX */
    DMA_CH_12,        /* I2C(0-4) RX */
    DMA_CH_13,        /* I2C(0-4) TX */
    DMA_CH_14,        /* I2C(0-4) RX */
    DMA_CH_15,        /* I2C(0-4) TX */
    DMA_CH_16,        /* I2C(0-4) RX */
    DMA_CH_17,        /* I2C(0-4) TX */
    DMA_CH_18,        /* AFE FIFO 08 */
    DMA_CH_19,        /* S/W         */
    DMA_CH_20,        /* UART0 RX    */
    DMA_CH_21,        /* UART0 TX    */
    DMA_CH_22,        /* UART1 RX    */
    DMA_CH_23,        /* UART1 TX    */
    DMA_CH_24,        /* UART2 RX    */
    DMA_CH_25,        /* UART2 TX    */
    DMA_CH_26,        /* AFE FIFO 0  */
    DMA_CH_27,        /* AFE FIFO 1  */
    DMA_CH_28,        /* AFE FIFO 2  */
    DMA_CH_29,        /* AFE FIFO 3  */
    DMA_CH_30,        /* AFE FIFO 4  */
    DMA_CH_31,        /* AFE FIFO 5  */

    DMA_CH_MAX,
    DMA_CH_NOT_ASSIGN
} dma_ch_t;


typedef enum {
    DMA_CYCLE_INVALID = 0,
    DMA_CYCLE_BASIC,
    DMA_CYCLE_AUTO_REQ,
    DMA_CYCLE_PING_PONG,
    DMA_CYCLE_MEM_SCATTER_PRI,
    DMA_CYCLE_MEM_SCATTER_ALT,
    DMA_CYCLE_PERI_SCATTER_PRI,
    DMA_CYCLE_PERI_SCATTER_ALT,
    DMA_CYCLE_MAX,
} DMA_cycle_t;


typedef enum _dma_mux_peri_ch_t {
    DMA_MUX_PERI_CH_0 = 0,
    DMA_MUX_PERI_CH_1,
    DMA_MUX_PERI_CH_2,
    DMA_MUX_PERI_CH_3,
    DMA_MUX_PERI_CH_4,

    DMA_MUX_PERI_CH_MAX,
} dma_mux_peri_ch_t;


typedef enum _dma_peri_type_t {
    DMA_PERI_TYPE_SPI_RX = 0,
    DMA_PERI_TYPE_SPI_TX,
    DMA_PERI_TYPE_I2C_RX,
    DMA_PERI_TYPE_I2C_TX,
    DMA_PERI_TYPE_UART_RX,
    DMA_PERI_TYPE_UART_TX,
    DMA_PERI_TYPE_AFE_FIFO,

    DMA_PERI_TYPE_MAX,
} dma_peri_type_t;


typedef enum {
    DMA_INC_SIZE_BYTE = 0,
    DMA_INC_SIZE_HALFWORD,
    DMA_INC_SIZE_WORD,
    DMA_NO_INCREMENT,

    DMA_INC_SIZE_MAX,
} DMA_inc_data_size_t;

typedef enum {
    DMA_R_POWER_1 = 0,
    DMA_R_POWER_2,
    DMA_R_POWER_4,
    DMA_R_POWER_8,
    DMA_R_POWER_16,
    DMA_R_POWER_32,
    DMA_R_POWER_64,
    DMA_R_POWER_128,
    DMA_R_POWER_256,
    DMA_R_POWER_512,
    DMA_R_POWER_1024,
} DMA_ArbiterCfg_t;

typedef struct {
    volatile uint32_t *srcAddr;
    volatile uint32_t *dstAddr;
    DMA_inc_data_size_t dstInc;
    DMA_inc_data_size_t srcInc;
    DMA_inc_data_size_t dstsize;
    DMA_inc_data_size_t srcsize;
    DMA_ArbiterCfg_t r_pwr;
    DMA_cycle_t cycle_ctr;
    uint16_t  nMinus1;
} DMA_cfg_desc_t;

typedef struct _dma_cfg_t {
    volatile uint32_t *srcAddrPrim;
    volatile uint32_t *dstAddrPrim;
    uint32_t srcSizePrim;
    uint32_t srcIncSizePrim;
    uint32_t dstSizePrim;
    uint32_t dstIncSizePrim;
    uint32_t rPowerPrim;
    uint32_t numPrim;
    uint32_t cycleCtrlPrim;

    volatile uint32_t *srcAddrAlter;
    volatile uint32_t *dstAddrAlter;
    uint32_t srcSizeAlter;
    uint32_t srcIncSizeAlter;
    uint32_t dstSizeAlter;
    uint32_t dstIncSizeAlter;
    uint32_t rPowerAlter;
    uint32_t numAlter;
    uint32_t cycleCtrlAlter;
} dma_cfg_t;


typedef struct _dma_mux_table_t {
    dma_mux_peri_ch_t dmaMuxCh0;
    dma_mux_peri_ch_t dmaMuxCh1;
    dma_mux_peri_ch_t dmaMuxCh2;
    dma_mux_peri_ch_t dmaMuxCh3;
    dma_mux_peri_ch_t dmaNotMuxCh;
} dma_mux_table_t;


typedef struct {
    volatile uint32_t srcEndPointer;
    volatile uint32_t dstEndPointer;
    volatile uint32_t control;
    volatile uint32_t unused;
} DMA_descript_t;


typedef struct {
    volatile DMA_descript_t primary[DMA_CH_MAX];
    volatile DMA_descript_t alternate[DMA_CH_MAX];
} DMA_ch_descript_t;

typedef void (*dma_callback_func_t)(dma_ch_t ch);
typedef void (*dma_error_callback_func_t)(void);

uint32_t bp6a_dma_get_free_chs(void);
uint32_t bp6a_dma_get_status(void);
uint32_t bp6a_dma_get_ch_conf_set(dma_ch_t ch);
int bp6a_dma_init(void);
void bp6a_dma_set_desc(uint32_t ch, bool primary, DMA_cfg_desc_t *pCfg);
int bp6a_dma_open(dma_ch_t ch, DMA_cfg_desc_t *prim, DMA_cfg_desc_t *alt);
int bp6a_dma_start(dma_ch_t ch);
int bp6a_dma_stop(dma_ch_t ch);
int bp6a_dma_close(dma_ch_t ch);
dma_ch_t bp6a_get_dma_ch(dma_peri_type_t periType, uint32_t periCh);
int bp6a_dma_set_callback(dma_ch_t ch, dma_callback_func_t func);
int bp6a_dma_release_callback(dma_ch_t ch);
void bp6a_set_error_callback(dma_error_callback_func_t func);
void bp6a_dma_release_error_callback(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DRV_DMA_H_ */
