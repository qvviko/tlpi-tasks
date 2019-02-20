#include "v_package.h"

size_t count_iovec_bytes(const struct iovec *iov, int iovcnt) {
    size_t bytes_count = 0;
    for (int i = 0; i < iovcnt; ++i) {
        bytes_count += iov[i].iov_len;
    }
    return bytes_count;
}

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt) {
    size_t total_bytes = count_iovec_bytes(iov, iovcnt);
    void *buf = malloc(total_bytes);

    ssize_t bytes_read = 0;
    if ((bytes_read = read(fd, buf, total_bytes)) == -1) {
        free(buf);
        return -1;
    }

    size_t offset = 0;
    for (int i = 0; i < iovcnt; ++i) {
        size_t to_write = min(iov[i].iov_len, bytes_read - offset);
        memcpy(iov[i].iov_base, buf + offset, to_write);
        offset += to_write;
    }
    free(buf);
    return bytes_read;
}

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt) {
    size_t total_bytes = count_iovec_bytes(iov, iovcnt);
    void *buf = malloc(total_bytes);

    size_t offset = 0;
    for (int i = 0; i < iovcnt; ++i) {
        memcpy(iov[i].iov_base, buf + offset, iov[i].iov_len);
        offset += iov[i].iov_len;
    }
    ssize_t bytes_written = write(fd, buf, total_bytes);
    if (bytes_written == -1)
        return -1;

    free(buf);
    return bytes_written;
}