#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#include "../include/subprocess.h"
#include "../include/debug_log.h"


#define ERR_FLAG -1


int runSubprocess(const char* exec_path, char* const* args, SubprocessErr* err) {
    int pipefd[2]; // Pipe to receive output from benchmark subprocess
    pid_t pid; // ID of benchmark process

    if(err) // Default ERR param to success
        *err = RUN_SUCCESS;

    DEBUG_LOG("\nStarting Benchmark Exec"); // DEBUG ***

    if(pipe(pipefd) == -1) { // Error creating pipe
        if(err) // Set error
            *err = RUN_ERR_PIPE;
        
        DEBUG_LOG("\nPipe creation failed"); // DEBUG ***

        return ERR_FLAG;
    }

    pid = fork(); // Create subprocess

    if(pid < 0) { // Error creating subprocess;
        if(err) // Set error
            *err = RUN_ERR_FORK;

        // Close pipe
        close(pipefd[0]);
        close(pipefd[1]);

        DEBUG_LOG("\nFork Failed"); // DEBUG ***

        return ERR_FLAG;
    }

    if(pid == 0) { // Child process
        close(pipefd[0]); // Close read end of stdout on child process
        
        if(dup2(pipefd[1], STDOUT_FILENO) == -1) // Redirect child's stdout to pipe
            exit(RUN_ERR_DUP2); // Error redirecting stdout

        close(pipefd[1]); // Close original pipe
        
        execvp(exec_path, args); // Execute program

        DEBUG_LOG("\nExecvp Returned"); // DEBUG ***

        exit(RUN_ERR_EXECVP); // Error occurred, execvp should not return
    } else { // Parent process
        close(pipefd[1]); // Close write end of pipe

        // Let child process execute
        int status;
        waitpid(pid, &status, 0);

        if(WIFEXITED(status)) { // Child returned normally
            int code = WEXITSTATUS(status); // Get exit code

            if(code != 0) { // Determine error based on code
                if(err) // Assign error from enum 
                    *err = (SubprocessErr)code;

                // Clean up and return
                close(pipefd[0]);
                return ERR_FLAG;
            }
        } else { // Child Process did not return normally
            if(err) // Set error
                *err = RUN_ERR_CHILD_EXIT; 

            // Clean up and return    
            close(pipefd[0]);
            return ERR_FLAG;
        }

        return pipefd[0]; // Return child process stdout
    }

    return ERR_FLAG; // Should not be reached
}

