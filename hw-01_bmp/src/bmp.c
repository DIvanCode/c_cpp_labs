#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

BMPHeader read_bmp_header(FILE *file) {
    BMPHeader header;

    if (fread(&header, sizeof(BMPHeader), 1, file) != 1) {
        exit(-1);
    }

    return header;
}

int check_bmp_header(BMPHeader bmp_header) {
    if (bmp_header.bf_type != CORRECT_BF_TYPE) return 0;
    if (bmp_header.bf_off_bits != CORRECT_BF_OFF_BITS) return 0;
    if (bmp_header.bi_planes != CORRECT_BI_PLANES) return 0;
    if (bmp_header.bi_compression != CORRECT_BI_COMPRESSION) return 0;
    if (bmp_header.bi_clr_used != CORRECT_BI_CLR_USED) return 0;
    if (bmp_header.bi_clr_important != CORRECT_BI_CLR_IMPORTANT) return 0;
    if (bmp_header.bi_bit_count != CORRECT_BI_BIT_COUNT) return 0;
    if (bmp_header.bi_height <= 0) return 0;
    if (bmp_header.bi_size_image != _get_image_size_bytes(bmp_header)) return 0;
    return 1;
}

BMPImage read_bmp(FILE *file) {
    BMPImage image;
    image.header = read_bmp_header(file);

    if (!check_bmp_header(image.header)) {
        exit(-1);
    }

    image.data = malloc(image.header.bi_size_image);

    if (fread(image.data, image.header.bi_size_image, 1, file) != 1) {
        exit(-1);
    }

    return image;
}

void write_bmp(FILE *file, BMPImage image) {
    fwrite(&image.header, sizeof(BMPHeader), 1, file);
    fwrite(image.data, image.header.bi_size_image, 1, file);
}

BMPImage crop(BMPImage image, int32_t crop_x, int32_t crop_y, int32_t crop_width, int32_t crop_height) {
    BMPImage crop_image = image;

    if (crop_x + crop_width > image.header.bi_width ||
        crop_y + crop_height > image.header.bi_height) {
        exit(-1);
    }

    crop_image.header.bi_width = crop_width;
    crop_image.header.bi_height = crop_height;
    crop_image.header.bi_size_image = _get_image_size_bytes(crop_image.header);
    crop_image.header.bf_size = BMP_HEADER_SIZE + crop_image.header.bi_size_image;

    crop_image.data = malloc(crop_image.header.bi_size_image);

    uint8_t *ptr = crop_image.data;

    for (int i = crop_y + crop_height - 1; i >= crop_y; --i) {
        for (int j = crop_x; j < crop_x + crop_width; ++j) {
            uint32_t img_offset = ((int) image.header.bi_height - i - 1) * _get_image_row_size_bytes(image.header) + j * _get_bytes_per_pixel(image.header);

            *ptr = *(image.data + img_offset);
            *(ptr + 1) = *(image.data + img_offset + 1);
            *(ptr + 2) = *(image.data + img_offset + 2);

            ptr += _get_bytes_per_pixel(image.header);
        }

        for (int p = 0; p < _get_padding(crop_image.header); ++p) {
            *ptr = 0x00;
            ++ptr;
        }
    }

    return crop_image;
}

BMPImage rotate(BMPImage image) {
    BMPImage rotate_image = image;

    rotate_image.header.bi_width = image.header.bi_height;
    rotate_image.header.bi_height = image.header.bi_width;

    rotate_image.header.bi_size_image = _get_image_size_bytes(rotate_image.header);
    rotate_image.header.bf_size = BMP_HEADER_SIZE + rotate_image.header.bi_size_image;

    rotate_image.data = malloc(rotate_image.header.bi_size_image);

    uint8_t *ptr = rotate_image.data;

    for (int j = (int) image.header.bi_width - 1; j >= 0; --j) {
        for (int i = (int) image.header.bi_height - 1; i >= 0; --i) {
            uint32_t img_offset = ((int) image.header.bi_height - i - 1) * _get_image_row_size_bytes(image.header) + j * _get_bytes_per_pixel(image.header);

            *ptr = *(image.data + img_offset);
            *(ptr + 1) = *(image.data + img_offset + 1);
            *(ptr + 2) = *(image.data + img_offset + 2);

            ptr += _get_bytes_per_pixel(image.header);
        }

        for (int p = 0; p < _get_padding(rotate_image.header); ++p) {
            *ptr = 0x00;
            ++ptr;
        }
    }

    return rotate_image;
}


int _get_image_size_bytes(BMPHeader header) {
    return _get_image_row_size_bytes(header) * header.bi_height;
}

int _get_image_row_size_bytes(BMPHeader header) {
    int bytes_per_row_without_padding = header.bi_width * _get_bytes_per_pixel(header);
    return bytes_per_row_without_padding + _get_padding(header);
}

int _get_bytes_per_pixel(BMPHeader header) {
    return header.bi_bit_count / BITS_PER_BYTE;
}

int _get_padding(BMPHeader header) {
    return (4 - (header.bi_width * _get_bytes_per_pixel(header)) % 4) % 4;
}