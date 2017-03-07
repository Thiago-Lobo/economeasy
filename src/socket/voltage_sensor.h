#pragma once

#define EZ_VOLTAGE_SENSOR_PORT A1
#define EZ_VOLTAGE_SENSOR_SENSITIVITY 0.00051045265f
#define EZ_VOLTAGE_SENSOR_SAMPLE_TIME 2000000 // (us)

void ez_voltage_sensor_initialize();
float ez_voltage_sensor_sample();
float ez_voltage_sensor_read();
