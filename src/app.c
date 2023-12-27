#include <paint/macro.h>
#include <paint/array.h>
#include <paint/app.h>

typedef struct __app_event_listener_t {
    void(*proc)(event_t, void*);
    void* param;
} __app_event_listener_t;

ARRAY_TYPE(__app_event_listener_array, __app_event_listener_t, DUMMY_COMPARATOR, DUMMY_SORTER, );

typedef struct app_t {
    __app_event_listener_array_t* listeners;
} app_t;

app_t* app_new(void) {
    return NEW(app_t, {
        .listeners = __app_event_listener_array_new()
    });
}

void app_on_event(app_t* app, void(*proc)(event_t, void*), void* param) {
    assert(("`app` is not NULL", app != NULL));
    assert(("`proc` is not NULL", proc != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void app_off_event(app_t* app, void(*proc)(event_t, void*), void* param) {
    assert(("`app` is not NULL", app != NULL));
    assert(("`proc` is not NULL", proc != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void app_poll_event(app_t* app, double timeout) {
    assert(("`app` is not NULL", app != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void app_free(app_t* app) {
    assert(("`app` is not NULL", app != NULL));
    __app_event_listener_array_free(app->listeners);
}