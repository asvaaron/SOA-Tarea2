#include "../include/validator.h"


ArgumentsFields* argument_type(int argc, char ** argv){
   ArgumentsFields * arguments = malloc(sizeof(ArgumentsFields));
   char * program_command[argc-1]; 
   int j = 0;
   int wait = 0;
   for (int i = 1; i < argc; i++) {
      if (strcmp("-v", argv[i]) == 0) {
         arguments->flag = argv[i];
      }
   
      if (strcmp("-V", argv[i]) == 0) {
         arguments->flag = argv[i];
         if(wait ==0){
            wait = 1;
         }
      }
      if(strcmp("-v", argv[i]) != 0 && strcmp("-V", argv[i])!=0){
         program_command[j++]=argv[i];
      }
   }
   arguments ->program_command = program_command;
   arguments -> wait = wait;
   arguments ->program_command_size = j;
   return arguments;
}

void concat_strings(char * a, char * b){
   return 0;
}