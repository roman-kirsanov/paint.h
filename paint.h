/*
MIT License

Copyright (c) 2024 Roman Kirsanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef PAINT_H
#define PAINT_H

typedef struct app_t app_t;
typedef struct window_t window_t;
typedef struct brush_t brush_t;
typedef struct path_t path_t;
typedef struct paint_t paint_t;

typedef struct vec2_t {
    union {
        float x;
        float width;
    };
    union {
        float y;
        float height;
    };
} vec2_t;

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
} event_t;

app_t* app_create(void);
void app_on_event(app_t*, void(*)(event_t, void*), void*);
void app_off_event(app_t*, void(*)(event_t, void*), void*);
void app_poll_event(app_t*);
void app_destroy(app_t*);

#ifdef PAINT_IMPLEMENTATION

#endif

#endif