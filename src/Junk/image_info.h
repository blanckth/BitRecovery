#ifndef IMAGE_INFO_H
#define IMAGE_INFO_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define DEFAULT_SECTOR_SIZE 512
#define MAX_SIGNATURE_NAME 32

typedef struct {
    const char *filename;
    FILE *fp;
    uint64_t file_size;
    uint64_t sector_count;
    uint32_t sector_size;
    uint8_t first_bytes[16];
    char signature[MAX_SIGNATURE_NAME];
    bool is_gpt;
    bool is_mbr;
    bool has_bitlocker;
} ImageInfo;

typedef struct {
    uint8_t status;
    uint8_t chs_first[3];
    uint8_t type;
    uint8_t chs_last[3];
    uint32_t lba_start;
    uint32_t lba_size;
} __attribute__((packed)) MBRPartitionEntry;

int init_image_info(ImageInfo *info, const char *filename, uint32_t sector_size);
void parse_mbr(uint8_t *sector);
void log_image_info(const ImageInfo *info);
void close_image_info(ImageInfo *info);

#endif
