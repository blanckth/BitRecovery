#include <stdio.h>
#include "modules/disk/disk.h"

int main() {
    DiskHandle *disk = open_disk("/dev/sdX"); // مسیر دستگاه یا ایمیج RAW
    if (!disk) {
        perror("Failed to open disk");
        return 1;
    }

    uint8_t buffer[SECTOR_SIZE];
    if (read_sector(disk, 0, buffer) > 0) {
        printf("Read sector 0 successfully.\n");
    } else {
        printf("Failed to read sector.\n");
    }

    close_disk(disk);
    return 0;
}
