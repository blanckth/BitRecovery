#include "image.h"

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

// st_dev	شناسه دیوایسی که فایل روی آن قرار دارد
// st_ino	شماره inode فایل (یکتا در فایل‌سیستم)
// st_mode	نوع فایل و مجوزهای دسترسی (bitmask: S_IFREG, S_IFDIR, 0777 و ...)
// st_nlink	تعداد hard linkها
// st_uid	شناسه کاربری مالک فایل
// st_gid	شناسه گروه مالک فایل
// st_rdev	شناسه دیوایس برای special file (مثلاً device node)
// st_size	اندازه فایل (بر حسب بایت)
// st_blksize	اندازه بلوک‌های I/O برای بهینه‌سازی
// st_blocks	تعداد بلوک‌های اختصاص یافته (هر بلوک = 512 بایت)
// st_atime	آخرین زمان دسترسی (ثانیه از epoch)
// st_mtime	آخرین زمان ویرایش فایل
// st_ctime	آخرین تغییر در متادیتا (نه محتوا)

int image_info(ImageFile *img, const char *path) {
    if (!img) return 1; // Error 1 : Invalid Image file struct
    if (!path) return 2; // Error 2 : Invalid Filepath
    img->path = path; // Set Image Path
    struct stat st; // File Stat Struct Init
    const int statRes = image_stat(path, &st); // Proceed Stat on File
    if ( statRes != 0) return 3000+statRes; // Error 3000 : FStat Failed
    img->file_stat = st; // Set Image File Stat
    img->opened = false;
    img->sector_size = st.st_blksize;
    return 0; // No Error
}

int image_stat(const char *path, struct stat *st){
    int fd = open(path,O_RDONLY);
    if (fd < 0) return -1;
    int res = fstat(fd, st);
    close(fd);
    return res;
}

void image_close(ImageFile *img) {
    if (img && img->opened) {
        fclose(img->fp);
        img->opened = false;
    }
}

bool image_is_open(const ImageFile *img) {
    return img && img->opened;
}

uint64_t image_get_size(const ImageFile *img) {
    return img ? img->file_stat.st_size : 0;
}

