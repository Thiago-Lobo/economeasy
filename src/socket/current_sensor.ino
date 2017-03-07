#include "current_sensor.h"

void ez_current_sensor_initialize()
{
	ez_println("Initializing current sensor.");
#ifdef EZ_CURRENT_SENSOR_ENABLE_CALIBRATION
	ez_current_sensor_calibrate();
#endif
}

void ez_current_sensor_calibrate()
{
	ez_println("Starting current sensor calibration.");
	float total = 0.0f;

	for (unsigned i = 0; i < EZ_CURRENT_SENSOR_CALIBRATION_SIZE; i++)
	{	
		total += ez_current_sensor_sample();
	}

	current_sensor_offset = total / EZ_CURRENT_SENSOR_CALIBRATION_SIZE;
	ez_println("Current sensor calibrated.");
	ez_print("Offset: ");
	ez_println(current_sensor_offset);
}

float ez_current_sensor_sample()
{
	float result;

	int read_value;
	int max_value = 0;
	int min_value = 1023;

	unsigned long start_time = ez_time_micros();	
	while ((ez_time_micros() - start_time) < EZ_CURRENT_SENSOR_SAMPLE_TIME)
	{
		read_value = ez_adc(EZ_CURRENT_SENSOR_PORT);
		
		if (read_value > max_value) 
		{
		   max_value = read_value;
		}
		
		if (read_value < min_value) 
		{
		   min_value = read_value;
		}
	}
	result = ADC_TO_VOLT(max_value - min_value) - current_sensor_offset;

	return result;

	// float result;

	// float read_value;
	// float sum = 0.0f;
	// unsigned samples = 0;

	// unsigned long start_time = ez_time_micros();
	
	// while ((ez_time_micros() - start_time) < EZ_CURRENT_SENSOR_SAMPLE_TIME)
	// {
	// 	// read_value = (float) ez_adc(EZ_CURRENT_SENSOR_PORT) - (1 << ADC_RESOLUTION) / 2.0f;
	// 	read_value = (float) ez_adc(EZ_CURRENT_SENSOR_PORT);
	// 	sum += EZ_SQR(read_value);
	// 	samples += 1;
	// }

	// result = ADC_TO_VOLT(EZ_SQRT(sum / samples)) - current_sensor_offset;

	// return result;
}

float ez_current_sensor_read()
{
	float voltage = ez_current_sensor_sample();
	float voltage_rms = voltage / 2.0f * 0.707f;
	float amps_rms = voltage_rms / EZ_CURRENT_SENSOR_SENSITIVITY;

	return EZ_MAX(amps_rms, 0.0f);
}
