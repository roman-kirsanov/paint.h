#include <paint/macro.h>
#include <paint/array.h>
#include <paint/window.h>

typedef struct __window_event_listener_t {
    void(*proc)(event_t, void*);
    void* param;
} __window_event_listener_t;

ARRAY_TYPE(__window_event_listener_array, __window_event_listener_t, DUMMY_COMPARATOR, DUMMY_SORTER, );

typedef struct window_t {
    __window_event_listener_array_t* listeners;
} window_t;

window_t* window_new(void) {
	return NEW(window_t, {
		.listeners = __window_event_listener_array_new()
	});
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

surface_t const* window_surface(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

vec2_t window_position(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

vec2_t window_size(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

vec2_t window_scale(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

char const* window_title(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

bool window_visible(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

bool window_sizable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

bool window_closable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

bool window_topmost(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

bool window_maximizable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

bool window_minimizable(window_t const* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_position(window_t* window, vec2_t position) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_size(window_t* window, vec2_t size) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_scale(window_t* window, vec2_t scale) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_title(window_t* window, char const* title) {
    assert(("`window` is not NULL", window != NULL));
    assert(("`title` is not NULL", title != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_visible(window_t* window, bool visible) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_sizable(window_t* window, bool sizable) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_closable(window_t* window, bool closable) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_topmost(window_t* window, bool topmost) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_maximizable(window_t* window, bool maximizable) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_set_minimizable(window_t* window, bool minimizable) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_on_event(window_t* window, void(*proc)(event_t, void*), void* param) {
    assert(("`window` is not NULL", window != NULL));
    assert(("`proc` is not NULL", proc != NULL));
    assert(("`param` is not NULL", param != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_off_event(window_t* window, void(*proc)(event_t, void*), void* param) {
    assert(("`window` is not NULL", window != NULL));
    assert(("`proc` is not NULL", proc != NULL));
    assert(("`param` is not NULL", param != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_center(window_t* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_swap(window_t* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void window_free(window_t* window) {
    assert(("`window` is not NULL", window != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}