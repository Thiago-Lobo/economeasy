#include "moving_average.h"

void ez_moving_average_initialize(ez_moving_average* data, unsigned size)
{
	data->size = size;
	data->values = (float*) malloc(sizeof(float) * size);
}

void ez_moving_average_push(ez_moving_average* data, float value)
{
	data->sum += value;

	if (!(data->entry_counter < data->size)) 
	{
		data->sum -= data->values[(data->entry_counter - data->size) % data->size];
	}

	data->values[data->entry_counter++ % data->size] = value;

	data->average = data->sum / ((data->entry_counter >= data->size) ? data->size : data->entry_counter);

	data->average -= data->average / data->size;
 	data->average += value / data->size;
}

void ez_moving_average_destroy(ez_moving_average* data)
{
	free(data->values);
}
