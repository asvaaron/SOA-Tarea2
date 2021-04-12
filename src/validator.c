#include "../include/validator.h"


char* argument_type(int argc, char ** argv){
    char * argument_type;
    for (int i = 1; i < argc; i++) {
       if (strcmp("-V", argv[i]) == 0) {
          printf("Verbose \n");
          argument_type = argv[i];
       }
       if (strcmp("-v", argv[i]) == 0) {
          printf("verbose \n ");
          argument_type = argv[i];
       }
       printf("argument %s\n", argv[i]);

    }

    return argument_type;
}