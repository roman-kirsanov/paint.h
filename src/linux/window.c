#include <glib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include "../window.h"

typedef struct __window_impl_t {
    GtkWidget* window;
    GtkWidget* glArea;
} __window_impl_t;

static gboolean __glarea_on_resize(GtkWidget* widget, GdkEvent* event, gpointer data) {
    window_t* window = g_object_get_data(G_OBJECT(widget), "window");
    if (window != NULL) {
        __window_resize(window);
    }
    return false;
}

static gboolean __window_on_close(GtkWidget* widget, GdkEvent* event, gpointer data) {
    window_t* window = g_object_get_data(G_OBJECT(widget), "window");
    if (window != NULL) {
        __window_close(window);
    }
    return true;
}

void __window_init(window_t* window) {
    assert(("window is not NULL", window != NULL));
    GtkWidget* widget = gtk_window_new();
    GtkWidget* glArea = gtk_gl_area_new();
    gtk_window_set_child(GTK_WINDOW(widget), glArea);
    gtk_window_set_resizable(GTK_WINDOW(widget), false);
    gtk_window_set_deletable(GTK_WINDOW(widget), false);
    g_object_set_data(G_OBJECT(widget), "window", window);
    g_object_set_data(G_OBJECT(glArea), "window", window);
    g_signal_connect(widget, "close-request", G_CALLBACK(__window_on_close), NULL);
    g_signal_connect(glArea, "resize", G_CALLBACK(__glarea_on_resize), NULL);
    window->impl = NEW(__window_impl_t, {
        .window = widget,
        .glArea = glArea
    });
}

void __window_done(window_t* window) {
    assert(("window is not NULL", window != NULL));
    gtk_window_destroy(GTK_WINDOW(window->impl->window));
    FREE(window->impl);
}

vec2_t __window_position(window_t const* window) {
    return (vec2_t){ 0.0f, 0.0f };
}

vec2_t __window_size(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return (vec2_t){
        (float)gtk_widget_get_allocated_width(window->impl->window),
        (float)gtk_widget_get_allocated_height(window->impl->window)
    };
}

vec2_t __window_scale(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return (vec2_t){ 0.0f, 0.0f };
}

char const* __window_title(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return gtk_window_get_title(GTK_WINDOW(window->impl->window));
}

bool __window_visible(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return gtk_widget_get_visible(window->impl->window);
}

bool __window_sizable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return gtk_window_get_resizable(GTK_WINDOW(window->impl->window));
}

bool __window_closable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return gtk_window_get_deletable(GTK_WINDOW(window->impl->window));
}

bool __window_topmost(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return false;
}

bool __window_maximizable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return true;
}

bool __window_minimizable(window_t const* window) {
    assert(("window is not NULL", window != NULL));
    return true;
}

void __window_set_position(window_t* window, vec2_t position) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_size(window_t* window, vec2_t size) {
    assert(("window is not NULL", window != NULL));
    gtk_widget_set_size_request(window->impl->window, (int32_t)size.x, (int32_t)size.y);
}

void __window_set_scale(window_t* window, vec2_t scale) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_title(window_t* window, char const* title) {
    assert(("window is not NULL", window != NULL));
    gtk_window_set_title(GTK_WINDOW(window->impl->window), title);
}

void __window_set_visible(window_t* window, bool visible) {
    assert(("window is not NULL", window != NULL));
    gtk_widget_set_visible(window->impl->window, visible);
}

void __window_set_sizable(window_t* window, bool sizable) {
    assert(("window is not NULL", window != NULL));
    gtk_window_set_resizable(GTK_WINDOW(window->impl->window), sizable);
}

void __window_set_closable(window_t* window, bool closable) {
    assert(("window is not NULL", window != NULL));
    gtk_window_set_deletable(GTK_WINDOW(window->impl->window), closable);
}

void __window_set_topmost(window_t* window, bool topmost) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_maximizable(window_t* window, bool maximizable) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_set_minimizable(window_t* window, bool minimizable) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_center(window_t* window) {
    assert(("window is not NULL", window != NULL));
    ;
}

void __window_swap(window_t* window) {
    assert(("window is not NULL", window != NULL));
    ;
}