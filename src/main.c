#include "utils/times/times.h"
#include "modules/image/image.h"
#include "modules/disk/disk.h"
#include "modules/disk/sector/sector.h"



#define DEFAULT_SECTOR_SIZE 512

void Usage(const char* progname);

int main(int argc, char* argv[]) {

    // Time Settings
    char tstrbuf[64];
    format_time(time(NULL),tstrbuf,64);                                                    // Time String Buffer
    printf("\nApplication Started at Local time: %s\n\n",tstrbuf);          // Print formatted time

    // Program Settings
    char* progname = argv[0];
    if (argc < 2 || argc > 5){
        Usage(progname);
        return 1001; // App Error 1001 : Invalid Arguments
    }

    // Arguments Settings
    char* imgpath = argv[1];

    // Application Start
    printf("# Application Start Running : \t%s\t%s\n#\n", progname, imgpath);

    // Loading Image File
    printf("# \tLoading Image File : \t\t%s\n#\n", imgpath);
    ImageFile img;                                                      // Open ImageFile Object
    int initRes = image_open(&img, imgpath);                            // Read Image File Information
    if ( initRes != 0 ) {
        printf("\t\tImage File Error : \t\t%d", initRes);
    } 

    // Close Image File
    image_close(&img);
    
    // Loading Disk
    printf("# \tLoading Disk:\n");

    DiskHandle *disk = open_disk(&img);             // Init DiskHandle Object
    if (!disk) {
        perror("\t\tFailed to open disk");
        return 1;
    }
    printf("# \t\tLoading Sectors:\n");

    uint64_t cur_sector_num = (argc > 2) ? strtoull(argv[2], NULL, 10) : img.lps;
    uint64_t cur_sector_size = (argc > 3) ? strtoull(argv[3], NULL, 10) : disk->block_size;
    uint64_t cur_sector_count = (argc > 4) ? strtoull(argv[4], NULL, 10) : 1;

    uint8_t buffer[cur_sector_size * cur_sector_count];


    // size_t readRes = read_sector(disk, cur_sector_num, cur_sector_size, buffer);
    size_t readRes = read_sectors(disk, cur_sector_num, cur_sector_size, cur_sector_count, buffer);

    if (readRes > 0) {
        printf("# \t\t\tRead sector %llu successfully.\n",(unsigned long long)cur_sector_num);
    } else {
        printf("\t\t\tFailed to read sector : %llu\n",(unsigned long long)cur_sector_num);
    }
    print_sector(buffer,cur_sector_size,cur_sector_num,cur_sector_count);
    

    close_disk(disk);
    img.opened = false;
    return 0;
}
void Usage(const char* progname){
    printf("\n# Usage : %s [ImagePath/DiskPath]\n", progname);
    return;
}