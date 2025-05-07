#include "events.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "apps.h"
#include "utils.h"

Bool handleKeyPress(Display *display, XEvent *event) {
    if (event->type == KeyPress) {
        KeySym key = XLookupKeysym(&event->xkey, 0);
        return (key == XK_Escape);
    }
}

void handleButtonPress(Display *display, XEvent *event) {
    UNUSED(display);
    if (event->type == ButtonPress) {
        printf("(%d, %d)", event->xbutton.x_root, event->xbutton.y_root);
        launchApp("xlogo");
    }
}