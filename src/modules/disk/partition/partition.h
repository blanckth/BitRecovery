#ifndef PARTITION_H
#define PARTITION_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../disk.h"

// Partition Types
typedef enum {
    PARTITION_TYPE_UNKNOWN,
    PARTITION_TYPE_MBR,
    PARTITION_TYPE_GPT
} PartitionTableType;

// Partition Entity
typedef struct {
    uint64_t start_lba;
    uint64_t end_lba;
    uint64_t size_in_sectors;
    uint8_t type;
    char name[64]; // در GPT میشه پرش کرد، در MBR خالی
} PartitionEntry;

// Partition Table
typedef struct {
    PartitionTableType type;
    size_t entry_count;
    PartitionEntry entries[128];  // ماکزیمم 128 برای GPT
} PartitionTable;

// تابع‌ها
int analyze_partition_table(DiskHandle *disk, PartitionTable *ptable);
void print_partition_table(const PartitionTable *ptable);

#endif
