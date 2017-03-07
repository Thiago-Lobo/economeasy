#include "voltage_sensor.h"

void ez_voltage_sensor_initialize()
{
	ez_println("Initializing voltage sensor.");
}

float ez_voltage_sensor_sample()
{
	float result;

	unsigned long read_value;
	unsigned long sum = 0;
	unsigned samples = 0;

	unsigned long start_time = ez_time_micros();	
	
	while ((ez_time_micros() - start_time) < EZ_VOLTAGE_SENSOR_SAMPLE_TIME)
	{
		read_value = ez_adc(EZ_VOLTAGE_SENSOR_PORT);
		
		sum += read_value * read_value;
		samples += 1;
	}
	
	result = (float) sum / samples;
	
	return result;
}

float ez_voltage_sensor_read()
{
	float voltage = ez_voltage_sensor_sample();
	float voltage_rms_scaled = voltage * EZ_VOLTAGE_SENSOR_SENSITIVITY;

	return voltage_rms_scaled;	
}
