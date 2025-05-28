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
void print_sector(const uint8_t *buffer, size_t size, uint64_t base_offset) {
    if (!buffer || size == 0) return;

    printf("# Dumping Sector (%zu bytes):\n", size);
    for (size_t i = 0; i < size; i += BYTES_PER_LINE) {
        printf("%08lx  ", (unsigned long)(base_offset + i));

        // Hex bytes
        for (size_t j = 0; j < BYTES_PER_LINE; ++j) {
            if (i + j < size)
                printf("%02x ", buffer[i + j]);
            else
                printf("   ");
            if (j == 7) printf(" ");
        }

        printf(" |");

        // ASCII representation
        for (size_t j = 0; j < BYTES_PER_LINE; ++j) {
            if (i + j < size) {
                uint8_t c = buffer[i + j];
                printf("%c", isprint(c) ? c : '.');
            } else {
                printf(" ");
            }
        }

        printf("|\n");
    }

    printf("\n");
}
// Print Sector Hex
// int sector_prt_hex( *img, const char *path){
    // at /sys/block/sda/queue/logical_block_size
    // cat /sys/block/sda/queue/physical_block_size
    
//     BlockBit *bb; = img



} 
