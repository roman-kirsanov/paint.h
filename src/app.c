#include "app.h"

ARRAY_TYPE_C(__app_event_listener_array, __app_event_listener_t, DUMMY_COMPARATOR, DUMMY_SORTER);

app_t* app_new(void) {
    app_t* app = NEW(app_t, {
        .listeners = __app_event_listener_array_new()
    });
    __app_init(app);
    return app;
}

void app_on_event(app_t* app, void(*proc)(event_t, void*), void* param) {
    assert(("`app` is not NULL", app != NULL));
    assert(("`proc` is not NULL", proc != NULL));
    ;
}

void app_off_event(app_t* app, void(*proc)(event_t, void*), void* param) {
    assert(("`app` is not NULL", app != NULL));
    assert(("`proc` is not NULL", proc != NULL));
    ;
}

void app_poll_event(app_t* app, double timeout) {
    assert(("`app` is not NULL", app != NULL));
    __app_poll_event(app, timeout);
}

void app_free(app_t* app) {
    assert(("`app` is not NULL", app != NULL));
    __app_event_listener_array_free(app->listeners);
    __app_done(app);
    FREE(app);
}