#ifndef DISK_H
#define DISK_H

#include <stdint.h>
#include <stddef.h>

#define SECTOR_SIZE 512

typedef struct {
    int fd;
    const char *path;
    size_t sector_size;
} DiskHandle;

// Initialize disk handle
DiskHandle *open_disk(const char *path);

// Read a sector
ssize_t read_sector(DiskHandle *disk, uint64_t sector_num, uint8_t *buffer);

// Read multiple sectors
ssize_t read_sectors(DiskHandle *disk, uint64_t start_sector, size_t count, uint8_t *buffer);

// Close disk
void close_disk(DiskHandle *disk);

#endif
