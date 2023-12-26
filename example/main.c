#define PAIN_IMPLEMENTATION

#include <stdio.h>
#include "../paint.h"

bool exit_ = false;

void app_event(event_t event, void* param) {
    ;
}

void window_event(event_t event, void* param) {
    ;
}

int main(int argc, char const *argv[]) {

    app_t* app = app_new();
    app_on_event(app, app_event, NULL);

    window_t* win = window_new();
    window_on_event(win, window_event, NULL);
    window_set_maximizable(win, true);
    window_set_minimizable(win, true);
    window_set_closable(win, true);
    window_set_sizable(win, true);
    window_set_visible(win, true);

    for (;;) {
        app_poll_event(app, 16.667);

        surface_t const* sfc = window_surface(win);
        surface_clear(sfc, (vec4_t){ 0.0f, 0.0f, 0.0f, 1.0f });
        ;
        surface_flush(sfc);
        window_swap(win);

        if (exit_) {
            break;
        }
    }

    window_off_event(win, window_event, NULL);
    app_off_event(app, app_event, NULL);
    window_free(win);
    app_free(app);

    return 0;
}
