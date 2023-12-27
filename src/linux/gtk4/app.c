#include <glib.h>
#include <gtk/gtk.h>
#include "../../app.h"

void __app_init(app_t* app) {
    static bool __gtk_inited = false;
    if (__gtk_inited == false) {
        __gtk_inited = true;
        gtk_init();
    }
}

void __app_done(app_t* app) {

}

void __app_poll_event(app_t* app, double timeout) {
    g_main_context_iteration(g_main_context_default(), false);
}
