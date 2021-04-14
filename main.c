#include <stdio.h>
#include <ctype.h>
#include "include/validator.h"

int main(int argc, char **argv) {
    ArgumentsFields * arguments = argument_type(argc, argv);
    printf("Type %d \n", arguments -> program_command_size);
    // for(int i=0; i<arguments->program_command_size; i++){
    //    printf("Args: %d. %s\n", i, arguments -> program_command[i]);
    // }
    return 0; 
}
