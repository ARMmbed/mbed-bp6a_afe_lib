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
#ifndef __S1SBP6A_BIA_API_H
#define __S1SBP6A_BIA_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <stdbool.h>

typedef void (*bia_callback_t)(void *pdata, uint32_t len);


/**
 * BIA function initialize with the given parameters
 *
 * @retval : 0 is success, others error
 */
int bia_init(void);

/**
 * BIA configuration with the given parameters
 *
 * @param[in] tx_freq Tx_frequency 1KHz ~ 1Mhz(unit : KHz)
 * @param[in] tx_amp  Tx amplitude (0~3 : 300mv~600mV)
 * @retval : 0 is success, others error
 */
int bia_conf(uint16_t tx_freq, uint8_t tx_amp);


/**
 * BIA callback function set
 *
 * @param[in] cb callback fucntion to be called when BIA data is ready.
 * @retval : 0 is success, others error
 */

int bia_set_callback(bia_callback_t cb);

/**
 * BIA signal capture start
 *
 *  @retval : 0 is success, others error
 */
int bia_start(void);

/**
 * BIA signal capture stop
 *
 *  @retval : 0 is success, others error
 */
int bia_stop(void);


/**
 * BIA function deinitialize
 *
 * @retval : 0 is success, others error
 */
int bia_close(void);

/**
 * BIA calibration
 *
 */
void bia_calibration(void);


/**
 * BIA body impedance calcuation
 *
 * @param[in] p_data pointer to bia raw data
 * @param[in] len bia data length
 * @retval : body impedance
 */
uint32_t bia_cal_impedance(uint16_t *pdata, uint32_t len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
