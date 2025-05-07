#include "apps.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

void launchApp(const char *appName) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp(appName, appName, NULL);
    }
}

void launchApps(const char *configFile) {
    FILE *file = fopen(configFile, "r");
    if (file == 0) {
        panic("Failed to open config file");
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