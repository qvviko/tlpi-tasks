#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "-h") == 0)
        usageErr("%s filename\n", argv[1]);

    int flags = O_RDWR | O_APPEND, fd;
    if ((fd = open(argv[1], flags)) == -1)
        errExit("failed to open a file");
    if (lseek(fd, 0, SEEK_SET) == -1)
        errExit("failed seek");
    if (write(fd, "test", 4) == -1)
        errExit("failed write");
    close(fd);
    return 0;
}