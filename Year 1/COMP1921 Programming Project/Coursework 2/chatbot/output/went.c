#include "output.h"

/*
  This file deals with outputs centred around the key word went
*/


/*---FUNCTON FOR WENT TRIGGER WORDS---*/
int went_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  index = went_trigger(hashtable,words,index+1);

  return index;
}



/*FUNCTION FOR WENT PHRASE---*/
int went_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---DECLARE DATA AND KEY---*/
  char went[90] = "went*";
  char *data = "";

  /*---GET KEY---*/
  strcat(went,words[index]);

  /*---GET DATA---*/
  data = get_entry_data(hashtable,went);

  /*---PRINT DATA---*/
  if(data != NULL) {
    printf("%s ",data);
  }

  else {
    int counter = index+1;

    /*---ITERATE THROUGH WORDS LOOKING FOR DATA---*/
    while(words[counter] != NULL) {

      /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
      if(check_word(hashtable,words[counter]) == false) {
          break;
      }
      strcpy(went,"went*");
      strcat(went,words[counter]);
      data = get_entry_data(hashtable,went);
      if(data != NULL) {
        printf("%s ",data);
        return counter;
      }
      ++counter;
    }

    counter = index+1;
    strcpy(went,"went*");

    /*---ITERATE THROUGH WORDS AGAIN LOOKING FOR DATA---*/
    while(words[counter] != NULL) {

      /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
      if(check_word(hashtable,words[counter]) == false) {
          break;
      }
      strcat(went,words[counter]);
      data = get_entry_data(hashtable,went);
      if(data != NULL) {
        printf("%s ",data);
        return counter;
      }
      ++counter;
    }

    /*---PRINT GENERIC MESSAGE IF NO DATA FOUND---*/
    printf("oh cool ");
    return counter-1;
  }

  return index;
}
