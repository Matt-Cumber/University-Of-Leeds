#include "format.h"

/*
  This file is used to format the user's input.
  The user's input will be changed to be in the format:
  word,word,word,word etc.
*/

/*---REPLACE COMMON WORDS WITH THE SAME WORD---*/
char *replace_a_word(char *word) {
  /*
    Compares passed word to a series of words and returns their replacement if necessary.
    This is done so that the program can remove some alternative ways of saying the same thing e.g.
    what is and what's
  */

  if(strcmp(word,"hi") == 0) { return "hello"; }
  else if(strcmp(word,"hey") == 0) { return "hello"; }
  else if(strcmp(word,"hiya") == 0) { return "hello"; }
  else if(strcmp(word,"goodbye") == 0) { return "bye"; }
  else if(strcmp(word,"dont") == 0) { return "do,not"; }
  else if(strcmp(word,"cant") == 0) { return "can,not"; }
  else if(strcmp(word,"cannot") == 0) { return "can,not"; }
  else if(strcmp(word,"whos") == 0) { return "who,is"; }
  else if(strcmp(word,"whats") == 0) { return "what,is"; }
  else if(strcmp(word,"color") == 0) { return "colour"; }
  else if(strcmp(word,"an") == 0) { return "a"; }
  else if(strcmp(word,"movie") == 0) { return "film"; }
  else if(strcmp(word,"names") == 0) { return "name,is"; }
  else if(strcmp(word,"im") == 0) { return "i,am"; }
  else if(strcmp(word,"ok") == 0) { return "okay"; }
  else if(strcmp(word,"ya") == 0) { return "you"; }
  else if(strcmp(word,"fave") == 0) { return "favourite"; }
  else if(strcmp(word,"favorite") == 0) { return "favourite"; }
  else if(strcmp(word,"thanks") == 0) { return "thank,you"; }
  else if(strcmp(word,"thankyou") == 0) { return "thank,you"; }
  else if(strcmp(word,"chatbot") == 0) { return "chat,bot"; }
  else if(strcmp(word,"fries") == 0) { return "chips"; }
  else if(strcmp(word,"dislike") == 0) { return "dont,like"; }
  else if(strcmp(word,"doughnuts") == 0) { return "donuts"; }
  else if(strcmp(word,"doughnut") == 0) { return "donut"; }
  else if(strcmp(word,"as") == 0) { return "because"; }
  else if(strcmp(word,"created") == 0) { return "made"; }
  else if(strcmp(word,"creator") == 0) { return "maker"; }
  else { return word; }
}

void replace_words(char *string) {

  /*---CREATE A COPY OF PASSED STRING SO THAT THE PASSED STRING IS NOT MODIFIED---*/
  char copy_of_string[MAX_LENGTH_INPUT];
  memset(copy_of_string,'\0',sizeof(copy_of_string));
  strcpy(copy_of_string,string);

  /*---CREATE SEVERAL VARIABLES USED TO GET INDIVIDUAL WORDS AND STORE THE REULTS---*/
  char *word;
  char *temp_word;
  char temp_string[MAX_LENGTH_INPUT] = "\0";
  const char *delimeter = ",";

  /*---GET FIRST WORD---*/
  word = strtok(copy_of_string,delimeter);

  /*---LOOP THROUGH ALL WORDS IN STRING---*/
  while(word != NULL) {

    /*---CHECK IF THE WORD NEEDS REPLACING---*/
    temp_word = replace_a_word(word);

    /*---COPY INTO VARIABLE WHICH STORES OUTPUT AND ENSURE IN THE CORRECT FORMAT(word,word,)---*/
    strcat(temp_string,temp_word);
    strcat(temp_string,delimeter);

    /*---GET NEXT WORD---*/
    word = strtok(NULL,delimeter);
  }

  /*---COPY RESULT INTO PASSED STRING---*/
  strcpy(string,temp_string);
}

/*---REMOVE CERTAIN CHARACTERS FROM THE PASSED STRING---*/
void remove_character(char *string, const char character_to_be_removed, int position_in_string) {

  int j = position_in_string;

  /*---SPECIAL CASE CHARACTER "'" USUALLY WITHIN WORD SO TREATED SEPERATLEY---*/
  if(character_to_be_removed == '\'') {

    /*---REMOVE ADDITIONAL WHITESPACE OR OTHER SEPERATING CHARACTERS AFTER CHARACTER---*/
    while(string[j+1] == ' ' || string[j+1] == ',' || string[j+1] == '?' || string[j+1] == '.'
          || string[j+1] == '!' || string[j+1] == '\'' || string[j+1] == '"')
    {
      memmove(&string[j], &string[j + 1], strlen(string) - j);
    }
    /*---REMOVE THE "'" FROM THE STRING---*/
    memmove(&string[j], &string[j + 1], strlen(string) - j);
  }

  else {
    /*---REMOVE ADDITIONAL WHITESPACE OR OTHER SEPERATING CHARACTERS AFTER CHARACTER---*/
    while(string[j+1] == ' ' || string[j+1] == ',' || string[j+1] == '?' || string[j+1] == '.'
          || string[j+1] == '!' || string[j+1] == '\'' || string[j+1] == '"')
    {
      memmove(&string[j], &string[j + 1], strlen(string) - j);
    }
    /*---CHANGE THE CHARACTER TO A COMMA SO EACH WORD IS COMMA SEPERATED---*/
    string[j] = ',';
  }

}

/*---FORMAT THE PASSED STRING---*/
void format_string(char *string) {

  int i = 0;

  /*---MODIFY INPUT TO CORRECT FORMAT FOR INTERPRETATION LATER---*/
  while(string[i] != '\0') {

    /*---CONVERT USER INPUT TO ALL LOWER CASE---*/
    if(string[i] > 64 && string[i] < 91) {
      string[i] = tolower(string[i]);
    }

    /*---REMOVE SEPERATING CHARACTERS AND REPLACE WITH A COMMA INSTEAD---*/
    else if(string[i] == ' ' || string[i] == ',' || string[i] == '?' || string[i] == '.'
            || string[i] == '!' || string[i] == '\'' || string[i] == '"')
    {
      remove_character(string, string[i], i);
    }
    ++i;
  }

  replace_words(string);

}
