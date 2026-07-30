#include "sensor.h"
#include <stdlib.h>

static float g_temp_offset = 0.0f;
static float g_pressure_offset = 0.0f;

void sensor_init(void) {
    g_temp_offset = 0.0f;
    g_pressure_offset = 0.0f;
}

float sensor_read_temperature(void) {
    /* Simulate a temperature reading */
    float base = 25.0f + (float)(rand() % 100) / 100.0f;
    return base + g_temp_offset;
}

float sensor_read_pressure(void) {
    float base = 1013.25f + (float)(rand() % 50) / 10.0f;
    return base + g_pressure_offset;
}

void sensor_calibrate(void) {
    /* Apply a small calibration offset */
    g_temp_offset = -0.2f;
    g_pressure_offset = 0.5f;
}
