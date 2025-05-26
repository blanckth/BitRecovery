#include "image_info.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static void detect_signature(ImageInfo *info) {
    memset(info->signature, 0, MAX_SIGNATURE_NAME);

    // Detect GPT (LBA 1 starts at 512)
    uint8_t gpt_header[8];
    fseek(info->fp, 512, SEEK_SET);
    fread(gpt_header, 1, 8, info->fp);
    if (memcmp(gpt_header, "EFI PART", 8) == 0) {
        strcpy(info->signature, "GPT Partition Table");
        info->is_gpt = true;
        return;
    }

    // Detect MBR
    uint8_t mbr[2];
    fseek(info->fp, 510, SEEK_SET);
    fread(mbr, 1, 2, info->fp);
    if (mbr[0] == 0x55 && mbr[1] == 0xAA) {
        strcpy(info->signature, "MBR Partition Table");
        info->is_mbr = true;
    }

    // Check BitLocker (in LBA 0 or later)
    uint8_t bitlocker_sig[8];
    fseek(info->fp, 0, SEEK_SET);
    fread(bitlocker_sig, 1, 8, info->fp);
    if (memcmp(bitlocker_sig, "-FVE-FS-", 8) == 0) {
        strcpy(info->signature, "BitLocker Volume");
        info->has_bitlocker = true;
    }
}

// Parse MBR Patiotion Table
void parse_mbr(uint8_t *sector) {
    printf("Partition Table Type: MBR\n");
    for (int i = 0; i < 4; i++) {
        MBRPartitionEntry *part = (MBRPartitionEntry *)(sector + 446 + i * 16);
        if (part->type == 0) continue;
        printf("Partition %d:\n", i + 1);
        printf("  Type: 0x%02X\n", part->type);
        printf("  Start LBA: %u\n", part->lba_start);
        printf("  Size (sectors): %u\n", part->lba_size);
        printf("  Size (bytes): %u\n", part->lba_size * SECTOR_SIZE);
    }
}

int init_image_info(ImageInfo *info, const char *filename, uint32_t sector_size) {
    memset(info, 0, sizeof(ImageInfo));
    info->filename = filename;
    info->sector_size = sector_size;
    FILE *fp = fopen(filename, "rb");
    if (!fp) return -1;
    info->fp = fp;
    struct stat st;
    if (stat(filename, &st) != 0) return -1;
    info->file_size = st.st_size;
    info->sector_count = st.st_size / sector_size;
    fread(info->first_bytes, 1, 16, fp);
    detect_signature(info);
    return 0;
}

void log_image_info(const ImageInfo *info) {
    log_message(LOG_LEVEL_INFO, "Image File: %s", info->filename);
    log_message(LOG_LEVEL_INFO, "Sector Size: %zu", info->sector_size);
    log_message(LOG_LEVEL_INFO, "File Size: %lu", info->file_size);
    log_message(LOG_LEVEL_INFO, "Total Sectors: %lu", info->sector_count);

    // log_info("First 16 bytes:");
    // for (int i = 0; i < 16; ++i)
    //     printf("%02X ", info->first_bytes[i]);
    // printf("\n");

    //
    if (strlen(info->signature) > 0)
        log_message(LOG_LEVEL_INFO, "Detected Signature: %s", info->signature);
    else
        log_message(LOG_LEVEL_INFO, "Signature: Unknown");

    if (info->is_gpt) log_message(LOG_LEVEL_INFO, "Partition Table: GPT");
    if (info->is_mbr) log_message(LOG_LEVEL_INFO, "Partition Table: MBR");
    if (info->has_bitlocker) log_message(LOG_LEVEL_INFO, "BitLocker Volume: Detected");
    
}

void close_image_info(ImageInfo *info) {
    if (info->fp) fclose(info->fp);
}
