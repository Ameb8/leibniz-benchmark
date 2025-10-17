#ifndef TESTS_H
#define TESTS_H


typedef struct {
     const char* name;
     const char* exec_path;
     char* const* args;
} Test;


const Test** get_tests(int* num_tests);

#endif