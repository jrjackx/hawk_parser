#include "library.h"

void program(Lex_Array* l) {

    set_token(l, "PROGRAM");

    l->idarr_capacity = DEFAULT_CAPACITY;
    l->idarr_size = 0;        
    l->identifiers = (char**)malloc(l->idarr_capacity*sizeof(char*));

    lex(l);

    if (lex_is(l, "begin")) {
        
        statement_section(l);
    } 

    else {
        
        declaration_section(l);
        
        if (lex_is(l, "begin")) {
            
            statement_section(l);
        }

        else {printf("Time to bust out gdb.. sigh...");}
        exit(1);
    }
}

void declaration_section(Lex_Array* l) {


    set_token(l, "DECL_SEC");

    declaration(l);
    lex(l);

    if (!lex_is(l, "begin")) {

        declaration_section(l);
    }
}

void declaration(Lex_Array* l) {

    set_token(l, "DECL");
    make_id_list(l);

    lex(l);
    if (!lex_is(l, "int") && !lex_is(l, "float") && !lex_is(l, "double")) {
        
        parse_error(l, UNKNOWN_TYPE, "N/A"); 
    }

    lex(l);
    if (!lex_is(l, ";")) {

        parse_error(l, EXPECTED_SEMICOLON, "declarations must end with a semicolon.");
    }

}


void idarr_capacity_check(Lex_Array* l) {

    if (l->idarr_size >= l->idarr_capacity) {

        l->idarr_capacity *= 2;
        l->identifiers = (char**)realloc(l->identifiers, l->idarr_capacity*sizeof(char*));
    }
}

void make_id_list(Lex_Array* l) {

    set_token(l, "ID_LIST");

    /* helper functions */
    
    bool id_is_keyword(Lex_Array* l) {

        char* keywords[] = {"program", "begin", "end", "if", "then", "else", "while", "loop",
            "input", "output", "int", "float", "double"};
        const char KEYWORDS_SIZE = 13;

        for (int i = 0; i < KEYWORDS_SIZE; i++) {
            
            if (lex_is(l, keywords[i])) {

                return true;
            }
        }

        return false;
    }
    
    bool id_is_good_format(Lex_Array* l) {

        /* I genuinely can't think of a better way to do this. sorry. */
        char valid_w_out_digits[] = 
        {'_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        const char VALID_W_OUT_DIGITS_SIZE = 53;

        char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        const char DIGITS_SIZE = 10;
        const char FULL_VALID_SIZE = VALID_W_OUT_DIGITS_SIZE + DIGITS_SIZE;

        /* checking the first character */
        bool is_valid_character = false;
        for (int j = 0; j < VALID_W_OUT_DIGITS_SIZE; j++) {
            
           if ((l->strings[l->cursor])[0] == valid_w_out_digits[j]) {
               is_valid_character = true;
               break;
           }
        }

        if (!is_valid_character) {return false;}

        /* checking the rest of the characters */
        size_t valid_characters_cursor;
        for (int i = 1; i < strlen(l->strings[l->cursor]); i++) {

            is_valid_character = false;

            for (int j = 0; j < FULL_VALID_SIZE; j++) {
            
                if (j >= VALID_W_OUT_DIGITS_SIZE)
                {valid_characters_cursor = j - VALID_W_OUT_DIGITS_SIZE;}
                
                else 
                {valid_characters_cursor = j;}

                if (j >= VALID_W_OUT_DIGITS_SIZE) {

                    if ((l->strings[l->cursor])[i] == digits[valid_characters_cursor]) {
                        
                        is_valid_character = true;
                        break;
                    }
                }

                else {
                    
                    if ((l->strings[l->cursor])[i] == valid_w_out_digits[valid_characters_cursor]) {
                        
                        is_valid_character = true;
                        break;
                    }
                }
            }

            /* honestly could have just put this all in one array and then done one check
             * that only uses a portion of the array for the first character. oh well. */

            if (!is_valid_character) {return false;}
        }

        return true;
    }

    /* checkpoints */

    if (id_is_keyword(l)) {

        parse_error(l, ILLEGAL_IDENTIFIER, "keyword used as identifier name.");
    }

    if (!id_is_good_format(l)) {
    
        parse_error(l, ILLEGAL_IDENTIFIER, "identifier contains irregular character.\n\t\
ID -> (_|a|b|...|z|A|B|...Z)(_|a|b|...|z|A|B|...|Z|0|1|...|9)*");
    }

    /* checking for duplicate identifiers */
    for (int i = 0; i < l->idarr_size; i++) {

        if (lex_is(l, l->identifiers[i])) {

            parse_error(l, ILLEGAL_IDENTIFIER, "identifier already declared.");
        }
    }

    /* all checkpoints passed */
    idarr_capacity_check(l);
    l->identifiers[l->idarr_size] = l->strings[l->cursor];
    l->idarr_size++;

    lex(l);
    if (lex_is(l, ",")) {lex(l); make_id_list(l);}
    
    else if (!lex_is(l, ":")) {
        
        parse_error(l, ILLEGAL_SYMBOL, "identifiers must be separated by commas (,)\
and end with a colon (:).");
    }
}


void statement_section(Lex_Array* l) {

    /* TODO start working on the statement section. how hard can it be?
     * probably also move it to its own file.*/
    set_token(l, "STMT_SEC");
    exit(0);
}













