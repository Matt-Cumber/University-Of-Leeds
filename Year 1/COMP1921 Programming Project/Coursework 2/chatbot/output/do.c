#include "output.h"

/*
  This file deals with outputs centred around the key word do
*/

/*---FUNCTON FOR DO TRIGGER WORDS---*/
int do_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  /*---ENSURE WORDS ARE NOT NULL TO AVOID CRASHING---*/
  if(words[index+1] != NULL && words[index+2] != NULL && words[index+3] != NULL) {
    /*---CHECK FOR TRIGGER PHRASES---*/
    if(strcmp(words[index+1],"you") == 0 && strcmp(words[index+2],"like") == 0) {
      index = do_you_like_trigger(hashtable,words,index+3);
    }
    else if(strcmp(words[index+1],"i") == 0 && strcmp(words[index+2],"like") == 0) {
      index = do_i_like_trigger(hashtable,words,index+3);
    }
  }
  return index;
}


/*---FUNCTION FOR DO PHRASE---*/
int do_you_like_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---INITIALISE BOT HASH KEY, PRINT WORD AND USER HASH KEY---*/
  char bot_like[90] = "botlike*";
  char user_like[90] = "userlike*";
  char like[80] = "";

  /*---CREATE BOT KEY, PRINT WORD AND USER KEY---*/
  strcat(bot_like,words[index]);
  strcat(like,words[index]);
  strcat(user_like,words[index]);

  /*---GET THE DATA FOR THE KEY---*/
  char *data = get_entry_data(hashtable,bot_like);

  /*---PRINT THE DATA IF POSSIBLE---*/
  if(data != NULL) {
    printf("%s ",data);


    /*---CHECK IF USER HAS OPINION ON SAME THING OTHERWISE ASK USER---*/
    if(get_entry_data(hashtable,user_like) == NULL) {
      printf("do you like %s? ",like);
      next_entry_after_do_you_like(hashtable,like);
    }
    return index;
  }

  /*---CREATE COUNTER TO GET REST OF WORDS---*/
  int counter = index+1;

  /*---ITERATE THROUGH REST OF WORDS---*/
  while(words[counter] != NULL) {
    if(check_word(hashtable,words[counter]) == false) {
        break;
    }

    /*---ADD WORDS TO KEYS AND CHECK IF THERE IS DATA FOR NEW KEY---*/
    strcat(bot_like,words[counter]);
    strcat(like," ");
    strcat(like,words[counter]);
    strcat(user_like,words[counter]);
    data = get_entry_data(hashtable,bot_like);
    if(data != NULL) {
      printf("%s ",data);

      /*---CHECK IF USER HAS OPINION ON SAME THING OTHERWISE ASK USER---*/
      if(get_entry_data(hashtable,user_like) == NULL) {
        printf("do you like %s? ",like);
      }
      return counter;
    }

    /*---INCREMENT COUNTER TO ADD NEXT WORD---*/
    ++counter;
  }

  /*---PRINT MESSAGE IF UNSUCCESSFUL AT FINDING HASH DATA---*/
  printf("I don't know if I like %s ",like);

  /*---CHECK IF USER HAS OPINION ON SAME THING OTHERWISE ASK USER---*/
  if(get_entry_data(hashtable,user_like) == NULL) {
    printf("do you like %s? ",like);
    next_entry_after_do_you_like(hashtable,like);
  }
  return index;
}


/*FUNCTION FOR DO PHRASE---*/
int do_i_like_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---INITIALISE HASH KEY---*/
  char user_like[90] = "userlike*";

  /*---CREATE KEY---*/
  strcat(user_like,words[index]);

  /*---GET THE DATA FOR THE KEY---*/
  char *data = get_entry_data(hashtable,user_like);

  /*---IF DATA EXISTS---*/
  if(data != NULL) {

    /*---CHECK IF THERE ARE FURTHER WORDS---*/
    if(words[index+1] != NULL) {
      /*---CHECK OF THE NEXT WORD CAN BE APART OF LIKE STATEMENT---*/
      if(check_word(hashtable,words[index+1]) == false) {
        /*---PRINT CORRECT MESSAGE WHEN THE LIKE IS A MATCH AND REST OF INPUT CAN'T BE PART OF LIKE---*/
        if(strcmp("true",data) == 0) {
          printf("Yes you do you told me so ");
        }
        else {
          printf("No you do not you told me so ");
        }
        return index;
      }
    }

    /*---IF NO FURTHER WORDS PRINT CORRECT MESSAGE---*/
    else {
      if(strcmp("true",data) == 0) {
        printf("Yes you do you told me so ");
      }
      else {
        printf("No you do not you told me so ");
      }
      return index;
    }
  }

  /*---CREATE COUNTER TO GET REST OF WORDS---*/
  int counter = index+1;

  /*---ITERATE THROUGH REST OF WORDS---*/
  while(words[counter] != NULL) {

    /*---ADD WORDS TO KEY AND CHECK IF THERE IS DATA FOR NEW KEY---*/
    strcat(user_like,words[counter]);
    data = get_entry_data(hashtable,user_like);
    /*---SIMILAR TO BEFORE EXCEPT WORKING WITH COUNTER NOT INDEX---*/
    if(data != NULL ) {
      if(words[counter+1] != NULL) {
        if(check_word(hashtable,words[counter+1]) == false) {
          if(strcmp("true",data) == 0) {
            printf("Yes you do you told me so ");
          }
          else {
            printf("No you do not you told me so ");
          }
          return counter;
        }
      }
      else {
        if(strcmp("true",data) == 0) {
          printf("Yes you do you told me so ");
        }
        else {
          printf("No you do not you told me so ");
        }
        return counter;
      }
    }

    /*---INCREMENT COUNTER TO ADD NEXT WORD---*/
    ++counter;
  }

  printf("I don't know have you told me yet? ");
  return counter-1;
}
