#ifndef PAINT_WINDOW_H
#define PAINT_WINDOW_H

#include <paint/math.h>
#include <paint/event.h>

typedef struct surface_t surface_t;
typedef struct window_t window_t;

window_t* window_new(void);
surface_t const* window_surface(window_t const*);
vec2_t window_position(window_t const*);
vec2_t window_size(window_t const*);
vec2_t window_scale(window_t const*);
char const* window_title(window_t const*);
bool window_visible(window_t const*);
bool window_sizable(window_t const*);
bool window_closable(window_t const*);
bool window_topmost(window_t const*);
bool window_maximizable(window_t const*);
bool window_minimizable(window_t const*);
void window_set_position(window_t*, vec2_t);
void window_set_size(window_t*, vec2_t);
void window_set_scale(window_t*, vec2_t);
void window_set_title(window_t*, char const*);
void window_set_visible(window_t*, bool);
void window_set_sizable(window_t*, bool);
void window_set_closable(window_t*, bool);
void window_set_topmost(window_t*, bool);
void window_set_maximizable(window_t*, bool);
void window_set_minimizable(window_t*, bool);
void window_on_event(window_t*, void(*)(event_t, void*), void*);
void window_off_event(window_t*, void(*)(event_t, void*), void*);
void window_center(window_t*);
void window_swap(window_t*);
void window_free(window_t*);

#endif /* PAINT_WINDOW_H */