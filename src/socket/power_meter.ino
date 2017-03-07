#include "power_meter.h"

void ez_power_meter_initialize()
{
	ez_println("Initializing power meter.");
	ez_moving_average_initialize(&pow_meter_current_average, EZ_POW_METER_MOVING_AVERAGE_SIZE);
}

void ez_power_meter_read()
{
	// Avoid erroneous initial integration step
	if (pow_meter_last_current_reading == 0)
	{
		pow_meter_last_current_reading = ez_time_micros();
		return;
	}

	// Compute moving average of sampled current
	ez_moving_average_push(&pow_meter_current_average, ez_current_sensor_read() * pow_meter_mains_voltage);
	
	// Update timer and calculate elapsed seconds
	unsigned long now = ez_time_micros();
	float seconds = (now - pow_meter_last_current_reading) / 1000000.0f;
	float hours = seconds / 3600.0f;
	pow_meter_last_current_reading = now;

	// Convert W to kWh
	pow_meter_total_power += hours * pow_meter_current_average.average / 1000.0f;

	ez_println(pow_meter_total_power, 16);

	// (pow_meter_current_average.average < EZ_POW_METER_NOISE_FLOOR) ? ez_println(0.0f) : ez_println(pow_meter_current_average.average);
}

