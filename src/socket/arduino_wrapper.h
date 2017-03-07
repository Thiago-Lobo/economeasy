#pragma once

#define DEFAULT_SERIAL Serial

#define ez_print DEFAULT_SERIAL.print
#define ez_println DEFAULT_SERIAL.println

#define ez_pwm(x, y) (analogWrite((x), (y)))
#define ez_time_micros() (micros())
#define ez_time_millis() (millis())
#define ez_time() (ez_time_micros() / 1000000.0f)
#define ez_delay(x) (delay((x)))

#define ADC_RESOLUTION 10
#define ADC_MAX_VOLTAGE 5.0f
#define ADC_TO_VOLT(x) ((float) (x) / ((float) (1 << ADC_RESOLUTION)) * ADC_MAX_VOLTAGE)
#define ez_adc(x) (analogRead((x)))
#define ez_adc_volts(x) (ADC_TO_VOLT(ez_adc((x))))

#define ON HIGH
#define OFF LOW
#define ez_make_output(x) (pinMode((x), OUTPUT))
#define ez_output_mode(x, y) (digitalWrite((x), (y)))

// Math stuff

#define EZ_PI 		3.14159265358979323f
#define EZ_TAU 		(2.0f * EZ_PI)
#define EZ_EULER 	2.71828182845904523f

#define EZ_DEG_FACTOR (180.0f / EZ_PI)
#define EZ_RAD_FACTOR (EZ_PI / 180.0f)
#define EZ_DEG(x) ((x) * EZ_DEG_FACTOR)
#define EZ_RAD(x) ((x) * EZ_RAD_FACTOR)

#define EZ_SQR(x) ((x) * (x))
#define EZ_POW(a, b) (powf(a, b))
#define EZ_MIN(a, b) ((a) < (b) ? (a) : (b))
#define EZ_MAX(a, b) ((a) > (b) ? (a) : (b))
#define EZ_ABS(x) ((x) >= 0.0f ? (x) : -(x))
#define EZ_SQRT(x) (sqrt(x))

#define EZ_QMF_SORT(a, b) {if ((a) > (b)) EZ_QMF_SWAP((a), (b));}
#define EZ_QMF_SWAP(a, b) {float temp = (a); (a) = (b); (b) = temp;}
#define EZ_QMF_COPY(p, v, n) {int i; for (i = 0; i < (n); i++) (p)[i] = (v)[i];}

float ez_quick_median_filter_3(float* vector)
{
    float p[3];
    EZ_QMF_COPY(p, vector, 3);

    EZ_QMF_SORT(p[0], p[1]); EZ_QMF_SORT(p[1], p[2]); EZ_QMF_SORT(p[0], p[1]) ;
    return p[1];
}

float ez_quick_median_filter_5(float* vector)
{
    float p[5];
    EZ_QMF_COPY(p, vector, 5);

    EZ_QMF_SORT(p[0], p[1]); EZ_QMF_SORT(p[3], p[4]); EZ_QMF_SORT(p[0], p[3]);
    EZ_QMF_SORT(p[1], p[4]); EZ_QMF_SORT(p[1], p[2]); EZ_QMF_SORT(p[2], p[3]);
    EZ_QMF_SORT(p[1], p[2]); 
    return p[2];
}

float ez_quick_median_filter_7(float* vector)
{
    float p[7];
    EZ_QMF_COPY(p, vector, 7);

    EZ_QMF_SORT(p[0], p[5]); EZ_QMF_SORT(p[0], p[3]); EZ_QMF_SORT(p[1], p[6]);
    EZ_QMF_SORT(p[2], p[4]); EZ_QMF_SORT(p[0], p[1]); EZ_QMF_SORT(p[3], p[5]);
    EZ_QMF_SORT(p[2], p[6]); EZ_QMF_SORT(p[2], p[3]); EZ_QMF_SORT(p[3], p[6]);
    EZ_QMF_SORT(p[4], p[5]); EZ_QMF_SORT(p[1], p[4]); EZ_QMF_SORT(p[1], p[3]);
    EZ_QMF_SORT(p[3], p[4]);
    return p[3];
}

float ez_quick_median_filter_9(float* vector)
{
    float p[9];
    EZ_QMF_COPY(p, vector, 9);

    EZ_QMF_SORT(p[1], p[2]); EZ_QMF_SORT(p[4], p[5]); EZ_QMF_SORT(p[7], p[8]);
    EZ_QMF_SORT(p[0], p[1]); EZ_QMF_SORT(p[3], p[4]); EZ_QMF_SORT(p[6], p[7]);
    EZ_QMF_SORT(p[1], p[2]); EZ_QMF_SORT(p[4], p[5]); EZ_QMF_SORT(p[7], p[8]);
    EZ_QMF_SORT(p[0], p[3]); EZ_QMF_SORT(p[5], p[8]); EZ_QMF_SORT(p[4], p[7]);
    EZ_QMF_SORT(p[3], p[6]); EZ_QMF_SORT(p[1], p[4]); EZ_QMF_SORT(p[2], p[5]);
    EZ_QMF_SORT(p[4], p[7]); EZ_QMF_SORT(p[4], p[2]); EZ_QMF_SORT(p[6], p[4]);
    EZ_QMF_SORT(p[4], p[2]);
    return p[4];
}

void ez_apply_median_filter_3(float* source, float* destination, int length)
{
    for (int k = 0; k < length; k++)
    {   
        float vector[3];
        for (int j = 0; j < 3; j++)
        {
            vector[j] = source[((k - 1 + j < 0) ? 0 : ((k - 1 + j >= length) ? length - 1 : (k - 1 + j)))];
        }
        destination[k] = ez_quick_median_filter_3(vector);
    }
}

void ez_apply_median_filter_5(float* source, float* destination, int length)
{
    for (int k = 0; k < length; k++)
    {   
        float vector[5];
        for (int j = 0; j < 5; j++)
        {
            vector[j] = source[((k - 2 + j < 0) ? 0 : ((k - 2 + j >= length) ? length - 1 : (k - 2 + j)))];
        }
        destination[k] = ez_quick_median_filter_5(vector);
    }
}

void ez_apply_median_filter_7(float* source, float* destination, int length)
{
    for (int k = 0; k < length; k++)
    {   
        float vector[7];
        for (int j = 0; j < 7; j++)
        {
            vector[j] = source[((k - 3 + j < 0) ? 0 : ((k - 3 + j >= length) ? length - 1 : (k - 3 + j)))];
        }
        destination[k] = ez_quick_median_filter_7(vector);
    }
}

void ez_apply_median_filter_9(float* source, float* destination, int length)
{
    for (int k = 0; k < length; k++)
    {   
        float vector[9];
        for (int j = 0; j < 9; j++)
        {
            vector[j] = source[((k - 4 + j < 0) ? 0 : ((k - 4 + j >= length) ? length - 1 : (k - 4 + j)))];
        }
        destination[k] = ez_quick_median_filter_9(vector);
    }
}
