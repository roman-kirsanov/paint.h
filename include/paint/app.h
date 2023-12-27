#ifndef PAINT_APP_H
#define PAINT_APP_H

#include <paint/event.h>

typedef struct app_t app_t;

app_t* app_new(void);
void app_on_event(app_t*, void(*)(event_t, void*), void*);
void app_off_event(app_t*, void(*)(event_t, void*), void*);
void app_poll_event(app_t*, double);
void app_free(app_t*);

#endif /* PAINT_APP_H*/