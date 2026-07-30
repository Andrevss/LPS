#include <stdio.h>
#include <stdint.h>
#include "logger.h"
#include "network.h"
#include "sensor.h"
#include "crypto.h"

static void system_init(void);
static void system_run(void);
static void system_shutdown(void);
static void handle_fatal(const char *msg);

int main(void) {
    system_init();
    system_run();
    system_shutdown();
    return 0;
}

static void system_init(void) {
    logger_init();
    log_info("System init");
    network_init();
    sensor_init();
    crypto_init();
}

static void system_run(void) {
    log_info("System run start");
    for (int i = 0; i < 3; ++i) {
        float t = sensor_read_temperature();
        char buf[64];
        snprintf(buf, sizeof(buf), "Temperature: %.2f", t);
        log_info(buf);

        uint8_t payload[8] = {0};
        int len = network_receive(payload, sizeof(payload));
        if (len > 0) {
            log_info("Network message received");
        } else {
            log_warn("No network message");
        }
    }
    log_info("System run end");
}

static void system_shutdown(void) {
    log_info("System shutdown");
    crypto_deinit();
    network_shutdown();
    logger_deinit();
}

static void handle_fatal(const char *msg) {
    log_error(msg);
    system_shutdown();
}
