#include <stdio.h>
#include <ctype.h>
#include "include/validator.h"

int main(int argc, char **argv) {
    ArgumentsFields * arguments = argument_type(argc, argv);
    printf("Type %s \n", arguments -> argument_type);
    return 0; 
}
