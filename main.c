#include <stdio.h>
#include <ctype.h>
#include "include/validator.h"
#include "include/trace.h"

int main(int argc, char **argv) {
    ArgumentsFields * arguments = argument_type(argc, argv);
    printf("Wait %d\n", arguments -> wait);
    printf("program %s\n", arguments -> program_command);
    printf("arguments size %d\n", arguments -> program_command_args_size);

    return 0; 
}
