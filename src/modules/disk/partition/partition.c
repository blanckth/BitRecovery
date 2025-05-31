// partition.c

#include <stdio.h>
#include <string.h>
#include "../disk.h"
#include "../sector/sector.h"
#include "partition.h"

#define GPT_HEADER_LBA 1
#define GPT_ENTRIES_LBA 2
#define MAX_GPT_ENTRIES 128

typedef struct {
    uint8_t signature[8];
    uint32_t revision;
    uint32_t header_size;
    uint32_t header_crc32;
    uint32_t reserved;
    uint64_t current_lba;
    uint64_t backup_lba;
    uint64_t first_usable_lba;
    uint64_t last_usable_lba;
    uint8_t disk_guid[16];
    uint64_t partition_entries_lba;
    uint32_t num_partition_entries;
    uint32_t size_of_partition_entry;
    uint32_t partition_entries_crc32;
} __attribute__((packed)) GptHeader;

typedef struct {
    uint8_t type_guid[16];
    uint8_t unique_guid[16];
    uint64_t start_lba;
    uint64_t end_lba;
    uint64_t attributes;
    uint16_t name[36];  // UTF-16
} __attribute__((packed)) GptEntry;


// Optional: ترجمه نوع پارتیشن در MBR
const char* get_mbr_partition_type_name(uint8_t type) {
    switch (type) {
        case 0x07: return "NTFS/ExFAT";
        case 0x0B: return "FAT32 CHS";
        case 0x0C: return "FAT32 LBA";
        case 0x83: return "Linux";
        case 0x82: return "Linux Swap";
        case 0xEE: return "GPT Protective";
        default:   return "Unknown";
    }
}

// Optional: بررسی ابتدایی GUID ها برای پارتیشن‌های شناخته‌شده
const char* get_gpt_partition_type_name(const uint8_t guid[16]) {
    if (!memcmp(guid,
        (uint8_t[]) {0xC1,0x2A,0x73,0x6D,0xF8,0xDA,0x11,0xD1,0xBA,0x4B,0x00,0xA0,0xC9,0x3E,0xC9,0x3B}, 16))
        return "EFI System";

    if (!memcmp(guid,
        (uint8_t[]) {0xE3,0xC9,0xE3,0x0C,0x0B,0x5C,0x4D,0x44,0xA8,0x03,0x41,0x5D,0xC2,0x07,0x8E,0xB4}, 16))
        return "BitLocker";

    return "Unknown GUID";
}

int read_utf16le_to_utf8(const uint16_t *src, size_t len, char *dest, size_t dest_size) {
    size_t j = 0;
    for (size_t i = 0; i < len && j < dest_size - 1; i++) {
        if (src[i] == 0) break;
        if (src[i] < 0x80) {
            dest[j++] = (char)src[i];
        } else {
            dest[j++] = '?';  // برای سادگی فقط کاراکترهای ASCII رو تبدیل می‌کنیم
        }
    }
    dest[j] = '\0';
    return 0;
}

int parse_gpt(DiskHandle *disk, PartitionTable *ptable) {
    uint8_t sector[512];

    // خواندن هدر GPT از LBA 1
    if (read_sector(disk, GPT_HEADER_LBA, sizeof(sector) ,sector) != 0)
        return -1;

    GptHeader *header = (GptHeader *)sector;

    if (memcmp(header->signature, "EFI PART", 8) != 0) {
        fprintf(stderr, "[-] Invalid GPT header signature.\n");
        return -1;
    }

    ptable->type = PARTITION_TYPE_GPT;
    ptable->entry_count = 0;

    size_t entry_count = header->num_partition_entries;
    size_t entry_size = header->size_of_partition_entry;
    if (entry_count > 128 || entry_size != 128) {
        fprintf(stderr, "[-] Unsupported GPT entry size or too many entries.\n");
        return -1;
    }

    for (size_t i = 0; i < entry_count && i < 128; i++) {
        uint8_t entry_data[128];
        if (read_sector(disk, GPT_ENTRIES_LBA + (i * entry_size) / 512, sizeof(sector), sector) != 0)
            break;

        size_t offset = (i * entry_size) % 512;
        memcpy(entry_data, &sector[offset], 128);
        GptEntry *entry = (GptEntry *)entry_data;

        if (entry->type_guid[0] == 0)
            continue; // Entry خالی

        PartitionEntry *pe = &ptable->entries[ptable->entry_count++];
        memcpy(pe->type_guid, entry->type_guid, 16);
        pe->start_lba = entry->start_lba;
        pe->end_lba = entry->end_lba;
        pe->size_in_sectors = entry->end_lba - entry->start_lba + 1;
        pe->type = 0xEE; // GPT marker
        uint16_t name_buf[36];
        memcpy(name_buf, entry->name, sizeof(name_buf));
        read_utf16le_to_utf8(name_buf, 36, pe->name, sizeof(pe->name));
        // read_utf16le_to_utf8(entry->name, 36, pe->name, sizeof(pe->name));
    }

    return 0;
}

