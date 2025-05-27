// log.h
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

// Log levels
typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} LogLevel;

// Initialize logger
int init_logger(const char *log_filename, bool to_stdout, LogLevel min_level);
void set_log_level(LogLevel level);
// Log a message
void log_message(LogLevel level, const char *format, ...);
// Resume Last Sector
int find_last_processed_sector(const char *log_file);
// Read logs from file (optional)
int log_read(const char *log_filename);
void log_close(void);

#endif