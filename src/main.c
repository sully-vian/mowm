#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "apps.h"
#include "events.h"
#include "utils.h"

int main() {
    /* X11 connection */
    Display *display;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        panic("Cannot open display");
    }

    /* Display's root */
    Window root = DefaultRootWindow(display);

    // select input events on the root window
    XSelectInput(display, root, KeyPressMask | ButtonPressMask);

    XEvent event;

    launchApps("apps.conf");
    printf("All apps launched\n");

    Bool exit = False;
    while (!exit) {
        XNextEvent(display, &event);
        exit = handleKeyPress(display, &event);
        handleButtonPress(display, &event);
    }
    XCloseDisplay(display);
    return 0;
}