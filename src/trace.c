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
        fprintf(stdout,"Fail to PTRACE_TRACEME\n");
        exit(errno);
    }
    // Every signal is send by parent process, because this process is being trace.
    // wake up parent to trace system calls of execvp (app) process, and stop current execution.
    error = kill(getpid(), SIGSTOP);
    if (error == -1) {
        fprintf(stdout,"Fail to SIGSTOP child process\n");
        exit(errno);
    }
    // execute application as child process
    execvp(app_file, app_argv);
    exit(errno);
}

int wait_for_system_call(pid_t app_process) {
    int status, error;
    while (1) {
        // continue execution on app process (right before execvp the first time), after every system call
        error = ptrace(PTRACE_SYSCALL, app_process, 0, 0);
        if (error == -1) {
            return 0; // exit execution
        }
        // wait until the app process is stopped.
        error = waitpid(app_process, &status, 0);
        if (error == -1) {
            return 0;
        }
        /**
         *  WIFSTOPPED(status) returns true if the child process was stopped by delivery of a signal;
         *          this is only possible if the call was done using WUNTRACED or when the child is being traced (see ptrace(2)).
         *  WSTOPSIG(status) returns the number of the signal which caused the child to stop.
         *          This macro should only be employed if WIFSTOPPED returned true.
         */
        // the app process stop, check status to find the reason.
        // 0x80 makes sure is a system call because of PTRACE_0_TRACESYSGOOD option set highest bit.
        if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80) {
            return 1; // continue execution
        }
        // app process finished.
        if (WIFEXITED(status)) {
            fprintf(stdout,"Process finished\n");
            return 0; //end execution
        }
//        if (status == 2943) {
//            getchar();
//        }
    }
}

int trace_process(pid_t app_process, int* call_counter, int wait) {
    int status, call_number;
    // wait to start tracing just before execvp
    waitpid(app_process, &status, 0);
    // when child process stops due to system call, signal will be SIGTRAP
    // sets highest bit (0x80), to differentiate syscalls from others kind of stops
    ptrace(PTRACE_SETOPTIONS, app_process, 0, PTRACE_O_TRACESYSGOOD);
    //waits until system call starts
    while(wait_for_system_call(app_process)) {
        call_number = ptrace(PTRACE_PEEKUSER, app_process, sizeof(long)*ORIG_RAX);
        call_counter[call_number]++;
        print_system_call_info(call_number);
        //wait until system call ends. (for each system call notifies twice start/end)
        wait_for_system_call(app_process);
        if (wait) {
            getchar();
        }
    }
    return 0;
}

void print_system_call_info(int call_number) {
    fprintf(
        stdout, "System call: %d name:%s location:%s \n",
        call_number,
        system_calls_list[call_number].sys_name,
        system_calls_list[call_number].implementation_path
    );
}


void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}


void print_system_calls_table_info(int syscalls[], int size){
    printf(" \n\n\tSystem Calls Table Information \n");
    printf("===============================================\n");
    printf("Sys Call ID                   Name       Count\n");
    printf("===============================================\n");

    for (int i = 0; i < size; ++i) {
        if(syscalls[i] !=0){
            printf("%11d%23s%12d\n", i, system_calls_list[i].sys_name, syscalls[i]);
        }
    }
}