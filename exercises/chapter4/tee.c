#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    int opt, maxLen = 4, curLen = 1;
    FILE **fds = malloc(maxLen * sizeof(FILE *));
    fds[curLen] = stdout; /* First output is going to the stdout */
    Boolean append = FALSE;

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

    return 0;
}