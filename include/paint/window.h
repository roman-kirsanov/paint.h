#ifndef PAINT_WINDOW_H
#define PAINT_WINDOW_H

#include <paint/math.h>
#include <paint/event.h>

typedef struct surface_t surface_t;
typedef struct window_t window_t;

/**
 * Creates a new window.
 * The window is created without sizebox, close, maximize, and minimize buttons.
 * To change the window decoration, use the appropriate functions.
 *
 * @return A pointer to the newly created window_t object.
 */
window_t* window_new(void);

/**
 * Retrieves the surface of a window.
 * This function returns a pointer to the surface_t object associated with the given window.
 * The surface represents the drawable area of the window.
 *
 * @param window A pointer to the window_t object.
 * @return A pointer to the surface_t object of the window.
 */
surface_t const* window_surface(window_t const*);

/**
 * Retrieves the position of a window.
 *
 * @param window A pointer to the window_t object.
 * @return The position of the window as a vec2_t object.
 */
vec2_t window_position(window_t const*);

/**
 * Retrieves the size of a window.
 *
 * @param window A pointer to the window_t object.
 * @return The size of the window as a vec2_t object.
 */
vec2_t window_size(window_t const*);

/**
 * Retrieves the scale of a window.
 *
 * @param window A pointer to the window_t object.
 * @return The scale of the window as a vec2_t object.
 */
vec2_t window_scale(window_t const*);

/**
 * Retrieves the title of a window.
 *
 * @param window A pointer to the window_t object.
 * @return The title of the window as a string.
 */
char const* window_title(window_t const*);

/**
 * Checks if a window is visible.
 *
 * @param window A pointer to the window_t object.
 * @return A boolean value indicating whether the window is visible.
 */
bool window_visible(window_t const*);

/**
 * Checks if a window is sizable.
 *
 * @param window A pointer to the window_t object.
 * @return A boolean value indicating whether the window is sizable.
 */
bool window_sizable(window_t const*);

/**
 * Checks if a window is closable.
 *
 * @param window A pointer to the window_t object.
 * @return A boolean value indicating whether the window is closable.
 */
bool window_closable(window_t const*);

/**
 * Checks if a window is topmost.
 *
 * @param window A pointer to the window_t object.
 * @return A boolean value indicating whether the window is topmost.
 */
bool window_topmost(window_t const*);

/**
 * Checks if a window is maximizable.
 *
 * @param window A pointer to the window_t object.
 * @return A boolean value indicating whether the window is maximizable.
 */
bool window_maximizable(window_t const*);

/**
 * Checks if a window is minimizable.
 *
 * @param window A pointer to the window_t object.
 * @return A boolean value indicating whether the window is minimizable.
 */
bool window_minimizable(window_t const*);

/**
 * Sets the position of a window.
 *
 * @param window A pointer to the window_t object.
 * @param position The new position of the window as a vec2_t object.
 */
void window_set_position(window_t*, vec2_t);

/**
 * Sets the size of a window.
 *
 * @param window A pointer to the window_t object.
 * @param size The new size of the window as a vec2_t object.
 */
void window_set_size(window_t*, vec2_t);

/**
 * Sets the scale of a window.
 *
 * @param window A pointer to the window_t object.
 * @param scale The new scale of the window as a vec2_t object.
 */
void window_set_scale(window_t*, vec2_t);

/**
 * Sets the title of a window.
 *
 * @param window A pointer to the window_t object.
 * @param title The new title of the window as a string.
 */
void window_set_title(window_t*, char const*);

/**
 * Sets the visibility of a window.
 *
 * @param window A pointer to the window_t object.
 * @param visible The new visibility state of the window as a boolean.
 */
void window_set_visible(window_t*, bool);

/**
 * Sets the sizability of a window.
 *
 * @param window A pointer to the window_t object.
 * @param sizable The new sizability state of the window as a boolean.
 */
void window_set_sizable(window_t*, bool);

/**
 * Sets the closability of a window.
 *
 * @param window A pointer to the window_t object.
 * @param closable The new closability state of the window as a boolean.
 */
void window_set_closable(window_t*, bool);

/**
 * Sets the topmost state of a window.
 *
 * @param window A pointer to the window_t object.
 * @param topmost The new topmost state of the window as a boolean.
 */
void window_set_topmost(window_t*, bool);

/**
 * Sets the maximizability of a window.
 *
 * @param window A pointer to the window_t object.
 * @param maximizable The new maximizability state of the window as a boolean.
 */
void window_set_maximizable(window_t*, bool);

/**
 * Sets the minimizability of a window.
 *
 * @param window A pointer to the window_t object.
 * @param minimizable The new minimizability state of the window as a boolean.
 */
void window_set_minimizable(window_t*, bool);

/**
 * Sets a callback function to handle events for a window.
 *
 * @param window A pointer to the window_t object.
 * @param handler A pointer to the function that will handle the events.
 * @param userdata A pointer to user data that will be passed to the handler function.
 */
void window_on_event(window_t*, void(*)(event_t, void*), void*);

/**
 * Removes a callback function from handling events for a window.
 *
 * @param window A pointer to the window_t object.
 * @param handler A pointer to the function that was handling the events.
 * @param userdata A pointer to user data that was passed to the handler function.
 */
void window_off_event(window_t*, void(*)(event_t, void*), void*);

/**
 * Centers a window.
 *
 * @param window A pointer to the window_t object.
 */
void window_center(window_t*);

/**
 * Swaps the front and back buffers of a window.
 * This should be called after all rendering commands for a window.
 *
 * @param window A pointer to the window_t object.
 */
void window_swap(window_t*);

/**
 * Frees the resources associated with a window.
 *
 * @param window A pointer to the window_t object.
 */
void window_free(window_t*);

#endif /* PAINT_WINDOW_H */