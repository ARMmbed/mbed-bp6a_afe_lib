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
#ifndef __S1SBP6A_PPG_API_H
#define __S1SBP6A_PPG_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <stdbool.h>

typedef void (*ppg_callback_t)(void);

/**
 * PPG function initialize with the given parameters
 *
 * @param[in] prt_ms PPG Pulse Repetition Time(1ms ~ 10ms)
 * @param[in] n_ch enable channels (1 or 2)
 * @retval : 0 is success, others error
 */
int ppg_init(uint32_t prt_ms, uint8_t n_ch);

/**
 * PPG channle configuration with the given parameters
 *
 * @param[in] ch PPG channel number
 * @param[in] t0 time slot 0 enable
 * @param[in] t1 time slot 1 enable
 * @param[in] t2 time slot 2 enable
 * @param[in] t3 time slot 3 enable
 * @retval : 0 is success, others error
 */
int ppg_conf_ch(int ch, bool t0, bool t1, bool t2, bool t3);

/**
 * PPG LED driver configuration with the given parameters
 *
 * @param[in] ontime LED on time in ms (max : prt / 4)
 * @param[in] drv_cur pointer to 4 LED driver current array (0~100mA)
 * @retval : 0 is success, others error
 */
int ppg_set_led_drv(uint8_t ontime, uint8_t *drv_cur);

/**
 * PPG callback function set for each channel
 *
 * @param[in] cb0 callback fucntion to be called when ch0 data is ready.
 * @param[in] cb1 callback function to be called when ch1 data is ready.
 */
void ppg_set_cb(ppg_callback_t cb0,  ppg_callback_t cb1);

/**
 * PPG signal capture start
 *
 *  @retval : 0 is success, others error
 */
int ppg_start(void);

/**
 * PPG signal capture stop
 *
 *  @retval : 0 is success, others error
 */
int ppg_stop(void);


/**
 * PPG function deinitialize
 *
 * @retval : 0 is success, others error
 */
int ppg_close(void);

/**
 * PPG data get from buffer
 *
 * @param[in] ch PPG channel
 * @param[in] time slot
 * @param[in,out] len pointer of data length
 * @retval : pointer of the data buffer
 */
uint32_t *ppg_get_data(int ch, int time_slot, uint32_t *len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
