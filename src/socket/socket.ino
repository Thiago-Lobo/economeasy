#include "Arduino.h"

#include "arduino_wrapper.h"

#include "current_sensor.h"
#include "voltage_sensor.h"
#include "power_meter.h"

void setup() 
{
    Serial.begin(9600);
    ez_current_sensor_initialize();
	ez_voltage_sensor_initialize();
	ez_power_meter_initialize();
}

void loop()
{
	ez_power_meter_read();
}