#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*---DEFINE MACROS---*/
#define MAX_LENGTH_INPUT 81

/*---DEFINE FUNCTIONS---*/
char *replace_a_word(char *word);

void replace_words(char *string);

void remove_character(char *string, const char character_to_be_removed, int position_in_string);

void format_string(char *string);
