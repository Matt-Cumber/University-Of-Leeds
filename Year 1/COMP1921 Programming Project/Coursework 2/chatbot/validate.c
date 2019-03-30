#include "validate.h"

/*---VALIDATION---*/
bool validate_string(char *string) {

  /*
    This validation is not prefect, words which contain 5 or more consanants in a row, conatain 3
    or more vowels in a row will not be valid. However, words such as "dddd" or "aa"
    will be considered to be valid.
    Additonally a string like "abababababab" will be valid.
    There are some exceptions but some words i have not thought of may not be valid.
    I have chosen this method as this allows for most everyday words to be valid.
  */

  /*---DECLARE VARIABLES---*/
  int i = 0;

  /*---CREATE COPY OF STRING---*/
  char copy_of_string[MAX_LENGTH_INPUT];
  memset(copy_of_string,'\0',sizeof(copy_of_string));
  strcpy(copy_of_string,string);

  /*---GET EACH WORD OF THE STRING AND STORE IN WORDS ARRAY---*/
  char *words[strlen(string)];
  const char *delimeter = ",";
  words[0] = strtok(copy_of_string,delimeter);

  while(words[i] != NULL) {
    ++i;
    words[i] = strtok(NULL,delimeter);
  }

  /*---RESET i---*/
  i = 0;

  /*---ITERATE THROUGH WORDS AND VALIDATE EACH ONE---*/
  while(words[i] != NULL) {

    /*---CHECK IF WORD IS ON THE EXCEPTION LIST---*/
    if(exceptions(words[i]) == false) {

      /*---VALIDATE THE WORD---*/
      if(validate_word(words[i]) == false) {
        return false;
      }
    }
    ++i;
  }

  /*---RETURN TRUE IF THE STRING PASSED ALL VALIDATION---*/
  return true;

}

/*---FUNCTION TO CHECK IF WORD IS AN EXCEPTION---*/
bool exceptions(char *word) {

  /*---CREATE EXCEPTIONS ARRAY---*/
  char *exceptions[10] = {"monthly","corkscrew","nightstick","nightclub","beautiful","queen","beauty",
  "serious","curious","beautician"};

  int i;

  /*---LOOP THROUGH ARRAY COMPARING WORD WITG+H EXCEPTIONS---*/
  for(i = 0;i < 10;++i) {
    if(strcmp(exceptions[i],word) == 0) {

      /*---IF THE WORD IS IN THE LIST RETURN TRUE---*/
      return true;
    }
  }

  /*---NOT AN EXCPETION RETURN FALSE---*/
  return false;
}

/*---VALIDATE A WORD FROM THE STRING---*/
bool validate_word(char *word) {

  /*---DECLARE ALL CONSONANTS AND VOWELS IN ORDER TO LOOP THROUGH LATER---*/
  char consonants[22] = "bcdfghjklmnpqrstvwxyz";
  char vowels[6] = "aeiou";

  /*---DECLARER ITERATING VARIABLES---*/
  int i,j;

  /*---DECLARE COUNTER FOR VOWELS AND CONSONANTS IN A ROW---*/
  int in_a_row_counter = 0;

    /*---LOOP THROUGH STRING AND CHECK FOR 4 OR MORE CONSONANTS IN A ROW---*/
    for(i = 0;word[i] != '\0';++i) {

      /*---CHECK FOR UNKNOWN CHARACTERS ONLY DONE IN ONE LOOP---*/
      if((word[i] < 97 || word[i] > 122) && word[i] != ',') {
        /*---RETURN FALSE IF AN UNKOWN CHARACTER WAS ENTERED---*/
        return false;
      }

      for(j = 0;j < 22;++j) {
        if(word[i] == consonants[j]) {
          /*--INCREASE COUNTER FOR EACH CONSONANT IN A ROW---*/
          ++in_a_row_counter;

          if(in_a_row_counter > 4) {
            /*---RETURN FALSE IF THE STRING IS NOT VALID---*/
            return false;
          }
        }

      }
      /*---RESET COUNTER WHEN A VOWEL IS FOUND INSTEAD---*/
      for(j = 0;j < 6;++j) {
        if(word[i] == vowels[j] || word[i] == ',') {
          in_a_row_counter = 0;
        }
      }
    }

    /*---RESET COUNTER FOR CHECKING VOWELS IN A ROW NOW---*/
    in_a_row_counter = 0;

    /*---LOOP THROUGH STRING AND CHECK FOR 3 OR MORE VOWELS IN A ROW---*/
    for(i = 0;word[i] != '\0';++i) {
      for(j = 0;j < 6;++j) {
        if(word[i] == vowels[j]) {
          /*--INCREASE COUNTER FOR EACH VOWEL IN A ROW---*/
          ++in_a_row_counter;

          if(in_a_row_counter > 2) {
            /*---RETURN FALSE IF THE STRING IS NOT VALID---*/
            return false;
          }
        }
      }
      /*---RESET COUNTER WHEN A CONSONANT IS FOUND INSTEAD---*/
      for(j = 0;j < 22;++j) {
        if(word[i] == consonants[j] || word[i] == ',') {
          in_a_row_counter = 0;
        }
      }
    }

    /*---RETURN TRUE IF THE STRING IS VALID---*/
    return true;
}

/*---CHECK IF USER HAS ALREADY SAID SOMETHING---*/
bool check_past_inputs(char *string) {

  /*---DECLARE VARIABLES---*/
  int i;

  /*---CHECK THROUGH ALL PREVIOUS INPUTS---*/
  for(i = 0;i < global_past_input_index;++i) {

    /*---IF THERE IS A MATCH RETURN FALSE---*/
    if(strcmp(global_past_inputs[i],string) == 0) {
      return true;
    }
  }

  /*---RETURN TRUE IF THE INPUT IS A NEW ONE---*/
  return false;
}
