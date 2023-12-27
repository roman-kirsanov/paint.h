#include <time.h>
#include "wayland-client.h"
#include "../window.h"

typedef struct wl_display wl_display_t;
typedef struct wl_registry wl_registry_t;
typedef struct wl_compositor wl_compositor_t;
typedef struct wl_surface wl_surface_t;
typedef struct wl_buffer wl_buffer_t;
typedef struct wl_shell wl_shell_t;

#define wl_display_connect_e(...) ({ \
    wl_display_t* __ret = wl_display_connect(__VA_ARGS__); \
    if (__ret == NULL) { \
        ABORT("wl_display_connect() failed"); \
    } \
    __ret; \
})

#define wl_display_get_registry_e(...) ({ \
    wl_registry_t* __ret = wl_display_get_registry(__VA_ARGS__); \
    if (__ret == NULL) { \
        ABORT("wl_display_get_registry() failed"); \
    } \
    __ret; \
})

#define wl_registry_add_listener_e(...) ({ \
    int __ret = wl_registry_add_listener(__VA_ARGS__); \
    if (__ret != 0) { \
        ABORT("wl_registry_add_listener() failed"); \
    } \
    __ret; \
})

#define wl_display_roundtrip_e(...) ({ \
    int __ret = wl_display_roundtrip(__VA_ARGS__); \
    if (__ret != 0) { \
        ABORT("wl_display_roundtrip() failed"); \
    } \
    __ret; \
})

#define wl_compositor_create_surface_e(...) ({ \
    wl_surface_t* __ret = wl_compositor_create_surface(__VA_ARGS__); \
    if (__ret == NULL) { \
        ABORT("wl_compositor_create_surface() failed"); \
    } \
    __ret; \
})

typedef struct __window_impl_t {
    wl_display_t* display;
    wl_registry_t* registry;
    wl_compositor_t* compositor;
    wl_surface_t* surface;
} __window_impl_t;

static char* __random() {
    static char const* const __chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static size_t const __chars_length = 62;
    static size_t const __length = 16;
    char* ret = NEW(char, __length + 1);
    for (size_t i = 0; i < __length; ++i) {
        ret[i] = __chars[rand() % __chars_length];
    }
    return ret;
}

static void __window_global_callback(void* data, wl_registry_t* registry, uint32_t id, char const* interface, uint32_t version) {
    window_t* window = (window_t*)data;
    if (window != NULL) {
        if (strcmp(interface, "wl_compositor") == 0) {
            window->impl->compositor = wl_registry_bind(registry, id, &wl_compositor_interface, version);
        } else if (strcmp(interface, "xdg_wm_base") == 0) {
            ;
        }

    }
}

static void __window_global_remove(void* data, wl_registry_t* registry, uint32_t id) {
    ;
}

void __window_init(window_t* window) {
    assert(("window is not NULL", window != NULL));
    wl_display_t* display = wl_display_connect_e(NULL);
    wl_registry_t* registry = wl_display_get_registry_e(display);
    wl_registry_add_listener_e(
        registry,
        &(struct wl_registry_listener){
            .global = __window_global_callback,
            .global_remove = __window_global_remove
        },
        window
    );
    window->impl = NEW(__window_impl_t, {
        .display = display,
        .registry = registry,
        .compositor = NULL,
        .surface = NULL
    });
    wl_display_roundtrip_e(display);
    window->impl->surface = wl_compositor_create_surface_e(window->impl->compositor);
}

void __window_done(window_t* window) {
    assert(("window is not NULL", window != NULL));
    wl_display_disconnect(window->impl->display);
    FREE(window->impl);
}

vec2_t __window_position(window_t const* window) {

}

vec2_t __window_size(window_t const* window) {

}

vec2_t __window_scale(window_t const* window) {

}

char const* __window_title(window_t const* window) {

}

bool __window_visible(window_t const* window) {

}

bool __window_sizable(window_t const* window) {

}

bool __window_closable(window_t const* window) {

}

bool __window_topmost(window_t const* window) {

}

bool __window_maximizable(window_t const* window) {

}

bool __window_minimizable(window_t const* window) {

}

void __window_set_position(window_t* window, vec2_t position) {

}

void __window_set_size(window_t* window, vec2_t size) {

}

void __window_set_scale(window_t* window, vec2_t scale) {

}

void __window_set_title(window_t* window, char const* title) {

}

void __window_set_visible(window_t* window, bool visible) {

}

void __window_set_sizable(window_t* window, bool sizable) {

}

void __window_set_closable(window_t* window, bool closable) {

}

void __window_set_topmost(window_t* window, bool topmost) {

}

void __window_set_maximizable(window_t* window, bool maximizable) {

}

void __window_set_minimizable(window_t* window, bool minimizable) {

}

void __window_center(window_t* window) {

}

void __window_swap(window_t* window) {

}

__attribute__((constructor)) static void __init() {
    srand(time(NULL));
}