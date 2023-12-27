#ifndef PAINT_APP_H
#define PAINT_APP_H

#include <paint/event.h>

typedef struct app_t app_t;

/**
 * Creates a new app.
 *
 * @return A pointer to the newly created app_t object.
 */
app_t* app_new(void);

/**
 * Sets a callback function to handle events for an app.
 *
 * @param app A pointer to the app_t object.
 * @param handler A pointer to the function that will handle the events.
 * @param userdata A pointer to user data that will be passed to the handler function.
 */
void app_on_event(app_t*, void(*)(event_t, void*), void*);

/**
 * Removes a callback function from handling events for an app.
 *
 * @param app A pointer to the app_t object.
 * @param handler A pointer to the function that was handling the events.
 * @param userdata A pointer to user data that was passed to the handler function.
 */
void app_off_event(app_t*, void(*)(event_t, void*), void*);

/**
 * Polls for an event from the app.
 *
 * @param app A pointer to the app_t object.
 * @param timeout The maximum amount of time to wait for an event, in milliseconds.
 */
void app_poll_event(app_t*, double);

/**
 * Frees the resources associated with an app.
 *
 * @param app A pointer to the app_t object.
 */
void app_free(app_t*);

#endif /* PAINT_APP_H*/