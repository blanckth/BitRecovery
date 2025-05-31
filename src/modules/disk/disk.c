#include "disk.h"
#include "../image/image.h"
//#include "partition/partition.h"

// Initialize disk handle
DiskHandle *open_disk(ImageFile *img) {
    DiskHandle *disk = malloc(sizeof(DiskHandle));
    if (!disk) return NULL;
    
    disk->fd = open(img->path, O_RDONLY);
    if (disk->fd < 0) {
        free(disk);
        return NULL;
    }
    size_t actual_size = 0;
    unsigned int soft_block_size = 0, logical_block_size = 0, physical_block_size = 0;
    int rcs = ioctl(disk->fd, BLKBSZGET, &soft_block_size);
    int rcl = ioctl(disk->fd, BLKSSZGET, &logical_block_size);
    int rcp = ioctl(disk->fd, BLKPBSZGET, &physical_block_size);
    disk->path = img->path;
    disk->block_size = img->sector_size ? img->sector_size : 512;

    printf("#\n# \t\tDisk Metadata:\n");
    printf("# \t\t\tDisk Path: %s\n",disk->path);
    printf("# \t\t\tDisk Name: %s\n",img->filename);
    printf("# \t\t\tDisk File Descriptor: %d\n",disk->fd);
    printf("# \t\t\tSoft block size: %u\n", soft_block_size);
    printf("# \t\t\tLogical block size: %u\n", logical_block_size);
    printf("# \t\t\tPhysical block size: %u\n", physical_block_size);
    printf("# \t\t\tDisk Block Size: %ld\n#\n",disk->block_size);

    

    return disk;
}

void close_disk(DiskHandle *disk) {
    if (!disk) return;
    close(disk->fd);
    free(disk);
}

