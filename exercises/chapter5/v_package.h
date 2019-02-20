//
// Created by vlad on 20.02.19.
//

#ifndef TLPI_TASKS_V_PACKAGE_H

#include "tlpi_hdr.h"
#include "sys/uio.h" /*for iovec structure */

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt);

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt);

size_t count_iovec_bytes(const struct iovec *iov, int iovcnt);

#define TLPI_TASKS_V_PACKAGE_H

#endif //TLPI_TASKS_V_PACKAGE_H
