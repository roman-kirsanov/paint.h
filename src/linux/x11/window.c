#include <X11/Xlib.h>
#include "../../window.h"
#include "app.h"

typedef struct __window_impl_t {
    Window window;
    char* title;
} __window_impl_t;

void __window_init(window_t* window) {
    assert(("window is not NULL", window != NULL));
    int scr = DefaultScreen(__display);
    Window win = XCreateSimpleWindow(
        __display,
        RootWindow(__display, scr),
        10, 10, 500, 500, 1,
        BlackPixel(__display, scr),
        WhitePixel(__display, scr)
    );
    XSelectInput(__display, win, ExposureMask | KeyPressMask);
    XMapWindow(__display, win);
    window->impl = NEW(__window_impl_t, {
        .window = win
    });
}

void __window_done(window_t* window) {
    assert(("window is not NULL", window != NULL));
    XDestroyWindow(__display, window->impl->window);
    FREE(window->impl->title);
    FREE(window->impl);
}

vec2_t __window_position(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    XWindowAttributes attrs = {};
    XGetWindowAttributes(__display, window->impl->window, &attrs);
    return (vec2_t){
        (float)attrs.x,
        (float)attrs.y
    };
}

vec2_t __window_size(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    XWindowAttributes attrs = {};
    XGetWindowAttributes(__display, window->impl->window, &attrs);
    return (vec2_t){
        (float)attrs.width,
        (float)attrs.height
    };
}

vec2_t __window_scale(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return (vec2_t){ 1.0f, 1.0f };
}

char const* __window_title(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    FREE(window->impl->title);
    if (XFetchName(__display, window->impl->window, &window->impl->title) > 0) {
        return window->impl->title;
    } else {
        return "";
    }
}

bool __window_visible(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    XWindowAttributes attrs;
    XGetWindowAttributes(__display, window->impl->window, &attrs);
    return attrs.map_state == IsViewable;
}

bool __window_sizable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return true;
}

bool __window_closable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return true;
}

bool __window_topmost(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return false;
}

bool __window_maximizable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return true;
}

bool __window_minimizable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return true;
}

void __window_set_position(window_t* window, vec2_t position) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_size(window_t* window, vec2_t size) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_scale(window_t* window, vec2_t scale) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_title(window_t* window, char const* title) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_visible(window_t* window, bool visible) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_sizable(window_t* window, bool sizable) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_closable(window_t* window, bool closable) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_topmost(window_t* window, bool topmost) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_maximizable(window_t* window, bool maximizable) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_minimizable(window_t* window, bool minimizable) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_center(window_t* window) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_swap(window_t* window) {
    assert(("window is not NULL", window != NULL));
    ;
}