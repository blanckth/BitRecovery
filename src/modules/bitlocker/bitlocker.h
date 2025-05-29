#ifndef BITRECOVERY_BITLOCKER_H
#define BITRECOVERY_BITLOCKER_H

#include <stdint.h>
#include <stddef.h>

#define MAX_SIG_HITS 1024

typedef struct {
    uint64_t offset;
    char signature[16];
} BitLockerSignatureHit;

typedef struct {
    BitLockerSignatureHit hits[MAX_SIG_HITS];
    size_t count;
} BitLockerScanResult;

void scan_bitlocker_signatures(int image_fd, BitLockerScanResult* result);

#endif // BITRECOVERY_BITLOCKER_H
