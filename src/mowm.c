#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void launchApp(const char *appName) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp(appName, appName, NULL);
    }
}

void launchApps() {
    FILE *file = fopen("apps.conf", "r");
    if (file == 0) {
        fprintf(stderr, "Failed to open config file\n");
        return;
    }
    char appName[256];
    while (fgets(appName, sizeof(appName), file)) {
        // make the string "stop" at the first newline
        appName[strcspn(appName, "\n")] = '\0';
        if (appName[0] == '\0') {  // skip empty lines
            continue;
        }
        launchApp(appName);
        sleep(1);
    }
    fclose(file);
}

void handleKeyPress(Display *display, XEvent *event) {
    if (event->type == KeyPress) {
        KeySym key = XLookupKeysym(&event->xkey, 0);
        if (key == XK_Escape) {
            XCloseDisplay(display);
            exit(0);
        }
    }
}

void handleButtonPress(Display *display, XEvent *event) {
    if (event->type == ButtonPress) {
        printf("(%d, %d)", event->xbutton.x_root, event->xbutton.y_root);
        launchApp("xlogo");
    }
}

int main() {
    Display *display;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    Window root = DefaultRootWindow(display);
    Window child;

    // select input events on the root window
    XSelectInput(display, root, KeyPressMask | ButtonPressMask);

    XEvent event;

    int rootX, rootY, winX, winY;
    unsigned int mask;

    launchApps();
    printf("All apps launched\n");

    for (;;) {
        XNextEvent(display, &event);
        handleKeyPress(display, &event);
        handleButtonPress(display, &event);
    }
    XCloseDisplay(display);
    return 0;
}