#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define SECTOR_SIZE 512

typedef struct {
    uint8_t status;
    uint8_t chs_first[3];
    uint8_t type;
    uint8_t chs_last[3];
    uint32_t lba_start;
    uint32_t lba_size;
} __attribute__((packed)) MBRPartitionEntry;

int is_gpt(uint8_t *sector) {
    return sector[0x1FE] == 0x55 && sector[0x1FF] == 0xAA && sector[0x1C2] == 0xEE;
}

void parse_mbr(uint8_t *sector) {
    printf("Partition Table Type: MBR\n");
    for (int i = 0; i < 4; i++) {
        MBRPartitionEntry *part = (MBRPartitionEntry *)(sector + 446 + i * 16);
        if (part->type == 0) continue;
        printf("Partition %d:\n", i + 1);
        printf("  Type: 0x%02X\n", part->type);
        printf("  Start LBA: %u\n", part->lba_start);
        printf("  Size (sectors): %u\n", part->lba_size);
        printf("  Size (bytes): %u\n", part->lba_size * SECTOR_SIZE);
    }
}

void parse_gpt(FILE *f) {
    uint8_t sector[SECTOR_SIZE];
    fseek(f, SECTOR_SIZE, SEEK_SET); // GPT header is in LBA 1
    fread(sector, 1, SECTOR_SIZE, f);

    if (memcmp(sector, "EFI PART", 8) != 0) {
        printf("Invalid GPT Header.\n");
        return;
    }

    printf("Partition Table Type: GPT\n");
    uint32_t entry_lba = *(uint32_t *)(sector + 72);
    uint32_t entry_count = *(uint32_t *)(sector + 80);
    uint32_t entry_size = *(uint32_t *)(sector + 84);

    fseek(f, entry_lba * SECTOR_SIZE, SEEK_SET);
    for (uint32_t i = 0; i < entry_count; i++) {
        uint8_t entry[128];
        fread(entry, 1, entry_size, f);
        if (memcmp(entry, "\x00\x00\x00\x00\x00\x00\x00\x00", 8) == 0)
            continue; // empty

        uint64_t start_lba = *(uint64_t *)(entry + 32);
        uint64_t end_lba = *(uint64_t *)(entry + 40);

        printf("Partition %u:\n", i + 1);
        printf("  Start LBA: %" PRIu64 "\n", start_lba);
        printf("  End LBA: %" PRIu64 "\n", end_lba);
        printf("  Size (bytes): %" PRIu64 "\n", (end_lba - start_lba + 1) * SECTOR_SIZE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <disk image>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }

    uint8_t sector[SECTOR_SIZE];
    fread(sector, 1, SECTOR_SIZE, f);

    if (is_gpt(sector)) {
        parse_gpt(f);
    } else {
        parse_mbr(sector);
    }

    fclose(f);
    return 0;
}
