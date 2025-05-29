#include "bitlocker.h"
#include "../image/image.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static const char* signatures[] = {
    "-FVE-FS-",
    "\xEB\x52\x90",
    "\xBE\xEF\xCA\xCE"
};

#define SIGNATURE_COUNT (sizeof(signatures)/sizeof(signatures[0]))

void scan_bitlocker_signatures(int image_fd, BitLockerScanResult* result) {
    result->count = 0;
    uint8_t buffer[512];
    uint64_t offset = 0;

    while (read(image_fd, buffer, 512) == 512) {
        for (size_t i = 0; i < SIGNATURE_COUNT; ++i) {
            size_t sig_len = strlen(signatures[i]);
            for (size_t j = 0; j < 512 - sig_len; ++j) {
                if (memcmp(buffer + j, signatures[i], sig_len) == 0) {
                    if (result->count < MAX_SIG_HITS) {
                        result->hits[result->count].offset = offset + j;
                        strncpy(result->hits[result->count].signature, signatures[i], 15);
                        result->hits[result->count].signature[15] = '\0';
                        result->count++;
                    }
                }
            }
        }
        offset += 512;
    }
}
