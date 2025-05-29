#include "sector.h"

// Read a sector
size_t read_sector(DiskHandle *disk, uint64_t sector_num, size_t sector_size, uint8_t *buffer){
    if (!disk || disk->fd < 0 || !buffer) return 0;
    off_t offset = sector_num * sector_size;
    if (lseek(disk->fd, offset, SEEK_SET) < 0) {
        perror("lseek failed");
        return 0;
    }
    ssize_t bytes_read = read(disk->fd, buffer, sector_size);
    if (bytes_read < 0) {
        perror("read failed");
        return 0;
    }
    return (size_t)bytes_read;
}


//size_t read_sectors(DiskHandle *disk, uint64_t start_sector, size_t count, uint8_t *buffer) {
//    off_t offset = start_sector * disk->sector_size;
//    if (lseek(disk->fd, offset, SEEK_SET) == (off_t)-1) return -1;
//    return read(disk->fd, buffer, disk->sector_size * count);
//}


void print_sector(const uint8_t *buffer, size_t size, uint64_t sector_num) {
    if (!buffer || size == 0) return;
    uint64_t base_offset = sector_num * size;
    printf("# \t\t\tDumping Sector (%zu bytes):\n", size);
    printf("#\n# \t\t\t\t============================ Sector %lu ============================\n", sector_num);

    for (size_t i = 0; i < size; i += BYTES_PER_LINE) {
        printf("# \t\t\t\t%08lx  ", (unsigned long)(base_offset + i));

        // Hex bytes
        for (size_t j = 0; j < BYTES_PER_LINE; ++j) {
            if (i + j < size)
                printf("%02x ", buffer[i + j]);
            else
                printf("   ");
            if (j == 7) printf(" ");
        }

        printf("\t |\t");

        // ASCII representation
        for (size_t j = 0; j < BYTES_PER_LINE; ++j) {
            if (i + j < size) {
                uint8_t c = buffer[i + j];
                printf("%c", isprint(c) ? c : '.');
            } else {
                printf(" ");
            }
        }

        printf("\t|\n");
    }

    printf("\n");
}
// Print Sector Hex
// int sector_prt_hex( *img, const char *path){
    // at /sys/block/sda/queue/logical_block_size
    // cat /sys/block/sda/queue/physical_block_size
    
//     BlockBit *bb; = img

// }
