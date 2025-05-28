#include "image.h"
#include "./../../utils/times/times.h"

static int fetch_file_stat(FILE *fp, struct stat *st) {
    if (!fp || !st) return -1;
    int fd = fileno(fp);
    if (fd < 0) return -2;
    return fstat(fd, st);
}
int image_open(ImageFile *img, const char *path) {

    if (!img) return 1;                         // Error 1: Null ImageFile pointer
    if (!path) return 2;                        // Error 2: Null path input

    // Open image file
    FILE *fp = fopen(path, "rb");
    if (!fp) return 3;                          // Error 3: Failed to open file

    // Fetch file metadata
    struct stat st;
    if (fetch_file_stat(fp, &st) != 0) {
        fclose(fp);
        return 4;                               // Error 4: Failed to stat file
    }

    // Initialize ImageFile structure
    img->path = path;
    img->fp = fp;
    img->open_time = time(NULL);
    img->opened = true;
    img->file_stat = st;
    img->last_processed_sector = -1;
    img->sector_size = st.st_blksize;
    memset(img->first_bytes, 0, sizeof(img->first_bytes));
    // Read first 16 bytes of image file
    size_t read_bytes = fread(img->first_bytes, 1, sizeof(img->first_bytes), fp);
    if (read_bytes < sizeof(img->first_bytes)) {
        // Still usable, but warn in logs if needed
    }
    memset(img->signature, 0, sizeof(img->signature));
    img->is_mbr = (img->first_bytes[510] == 0x55 && img->first_bytes[511] == 0xAA)? true : false;
    img->is_gpt = (memcmp(&img->first_bytes[512], "EFI PART", 8) == 0)? true : false;
    img->has_bitlocker = (memcmp(&img->first_bytes[3], "-FVE-FS-", 8) == 0)? true : false;

    // Reset file position to start
    rewind(fp);

    // Print Results
    char tstrbuf[64];
    format_time(img->open_time, tstrbuf, sizeof(tstrbuf));
    printf("# \t\tFile Open Timestamp: %s\n", tstrbuf); // Timestamp when file was opened
    printf("# \t\tResume Sector: %d\n",img->last_processed_sector +1);
    printf("# \t\tSector Block Size: %d\n",img->sector_size);
    if (img->is_mbr)
    printf("# \t\tPartitioning scheme: MBR (Master Boot Record)\n");
    else if (img->is_gpt)
    printf("# \t\tPartitioning scheme: GPT (GUID Partition Table)\n");
    else
    printf("# \t\tPartitioning scheme: UNKNOWN\n");
    if (img->has_bitlocker)
    printf("# \t\tBitLocker presence: Found\n");
    else
    printf("# \t\tBitLocker presence: Not found\n");
    // Printing Image File Metadata
    printf("\n# \t\tFile Metadata:\n");
    printf("# \t\t\tInode: %lu\n", (unsigned long)img->file_stat.st_ino);
    printf("# \t\t\tDevice ID: %lu\n", (unsigned long)img->file_stat.st_dev);
    printf("# \t\t\tUID (Owner): %u\n", img->file_stat.st_uid);
    printf("# \t\t\tGID (Group): %u\n", img->file_stat.st_gid);
    printf("# \t\t\tFile Size: %ld bytes\n", (long)img->file_stat.st_size);
    printf("# \t\t\tPermissions: %o (octal)\n", img->file_stat.st_mode & 0777);
    format_time(img->file_stat.st_atime, tstrbuf, sizeof(tstrbuf));
    printf("# \t\t\tLast Access Time: %s\n", tstrbuf);
    format_time(img->file_stat.st_mtime, tstrbuf, sizeof(tstrbuf));
    printf("# \t\t\tLast Modification Time: %s\n", tstrbuf);
    format_time(img->file_stat.st_ctime, tstrbuf, sizeof(tstrbuf));
    printf("# \t\t\tLast Status Change Time: %s\n", tstrbuf);
    printf("# \t\t\tI/O Block Size: %ld bytes\n", (long)img->file_stat.st_blksize);
    printf("# \t\t\tBlock Count: %ld Blocks\n\n", (long)img->file_stat.st_blocks);
    // Printing Image File Metadata

    return 0; // Success
}

void image_close(ImageFile *img) {
    if (img && img->opened && img->fp) {
        fclose(img->fp);
        img->fp = NULL;
        img->opened = false;
        memset(&img->file_stat, 0, sizeof(img->file_stat));
    }
}

bool image_is_open(const ImageFile *img) {
    return img && img->opened;
}

uint64_t image_get_size(const ImageFile *img) {
    return img ? img->file_stat.st_size : 0;
}