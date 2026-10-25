#include "library.h"

void parse_error(Lex_Array* l, ERROR_TYPE e, char* reason) {
    
    switch (e) {

        case ILLEGAL_SYMBOL:
            fprintf(stderr, "Error on line %zu: illegal symbol \"%s\": %s\n",
                    l->line_count, l->strings[l->cursor], reason);
            exit(EXIT_FAILURE);
            break;

        case ILLEGAL_IDENTIFIER:
            fprintf(stderr, "Error on line %zu: illegal identifier \"%s\": %s\n",
                    l->line_count, l->strings[l->cursor], reason);
            exit(EXIT_FAILURE);
            break;
            
        case ILLEGAL_NUMBER:
            fprintf(stderr, "TODO MAKE A PROPER ERROR MESSAGE HERE\n");
            exit(EXIT_FAILURE);
            break;
       
        case UNKNOWN_TYPE:
            fprintf(stderr, "Error on line %zu: unknown type \"%s\". Acceptable types are\
int, float, or double.\n", l->line_count, l->strings[l->cursor]);  
            exit(EXIT_FAILURE);
            break;

        case EXPECTED_PROGRAM:
            fprintf(stderr, "Error on line %zu: expected \"program\" but recieved\
\"%s\" instead.\n", l->line_count, l->strings[l->cursor]);
            exit(EXIT_FAILURE);
            break;

        case EXPECTED_SEMICOLON:
            fprintf(stderr, "Error on line %zu: missing semicolon: %s\n",
                    l->line_count, l->strings[l->cursor], reason);
            break;
    }
}
