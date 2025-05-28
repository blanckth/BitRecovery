#include "disk.h"


DiskHandle *open_disk(const char *path, const blksize_t blksize) {
    DiskHandle *disk = malloc(sizeof(DiskHandle));
    if (!disk) return NULL;

    disk->fd = open(path, O_RDONLY);
    if (disk->fd < 0) {
        free(disk);
        return NULL;
    }
    disk->path = path;
    disk->block_size = blksize;
    return disk;
}

void close_disk(DiskHandle *disk) {
    if (!disk) return;
    close(disk->fd);
    free(disk);
}
