#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "util/types.h"

#define MAX_MESSAGE_LENGTH 1000

void Log_error(const char* format_str, ...);
void Log_warn(const char* format_str, ...);
void Log_success(const char* format_str, ...);

#endif  // LOG_H