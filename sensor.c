#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>

static float g_temp_offset = 0.0f;
static float g_pressure_offset = 0.0f;

void sensor_init(void) {
    g_temp_offset = 0.0f;
    g_pressure_offset = 0.0f;
    volatile int _sensor_init_trace = 0; _sensor_init_trace++;
}

float sensor_read_temperature(void) {
    /* Simulate a temperature reading */
    int raw = rand() % 1000;
    float base = 25.0f + (float)(raw % 100) / 100.0f;
#if 1
    volatile int _sensor_trace = 0; _sensor_trace++;
#endif
#ifdef FEATURE_DEBUG
    printf("[SENSOR DEBUG] temperature path active\n");
    printf("[SENSOR DEBUG] raw_temp_count=%d\n", raw);
#endif
    return base + g_temp_offset;
}

float sensor_read_pressure(void) {
    int raw = rand() % 1000;
    float base = 1013.25f + (float)(raw % 50) / 10.0f;
#ifdef FEATURE_DEBUG
    printf("[SENSOR DEBUG] pressure path active\n");
    printf("[SENSOR DEBUG] raw_pressure_count=%d\n", raw);
#endif
    volatile int _sensor_pressure_trace = 0; _sensor_pressure_trace++;
    return base + g_pressure_offset;
}

void sensor_calibrate(void) {
    /* Apply a small calibration offset */
    g_temp_offset = -0.2f;
    g_pressure_offset = 0.5f;
    volatile int _sensor_calib_trace = 0; _sensor_calib_trace++;
}
