#include "tlpi_hdr.h"

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int out_flags = O_RDWR | O_CREAT | O_TRUNC, input, output;
    char buf[MAX_BUFFER_SIZE];
    ssize_t numRead;

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw */

    if (argc != 3 || strcmp(argv[1], "-h") == 0)
        usageErr("%s oldfile newfile\n", argv[0]);


    if ((input = open(argv[1], O_RDONLY)) == -1)
        errExit("failed to open %s", argv[1]);

    if ((output = open(argv[2], out_flags, mode)) == -1)
        errExit("failed to open %s", argv[2]);

    while ((numRead = read(input, buf, MAX_BUFFER_SIZE))) {
        if (numRead == -1)
            fatal("error on read of %s", argv[1]);

        int i = 0, j;
        while (i < numRead) {
            for (j = i; j < numRead; j++) {
                if (buf[j] == '\0') break;
            }
            size_t nonzeroBytes = (size_t) j - i;
            if (nonzeroBytes > 0) {
                if (write(output, buf + i, nonzeroBytes) != (ssize_t) nonzeroBytes)
                    errExit("failed to write");
            }

            for (i = j; j < numRead; j++) {
                if (buf[j] != '\0') break;
            }
            off_t zeroBytes = (off_t) j - i;
            if (zeroBytes > 0) {
                if (lseek(output, zeroBytes, SEEK_CUR) == -1)
                    errExit("failed to seek");
            }
            i = j;
        }
    }
    return 0;
}