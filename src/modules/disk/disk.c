#include "disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

DiskHandle *open_disk(const char *path) {
    DiskHandle *disk = malloc(sizeof(DiskHandle));
    if (!disk) return NULL;

    disk->fd = open(path, O_RDONLY);
    if (disk->fd < 0) {
        free(disk);
        return NULL;
    }

    disk->path = path;
    disk->sector_size = SECTOR_SIZE;
    return disk;
}

ssize_t read_sector(DiskHandle *disk, uint64_t sector_num, uint8_t *buffer) {
    off_t offset = sector_num * disk->sector_size;
    if (lseek(disk->fd, offset, SEEK_SET) == (off_t)-1) return -1;
    return read(disk->fd, buffer, disk->sector_size);
}

ssize_t read_sectors(DiskHandle *disk, uint64_t start_sector, size_t count, uint8_t *buffer) {
    off_t offset = start_sector * disk->sector_size;
    if (lseek(disk->fd, offset, SEEK_SET) == (off_t)-1) return -1;
    return read(disk->fd, buffer, disk->sector_size * count);
}

void close_disk(DiskHandle *disk) {
    if (!disk) return;
    close(disk->fd);
    free(disk);
}
