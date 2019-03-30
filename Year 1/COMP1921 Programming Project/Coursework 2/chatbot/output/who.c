#include "output.h"

/*
  This file deals with outputs centred around the key word who
*/


/*---FUNCTON FOR WHO TRIGGER WORDS---*/
int who_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  index = who_trigger(hashtable,words,index+1);

  return index;
}



/*FUNCTION FOR WHO PHRASE---*/
int who_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---DECLARE DATA AND KEY---*/
  char who[90] = "who*";
  char *data = "";

  /*---GET KEY---*/
  strcat(who,words[index]);

  /*---GET DATA---*/
  data = get_entry_data(hashtable,who);

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
      strcat(who,words[counter]);
      data = get_entry_data(hashtable,who);
      if(data != NULL) {
        printf("%s ",data);
        return counter;
      }
      ++counter;
    }

    /*---PRINT GENERIC MESSAGE IF NO DATA FOUND---*/
    printf("I don't know ");
    return counter-1;
  }

  return index;
}
