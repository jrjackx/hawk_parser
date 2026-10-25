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
    if (!lex_is(l, "program")) { /* TODO finish this part */
       parse_error(l, EXPECTED_PROGRAM, "N/A");
    }

    else {

        program(l);
    }

    exit(EXIT_SUCCESS);
}

