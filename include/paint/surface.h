#ifndef PAINT_SURFACE_H
#define PAINT_SURFACE_H

#include <paint/math.h>

typedef struct texture_t texture_t;
typedef struct surface_t surface_t;

surface_t* surface_new(void);
texture_t* surface_dump(surface_t const*);
vec2_t surface_size(surface_t const*);
void surface_set_size(surface_t*);
void surface_clear(surface_t const*, vec4_t);
void surface_flush(surface_t const*);
void surface_free(surface_t*);

#endif /* PAINT_SURFACE_H */