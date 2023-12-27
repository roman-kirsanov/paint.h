#ifndef PAINT_EVENT_H
#define PAINT_EVENT_H

#include <paint/math.h>

typedef struct window_t window_t;

typedef enum {
    EVENT_TYPE_SHOW = 0,
    EVENT_TYPE_HIDE = 1,
    EVENT_TYPE_CLOSE = 2,
    EVENT_TYPE_RESIZE = 3,
    EVENT_TYPE_MAXIMIZE = 4,
    EVENT_TYPE_MINIMIZE = 5,
    EVENT_TYPE_DEMAXIMIZE = 6,
    EVENT_TYPE_DEMINIMIZE = 7,
    EVENT_TYPE_PIXELRATIO = 8,
    EVENT_TYPE_MOUSEMOVE = 9,
    EVENT_TYPE_MOUSEENTER = 10,
    EVENT_TYPE_MOUSEEXIT = 11,
    EVENT_TYPE_MOUSEWHEEL = 12,
    EVENT_TYPE_LBUTTONDOWN = 13,
    EVENT_TYPE_RBUTTONDOWN = 14,
    EVENT_TYPE_MBUTTONDOWN = 15,
    EVENT_TYPE_LBUTTONUP = 16,
    EVENT_TYPE_RBUTTONUP = 17,
    EVENT_TYPE_MBUTTONUP = 18,
    EVENT_TYPE_KEYDOWN = 19,
    EVENT_TYPE_KEYUP = 20,
    EVENT_TYPE_FOCUS = 21,
    EVENT_TYPE_BLUR = 22
} EVENT_TYPE;

typedef struct event_t {
    EVENT_TYPE type;
    window_t const* window;
    vec2_t position;
    vec2_t wheel;
} event_t;

#endif /* PAINT_EVENT_H*/