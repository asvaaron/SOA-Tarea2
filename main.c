#include <stdio.h>
#include <ctype.h>
#include "include/validator.h"

int main(int argc, char **argv) {
    char * type = argument_type(argc, argv);
    printf("Type %s", type);
    return 0; 
}
