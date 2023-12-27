#ifndef PAINT_APP_PRIVATE_H
#define PAINT_APP_PRIVATE_H

#include <paint/macro.h>
#include <paint/array.h>
#include <paint/app.h>

typedef struct __app_event_listener_t {
    void(*proc)(event_t, void*);
    void* param;
} __app_event_listener_t;

ARRAY_TYPE_H(__app_event_listener_array, __app_event_listener_t, );

typedef struct app_t {
    __app_event_listener_array_t* listeners;
} app_t;

void __app_init(app_t*);
void __app_done(app_t*);
void __app_poll_event(app_t*, double);

#endif /* PAINT_APP_PRIVATE_H */