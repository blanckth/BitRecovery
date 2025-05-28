#include "sector.h"

size_t read_sector(DiskHandle *disk, uint64_t sector_num, uint8_t *buffer) {
    off_t offset = sector_num * disk->sector_size;
    if (lseek(disk->fd, offset, SEEK_SET) == (off_t)-1) return -1;
    return read(disk->fd, buffer, disk->sector_size);
}

size_t read_sectors(DiskHandle *disk, uint64_t start_sector, size_t count, uint8_t *buffer) {
    off_t offset = start_sector * disk->sector_size;
    if (lseek(disk->fd, offset, SEEK_SET) == (off_t)-1) return -1;
    return read(disk->fd, buffer, disk->sector_size * count);
}

// Print Sector Hex
int sector_prt_hex( *img, const char *path){
    BlockBit 



} 
