#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"

/*---DEFINE MACROS---*/
#define MAX_PAST_INPUTS 30

/*---DECLARE GLOBAL VARIABLES USED---*/
extern int global_past_input_index;
extern char *global_past_inputs[MAX_PAST_INPUTS];

/*---DEFINE FUNCTIONS---*/
bool validate_string(char *string);

bool exceptions(char *word);

bool validate_word(char *word);

bool check_past_inputs(char *string);
