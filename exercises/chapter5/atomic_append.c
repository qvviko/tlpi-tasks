#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    if (argc == 1 || argc > 5 || (argc == 2 && strcmp(argv[1], "-h") == 0)) {
        usageErr("%s filename num-bytes [x]\n", argv[0]);
    }
    int flags = O_RDWR | O_CREAT, fd_out;
    long n_bytes;
    Boolean x = FALSE;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw */

    if (argc == 4 && strcmp(argv[3], "x") == 0)
        x = TRUE;
    if (!x)
        flags |= O_APPEND;
    n_bytes = getLong(argv[2], GN_ANY_BASE, "bytes num");

    if ((fd_out = open(argv[1], flags, mode)) == -1)
        errExit("failed to open %s", argv[1]);

    for (int i = 0; i < n_bytes; ++i) {
        if (x)
            if (lseek(fd_out, 0, SEEK_END) == 1)
                errExit("seek failed");
        if (write(fd_out, "a", 1) == -1)
            errExit("write failed");
    }
    exit(EXIT_SUCCESS);
}