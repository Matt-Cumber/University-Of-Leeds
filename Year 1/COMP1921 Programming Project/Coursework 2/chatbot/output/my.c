#include "output.h"

/*
  This file deals with outputs centred around the key word my
*/


/*---FUNCTION FOR MY TRIGGER---*/
int my_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  /*---ENSURE WORDS ARE NOT NULL---*/
  if(words[index+1] != NULL && words[index+2] != NULL) {
    /*---CHECK FOR PHRASES---*/
    if(strcmp(words[index+1],"favourite") == 0) {
      index = my_favourite_trigger(hashtable,words,index+2);
    }

    /*---CHECK FOR FURTHER PHRASES---*/
    else if(words[index+3] != NULL) {
      if(strcmp("name",words[index+1]) == 0 && strcmp("is",words[index+2]) == 0) {

        /*---ADD THE NAME TO HASHTABLE---*/
        words[index+3][0] = toupper(words[index+3][0]);
        insert_into_hashtable(hashtable,"user*name",words[index+3]);
        printf("welcome %s ",words[index+3]);
        return index+3;
      }
    }
  }

  return index;
}



/*---FUNCTION FOR MY PHRASE---*/
int my_favourite_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---INITIALISE VARIABLES AND KEY AND DATA---*/
  int counter = index;
  int data_success = 0;
  char user_fave[90] = "userfave*";
  char user_fave_data[90] = "";
  char fave[90] = "";
  char *data;

  /*---GET THE HASH KEY---*/
  while(strcmp("is",words[counter]) != 0 && strcmp("are",words[counter]) != 0) {
    strcat(user_fave,words[counter]);
    strcat(fave,words[counter]);
    ++counter;
  }

  /*---GET DATA FOR HASH KEY---*/
  data = get_entry_data(hashtable,user_fave);

  /*---IF NOT NULL THEN USER ALREADY SAID SAME THING---*/
  if(data != NULL) {
    if(strcmp(words[counter],"are") == 0) {
      printf("You already told me your favourite %s, your favourite %s are %s ",fave,fave,data);
    }

    else if(strcmp(words[counter],"is") == 0) {
      printf("You already told me your favourite %s, your favourite %s is %s ",fave,fave,data);
    }

    return counter;
  }

  else {

    /*---INCREASE COUNTER TO MOVE ONTO WORD AFTER 'is' OR 'are'---*/
    ++counter;
    while(words[counter] != NULL) {
      if(check_word(hashtable,words[counter]) == false) {
          break;
      }

      /*---CREATE HASH DATA AND MAKE DATA SUCCESS---*/
      strcat(user_fave_data,words[counter]);
      ++data_success;
      ++counter;
    }

    /*---ONLY PRINT SUCCESS MESSAGE IF DATA A SUCCESS---*/
    if(data_success == 1) {
      insert_into_hashtable(hashtable,user_fave,user_fave_data);
      get_note_word();
      printf("I'll take note of that ");
      return counter-1;
    }
  }

  /*---MUST PRINT ERROR MESSAGE HERE AS REPY FUNCTION WILL BE SUCCESSFUL BUT THIS FUNCTION IS NOT---*/
  printf("I'm not sure that made sense to me ");
  return counter-1;
}
