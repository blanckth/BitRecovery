#include "disk.h"
#include "./../image/image.h"

// Initialize disk handle
DiskHandle *open_disk(const char *path, const blksize_t blksize) {
    DiskHandle *disk = malloc(sizeof(DiskHandle));
    if (!disk) return NULL;

    disk->fd = open(path, O_RDONLY);
    if (disk->fd < 0) {
        free(disk);
        return NULL;
    }
    blksize_t actual_size = blksize;
#ifdef BLKSSZGET
    ioctl(disk->fd, BLKSSZGET, &actual_size);
#endif
    disk->actual_size = actual_size;
    disk->path = path;
    disk->block_size = blksize;

    printf("# \t\t\tDisk Metadata:\n\n");
    printf("# \t\t\t\tDisk File Descriptor: %d\n",disk->fd);
    return disk;
}

void close_disk(DiskHandle *disk) {
    if (!disk) return;
    close(disk->fd);
    free(disk);
}

// Read a sector
size_t read_sector(DiskHandle *disk, uint64_t sector_num, uint8_t *buffer){
    if (!disk || disk->fd < 0 || !buffer) return 0;
    off_t offset = sector_num * disk->block_size;
    if (lseek(disk->fd, offset, SEEK_SET) < 0) {
        perror("lseek failed");
        return 0;
    }
    ssize_t bytes_read = read(disk->fd, buffer, disk->block_size);
    if (bytes_read < 0) {
        perror("read failed");
        return 0;
    }
    return (size_t)bytes_read;
}
