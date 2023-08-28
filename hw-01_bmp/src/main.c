#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int parse_int(char *str) {
    unsigned int res = 0;

    while (*str != '\0') {
        int digit = *str - '0';
        if (digit < 0 || digit > 9) exit(-1);

        res = res * 10 + digit;
        ++str;
    }

    return res;
}

int main(int argc, char **argv) {
    if (argc != 8) exit(-1);

    char *type = argv[1];
    char *in_file = argv[2];
    char *out_file = argv[3];
    int crop_x = parse_int(argv[4]);
    int crop_y = parse_int(argv[5]);
    int crop_width = parse_int(argv[6]);
    int crop_height = parse_int(argv[7]);

    if (strcmp(type, "crop-rotate") != 0) exit(-1);

    FILE *file_in = fopen(in_file, "rb");

    if (file_in == NULL) exit(-1);

    BMPImage image = read_bmp(file_in);

    fclose(file_in);

    BMPImage crop_image = crop(image, crop_x, crop_y, crop_width, crop_height);
    BMPImage rotate_image = rotate(crop_image);

    FILE *file_out = fopen(out_file, "wb");

    write_bmp(file_out, rotate_image);

    fclose(file_out);

    free(image.data);
    free(crop_image.data);
    free(rotate_image.data);

    return 0;
}