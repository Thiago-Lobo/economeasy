#pragma once

#define EZ_CURRENT_SENSOR_PORT A0
#define EZ_CURRENT_SENSOR_SENSITIVITY 0.1f // (V / A)
#define EZ_CURRENT_SENSOR_CALIBRATION_SIZE 10
#define EZ_CURRENT_SENSOR_SAMPLE_TIME 100000 // (us)
#define EZ_CURRENT_SENSOR_ENABLE_CALIBRATION

float current_sensor_offset = 0.0f;

void ez_current_sensor_initialize();
void ez_current_sensor_calibrate();
float ez_current_sensor_sample();
float ez_current_sensor_read();
