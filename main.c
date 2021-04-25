#include <stdio.h>
#include <ctype.h>
#include "include/validator.h"
#include "include/trace.h"

int main(int argc, char **argv) {
    struct_arguments_fields * arguments = argument_type(argc, argv);
    int syscall[350] = {0};
    trace_app(arguments->program_command, arguments->args, syscall, arguments -> wait);
//    for (int i = 0; i < arguments->program_command_args_size; ++i) {
//        fprintf(stdout,"Param: %s\n", arguments->args[i]);
//    }

    print_system_calls_table_info(syscall, 350);



    return 0; 
}

// tabla nombres
// fix command  without params
// print final result table