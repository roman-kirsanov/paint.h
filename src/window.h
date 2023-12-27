#ifndef PAINT_WINDOW_PRIVATE_H
#define PAINT_WINDOW_PRIVATE_H

#include <paint/macro.h>
#include <paint/array.h>
#include <paint/window.h>

typedef struct __window_impl_t __window_impl_t;

typedef struct __window_event_listener_t {
    void(*proc)(event_t, void*);
    void* param;
} __window_event_listener_t;

ARRAY_TYPE_H(__window_event_listener_array, __window_event_listener_t, );

typedef struct window_t {
    surface_t* surface;
    __window_event_listener_array_t* listeners;
    __window_impl_t* impl;
} window_t;

void __window_init(window_t*);
void __window_done(window_t*);
vec2_t __window_position(window_t const*);
vec2_t __window_size(window_t const*);
vec2_t __window_scale(window_t const*);
char const* __window_title(window_t const*);
bool __window_visible(window_t const*);
bool __window_sizable(window_t const*);
bool __window_closable(window_t const*);
bool __window_topmost(window_t const*);
bool __window_maximizable(window_t const*);
bool __window_minimizable(window_t const*);
void __window_set_position(window_t*, vec2_t);
void __window_set_size(window_t*, vec2_t);
void __window_set_scale(window_t*, vec2_t);
void __window_set_title(window_t*, char const*);
void __window_set_visible(window_t*, bool);
void __window_set_sizable(window_t*, bool);
void __window_set_closable(window_t*, bool);
void __window_set_topmost(window_t*, bool);
void __window_set_maximizable(window_t*, bool);
void __window_set_minimizable(window_t*, bool);
void __window_center(window_t*);
void __window_swap(window_t*);

#endif /* PAINT_WINDOW_PRIVATE_H */