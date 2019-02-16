#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {

    if (argc == 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s [options] filename", argv[0]);
    }
    return 0;
}