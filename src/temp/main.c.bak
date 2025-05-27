#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "log.h"
#include "image_info.h"
#include "sector_reader.h"

// Project Bitlocker Recovery Cracker
// By Salar Muhammadi

// Constant Variables
#define SECTOR_SIZE 512
#define LOG_FILE "scan.log"

// Function Prototype
void usage(const char *progname);
int print_sector_callback(uint8_t *buffer, size_t size, unsigned long sector_num);

// Type Define
typedef uint8_t BYTE;

// MAIN
int main(int argc, char *argv[]) {
    // Program Name
    char *progname = argv[0];
    // Logging
    int resume_sector = find_last_processed_sector(LOG_FILE);
    init_logger(LOG_FILE, true, LOG_LEVEL_INFO);
    // Remember Image Name
    char *imagename = argv[1];
    if (argc != 2) {
        usage(progname);
        return 1;
    }

    // Log Image File Info
    ImageInfo img;
    if (init_image_info(&img, imagename, SECTOR_SIZE) != 0) {
        fprintf(stderr, "Failed to open or analyze image file.\n");
        return 1;
    }
    log_image_info(&img);
    printf("Press Enter to continue...");
    getchar();

    unsigned char buffer[SECTOR_SIZE];
    size_t read;
    unsigned long sector_num = 0;
    
    read_sectors_from(img.fp, SECTOR_SIZE, resume_sector, print_sector_callback);
   
    close_image_info(&img);
    log_close();
    return 0;
}

// Print Usage
void usage(const char *progname)
{
    log_message(LOG_LEVEL_INFO, "Usage: %s <image_file>\n", progname);
    // fprintf(stderr, "Usage: %s <image_file>\n", progname);
}
//
int print_sector_callback(uint8_t *buffer, size_t size, unsigned long sector_num) {
    printf("Sector %lu:\n", sector_num);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n\n");
    log_message(LOG_LEVEL_INFO, "SECTOR_DONE: %lu", sector_num);
    printf("Press Enter...");
    getchar();
    return 0;
}
