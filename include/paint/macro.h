#ifndef PAINT_MACRO_H
#define PAINT_MACRO_H

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

#define LENGTH(A) (sizeof(A) / sizeof(*A))

#endif /* PAINT_MACRO_H */