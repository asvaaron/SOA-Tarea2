#include <stdio.h>
#include <ctype.h>
#include "include/validator.h"
#include "include/trace.h"

int main(int argc, char **argv) {
    ArgumentsFields * arguments = argument_type(argc, argv);
    printf("Wait %d\n", arguments -> wait);
    printf("program %s\n", arguments -> program_command);
    printf("arguments size %d\n", arguments -> program_command_args_size);
    int syscall[350] = {0};
    trace_app(arguments->program_command, arguments->args, syscall, arguments -> wait);
//    for (int i = 0; i < arguments->program_command_args_size; ++i) {
//        fprintf(stdout,"Param: %s\n", arguments->args[i]);
//    }
//    for (int i = 0; i < 350; ++i) {
//        printf("System call: %d, %d\n", i, syscall[i]);
//    }



    return 0; 
}

// tabla nombres
// fix command  without params
// print final result table