#include "library.h"

Lex_Array* l;

int main(int argc, char* argv[]) {

    if (file_check(argc, argv) == EXIT_FAILURE) {
       
        exit(EXIT_FAILURE);
    }

    FILE* the_file;
    the_file = fopen(argv[1], "r");
    l = lexify(the_file);

    fclose(the_file);
    
    lex(l);
    if (strcmp("PROGRAM", l->token) != 0){
       parse_error(l, EXPECTED_PROGRAM);
    }

    else {

        printf("%s\n", l->token);
        program(l);
    }

    exit(EXIT_SUCCESS);
}

