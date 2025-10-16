#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H


#include <stdio.h>


#define DEBUG 1

#if DEBUG
    #define DEBUG_LOG(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define DEBUG_LOG(fmt, ...) do {} while (0)
#endif

#endif