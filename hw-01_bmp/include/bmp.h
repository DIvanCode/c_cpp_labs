#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BITS_PER_BYTE 8
#define BMP_HEADER_SIZE 0x0036


#define CORRECT_BF_TYPE 0x4d42
#define CORRECT_BF_OFF_BITS 0x0036

#define CORRECT_BI_PLANES 0x0001
#define CORRECT_BI_COMPRESSION 0x0000
#define CORRECT_BI_CLR_USED 0x0000
#define CORRECT_BI_CLR_IMPORTANT 0x0000
#define CORRECT_BI_BIT_COUNT 0x0018

#pragma pack(push)
#pragma pack(1)

typedef struct {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved_1;
    uint16_t bf_reserved_2;
    uint32_t bf_off_bits;

    uint32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    int32_t bi_x_pels_per_meter;
    int32_t bi_y_pels_per_meter;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
} BMPHeader;

#pragma pack(pop)

typedef struct {
    BMPHeader header;
    uint8_t *data;
} BMPImage;


BMPHeader read_bmp_header(FILE *file);
int check_bmp_header(BMPHeader bmp_header);
BMPImage read_bmp(FILE *file);

void write_bmp(FILE *file, BMPImage image);

BMPImage crop(BMPImage image, int32_t crop_x, int32_t crop_y, int32_t crop_width, int32_t crop_height);
BMPImage rotate(BMPImage image);


int _get_image_size_bytes(BMPHeader header);
int _get_image_row_size_bytes(BMPHeader header);
int _get_bytes_per_pixel(BMPHeader header);
int _get_padding(BMPHeader header);