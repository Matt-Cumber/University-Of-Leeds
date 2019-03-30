#include "output.h"

/*
  This file deals with outputs centred around the key word you
*/

extern int global_bot_mood;

/*---FUNCTON FOR YOU TRIGGER WORDS---*/
int you_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  /*---RUN IF THERE ARE MORE WORDS---*/
  if(words[index+1] != NULL) {

    /*---DECLARE VARIABLES---*/
    char you[90] = "you*";
    char *data;

    strcat(you,words[index+1]);

    /*---GET DATA AND PRINT IF NOT NULL---*/
    data = get_entry_data(hashtable,you);
    if(data != NULL) {
      printf("%s ",data);
      if(strcmp(you,"you*suck") == 0) {
        printf("anyway that wasn't very nice now I'm sad ");
        global_bot_mood = 4;
      }
      return index+1;
    }

    int counter = index+2;

    /*---ELSE LOOP THROUGH WORDS CHECKING FOR DATA---*/
    while(words[counter] != NULL) {
      if(check_word(hashtable,words[counter]) == false) {
          break;
      }
        strcat(you,words[counter]);
        data = get_entry_data(hashtable,you);
        if(data != NULL) {
          printf("%s ",data);
          return counter-1;
        }
      ++counter;
    }

    /*---PRINT GENERIC RESPONSE OTHERWISE---*/
    printf("okay ");
    return counter-1;
  }
  return index;
}
