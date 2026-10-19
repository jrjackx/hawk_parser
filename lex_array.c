#include "library.h"

/* creates the Lex_Array record and populates it using the input file */
Lex_Array* lexify(FILE* the_file) {

    /* helper functions */

    void capacity_check(Lex_Array* l) {

        if (l->size >= l->capacity) {

            l->capacity *= 2;
            l->strings = realloc(l->strings, l->capacity * sizeof(char*));
        }
    }

    bool is_operator(char letter) {
        
        char operators[] = {';', ':', '=', ',', '<', '>', '+', '-', '*', '/', '(', ')'};
        for(int i = 0; i < 12; i++) { /* 12 is the length of operators */

            if (letter == operators[i]) {

                return true;
            }
        }
        
        return false;
    }

    void cut_and_send(Lex_Array* l, char* string, size_t* string_size_ptr, bool* empty_string_ptr) {
        
        string[*string_size_ptr] = '\0';
        l->strings[l->size] = malloc((*string_size_ptr+1) * sizeof(char));
        capacity_check(l);
        strcpy(l->strings[l->size], string);
        l->size++;

        *string_size_ptr = 0;
        string = realloc(string, (*string_size_ptr + 1) * sizeof(char));
        *empty_string_ptr = true;
    }

    /* initializating */

    Lex_Array* l = (Lex_Array*)malloc(sizeof(Lex_Array));
    l->capacity = DEFAULT_CAPACITY;
    l->size = 0;
    l->cursor = -1; /* cursor is used to index strings. lex always increments cursor first thing,
                       so i need to do this in order to get strings[0] out of the first lex(). */
    l->line_count = 1;
    l->strings = malloc(l->capacity * sizeof(char*));

    size_t string_size = 0;
    char* string = malloc(sizeof(char));
    int letter = 0;
    bool empty_string = true;
    bool done = false;

    /* main loop */
    
    while (!done) {
        
        letter = fgetc(the_file);
       
        if (letter == EOF) {

            if (!empty_string) {

               cut_and_send(l, string, &string_size, &empty_string);
            }

            capacity_check(l);
            l->strings[l->size] = (char*)malloc(4 * sizeof(char));
            l->strings[l->size] = "EOF";
            done = true;
        }

        else if (!empty_string && (letter == ' ' || letter == '\t')) {
            
            cut_and_send(l, string, &string_size, &empty_string);
        }

        else if (letter != ' ' && letter != '\t') {

            if(!empty_string && (is_operator(letter) || letter == '\n')) { /*newline characters will be
                                                                             counted for error messages*/

                cut_and_send(l, string, &string_size, &empty_string);
            }

            empty_string = false;
            string[string_size] = letter;
            string_size++;
            string = realloc(string, (string_size + 1) * sizeof(char));

            if(is_operator(letter) || letter == '\n') {

                cut_and_send(l, string, &string_size, &empty_string);
            }        
        }
    }
   
    free(string);
    return l;
}

/* helper functions */

void lex(Lex_Array* l) {

    l->cursor++;
    while (strcmp("\n", l->strings[l->cursor]) == 0) {

        l->cursor++;
        l->line_count++;
    }

    set_token(l);
}

void set_token(Lex_Array* l) {

    char* lex = l->strings[l->cursor];
    if (strcmp(lex, "program") == 0) {l->token = "PROGRAM";}
    else if (strcmp(lex, "begin") != 0 && l->token == "PROGRAM") (l->token = "DECL_SEC");
    else if (l->token == "DECL_SEC") (l->token = "DECL");
    else if (strcmp(lex, "begin") == 0) {l->token = "STMT_SEC";}
    else if (strcmp(lex, "input") == 0) {l->token = "INPUT";}
    else if (strcmp(lex, "output") == 0) {l->token = "OUTPUT";}
    else (l->token = "UNIDENTIFIED");
}













