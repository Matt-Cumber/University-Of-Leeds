#include "output.h"

/*
  This file deals with outputs centred around the key word why
*/



/*---FUNCTION FOR WHY TRIGGER WORDS---*/
int why_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  if(words[index+1] != NULL && words[index+2] != NULL && words[index+3] != NULL
    && words[index+4] != NULL) {
      if(strcmp("do",words[index+1]) == 0 && strcmp("you",words[index+2]) == 0 &&
        strcmp("like",words[index+3]) == 0) {
          index = why_do_you_like_trigger(hashtable,words,index+4);
        }

      if(words[index+5] != NULL) {
        if(strcmp("do",words[index+1]) == 0 && strcmp("you",words[index+2]) == 0 &&
          strcmp("not",words[index+3]) == 0 && strcmp("like",words[index+4]) == 0) {
            index = why_do_you_not_like_trigger(hashtable,words,index+5);
          }
      }
    }

  return index;
}


int why_do_you_like_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---SEEDING RANDOM NUMBER---*/
  time_t t;
  srand((unsigned) time(&t));

  int why_do_you_like = rand() % 3;
  char like[90] = "";

  /*---ITERATE THROUGH WORDS LOOKING FOR DATA---*/
  while(words[index] != NULL) {

    /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
    if(check_word(hashtable,words[index]) == false) {
        break;
    }
    strcat(like,words[index]);
    ++index;
  }

  /*---PRINT THE CORRESPONDING MOOD TO EACH VALUE---*/
  if(why_do_you_like == 0) { printf("I like %s because it's good ",like); }
  else if(why_do_you_like == 1) { printf("I don't know "); }
  else if(like[strlen(like)-1] == 's') {
    printf("I like %s because I just love them ",like);
  }
  else { printf("I like %s because I just love it ",like); }

  return index;
}


int why_do_you_not_like_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---SEEDING RANDOM NUMBER---*/
  time_t t;
  srand((unsigned) time(&t));

  int why_do_you_not_like = rand() % 3;
  char like[90] = "";

  /*---ITERATE THROUGH WORDS LOOKING FOR DATA---*/
  while(words[index] != NULL) {

    /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
    if(check_word(hashtable,words[index]) == false) {
        break;
    }
    strcat(like,words[index]);
    ++index;
  }

  /*---PRINT THE CORRESPONDING MOOD TO EACH VALUE---*/
  if(why_do_you_not_like == 0) { printf("I don't like %s because it sucks ",like); }
  else if(why_do_you_not_like == 1) { printf("I don't know "); }
  else if(like[strlen(like)-1] == 's') {
    printf("I like %s because I just hate them ",like);
  }
  else { printf("I like %s because I just hate it ",like); }

  return index;
}
