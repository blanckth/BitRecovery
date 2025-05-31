#ifndef PARTITION_H
#define PARTITION_H

#include "../sector/sector.h"
#include "../disk.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//typedef struct DiskHandle DiskHandle;

// struct DiskHandle; // forward declaration
// typedef struct disk DiskHandle;

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
    uint8_t type_guid[16];  // NEW: full GUID for GPT partitions
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
