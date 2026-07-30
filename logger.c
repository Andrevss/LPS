#include "logger.h"
#include <time.h>
#include <string.h>

static int g_logger_enabled = 0;

void logger_init(void) {
    g_logger_enabled = 1;
}

void logger_deinit(void) {
    g_logger_enabled = 0;
}

static void logger_do_log(const char *level, const char *msg) {
    if (!g_logger_enabled) return;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buf[64];
    if (tm) strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    else strncpy(buf, "unknown-time", sizeof(buf));
    printf("%s [%s] %s\n", buf, level, msg);
}

void log_info(const char *msg) {
    logger_do_log("INFO", msg);
}

void log_warn(const char *msg) {
    logger_do_log("WARN", msg);
}

void log_error(const char *msg) {
    logger_do_log("ERROR", msg);
}
