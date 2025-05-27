// sector_reader.c
#include "sector_reader.h"
#include "log.h"

int read_sector_by_number(FILE *fp, unsigned long sector_num, size_t sector_size, uint8_t *buffer) {
    if (fseek(fp, sector_num * sector_size, SEEK_SET) != 0) return -1;
    if (fread(buffer, 1, sector_size, fp) != sector_size) return -1;
    return 0;
}

int read_sector_by_offset(FILE *fp, unsigned long offset, size_t sector_size, uint8_t *buffer) {
    if (fseek(fp, offset, SEEK_SET) != 0) return -1;
    if (fread(buffer, 1, sector_size, fp) != sector_size) return -1;
    return 0;
}

int read_sectors_from(FILE *fp, size_t sector_size, unsigned long start_sector,
                      int (*callback)(uint8_t*, size_t, unsigned long)) {
    if (fseek(fp, start_sector * sector_size, SEEK_SET) != 0) return -1;
    uint8_t buffer[sector_size];
    size_t read_size;
    unsigned long sector_num = start_sector;
    while ((read_size = fread(buffer, 1, sector_size, fp)) == sector_size) {
        if (callback(buffer, read_size, sector_num++) != 0)
            break;
    }
    return 0;
}

//int read_sector(FILE *fp, unsigned long sector_num, unsigned char *buffer) {
//    if (fseek(fp, sector_num * SECTOR_SIZE, SEEK_SET) != 0) return -1;
//    size_t read = fread(buffer, 1, SECTOR_SIZE, fp);
//    return (read == SECTOR_SIZE) ? 0 : -2;
//}

// void print_sector_hex(const unsigned char *buffer, size_t size, unsigned long sector_num) {
//    printf("Sector %lu:\n", sector_num);
//    for (size_t i = 0; i < size; i++) {
//        printf("%02X ", buffer[i]);
//        if ((i + 1) % 16 == 0) printf("\n");
//    }
//    printf("\n");
//}
