#include "../include/validator.h"


ArgumentsFields* argument_type(int argc, char ** argv){
   ArgumentsFields * arguments = malloc(sizeof(ArgumentsFields));; 
   for (int i = 1; i < argc; i++) {
      if (strcmp("-V", argv[i]) == 0) {
         arguments -> flag = argv[i];
      }
      if (strcmp("-v", argv[i]) == 0) {
         arguments -> flag = argv[i];
      }
    }

    return arguments;
}