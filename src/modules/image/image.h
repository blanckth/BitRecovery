// src/modules/image/image.h

#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIGNATURE_NAME 32

typedef struct {
    const char *path;                   // Full path to image file
    const char *filename;               // Image File Name
    struct stat file_stat;              // Full stat information
    FILE *fp;                           // File pointer (standard I/O)
    time_t open_time;                   // Timestamp when file was opened
    bool opened;                        // File open status
    blksize_t sector_size;              // Usually 512 bytes
    int lps;                            // Resume point last_processed_sector
    uint8_t first_bytes[4096];          // First Block of image (e.g., for MBR/GPT check)
    char signature[MAX_SIGNATURE_NAME]; // File signature (label)
    bool is_gpt;                        // GPT partitioning scheme
    bool is_mbr;                        // MBR partitioning scheme
    bool has_bitlocker;                 // BitLocker presence flag
} ImageFile;

//struct stat {
//    dev_t     st_dev;         // Device ID of device containing file
//    ino_t     st_ino;         // Inode number
//    mode_t    st_mode;        // File type and mode (permissions)
//    nlink_t   st_nlink;       // Number of hard links
//    uid_t     st_uid;         // User ID of owner
//    gid_t     st_gid;         // Group ID of owner
//    dev_t     st_rdev;        // Device ID (if special file)
//    off_t     st_size;        // Total size, in bytes
//    blksize_t st_blksize;     // Block size for filesystem I/O
//    blkcnt_t  st_blocks;      // Number of 512B blocks allocated
//
//    // Time fields (may vary depending on libc/kernel version)
//    struct timespec st_atim;  // Last access time
//    struct timespec st_mtim;  // Last modification time
//    struct timespec st_ctim;  // Last status change time
//
//    // Alternative older versions (POSIX format, seconds only)
//    #define st_atime st_atim.tv_sec  // Last access time (legacy)
//    #define st_mtime st_mtim.tv_sec  // Last mod time (legacy)
//    #define st_ctime st_ctim.tv_sec  // Last status change time (legacy)
//};

// Function Prototypes
void extractFilename(const char *fullpath, char *filename);
int image_open(ImageFile *img, const char *path);
void image_close(ImageFile *img);
bool image_is_open(const ImageFile *img);
uint64_t image_get_size(const ImageFile *img);


#endif