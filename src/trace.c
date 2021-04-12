//
// Created by geykelhodgson on 4/12/21.
//

#include "../include/trace.h"

int trace_app(char* app_file, char** app_argv, int* call_counter, int wait) {
    pid_t app_process = fork();
    switch (app_process) {
        case -1:
            fprintf(stderr, "Unable to fork process.\n");
            exit(1);
        case 0:
            return run_app(app_file, app_argv);
        default:
            return trace_process(app_process, call_counter, wait);
    }
}

int run_app(char* app_file, char** app_argv) {
    int error = ptrace(PTRACE_TRACEME); //trace this process
    if (error == -1) {
        fprintf(stderr, "Fail to PTRACE_TRACEME\n");
        return error;
    }
    // Every signal is send by parent process, because this process is being trace.
    // wake up parent to trace system calls of execvp (app) process, and stop current execution.
    error = kill(getpid(), SIGSTOP);
    if (error == -1) {
        fprintf(stderr, "Fail to SIGSTOP child process\n");
        return error;
    }
    // execute application as child process
    error = execvp(app_file, app_argv);
    if (error == -1) {
        fprintf(stderr, "Fail to execvp %s\n", app_file);
        return error;
    }
    return 0;
}

int wait_for_system_call(pid_t app_process, int wait) {
    int status;
    while (1) {
        // continue execution on app process (right before execvp the first time), after every system call
        ptrace(PTRACE_SYSCALL, app_process, 0, 0);
        waitpid(app_process, &status, 0);
        /**
         *  WIFSTOPPED(status) returns true if the child process was stopped by delivery of a signal;
         *          this is only possible if the call was done using WUNTRACED or when the child is being traced (see ptrace(2)).
         *  WSTOPSIG(status) returns the number of the signal which caused the child to stop.
         *          This macro should only be employed if WIFSTOPPED returned true.
         */
        // the app process stop, check status to find the reason.
        // 0x80 makes sure is a system call because of PTRACE_0_TRACESYSGOOD option
        if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80) {
            if (wait) {
                // TODO: wait for user input.
            }
            return 1; // continue execution
        }
        // app process finished.
        if (WIFEXITED(status)) {
            return 0; //end execution
        }
    }
}

int trace_process(pid_t app_process, int* call_counter, int wait) {
    int status, call_number;
    // wait to start tracing just before execvp
    waitpid(app_process, &status, 0);
    // when child process stops due to system call, signal will be SIGTRAP
    // sets highest bit (0x80), to differentiate syscalls from others kind of stops
    ptrace(PTRACE_SETOPTIONS, app_process, 0, PTRACE_0_TRACESYSGOOD);
    while(wait_for_system_call(app_process, wait)) {
        call_number = ptrace(PTRACE_PEEKUSER, app_process, sizeof(long)*ORIG_EAX);
        call_counter[call_number]++;
    }
}