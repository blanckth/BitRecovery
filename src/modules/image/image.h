// src/modules/image/image.h

#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_SIGNATURE_NAME 32

typedef struct {
    const char *path;                   // IMAGE File Full Path
    struct stat file_stat;              // File Stat Full information
    FILE *fp;                           // Opened File Pointer
    time_t open_time;                   // File Open Time
    bool opened;                        // Open Status
    blksize_t sector_size;               // Default 512
    int last_processed_sector;          // Last Processed Sector
    uint8_t first_bytes[16];            // First 16 Bytes
    char signature[MAX_SIGNATURE_NAME]; // Signature
    bool is_gpt;                        // Image File has GPT Format
    bool is_mbr;                        // Image File has MBR Format
    bool has_bitlocker;                 // Image File has bitlocker Signature
} ImageFile;

// Prototype Functions
int image_info(ImageFile *img, const char *path);
int image_stat(const char *path, struct stat *st);
// int init_image_file(ImageFile *img, const char *path, uint64_t sector_size);
void close_image_file(ImageFile *img);
void log_image_file_info(const ImageFile *img);
int find_last_processed_sector(const char *log_path); // برای resume

#endif