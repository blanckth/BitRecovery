#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

static FILE *log_file = NULL;
static bool log_stdout = true;
static LogLevel current_min_level = LOG_LEVEL_INFO;

static const char *level_to_string(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG:   return "DEBUG";
        case LOG_LEVEL_INFO:    return "INFO";
        case LOG_LEVEL_WARN:    return "WARN";
        case LOG_LEVEL_ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}

const char *level_to_color(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG: return "\033[36m"; // Cyan
        case LOG_LEVEL_INFO:  return "\033[32m"; // Green
        case LOG_LEVEL_WARN:  return "\033[33m"; // Yellow
        case LOG_LEVEL_ERROR: return "\033[31m"; // Red
        default:              return "\033[0m";  // Reset
    }
}

int init_logger(const char *log_filename, bool to_stdout, LogLevel min_level) {
    log_file = fopen(log_filename, "a");
    if (!log_file) {
        perror("Failed to open log file");
        return -1;
    }
    log_stdout = to_stdout;
    current_min_level = min_level;
    return 0;
}

void set_log_level(LogLevel level) {
    current_min_level = level;
}

void log_message(LogLevel level, const char *format, ...) {
    if (level < current_min_level || !log_file) return;    

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", t);

    va_list args;
    va_start(args, format);
    va_list args_copy;
    va_copy(args_copy, args);

    // Write to file
    fprintf(log_file, "[%s] %s: ", timebuf, level_to_string(level));
    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");
    fflush(log_file);

    // Optional stdout Terminal output (colorized)
    if (log_stdout) {
        const char *color = level_to_color(level);
        printf("%s[%s] %s: ", color, timebuf, level_to_string(level));
        vprintf(format, args_copy);
        printf("\033[0m\n"); // Reset color
        
    }
    va_end(args_copy);
    va_end(args);
}

void log_close(void) {
    if (log_file) {
        fflush(log_file);
        fclose(log_file);
        log_file = NULL;
    }
}

int log_read(const char *log_filename) {
    FILE *f = fopen(log_filename, "r");
    if (!f) {
        perror("Failed to read log file");
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    fclose(f);
    return 0;
}

int find_last_processed_sector(const char *log_file) {
    FILE *fp = fopen(log_file, "r");
    if (!fp) return 0;

    char line[512];
    uint64_t last_sector = 0;
    bool found = false;

    while (fgets(line, sizeof(line), fp)) {
        char *pos = strstr(line, "SECTOR_DONE:");
        if (pos) {
            uint64_t sector;
            if (sscanf(pos, "SECTOR_DONE: %lu", &sector) == 1) {
                last_sector = sector;
                found = true;
            }
        }
    }
    fclose(fp);
    return found ? last_sector + 1 : 0; // resume from next sector
}
