#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

void logger_init(void);
void logger_deinit(void);
void log_info(const char *msg);
void log_warn(const char *msg);
void log_error(const char *msg);

#endif // LOGGER_H
