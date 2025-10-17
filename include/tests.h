#ifndef TESTS_H
#define TESTS_H


typedef struct {
     const char* name;
     const char* exec_path;
     char* const* args;
} Test;


Test** getTests(int nTerm, int* num_tests);
void freeTests(Test** tests);

#endif