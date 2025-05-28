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
#include <time.h>

#define MAX_SIGNATURE_NAME 32

typedef struct {
    const char *path;                   // Full path to image file
    struct stat file_stat;              // Full stat information
    FILE *fp;                           // File pointer (standard I/O)
    time_t open_time;                   // Timestamp when file was opened
    bool opened;                        // File open status
    blksize_t sector_size;              // Usually 512 bytes
    int last_processed_sector;          // Resume point
    uint8_t first_bytes[16];            // First 16 bytes of image (e.g., for MBR/GPT check)
    char signature[MAX_SIGNATURE_NAME]; // File signature (label)
    bool is_gpt;                        // GPT partitioning scheme
    bool is_mbr;                        // MBR partitioning scheme
    bool has_bitlocker;                 // BitLocker presence flag
} ImageFile;

// Function Prototypes
int image_open(ImageFile *img, const char *path);
void image_close(ImageFile *img);
bool image_is_open(const ImageFile *img);
uint64_t image_get_size(const ImageFile *img);


#endif