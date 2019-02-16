#include "tlpi_hdr.h"

#define STDIN 0
#define STDOUT 1
#define MAX_BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    int opt, maxLen = 4, curLen = 1;
    ssize_t num_read;
    int *fds = malloc(maxLen * sizeof(int));
    char buffer[MAX_BUFFER_SIZE];
    fds[curLen] = STDOUT; /* First output is going to the stdout */
    Boolean append = FALSE;
    int flags = O_WRONLY | O_CREAT;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw */

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s [options] filename", argv[0]);
    }
    while ((opt = getopt(argc, argv, ":a")) != -1) {
        switch (opt) {
            case 'a':
                append = TRUE;
                break;
            case '?':
                usageError("Unrecognized option", optopt, "Usage: %s [-a] [filename] [filename]...", argv[0]);
            default:
                fatal("Unexpected case in switch()");
        }
    }

    if (append) {
        flags |= O_APPEND;

        // This might be useless
        int stdout_flags = fcntl(STDOUT, F_GETFL);
        if (stdout_flags == -1) {
            errExit("fcntl get flags of stdout");
        }
        stdout_flags |= O_APPEND;
        if (fcntl(STDOUT, F_SETFL, stdout_flags) == -1) {
            errExit("fcntl set flags on stdout");
        }
    }

    while (argc != optind) {
        if (curLen == maxLen) {
            maxLen *= 2;
            fds = realloc(fds, (maxLen * sizeof(int)));
        }

        fds[curLen] = open(argv[optind], flags, mode);
        if (fds[curLen] == -1) {
            errExit("open failed on file %s", argv[optind]);
        }

        curLen++;
        optind++;
    }

    while ((num_read = read(STDIN, buffer, MAX_BUFFER_SIZE))) {
        if (num_read == -1) {
            errExit("fail on read");
        }
        for (int fd_n = 0; fd_n < curLen; ++fd_n) {
            if (write(fds[curLen], buffer, (size_t) num_read) == -1) {
                errExit("fail on write");
            }
        }
    }
    return 0;
}