#include "library.h"

void program(Lex_Array* l) {

    lex(l);
    
    if (strcmp(l->token, "DECL_SEC") == 0) {

        printf("%s\n", l->token);
        declaration_section(l);
    }

    else if (strcmp(l->token, "STMT_SEC") == 0) {
        
        printf("%s\n", l->token);
        statement_section(l);
    }
}

void declaration_section(Lex_Array* l) {

    void symbol_capacity_check(Lex_Array* l) {

        if (l->symbol_size >= l->symbol_capacity) {

            l->symbol_capacity *= 2;
            l->symbol_table = (char**)realloc(l->symbol_table, l->symbol_capacity*sizeof(char*));
        }
    }
    
    if (l->symbol_table = NULL) {

        l->symbol_capacity = DEFAULT_CAPACITY;
        l->symbol_size = 0;        
        l->symbol_table = (char**)malloc(l->symbol_capacity*sizeof(char*));
    }
    
    declaration(l);
    
    /*TODO check (while loop) ? to make sure there are no more declaration sections.
     * make sure after hitting the last declaration section, that it returns all the way
     * back to the top before going on to the statement section. */
}

void declaration(Lex_Array* l) {

    set_token(l);
    printf("%s\n", l->token);
    id_list(l);
}

void id_list(Lex_Array* l) {

}

void statement_section(Lex_Array* l) {

}