int analyze_partition_table(DiskHandle *disk, PartitionTable *ptable) {
    uint8_t sector[512];
    size_t readres = read_sector(disk, 0, sizeof(sector), sector);
    // Read first sector (MBR or Protective MBR)
    if ( readres != 0) {
        fprintf(stderr, "[-] Failed to read sector 0\n");
        return -1;
    }

    // Check for MBR signature (0x55AA at offset 510)
    if (sector[510] != 0x55 || sector[511] != 0xAA) {
        fprintf(stderr, "[-] Invalid MBR signature\n");
        return -1;
    }

    // Check if this is GPT (protective MBR with type 0xEE)
    bool is_gpt = false;
    for (int i = 0; i < 4; i++) {
        uint8_t part_type = sector[446 + i * 16 + 4];
        if (part_type == 0xEE) {
            is_gpt = true;
            printf("# \t\t\tRead sector(s) successfully.\n");
            break;
        }
    }

    if (is_gpt) {
        ptable->type = PARTITION_TYPE_GPT;
        // مرحله بعدی: تجزیه‌ی GPT header و entries
        return parse_gpt(disk, ptable);
    } else {
        ptable->type = PARTITION_TYPE_MBR;
        // مرحله بعدی: تجزیه‌ی پارتیشن‌های MBR
        for (int i = 0; i < 4; i++) {
            uint8_t *entry = &sector[446 + i * 16];
            uint8_t part_type = entry[4];
            uint32_t start_lba = *(uint32_t *)&entry[8];
            uint32_t size = *(uint32_t *)&entry[12];

            if (part_type == 0x00 || size == 0)
                continue; // entry خالی

            PartitionEntry *pe = &ptable->entries[ptable->entry_count++];
            pe->start_lba = start_lba;
            pe->size_in_sectors = size;
            pe->end_lba = start_lba + size - 1;
            pe->type = part_type;
            pe->name[0] = '\0'; // در MBR اسمی وجود نداره
        }
    }

    return 0;
}

void print_partition_table(const PartitionTable *ptable) {
    printf("\n========== Partition Table ==========\n");
    printf("Patition Table Type: %s\n", 
           (ptable->type == PARTITION_TYPE_GPT) ? "GPT" :
           (ptable->type == PARTITION_TYPE_MBR) ? "MBR" : "Unknown");

    printf("Found %zu partition(s):\n\n", ptable->entry_count);
    printf("  # |   Start LBA   |    End LBA    |   Size (sectors)  | Type       | Name\n");
    printf("----+---------------+---------------+-------------------+------------+-----------------------------\n");

    for (size_t i = 0; i < ptable->entry_count; i++) {
        const PartitionEntry *p = &ptable->entries[i];

        const char *type_str = (ptable->type == PARTITION_TYPE_GPT)
            ? get_gpt_partition_type_name(p->type_guid) // NOTE: optional
            : get_mbr_partition_type_name(p->type);

        printf("%3zu | %13lu | %13lu | %17lu | %-10s | %s\n",
               i + 1, p->start_lba, p->end_lba, p->size_in_sectors,
               type_str, p->name);
    }

    printf("======================================\n\n");
}