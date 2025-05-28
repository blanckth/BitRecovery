#include <stdio.h>
#include <time.h>
#include "modules/disk/disk.h"
#include "modules/image/image.h"

#define SECTOR_SIZE 512

// void Usage(void);

int main(int argc, char* argv[]) {

    // Time Settings
    time_t timer = time(NULL);                                            // Current Time
    char tstrbuf[64];                                                     // Time String Buffer
    struct tm *local_time = localtime(&timer);                            // Local Time Structure
    if (local_time == NULL) {
        printf("Error converting time\n");
        return 1;
    }
    strftime(tstrbuf, sizeof(tstrbuf), "%Y-%m-%d %H:%M:%S", local_time);  // Local Time String Format
    printf("Application Started at Local time: %s\n\n",tstrbuf);          // Print formatted time

    // Program Settings
    char* progname = argv[0];
    if (argc != 2){
        // Usage();
        return 1001; // App Error 1001 : Invalid Arguments
    }
    char* imgpath = argv[1];
    printf("# Application Start Running : \t%s\t%s\n\n", progname, imgpath);
    printf("# \tLoading Image File : \t\t%s\n\n", imgpath);
    ImageFile img;                                                      // Init ImageFile Object
    int initRes = image_info(&img, imgpath);                            // Read Image File Information
    if ( initRes != 0 ) {
        printf("# \t\tImage File Error : \t\t%d", initRes);
    } 
    // Printing Image File Metadata
    printf("# \t\tFile Metadata:\n");
    printf("# \t\t\tInode: %lu\n", (unsigned long)img.file_stat.st_ino);
    printf("# \t\t\tDevice ID: %lu\n", (unsigned long)img.file_stat.st_dev);
    printf("# \t\t\tUID (Owner): %u\n", img.file_stat.st_uid);
    printf("# \t\t\tGID (Group): %u\n", img.file_stat.st_gid);
    printf("# \t\t\tFile Size: %ld bytes\n", (long)img.file_stat.st_size);
    printf("# \t\t\tPermissions: %o (octal)\n", img.file_stat.st_mode & 0777);
    timer = (long)img.file_stat.st_atime;
    local_time = localtime(&timer);
    strftime(tstrbuf, sizeof(tstrbuf), "%Y-%m-%d %H:%M:%S", local_time);
    printf("# \t\t\tLast Access Time: %s\n", tstrbuf);
    timer = (long)img.file_stat.st_mtime;
    local_time = localtime(&timer);
    strftime(tstrbuf, sizeof(tstrbuf), "%Y-%m-%d %H:%M:%S", local_time);
    printf("# \t\t\tLast Modification Time: %s\n", tstrbuf);
    timer = (long)img.file_stat.st_ctime;
    local_time = localtime(&timer);
    strftime(tstrbuf, sizeof(tstrbuf), "%Y-%m-%d %H:%M:%S", local_time);
    printf("# \t\t\tLast Status Change Time: %s\n", tstrbuf);
    printf("# \t\t\tI/O Block Size: %ld bytes\n", (long)img.file_stat.st_blksize);
    printf("# \t\t\tBlock Count: %ld Blocks\n", (long)img.file_stat.st_blocks);
    // Printing Image File Metadata

    getchar();
    printf("# \t\tLoading Disk:\n");

    DiskHandle *disk = open_disk(imgpath, img.sector_size);             // Init DiskHandle Object
    if (!disk) {
        perror("Failed to open disk");
        return 1;
    }
    img.opened = true;
    uint8_t buffer[img.file_stat.st_blksize];

    //if (read_sector(disk, 0, buffer) > 0) {
    //    printf("Read sector 0 successfully.\n");
    //} else {
    //    printf("Failed to read sector.\n");
    //}

    close_disk(disk);
    return 0;
}
