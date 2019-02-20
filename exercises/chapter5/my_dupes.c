#include "my_dupes.h"
#include "limits.h"

int dup(int oldfd) {
    return fcntl(oldfd, F_DUPFD);
}

int dup2(int oldfd, int newfd) {

    if (newfd < 0) {
        errno = EBADF;
        return -1;
    }

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
