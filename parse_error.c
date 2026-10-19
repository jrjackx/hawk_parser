#include "library.h"

void parse_error(Lex_Array* l, ERROR_TYPE e) {
    
    switch (e) {

        case ILLEGAL_SYMBOL:
            fprintf(stderr, "Error on line %zu: unrecognized symbol \"%s\". Did you declare it?\n",
                    l->line_count, l->strings[l->cursor]);
            exit(EXIT_FAILURE);
            break;

        case ILLEGAL_IDENTIFIER:
            fprintf(stderr, "TODO MAKE A PROPER ERROR MESSAGE HERE\n");
            exit(EXIT_FAILURE);
            break;
            
        case ILLEGAL_NUMBER:
            fprintf(stderr, "TODO MAKE A PROPER ERROR MESSAGE HERE\n");
            exit(EXIT_FAILURE);
            break;
       
        case EXPECTED_PROGRAM:
            fprintf(stderr, "Error on line %zu: code must begin with program token\n", l->line_count);
            exit(EXIT_FAILURE);
            break;
    }
}
