#include "../include/validator.h"


ArgumentsFields* argument_type(int argc, char ** argv){
   ArgumentsFields * arguments = malloc(sizeof(ArgumentsFields));
   char * args[argc-1]; 
   int j = 0;
   int wait = 0;
   int flagged = 0;
   int first = 0; 
   for (int i = 1; i < argc; i++) {
      
      if (strcmp("-v", argv[i]) == 0 && flagged ==0) {
         arguments->flag = argv[i];
         flagged = 1;
      }
      else{
         if (strcmp("-v", argv[i]) == 0){
            j++;
         }
      }
   
      if (strcmp("-V", argv[i]) == 0 && flagged ==0) {
         arguments->flag = argv[i];
         if(wait ==0){
            wait = 1;
         }
         flagged =1;
         
      }
      else{
         if (strcmp("-V", argv[i]) == 0){
            j++;
         }
      }
      if( strcmp("-v", argv[i]) != 0 && strcmp("-V", argv[i])!= 0){
         if(first ==0){
            arguments -> program_command = argv[i];
            first++;
         }
         else{
            j++;
         }
      }
   }
   arguments->args = malloc(sizeof(char) * j);
   arguments->wait = wait;
   arguments->program_command_args_size = j;
   int z = 0;
   for(int i=(argc-j);i<argc; i++){
      printf("z: %d i: %d \n",z,i);
      arguments -> args[z] = argv[i];
      z++;
   }
   return arguments;
}

void concat_strings(char * a, char * b){
   return 0;
} 