#include "output.h"

/*
  This file deals with outputs centred around the key word what
*/


/*---FUNCTON FOR WHAT TRIGGER WORDS---*/
int what_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  if(words[index+1] != NULL && words[index+2] != NULL && words[index+3] != NULL) {
    if(strcmp(words[index+1],"do") == 0 && strcmp(words[index+2],"you") == 0 &&
      strcmp(words[index+3],"like") == 0) {
        index = what_do_you_like(hashtable,words,index+3);
      }
  }

  /*---ENSURE WORDS ARE NOT NULL TO AVOID CRASHING---*/
  if(words[index+1] != NULL && words[index+2] != NULL && words[index+3] != NULL &&
     words[index+4] != NULL) {
       /*---CHECK FOR TRIGGER PHRASES---*/
      if(strcmp(words[index+1],"is") == 0 && strcmp(words[index+2],"your") == 0 &&
        strcmp(words[index+3],"favourite") == 0) {
          index = what_is_your_favourite_trigger(hashtable,words,index+4);
      }

      else if(strcmp(words[index+1],"is") == 0 && strcmp(words[index+2],"my") == 0 &&
        strcmp(words[index+3],"favourite") == 0) {
          index = what_is_my_favourite_trigger(hashtable,words,index+4);
      }
  }

  return index;
}


/*---FUNCTION FOR WHAT PHRASE---*/
int what_is_your_favourite_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---INITIALISE HASH KEY---*/
  char bot_fave[90] = "botfave*";

  /*---CREATE KEY---*/
  strcat(bot_fave,words[index]);

  /*---GET THE DATA FOR THE KEY---*/
  char *data = get_entry_data(hashtable,bot_fave);

  /*---PRINT THE DATA IF POSSIBLE---*/
  if(data != NULL) {
    printf("%s ",data);
    return index;
  }

  /*---CREATE COUNTER TO GET REST OF WORDS---*/
  int counter = index+1;

  /*---ITERATE THROUGH REST OF WORDS---*/
  while(words[counter] != NULL) {

    /*---ADD WORDS TO KEY AND CHECK IF THERE IS DATA FOR NEW KEY---*/
    strcat(bot_fave,words[counter]);
    data = get_entry_data(hashtable,bot_fave);
    if(data != NULL) {
      printf("%s ",data);
      return counter;
    }

    /*---INCREMENT COUNTER TO ADD NEXT WORD---*/
    ++counter;
  }

  printf("I don't know what my favourite of that is ");
  return index;
}


/*---FUNCTION FOR WHAT PHRASE---*/
int what_is_my_favourite_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---INITIALISE HASH KEY---*/
  char user_fave[90] = "userfave*";
  char fave[80] = "";

  /*---CREATE KEY---*/
  strcat(user_fave,words[index]);
  strcat(fave,words[index]);

  /*---GET THE DATA FOR THE KEY---*/
  char *data = get_entry_data(hashtable,user_fave);

  /*---PRINT THE DATA IF POSSIBLE---*/
  if(data != NULL) {
    printf("Your favourite %s is %s",fave,data);
    return index;
  }

  /*---CREATE COUNTER TO GET REST OF WORDS---*/
  int counter = index+1;

  /*---ITERATE THROUGH REST OF WORDS---*/
  while(words[counter] != NULL) {

    /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
    if(check_word(hashtable,words[counter]) == false) {
        break;
    }

    /*---ADD WORDS TO KEY AND CHECK IF THERE IS DATA FOR NEW KEY---*/
    strcat(user_fave,words[counter]);
    strcat(fave,words[counter]);
    data = get_entry_data(hashtable,user_fave);
    if(data != NULL) {
      printf("Your favourite %s is %s",fave,data);
      return counter;
    }

    /*---INCREMENT COUNTER TO ADD NEXT WORD---*/
    ++counter;
  }

  printf("I don't know have you told me yet? ");
  return counter-1;
}


/*---FUNCTION FOR WHAT PHRASE---*/
int what_do_you_like(entry_t *hashtable[SIZE],char **words, int index) {

  /*---DECLARE VARIABLES---*/
  int i;
  int k = 8;
  int first;

  printf("a few things I like are ");

  /*---SEEDING RANDOM NUMBER---*/
  time_t t;
  srand((unsigned) time(&t));

  while(1) {

  i = rand() % SIZE;

  if(hashtable[i] != NULL) {
    if(strncmp(hashtable[i]->entry_key,"botlike*",8) == 0) {
      first = i;
      while(hashtable[i]->entry_key[k] != '\0') {
        printf("%c",hashtable[i]->entry_key[k]);
        ++k;
      }
      break;
    }
  }

  }

  printf(" and ");
  k = 8;

  while(1) {

  i = rand() % SIZE;

  if(i == first) {
    continue;
  }

  if(hashtable[i] != NULL) {
    if(strncmp(hashtable[i]->entry_key,"botlike*",8) == 0) {
      while(hashtable[i]->entry_key[k] != '\0') {
        printf("%c",hashtable[i]->entry_key[k]);
        ++k;
      }
      break;
    }
  }

  }

  printf(" ");
  return index;
}
