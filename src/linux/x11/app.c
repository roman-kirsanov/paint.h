#include "app.h"

Display* __display = NULL;

void __app_init(app_t* app) {
    if (__display != NULL) {
        ABORT("__app_init() failed: Display is already initialized");
    }
    __display = XOpenDisplay(NULL);
    if (__display == NULL) {
        ABORT("__app_init() failed: XOpenDisplay() failed");
    }
}

void __app_done(app_t* app) {
    XCloseDisplay(__display);
    __display = NULL;
}

void __app_poll_event(app_t* app, double timeout) {
    XEvent event = {};
    if (XPending(__display)) {
        XNextEvent(__display, &event);
    }
}
