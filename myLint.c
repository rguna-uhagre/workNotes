#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    FILE *f = fopen(argv[1], "rb+");
    if (!f) {
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = malloc(size);
    if (!buf) {
        fclose(f);
        return 1;
    }

    fread(buf, 1, size, f);

    /* Naive in-place replacement */
    for (long i = 0; i < size - 1; i++) {
        if (buf[i] == ' ' && buf[i + 1] == ' ') {
            buf[i]     = ' ';
            buf[i + 1] = ' ';
            buf[i + 2] = ' ';
            i += 2;
        }
    }

    rewind(f);
    fwrite(buf, 1, size, f);

    fclose(f);
    free(buf);
    return 0;
}
