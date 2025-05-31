#include "../disk.h"
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

// Read Sectors From To
size_t read_sectors(DiskHandle *disk, uint64_t sector_num, size_t sector_size,uint64_t sector_count, uint8_t *buffer){
    if (!disk || disk->fd < 0 || !buffer) return 0;
    off_t offset = sector_num * sector_size;
    if (lseek(disk->fd, offset, SEEK_SET) < 0) {
        perror("lseek failed");
        return 0;
    }
    ssize_t bytes_read = read(disk->fd, buffer, sector_size * sector_count);
    if (bytes_read < 0) {
        perror("read failed");
        return 0;
    }
    return (size_t)bytes_read;
}


void print_sector(const uint8_t *buffer, const size_t size, const uint64_t sector_num, const uint64_t sector_count) {
    if (!buffer || size == 0) return;
    uint64_t base_offset = sector_num * size;
    printf("# \t\t\tDumping %lu Sector(s) (%zu bytes):\n",sector_count, size);
    for ( size_t n = 0; n < sector_count; n++){
        printf("#%lu\n# \t\t\t\t============================ Sector %lu ============================\n",n+1, sector_num + n);
        for (size_t i = 0; i < size; i += BYTES_PER_LINE) {
        printf("# \t\t\t\t%08lx  ", (unsigned long)(base_offset + i + ( n * size )));

        // Hex bytes
        for (size_t j = 0; j < BYTES_PER_LINE; ++j) {
            if (i + j < size)
                printf("%02x ", buffer[i + j + (n * size)]);
            else
                printf("   ");
            if (j == 7) printf(" ");
        }

        printf("\t |\t");

        // ASCII representation
        for (size_t j = 0; j < BYTES_PER_LINE; ++j) {
            if (i + j < size) {
                uint8_t c = buffer[i + j + (n * size)];
                printf("%c", isprint(c) ? c : '.');
            } else {
                printf(" ");
            }
        }

        printf("\t|\n");
      }
    
        printf("#\n");
    }


}

// Print Sector Hex
// int sector_prt_hex( *img, const char *path){
    // at /sys/block/sda/queue/logical_block_size
    // cat /sys/block/sda/queue/physical_block_size
    
//     BlockBit *bb; = img

// }
