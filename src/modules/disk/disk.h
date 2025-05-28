#ifndef DISK_H
#define DISK_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SECTOR_SIZE 512

typedef struct {
    int fd;
    const char *path;
    blksize_t block_size;
} DiskHandle;

// Initialize disk handle
DiskHandle *open_disk(const char *path, const blksize_t blksize);

// Read a sector
size_t read_sector(DiskHandle *disk, uint64_t sector_num, uint8_t *buffer);

// Read multiple sectors
size_t read_sectors(DiskHandle *disk, uint64_t start_sector, size_t count, uint8_t *buffer);

// Close disk
void close_disk(DiskHandle *disk);

#endif
