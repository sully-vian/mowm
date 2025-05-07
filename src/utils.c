#include "utils.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void panic(const char *msg) {
    fprintf(stderr, msg);
    exit(EXIT_FAILURE);
}
