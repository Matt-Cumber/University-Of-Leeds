#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "../myhashstring.h"
#include "../input.h"
#include "../validate.h"
#include "../format.h"

/*---DEFINE MACROS---*/
#define MAX_LENGTH_INPUT 81
#define CHATBOT_NAME "MattBot"

/*---DEFINE FUNCTIONS---*/
void help_me_talk();
bool exit_messages(char *string);
void get_note_word();
void get_like_word();
bool try_reply(entry_t *hashtable[SIZE], char *input);
int find_trigger_word(entry_t *hashtable[SIZE],char **words,int index);
int what_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int what_is_your_favourite_trigger(entry_t *hashtable[SIZE],char **words, int index);
int what_is_my_favourite_trigger(entry_t *hashtable[SIZE],char **words, int index);
int what_do_you_like(entry_t *hashtable[SIZE],char **words, int index);
int how_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
void how_are_you_trigger();
void how_was_your_day_trigger();
int who_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int who_trigger(entry_t *hashtable[SIZE],char **words, int index);
int do_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int do_you_like_trigger(entry_t *hashtable[SIZE],char **words, int index);
int do_i_like_trigger(entry_t *hashtable[SIZE],char **words, int index);
int went_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int went_trigger(entry_t *hashtable[SIZE],char **words, int index);
int going_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int i_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int i_like_trigger(entry_t *hashtable[SIZE],char **words, int index);
int i_am_trigger(entry_t *hashtable[SIZE],char **words, int index);
int i_have_trigger(entry_t *hashtable[SIZE],char **words, int index);
int i_do_not_like_trigger(entry_t *hashtable[SIZE],char **words, int index);
int you_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int why_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int why_do_you_like_trigger(entry_t *hashtable[SIZE],char **words, int index);
int why_do_you_not_like_trigger(entry_t *hashtable[SIZE],char **words, int index);
int my_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int my_favourite_trigger(entry_t *hashtable[SIZE],char **words, int index);
int change_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
int are_trigger_word(entry_t *hashtable[SIZE],char **words, int index);
void tell_a_joke();
void sing_a_song();
void next_entry_after_do_you_like(entry_t *hashtable[SIZE], char *like);
bool check_word(entry_t *hashtable[SIZE], char *word);

// bool try_get_repsonse(entry_t *hashtable[SIZE], char *string);
// int my_name_is(entry_t *hashtable[SIZE], char **words, int index);
// int i_am(entry_t *hashtable[SIZE], char **words, int index);
// int went(entry_t *hashtable[SIZE], char **words, int index);
// int do_i_like(entry_t *hashtable[SIZE], char **words, int index);
// int find_question(entry_t *hashtable[SIZE], char **words, int index);
// int what_response(entry_t *hashtable[SIZE], char **words, int index);
// void what_is_your_favourite(entry_t *hashtable[SIZE], char *string);
// void what_do_i_like(entry_t *hashtable[SIZE]);
// int how_response(entry_t *hashtable[SIZE], char **words, int index);
// int find_like_do_not_like(entry_t *hashtable[SIZE], char **words, int index);
// void how_are_you_reply();
// bool exit_messages(char *string);
// bool known_inputs(char *string);
// void get_note_word();
