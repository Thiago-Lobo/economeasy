#pragma once

typedef struct ez_moving_average_def
{
	float sum = 0.0f;
	float* values;
	unsigned size = 0;
	float average = 0.0f;
	unsigned long entry_counter = 0;
} ez_moving_average;

void ez_moving_average_initialize(ez_moving_average* data, unsigned size);
void ez_moving_average_push(ez_moving_average* data, float value);
void ez_moving_average_destroy(ez_moving_average* data);
