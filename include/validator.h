
#ifndef SOA_TAREA2_VALIDATOR_H
#define SOA_TAREA2_VALIDATOR_H

#include <string.h>

typedef struct ArgumentsFields {
   char * flag;
   int wait;
   char * program_command;
   char ** args;
   int program_command_args_size;
} ArgumentsFields;

ArgumentsFields* argument_type(int, char **);

void concat_strings(char *, char *);

#endif
