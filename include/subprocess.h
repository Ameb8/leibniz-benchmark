#ifndef SUBPROCESS_H
#define SUBPROCESS_H


typedef enum {
    RUN_SUCCESS = 0,
    RUN_ERR_PIPE = 1,
    RUN_ERR_FORK = 2,
    RUN_ERR_DUP2 = 3,
    RUN_ERR_EXECVP = 4,
    RUN_ERR_WAITPID = 5,
    RUN_ERR_CHILD_EXIT = 6,
} SubprocessErr;


int subprocessRun(const char* exec_path, char* const* args, SubprocessErr* err);
const char* subprocessErrStr(SubprocessErr err);


#endif