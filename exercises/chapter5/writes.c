#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "-h") == 0)
        usageErr("%s filename\n", argv[1]);

    int flags = O_RDWR | O_CREAT | O_TRUNC, fd1, fd2, fd3;
    mode_t mode = S_IRUSR | S_IWUSR;

    if ((fd1 = open(argv[1], flags, mode)) == -1)
        errExit("failed to open a file");
    if ((fd2 = dup(fd1)) == -1)
        errExit("failed on dup");
    if ((fd3 = open(argv[1], O_RDWR)) == -1)
        errExit("failed on open");

    write(fd1, "Hello,", 6);
    write(fd2, " world", 6);
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "HELLO,", 6);
    write(fd3, "Gidday", 6);

    return 0;
}