#ifndef PAINT_MATH_H
#define PAINT_MATH_H

typedef struct vec2_t {
    union {
        float x;
        float width;
    };
    union {
        float y;
        float height;
    };
} vec2_t;

typedef struct vec4_t {
    union {
        float x;
        float red;
    };
    union {
        float y;
        float green;
    };
    union {
        float width;
        float blue;
    };
    union {
        float height;
        float alpha;
    };
} vec4_t;

#endif /* PAINT_MATH_H*/