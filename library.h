#ifndef LIBRARY
#define LIBRARY

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_CAPACITY 8

/* structs & enums */
typedef struct Lex_Array {

    /* initializing */
    char** strings;
    size_t capacity;
    size_t size;
    
    /* navigating */
    int cursor;
    size_t line_count;

    /* derived information */
    char* token;
    char** symbol_table;

    /* symbol initializing */
    size_t symbol_capacity;
    size_t symbol_size;
} Lex_Array;

typedef enum ERROR_TYPE {
    ILLEGAL_SYMBOL,
    ILLEGAL_IDENTIFIER,
    ILLEGAL_NUMBER,
    EXPECTED_PROGRAM
} ERROR_TYPE;

/* file_check.c */
int file_check(int argc, char* argv[]);

/* lex.c */
Lex_Array* lexify(FILE* the_file); 
    void capacity_check(Lex_Array* l);
    bool is_operator(char letter);
    void cut_and_send(Lex_Array* l, char* string, size_t* string_size_ptr, bool* empty_string_ptr);
void lex(Lex_Array* l);
void set_token(Lex_Array* l);

/* parse_error.c */
void parse_error(Lex_Array* l, ERROR_TYPE e);

/* parse_functions.c */
void program(Lex_Array* l);
void declaration_section(Lex_Array* l);
    void symbol_capacity_check(Lex_Array* l);
void declaration(Lex_Array* l);
void id_list(Lex_Array* l);
void statement_section(Lex_Array* l);

#endif

