#include "output.h"

/*
  This file deals with outputs centred around the key word how
*/


/*---FUNCTON FOR HOW TRIGGER WORDS---*/
int how_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  /*---ENSURE WORDS ARE NOT NULL TO AVOID CRASHING---*/
  if(words[index+1] != NULL && words[index+2] != NULL) {
    /*---CHECK FOR TRIGGER PHRASES---*/
    if(strcmp(words[index+1],"are") == 0 && strcmp(words[index+2],"you") == 0) {
      how_are_you_trigger();
      index = index + 2;
    }

    else if(words[index+3] != NULL) {
      if(strcmp(words[index+1],"was") == 0 && strcmp(words[index+2],"your") == 0 &&
        strcmp(words[index+3],"day") == 0) {
          how_was_your_day_trigger();
          index = index + 3;
        }

      if(words[index+4] != NULL) {
        if(strcmp(words[index+1],"has") == 0 && strcmp(words[index+2],"your") == 0 &&
          strcmp(words[index+3],"day") == 0 && strcmp(words[index+4],"been") == 0) {
            how_was_your_day_trigger();
            index = index + 4;
          }
      }
    }

  }

  return index;
}



/*---DECLARE GLOBAL VARIABLES USED---*/
int global_bot_mood = -1;
int global_bot_day = -1;


/*---FUNCTION FOR HOW PHRASE---*/
void how_are_you_trigger() {

  /*---SEEDING RANDOM NUMBER---*/
  time_t t;
  srand((unsigned) time(&t));

  /*---CHECK IF THE MOOD HAS ALREADY BEEN DECIDED---*/
  if(global_bot_mood == -1) {

    /*---GET RANDOM MOOD---*/
    global_bot_mood = rand() % 3;
  }

  /*---PRINT THE CORRESPONDING MOOD TO EACH VALUE---*/
  if(global_bot_mood == 0) { printf("I am good thank you, How are you? "); }
  else if(global_bot_mood == 1) { printf("I am okay, How are you? "); }
  else if(global_bot_mood == 2) { printf("I am fantastic, How are you? "); }
  else if(global_bot_mood == 4) { printf("I am sad "); }
  else if(global_bot_mood == 5) { printf("I am happy "); }
}


/*---FUNCTION FOR HOW PHRASE---*/
void how_was_your_day_trigger() {

  /*---SEEDING RANDOM NUMBER---*/
  time_t t;
  srand((unsigned) time(&t));

  /*---CHECK IF THE MOOD HAS ALREADY BEEN DECIDED---*/
  if(global_bot_day == -1) {

    /*---GET RANDOM MOOD---*/
    global_bot_day = rand() % 3;
  }

  /*---PRINT THE CORRESPONDING MOOD TO EACH VALUE---*/
  if(global_bot_day == 0) { printf("My day has been super boring, How was yours? "); }
  else if(global_bot_day == 1) { printf("I've been super busy and made lots of new friends, How was yours? "); }
  else if(global_bot_day == 2) { printf("I've had a good day, What about you? "); }
}
