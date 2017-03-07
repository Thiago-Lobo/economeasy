#include "current_sensor.h"
#include "voltage_sensor.h"
#include "moving_average.h"

#pragma once

#define EZ_POW_METER_MOVING_AVERAGE_SIZE 25
#define EZ_POW_METER_NOISE_FLOOR 4.0f

ez_moving_average pow_meter_current_average;

float pow_meter_total_power = 0.0f;

unsigned long pow_meter_last_current_reading = 0;
float pow_meter_mains_voltage = 123.0f;

void ez_power_meter_initialize();
void ez_power_meter_read();
