#include "utils/times/times.h"
#include "modules/image/image.h"
#include "modules/disk/disk.h"
#include "modules/disk/sector/sector.h"
#include "modules/disk/partition/partition.h"




#define DEFAULT_SECTOR_SIZE 512
#define MAX_TIME_STRING_BUF 64
void Usage(const char* progname);

int main(int argc, char* argv[]) {

    // Time Settings
    char tstrbuf[MAX_TIME_STRING_BUF];
    format_time(time(NULL),tstrbuf,MAX_TIME_STRING_BUF);                                                    // Time String Buffer
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
    printf("# Application Start Running : ");
    for(int a = 0; a < argc; a++){
        printf("[ %s : %s ] ",
                          (a == 0)? "App" : 
                          (a == 1)? "Image":
                          (a == 2)? "First Sector":
                          (a == 3)? "Sector Size":
                          (a == 4)? "Sector Count": "UNKNOWN",
                          argv[a]);
    }
    printf("\n");

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
    
    printf("#\n# \t\tDisk Partition Table:\n");
    PartitionTable *ptable = malloc(sizeof(PartitionTable));
    if (!ptable) return NULL;
    int PartRes = analyze_partition_table(disk, ptable);
    if ( PartRes == 0 ) {
        printf("# \t\t\tPartition Table Found!\n");
        print_partition_table(ptable);
    }
    else
        printf("# \t\t\tPartition Table Not Found!\n");

    printf("# \t\tLoading Sectors:\n");


    // Init Sector Variables
    uint64_t cur_sector_num = img.lps;
    uint64_t cur_sector_size = disk->block_size;
    uint64_t cur_sector_count = 1;
    if (argc >= 3) cur_sector_num = strtoull(argv[2], NULL, 10)? strtoull(argv[2], NULL, 10) : img.lps;
    printf("# \t\t\tFirst Sector : %lu, ",cur_sector_num);
    if (argc >= 4) cur_sector_size = strtoull(argv[3], NULL, 10)? strtoull(argv[3], NULL, 10) : disk->block_size;
    printf("Sector Size : %lu, ",cur_sector_size);
    printf("Sector OFFSET : %lu, ",cur_sector_size * cur_sector_num);
    if (argc >= 5) cur_sector_count = strtoull(argv[4], NULL, 10) ? strtoull(argv[4], NULL, 10) : 1;
    printf("Sector Count : %lu, ",cur_sector_count);
    printf("Buffer Size : %lu\n",cur_sector_count * cur_sector_size);

    // Init Sector Buffer
    uint64_t total_buf_size = cur_sector_size * cur_sector_count;
    uint8_t* buffer = malloc(total_buf_size);
    if (!buffer) {
    perror("malloc failed");
    close_disk(disk);
    return 1;
}   
    // Read Sectors
    size_t readRes = read_sectors(disk, cur_sector_num, cur_sector_size, cur_sector_count, buffer);

    if (readRes > 0) {
        printf("# \t\t\tRead sector(s) successfully.\n");
    } else {
        printf("\t\t\tFailed to read sector(s)\n");
    }
    print_sector(buffer,cur_sector_size,cur_sector_num,cur_sector_count);
    
    free(buffer);
    close_disk(disk);
    img.opened = false;
    return 0;
}
void Usage(const char* progname){
    printf("\n# Usage : %s [ImagePath/DiskPath] [ [Sector Number] [ [Sector Size] [Sector Count] ] ]\n", progname);
    return;
}