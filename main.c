#include <stdio.h>
#include <ctype.h>
#include <pthread.h>

int main(int argc, char **argv) {

/* iterate over all arguments */
   for (int i = 1; i < argc; i++) {
       if (strcmp("-V", argv[i]) == 0) {
          printf("Verbose \n");
       }
       if (strcmp("-v", argv[i]) == 0) {
          printf("verbose \n ");
       }
       printf("argument %s\n", argv[i]);
   }
    return 0; 
}
