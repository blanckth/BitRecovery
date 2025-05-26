// sector_reader.h
#ifndef SECTOR_READER_H
#define SECTOR_READER_H

#include <stdio.h>
#include <stdint.h>

int read_sector_by_number(FILE *fp, unsigned long sector_num, size_t sector_size, uint8_t *buffer);
int read_sector_by_offset(FILE *fp, unsigned long offset, size_t sector_size, uint8_t *buffer);
int read_sectors_from(FILE *fp, size_t sector_size, unsigned long start_sector,
                        int (*callback)(uint8_t*, size_t, unsigned long));

#endif
