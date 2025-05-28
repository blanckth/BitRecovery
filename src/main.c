#include "utils/times/times.h"
#include "modules/disk/disk.h"
#include "modules/image/image.h"

#define DEFAULT_SECTOR_SIZE 512

void Usage(const char* progname);

int main(int argc, char* argv[]) {

    // Time Settings
    char tstrbuf[64];
    format_time(time(NULL),tstrbuf,64);                                                    // Time String Buffer
    printf("\nApplication Started at Local time: %s\n\n",tstrbuf);          // Print formatted time

    // Program Settings
    char* progname = argv[0];
    if (argc != 2){
        Usage(progname);
        return 1001; // App Error 1001 : Invalid Arguments
    }

    // Arguments Settings
    char* imgpath = argv[1];

    // Application Start
    printf("# Application Start Running : \t%s\t%s\n\n", progname, imgpath);

    // Loading Image File
    printf("# \tLoading Image File : \t\t%s\n\n", imgpath);
    ImageFile img;                                                      // Open ImageFile Object
    int initRes = image_open(&img, imgpath);                            // Read Image File Information
    if ( initRes != 0 ) {
        printf("# \t\tImage File Error : \t\t%d", initRes);
    } 
    
    // Loading Disk
    printf("# \t\tLoading Disk:\n");

    DiskHandle *disk = open_disk(imgpath, img.sector_size);             // Init DiskHandle Object
    if (!disk) {
        perror("Failed to open disk");
        return 1;
    }
    uint8_t buffer[img.file_stat.st_blksize];

    //if (read_sector(disk, 0, buffer) > 0) {
    //    printf("Read sector 0 successfully.\n");
    //} else {
    //    printf("Failed to read sector.\n");
    //}

    close_disk(disk);
    img.opened = false;
    return 0;
}
void Usage(const char* progname){
    printf("\n# Usage : %s [ImagePath/DiskPath]\n", progname);
    return;
}