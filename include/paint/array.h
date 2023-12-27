#ifndef PAINT_ARRAY_H
#define PAINT_ARRAY_H

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

#endif /* PAINT_ARRAY_H */