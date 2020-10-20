# BP6A AFE API
This project helps users easily use AFE in BP6A.
You can find API documents in ./doc/html/index.html

## BP6A ECG API
This section is about how to use ECG APIs. Please following steps to get ECG data
- step 1. call ecg_init to enable ecg function
- step 2. call ecg_set_decimation_rate to set sampling rate
- step 3. call ecg_set_callback to get notification when ECG data ready
- step 4. call ecg_start to start ECG data streaming
- step 5. The callback function will be called when the ECG data ready.

## BP6A PPG API
This section is about how to use PPG APIs. Please following steps to get PPG data

- step 1. call ppg_init with prt time and number of channles to use
- step 2. call ppg_conf_ch to enable time slot in each channel
- step 3. call ppg_set_led_drv to set led driver with LED on time and LED drive current
- step 4. call ppg_set_cb to set callback when the PPG data ready.
- step 5. call ppg_start to start PPG data streaming
- step 6. The callback function will be called when the PPG data ready.
- step 7. You can get specific time slot data by calling ppg_get_data.

## BP6A BIA API
This section is about how to use BIA APIs. Please following steps to get PPG data
- step 1. call bia_init to enable BIA function
- step 2. call bia_conf with tx frequency and tx amplitude
- step 3. call bia_calibration to calibration
- step 4. call bia_set_callback to set callback when the BIA data ready.
- step 5. call bia_start to start BIA data streaming
- step 6. The callback function will be called when the BIA data ready.
- step 7. You can get body impedance by calling bia_cal_impedance.
