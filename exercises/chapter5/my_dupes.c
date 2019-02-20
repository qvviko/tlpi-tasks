#include "my_dupes.h"
#include "limits.h"
#include "assert.h"

int dup(int oldfd) {
    return fcntl(oldfd, F_DUPFD, 0);
}

int dup2(int oldfd, int newfd) {

    if (newfd < 0 || newfd >= FOPEN_MAX) {
        errno = EBADF;
        return -1;
    };
    if (fcntl(oldfd, F_GETFL) == -1) {
        errno = EBADF;
        return -1;
    }
    if (newfd == oldfd) {
        return newfd;
    }
    close(newfd);
    return fcntl(oldfd, F_DUPFD, newfd);
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "-h") == 0) {
        usageErr("%s testfile\n", argv[0]);
    }
    int flags = O_RDWR | O_CREAT, fd_out, fd_dup;
    off_t seek_pos;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw */
    if ((fd_out = open(argv[1], flags, mode)) == -1) {
        errExit("failed to open");
    }
    assert(dup(-1) == -1);
    assert(dup(500) == -1);
    assert(dup(4) == -1);

    fd_dup = dup(fd_out);
    assert(fd_dup != -1);
    assert(fd_dup != fd_out);
    if ((seek_pos = lseek(fd_out, 10, SEEK_CUR)) == -1)
        errExit("failed to seek first");
    assert(lseek(fd_out, 0, SEEK_CUR) == seek_pos);
    assert(lseek(fd_dup, 0, SEEK_CUR) == seek_pos);

    assert(dup2(-1, 1) == -1);
    assert(dup2(500, 1) == -1);
    assert(dup2(500, 500) == -1);
    assert(dup2(STDIN_FILENO, STDIN_FILENO) == STDIN_FILENO);
    fd_dup = dup2(fd_out, 5);

    assert(fd_dup != -1);
    assert(fd_dup == 5);

    if ((seek_pos = lseek(fd_dup, 10, SEEK_CUR)) == -1)
        errExit("failed to seek second");
    assert(lseek(fd_out, 0, SEEK_CUR) == seek_pos);
    assert(lseek(fd_dup, 0, SEEK_CUR) == seek_pos);
    printf("Tests done\n");
}