//
// Created by geykelhodgson on 4/12/21.
//

#ifndef SOA_TAREA2_TRACE_H
#define SOA_TAREA2_TRACE_H

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>

#define SYSTEM_CALLS 350

int trace_app(char* app_file, char** app_argv, int* call_counter, int wait);
int run_app(char* app_file, char** app_argv);
int trace_process(pid_t app_process, int* call_counter, int wait);
int wait_for_system_call(pid_t app_process);
void print_system_call_info(int call_number);

#endif //SOA_TAREA2_TRACE_H
