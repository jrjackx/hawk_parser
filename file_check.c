#include "library.h"

int file_check(int argc, char* argv[]) {

   if (argc != 2) {

       fprintf(stderr, "Improper usage. Use Hawk [filename].\n");
       return EXIT_FAILURE;
   }

   else {

       FILE* check;
       check = fopen(argv[1], "r");
   
       if (check == NULL) {

           fprintf(stderr, "No such file.\n");
           return EXIT_FAILURE;
       }

       fclose(check);
       return 0;
   }
}
