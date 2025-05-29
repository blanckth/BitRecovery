// /src/modules/disk/disk.h
#ifndef DISK_H
#define DISK_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include "../image/image.h"

#define SECTOR_SIZE 4096

typedef struct {
    int fd;
    const char *path;
    blksize_t block_size;
    blksize_t actual_size;
} DiskHandle;

// Initialize disk handle
DiskHandle *open_disk(ImageFile *img);

// Close disk
void close_disk(DiskHandle *disk);

#endif
