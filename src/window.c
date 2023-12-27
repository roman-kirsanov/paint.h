#include "surface.h"
#include "window.h"

ARRAY_TYPE_C(__window_event_listener_array, __window_event_listener_t, DUMMY_COMPARATOR, DUMMY_SORTER);

window_t* window_new(void) {
    window_t* window = NEW(window_t, {
        .surface = NULL,
		.listeners = __window_event_listener_array_new(),
        .impl = NULL
	});
    __window_init(window);
    return window;
}

surface_t const* window_surface(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return window->surface;
}

vec2_t window_position(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_position(window);
}

vec2_t window_size(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_size(window);
}

vec2_t window_scale(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_scale(window);
}

char const* window_title(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_title(window);
}

bool window_visible(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_visible(window);
}

bool window_sizable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_sizable(window);
}

bool window_closable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_closable(window);
}

bool window_topmost(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_topmost(window);
}

bool window_maximizable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_maximizable(window);
}

bool window_minimizable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
    return __window_minimizable(window);
}

void window_set_position(window_t* window, vec2_t position) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_position(window, position);
}

void window_set_size(window_t* window, vec2_t size) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_size(window, size);
}

void window_set_scale(window_t* window, vec2_t scale) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_scale(window, scale);
}

void window_set_title(window_t* window, char const* title) {
    assert(("`window` is not NULL", window != NULL));
    assert(("`title` is not NULL", title != NULL));
    __window_set_title(window, title);
}

void window_set_visible(window_t* window, bool visible) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_visible(window, visible);
}

void window_set_sizable(window_t* window, bool sizable) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_sizable(window, sizable);
}

void window_set_closable(window_t* window, bool closable) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_closable(window, closable);
}

void window_set_topmost(window_t* window, bool topmost) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_topmost(window, topmost);
}

void window_set_maximizable(window_t* window, bool maximizable) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_maximizable(window, maximizable);
}

void window_set_minimizable(window_t* window, bool minimizable) {
    assert(("`window` is not NULL", window != NULL));
    __window_set_minimizable(window, minimizable);
}

void window_on_event(window_t* window, void(*proc)(event_t, void*), void* param) {
    assert(("`window` is not NULL", window != NULL));
    assert(("`proc` is not NULL", proc != NULL));
    ;
}

void window_off_event(window_t* window, void(*proc)(event_t, void*), void* param) {
    assert(("`window` is not NULL", window != NULL));
    assert(("`proc` is not NULL", proc != NULL));
    ;
}

void window_center(window_t* window) {
    assert(("`window` is not NULL", window != NULL));
    __window_center(window);
}

void window_swap(window_t* window) {
    assert(("`window` is not NULL", window != NULL));
    __window_swap(window);
}

void window_free(window_t* window) {
    assert(("`window` is not NULL", window != NULL));
    __window_done(window);
    __window_event_listener_array_free(window->listeners);
    // surface_free(window->surface);
    FREE(window);
}