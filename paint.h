/*
MIT License

Copyright (c) 2024 Roman Kirsanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef PAINT_H
#define PAINT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define OUTPUT(...) { \
    fprintf(stdout, __VA_ARGS__); \
    fflush(stdout); \
}

#define ERROR(...) { \
    fprintf(stderr, __VA_ARGS__); \
    fflush(stderr); \
}

#ifndef _WIN32
    #include <execinfo.h>
    #define BACKTRACE() { \
        void* __buffer[10]; \
        int __ents_n = backtrace(__buffer, 10); \
        char** __ents = backtrace_symbols(__buffer, __ents_n); \
        if (__ents != NULL) { \
            for (int i = 0; i < __ents_n; i++) \
                fprintf(stderr, "%s\n", __ents[i]); \
            fflush(stderr); \
            free(__ents); \
        } \
    }
#else
    #define BACKTRACE()
#endif

#define ABORT(...) { \
    ERROR(__VA_ARGS__); \
    BACKTRACE(); \
    exit(1); \
}

#define FREE(A) { \
    if (A != NULL) { \
        free(A); \
        A = NULL; \
    } \
}

#define ALLOC(TYPE, N) ({ \
    TYPE* __ret = (TYPE*)calloc(N, sizeof(TYPE)); \
    assert(__ret != NULL); \
    __ret; \
})

#define NEW(TYPE, ...) ({ \
    TYPE* __ret = ALLOC(TYPE, 1); \
    *__ret = (TYPE)__VA_ARGS__; \
    __ret; \
})

#define FORMAT(...) ({ \
    size_t __len = snprintf(NULL, 0, __VA_ARGS__); \
    char* __ret = ALLOC(char, (__len + 1)); \
    snprintf(__ret, (__len + 1), __VA_ARGS__); \
    __ret; \
})

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define DUMMY_COMPARATOR(a, b) false
#define BASIC_COMPARATOR(a, b) a == b
#define STRING_COMPARATOR(a, b) strcmp(a, b) == 0

#define DUMMY_SORTER(a, b) false
#define BASIC_SORTER(a, b) a > b
#define STRING_SORTER(a, b) strcmp(a, b) > 0

#define ARRAY_TYPE_H(NAME, TYPE, LINKAGE) \
typedef struct NAME##_t { \
	TYPE* data; \
	int64_t size; \
	int64_t capacity; \
} NAME##_t; \
LINKAGE void NAME##_init(NAME##_t*); \
LINKAGE void NAME##_done(NAME##_t*); \
LINKAGE NAME##_t* NAME##_new(void); \
LINKAGE void NAME##_free(NAME##_t*); \
LINKAGE void NAME##_reserve(NAME##_t*, int64_t); \
LINKAGE void NAME##_resize(NAME##_t*, int64_t); \
LINKAGE void NAME##_attach(NAME##_t*, TYPE*, int64_t, int64_t); \
LINKAGE void NAME##_detach(NAME##_t*); \
LINKAGE void NAME##_assign(NAME##_t*, NAME##_t const*); \
LINKAGE bool NAME##_equals(NAME##_t const*, NAME##_t const*); \
LINKAGE bool NAME##_empty(NAME##_t const*); \
LINKAGE void NAME##_splice(NAME##_t*, int64_t, int64_t, TYPE const*, int64_t); \
LINKAGE void NAME##_push(NAME##_t*, TYPE); \
LINKAGE void NAME##_unshift(NAME##_t*, TYPE); \
LINKAGE TYPE NAME##_pop(NAME##_t*); \
LINKAGE TYPE NAME##_shift(NAME##_t*); \
LINKAGE void NAME##_clear(NAME##_t*); \
LINKAGE bool NAME##_remove_index(NAME##_t*, int64_t); \
LINKAGE bool NAME##_remove(NAME##_t*, TYPE); \
LINKAGE int64_t NAME##_index_of(NAME##_t const*, const TYPE, int64_t); \
LINKAGE bool NAME##_contains(NAME##_t const*, const TYPE); \
LINKAGE TYPE NAME##_first(NAME##_t const*); \
LINKAGE TYPE NAME##_last(NAME##_t const*); \
LINKAGE TYPE NAME##_next(NAME##_t const*, TYPE); \
LINKAGE TYPE NAME##_prev(NAME##_t const*, TYPE); \
LINKAGE void NAME##_sort(NAME##_t const*, bool); \
LINKAGE int64_t NAME##_size(NAME##_t const*); \
LINKAGE TYPE NAME##_item(NAME##_t*, int64_t);

#define ARRAY_TYPE_C(NAME, TYPE, COMPARATOR, SORTER) \
void NAME##_init(NAME##_t* array) { \
	assert(array != NULL); \
	assert(array->data == NULL); \
	assert(array->capacity == 0); \
	assert(array->size == 0); \
} \
void NAME##_done(NAME##_t* array) { \
	assert(array != NULL); \
	if (array->data != NULL) { \
		free(array->data); \
	} \
	array->capacity = 0; \
	array->size = 0; \
	array->data = NULL; \
} \
NAME##_t* NAME##_new(void) { \
	NAME##_t* array = (NAME##_t*)calloc(1, sizeof(NAME##_t)); \
	NAME##_init(array); \
	return array; \
} \
void NAME##_free(NAME##_t* array) { \
	assert(array != NULL); \
	NAME##_done(array); \
	free(array); \
} \
void NAME##_reserve(NAME##_t* array, int64_t capacity) { \
	assert(array != NULL); \
	if (array->capacity < capacity) { \
		TYPE* nd = (TYPE*)malloc(capacity * sizeof(TYPE)); \
		if (array->data != NULL) { \
			memcpy(nd, array->data, array->size * sizeof(TYPE)); \
			free(array->data); \
		} \
		array->data = nd; \
		array->capacity = capacity; \
	} \
} \
void NAME##_resize(NAME##_t* array, int64_t size) { \
	assert(array != NULL); \
	if (array->capacity < size) \
		NAME##_reserve(array, size); \
	array->size = size; \
} \
void NAME##_attach(NAME##_t* array, TYPE* data, int64_t size, int64_t capacity) { \
	assert(array != NULL); \
	assert(data != NULL); \
	assert(capacity > 0); \
	assert(size >= 0); \
	assert((array->data == NULL) && (array->size == 0) && (array->capacity == 0)); \
	array->data = data; \
	array->size = size; \
	array->capacity = capacity; \
} \
void NAME##_detach(NAME##_t* array) { \
	assert(array != NULL); \
	array->data = NULL; \
	array->size = 0; \
	array->capacity = 0; \
} \
void NAME##_assign(NAME##_t* array1, NAME##_t const* array2) { \
	assert(array1 != NULL); \
	assert(array2 != NULL); \
	NAME##_resize(array1, array2->size); \
	for (int64_t i = 0; i < array2->size; i++) { \
		array1->data[i] = array2->data[i]; \
	} \
} \
bool NAME##_equals(NAME##_t const* array1, NAME##_t const* array2) { \
	assert(array1 != NULL); \
	assert(array2 != NULL); \
	if (array1->size == array2->size) { \
		for (int64_t i = 0; i < array1->size; i++) \
			if ((COMPARATOR(array1->data[i], array2->data[i])) == false) \
				return false; \
		return true; \
	} else return false; \
} \
bool NAME##_empty(NAME##_t const* array) { \
	assert(array != NULL); \
	return (array->size == 0); \
} \
void NAME##_splice(NAME##_t* array, int64_t index, int64_t remove, TYPE const* data, int64_t data_size) { \
	assert(array != NULL); \
	assert((data != NULL && data_size > 0) || (data == NULL && data_size == 0)); \
	index = (index < 0 ? 0 : (index > array->size ? array->size : index)); \
	remove = (remove < 0 ? 0 : (remove > (array->size - index) ? (array->size - index) : remove)); \
	int64_t lf = 0; \
	int64_t lt = index > array->size ? array->size : index; \
	int64_t rf = (index + remove) > array->size ? array->size : (index + remove); \
	int64_t rt = array->size; \
	int64_t ns = (lt - lf) + data_size + (rt - rf); \
	int64_t nc = (ns > array->capacity) ? (ns * 2) : array->capacity; \
	TYPE* data_copy = (TYPE*)calloc(data_size, sizeof(TYPE)); \
	memcpy(data_copy, data, (data_size * sizeof(TYPE))); \
	if (nc > array->capacity) { \
		TYPE* nd = (TYPE*)malloc(nc * sizeof(TYPE)); \
		memcpy(nd, array->data, (lt - lf) * sizeof(TYPE)); \
		memcpy(nd + lt, data_copy, data_size * sizeof(TYPE)); \
		memcpy(nd + lt + data_size, array->data + rf, (rt - rf) * sizeof(TYPE)); \
		if (array->data != NULL) { \
			free(array->data); \
		} \
		array->data = nd; \
		array->size = ns; \
		array->capacity = nc; \
	} else { \
		int64_t dl = data_size - remove; \
		memmove(array->data + rf + dl, array->data + rf, (rt - rf) * sizeof(TYPE)); \
		if (data != NULL) { \
			memcpy(array->data + lt, data_copy, data_size * sizeof(TYPE)); \
		} \
		array->size = ns; \
	} \
	free(data_copy); \
} \
void NAME##_push(NAME##_t* array, TYPE item) { \
	NAME##_splice(array, array->size, 0, &item, 1); \
} \
void NAME##_unshift(NAME##_t* array, TYPE item) { \
	NAME##_splice(array, 0, 0, &item, 1); \
} \
TYPE NAME##_pop(NAME##_t* array) { \
	assert(array != NULL); \
	assert(array->size > 0); \
	int64_t index = (array->size - 1); \
	TYPE value = array->data[index]; \
	NAME##_splice(array, index, 1, NULL, 0); \
	return value; \
} \
TYPE NAME##_shift(NAME##_t* array) { \
	assert(array != NULL); \
	assert(array->size > 0); \
	TYPE value = array->data[0]; \
	NAME##_splice(array, 0, 1, NULL, 0); \
	return value; \
} \
void NAME##_clear(NAME##_t* array) { \
	assert(array != NULL); \
	array->size = 0; \
} \
bool NAME##_remove_index(NAME##_t* array, int64_t index) { \
	if ((index >= 0) && (index < array->size)) { \
		NAME##_splice(array, index, 1, NULL, 0); \
		return true; \
	} else return false; \
} \
bool NAME##_remove(NAME##_t* array, TYPE item) { \
	assert(array != NULL); \
	for (int64_t i = 0; i < array->size; i++) \
		if (COMPARATOR(array->data[i], item)) { \
			NAME##_splice(array, i, 1, NULL, 0); \
			return true; \
		} \
	return false; \
} \
int64_t NAME##_index_of(NAME##_t const* array, const TYPE item, int64_t start) { \
	assert(array != NULL); \
	start = (start < 0) ? 0 : ((start > array->size) ? array->size : start); \
	for (int64_t i = start; i < array->size; i++) \
		if (COMPARATOR(array->data[i], item)) \
			return i; \
	return -1; \
} \
bool NAME##_contains(NAME##_t const* array, const TYPE item) { \
	assert(array != NULL); \
	for (int64_t i = 0; i < array->size; i++) \
		if (COMPARATOR(array->data[i], item)) \
			return true; \
	return false; \
} \
TYPE NAME##_first(NAME##_t const* array) { \
	assert(array != NULL); \
	assert(array->size > 0); \
	return array->data[0]; \
} \
TYPE NAME##_last(NAME##_t const* array) { \
	assert(array != NULL); \
	assert(array->size > 0); \
	return array->data[array->size - 1]; \
} \
TYPE NAME##_next(NAME##_t const* array, TYPE item) { \
	assert(array != NULL); \
	assert(array->size > 0); \
	int64_t index = NAME##_index_of(array, item, 0); \
	assert((index > -1) && (index < (array->size - 1))); \
	return array->data[index + 1]; \
} \
TYPE NAME##_prev(NAME##_t const* array, TYPE item) { \
	assert(array != NULL); \
	assert(array->size > 0); \
	int64_t index = NAME##_index_of(array, item, 0); \
	assert(index > 0); \
	return array->data[index - 1]; \
} \
void NAME##_sort(NAME##_t const* array, bool desc) { \
	TYPE* tmp = (TYPE*)calloc(1, sizeof(TYPE)); \
    for (int64_t i = 0; i < (array->size - 1); i++) { \
    	for (int64_t j = 0; j < (array->size - i - 1); j++) { \
    		bool yes = SORTER(array->data[j], array->data[j + 1]); \
    		if (desc) { \
    			yes = !yes; \
    		} \
    		if (yes) { \
    			memcpy(tmp, &array->data[j], sizeof(TYPE)); \
    			memcpy(&array->data[j], &array->data[j + 1], sizeof(TYPE)); \
    			memcpy(&array->data[j + 1], tmp, sizeof(TYPE)); \
    		} \
    	} \
    } \
    free(tmp); \
} \
int64_t NAME##_size(NAME##_t const* array) { \
    assert(array != NULL); \
    return array->size; \
} \
TYPE NAME##_item(NAME##_t* array, int64_t index) { \
    assert(array != NULL); \
    assert(index >= 0); \
    assert(index < array->size); \
    return array->data[index]; \
}

#define ARRAY_TYPE(NAME, TYPE, COMPARATOR, SORTER, LINKAGE) \
ARRAY_TYPE_H(NAME, TYPE, LINKAGE); \
ARRAY_TYPE_C(NAME, TYPE, COMPARATOR, SORTER);

#define LENGTH(A) (sizeof(A) / sizeof(*A))

typedef struct app_t app_t;
typedef struct window_t window_t;
typedef struct surface_t surface_t;
typedef struct texture_t texture_t;
typedef struct brush_t brush_t;
typedef struct path_t path_t;
typedef struct paint_t paint_t;

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

typedef enum {
    EVENT_TYPE_SHOW = 0,
    EVENT_TYPE_HIDE = 1,
    EVENT_TYPE_CLOSE = 2,
    EVENT_TYPE_RESIZE = 3,
    EVENT_TYPE_MAXIMIZE = 4,
    EVENT_TYPE_MINIMIZE = 5,
    EVENT_TYPE_DEMAXIMIZE = 6,
    EVENT_TYPE_DEMINIMIZE = 7,
    EVENT_TYPE_PIXELRATIO = 8,
    EVENT_TYPE_MOUSEMOVE = 9,
    EVENT_TYPE_MOUSEENTER = 10,
    EVENT_TYPE_MOUSEEXIT = 11,
    EVENT_TYPE_MOUSEWHEEL = 12,
    EVENT_TYPE_LBUTTONDOWN = 13,
    EVENT_TYPE_RBUTTONDOWN = 14,
    EVENT_TYPE_MBUTTONDOWN = 15,
    EVENT_TYPE_LBUTTONUP = 16,
    EVENT_TYPE_RBUTTONUP = 17,
    EVENT_TYPE_MBUTTONUP = 18,
    EVENT_TYPE_KEYDOWN = 19,
    EVENT_TYPE_KEYUP = 20,
    EVENT_TYPE_FOCUS = 21,
    EVENT_TYPE_BLUR = 22
} EVENT_TYPE;

typedef struct event_t {
    EVENT_TYPE type;
    window_t const* window;
    vec2_t position;
    vec2_t wheel;
} event_t;

app_t* app_new(void);
void app_on_event(app_t*, void(*)(event_t, void*), void*);
void app_off_event(app_t*, void(*)(event_t, void*), void*);
void app_poll_event(app_t*, double);
void app_free(app_t*);

window_t* window_new(void);
surface_t const* window_surface(window_t const*);
vec2_t window_position(window_t const*);
vec2_t window_size(window_t const*);
vec2_t window_scale(window_t const*);
char const* window_title(window_t const*);
bool window_visible(window_t const*);
bool window_sizable(window_t const*);
bool window_closable(window_t const*);
bool window_topmost(window_t const*);
bool window_maximizable(window_t const*);
bool window_minimizable(window_t const*);
void window_set_position(window_t*, vec2_t);
void window_set_size(window_t*, vec2_t);
void window_set_scale(window_t*, vec2_t);
void window_set_title(window_t*, char const*);
void window_set_visible(window_t const*, bool);
void window_set_sizable(window_t const*, bool);
void window_set_closable(window_t const*, bool);
void window_set_topmost(window_t const*, bool);
void window_set_maximizable(window_t const*, bool);
void window_set_minimizable(window_t const*, bool);
void window_on_event(window_t*, void(*)(event_t, void*), void*);
void window_off_event(window_t*, void(*)(event_t, void*), void*);
void window_center(window_t*);
void window_swap(window_t*);
void window_free(window_t*);

surface_t* surface_new(void);
texture_t* surface_dump(surface_t const*);
vec2_t surface_size(surface_t const*);
void surface_set_size(surface_t*);
void surface_clear(surface_t*, vec4_t);
void surface_flush(surface_t*);
void surface_free(surface_t*);

#ifdef PAINT_IMPLEMENTATION

#include <assert.h>

typedef struct app_event_listener_t {
    void(*proc)(event_t, void*);
    void* param;
} app_event_listener_t;

ARRAY_TYPE(app_event_listener_array, app_event_listener_t, DUMMY_COMPARATOR, DUMMY_SORTER, );

typedef struct app_t {
    app_event_listener_array_t* listeners;
} app_t;

app_t* app_new(void) {
    return NEW(app_t, {
        .listeners = app_event_listener_array_new()
    });
}

void app_on_event(app_t* app, void(*proc)(event_t, void*), void* param) {
    assert(("`app` is not NULL", app != NULL));
    assert(("`proc` is not NULL", proc != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void app_off_event(app_t* app, void(*proc)(event_t, void*), void* param) {
    assert(("`app` is not NULL", app != NULL));
    assert(("`proc` is not NULL", proc != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void app_poll_event(app_t* app, double timeout) {
    assert(("`app` is not NULL", app != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

void app_free(app_t* app) {
    assert(("`app` is not NULL", app != NULL));
#ifdef __linux__
    ;
#elif __MACH__
    ;
#elif _WIN32
    ;
#endif
}

#endif
#endif /* PAINT_H */