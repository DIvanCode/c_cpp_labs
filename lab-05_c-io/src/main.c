#include "clist.h"
#include "point_list.h"

#include <stdio.h>
#include <string.h>

void make_int(int *x) {
    if ((*x) & 0x00800000) {
        (*x) |= 0xff000000;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Unknown type\n");
        return 0;
    }

    char *type = argv[1];
    char *infile = argv[2];
    char *action = argv[3];

    intrusive_list_t l;
    init_list(&l);

    if (strcmp(type, "loadtext") == 0) {
        FILE *fin = fopen(infile, "r");

        int x, y;
        while (fscanf(fin, "%d %d", &x, &y) != -1) {
            add_point(&l, x, y);
        }

        fclose(fin);
    } else if (strcmp(type, "loadbin") == 0) {
        FILE *fin = fopen(infile, "rb");

        int x = 0, y = 0;
        while (fread(&x, 3, 1, fin) != 0 &&
                fread(&y, 3, 1, fin) != 0) {
            make_int(&x);
            make_int(&y);
            add_point(&l, x, y);
            x = 0, y = 0;
        }

        fclose(fin);
    } else {
        printf("Unknown type\n");
        return 0;
    }

    if (strcmp(action, "count") == 0) {
        int cnt = 0;
        apply(&l, count, &cnt);
        printf("%d\n", cnt);
    } else if (strcmp(action, "savetext") == 0) {
        if (argc < 5) {
            printf("Missing out file\n");
            return 0;
        }

        char *outfile = argv[4];

        FILE *fout = fopen(outfile, "w");

        apply(&l, savetext, fout);

        fclose(fout);
    } else if (strcmp(action, "savebin") == 0) {
        if (argc < 5) {
            printf("Missing out file\n");
            return 0;
        }

        char *outfile = argv[4];

        FILE *fout = fopen(outfile, "wb");

        apply(&l, savebin, fout);

        fclose(fout);
    } else if (strcmp(action, "print") == 0) {
        if (argc < 5) {
            printf("Missing print format\n");
            return 0;
        }

        char *format = argv[4];
        apply(&l, print, format);
        printf("\n");
    } else {
        printf("Unknown action\n");
        return 0;
    }

    remove_all_points(&l);

    return 0;
}
