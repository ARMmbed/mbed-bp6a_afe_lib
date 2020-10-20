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
#ifndef __S1SBP6A_ECG_API_H
#define __S1SBP6A_ECG_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/**@brief  ECG callback function */
typedef void (*ecg_callback_t)(void *pdata, uint32_t len);

/**@brief  ECG ADC sampling data decimation rates */
typedef enum _ecg_decimation_rate_t {
    ECG_NO_DECIMATION = 0,   /**< Parameters for 1KSPS */
    ECG_DECIMATION_2 = 1,    /**< Parameters for 512SPS*/
    ECG_DECIMATION_4 = 2,    /**< Parameters for 256SPS*/
    ECG_DECIMATION_8 = 3,    /**< Parameters for 128SPS*/
    ECG_DECIMATION_16 = 4,   /**< Parameters for 64SPS*/
    ECG_DECIMATION_INVALID,  /**< Parameters for INVALID */
} ecg_decimation_rate_t;

/**
 * ECG callback function set
 *
 * @param[in] cb  callback fucntion is called if data ready
 * @retval : 0 is success, others error
 */
int ecg_set_callback(ecg_callback_t cb);

/**
 * ECG decimation rate set
 *
 * @param[in] rate ecg data decimation rate(Basic decimation rate is 1KHz)
 * @retval : 0 is success, others error
 */

int ecg_set_decimation_rate(ecg_decimation_rate_t rate);

/**
 * ECG function initialize with the given parameters
 *
 * @retval : 0 is success, others error
 */
int ecg_init(void);
/**
 * ECG signal capture start
 *
 * @retval : 0 is success, others error
 */
int ecg_start(void);

/**
 * ECG signal capture stop
 *
 * @retval : 0 is success, others error
 */
int ecg_stop(void);

/**
 * ECG function de-initialize
 *
 * @retval : 0 is success, others error
 */
int ecg_close(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
