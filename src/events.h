#ifndef EVENTS_H
#define EVENTS_H

#include <X11/Xlib.h>

Bool handleKeyPress(Display *display, XEvent *event);
void handleButtonPress(Display *display, XEvent *event);

#endif