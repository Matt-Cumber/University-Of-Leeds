#include "output.h"

/*
  This file deals with outputs centred around the key word going
*/


/*---FUNCTON FOR GOING TRIGGER WORDS---*/
int going_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  /*---DECLARE DATA AND KEY---*/
  char going[90] = "going*";
  char *data = "";

  /*---GET KEY---*/
  strcat(going,words[index]);

  /*---GET DATA---*/
  data = get_entry_data(hashtable,going);

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
      strcpy(going,"going*");
      strcat(going,words[counter]);
      data = get_entry_data(hashtable,going);
      if(data != NULL) {
        printf("%s ",data);
        return counter;
      }
      ++counter;
    }

    counter = index+1;
    strcpy(going,"going*");

    /*---ITERATE THROUGH WORDS AGAIN LOOKING FOR DATA---*/
    while(words[counter] != NULL) {

      /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
      if(check_word(hashtable,words[counter]) == false) {
          break;
      }
      strcat(going,words[counter]);
      data = get_entry_data(hashtable,going);
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
