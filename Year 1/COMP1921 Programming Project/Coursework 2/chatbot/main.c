#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include "input.h"
#include "format.h"
#include "validate.h"
#include "output/output.h"

//#define TESTING true

/*---DECLARE GLOBAL VARIABLES---*/
int global_past_input_index;
char *global_past_inputs[MAX_PAST_INPUTS];

int main() {

  /*---DECLARE VARIABLES---*/
  char *name;
  char *user_input;
  entry_t *hashtable[SIZE];
  global_past_input_index = 0;

  /*---INITIALISE HASHTABLE---*/
  init_hashtable(hashtable);

  /*---DECLARE VERSION AND OTHER USEFUL INFORMATION---*/
  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("CHATBOT VERSION < 3.0.0 > BY MATTHEW CUMBER\n"
  "LATEST NEWS:\n    -THIS VERSION HAS A NEW OUTPUT FILE THAT CAN RESPOND MORE OFTEN\n"
  "    -IMPLEMENTED MORE TRIGGER WORDS FOR MORE NON GENERIC RESPONSES\n"
  "    -FIXED BUG IN DO I LIKE WHICH STOPS READING INPUT AS SOON AS\n     DATA FOUND EVEN IF NOT CORRECT DATA\n"
  "    -I CAN SEE WHAT YOU ARE TYPING SO BE NICE\n"
  "UPCOMING FEATURES:\n    -BOT WILL PLAY A GAME WITH YOU\n    -HUNDREDS MORE LIKES ETC.\n"
  "    -ASKS YOU QUESTIONS TO GET TO KNOW YOU\n"
  "NEWEST FEATURES:\n    -BOT HAS NAME\n    -CAN REMEMBER AND CHANGE YOUR NAME\n"
  "    -BOT CAN TELL JOKES\n    -BOT CAN SING A SONG\n    - < BETA > CAN READ CONNECTED SENTENCES\n"
  "    - < BETA > READ MORE THAN ONE WORD LIKES/FAVES ETC.\n"
  "BUGS:\n    -DOES NOT ADD SPACE FOR COMBINED WORDS\n"
  "HELP MAKE CHAT BOT BE MORE EFFECTVE BY SHOWING CONVERSATIONS TO REAL MATT\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  /*---WELCOME MESSAGES---*/
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("WELCOME TO MATTBOT THE CHATBOT\nUSE EFFECTIVELY BY LIMITING INPUTS\nBEGIN BY TYPING\n"
  "ENTER EXACTLY 'HELPMETALK' FOR HELP ON HOW TO USE CHATBOT\nENJOY USING CHATBOT\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  /*---CREATE PROGRAM LOOP TO MIMIC CONVERSATION---*/
  while(1) {

    /*---READ TEST FILE IF TESTING IS DEFINED---*/
    #ifdef TESTING
      FILE *file;
      file = fopen("tests.txt","r");
      if (file == NULL) {
        printf("File couldn't be opened\n\a\a");
        fclose(file);
        exit(0);
      }
      char line[90];
      while(fgets(line,sizeof(line),file)) {
        name = get_entry_data(hashtable,"user*name");
        if(name == NULL) {
          printf("\nME :\n");
        }
        else {
          printf("\nME (%s) :\n",name);
        }
        line[strlen(line)-1] = '\0';
        printf("%s\n",line);
        printf("\n%s :\n",CHATBOT_NAME);
        if(exit_messages(line) == false) {
          try_reply(hashtable,line);
          printf("\n");
        }
        int x,y;
        for(x = 1;x <= 20000;++x)
          for(y = 1;y <= 30000;++y)
            {}
      }
      printf("\nTest completed\n");
      return 0;
    #endif

    name = get_entry_data(hashtable,"user*name");

    /*---START UI CHECKING IF NAME HAS BEEN MADE AND GET INPUT---*/
    if(name == NULL) {
      printf("\nME :\n");
    }

    else {
      printf("\nME (%s) :\n",name);
    }

    user_input = get_input();

    printf("\n%s :\n",CHATBOT_NAME);

    /*---PRINT ERROR MESSAGE IF THE INPUT EXCEEDS THA MAXIMUM LIMIT---*/
    if(user_input[80] != '\0') {
      printf("I can't read all that\n");
      /*---CLEAR THE REST OF THE INPUT STREAM---*/
      char c;
      while ((c = getchar()) != '\n' && c != EOF) { }
      continue;
    }

    /*---FORMAT INPUT FOR PROCESSING---*/
    format_string(user_input);

    /*---CHECK USER TYPED SOMETHING---*/
    if(user_input[0] == '\0') {
      printf("Type something for me to read\n");
      continue;
    }

    /*---CHECK IF USER DID NOT ENTER AN EXIT MESSAGE---*/
    else if(exit_messages(user_input) == false) {

      /*---VALIDATE THE INPUT---*/
      if(validate_string(user_input) == true) {

        /*---CHECK IF THE SAME INPUT HAS BEEN MADE TWICE---*/
    //    if(check_past_inputs(user_input) == false) {

          /*---ENSURE PROGRAM DOESN'T CRASH BY TERMINATING AFTER MAX INPUTS REACHED---*/
          if(global_past_input_index == MAX_PAST_INPUTS) {
            printf("Sorry to leave so soon but I must go now. Lovely to meet you, good bye!\n\n");
            return 0;
          }

          /*---TRY TO PRINT RESPONSE TO USERS INPUT---*/
          if(try_reply(hashtable,user_input) == false) {

            /*---PRINT ERROR MESSAGE USER WILL UNDERSTAND IF NO REPLY WAS PRINTED---*/
            printf("Sorry but I'm not sure what to say to that");
          }

      //  }

        /*---IF THE INPUT HAS ALREADY BEEN MADE PRINT ERROR MESSAGE TO USER---*/
  //      else {
  //        printf("You already said that. Why are you repeating yourself");
  //      }

          /*---ADD THE INPUT TO THE PAST INPUT TEXT FILE---*/
          save_inputs_to_file(user_input);

      }

      /*---IF THE INPUT WAS INVALID SEND ERROR MESSAGE USER WILL UNDERSTAND---*/
      else {
        printf("I'm sorry but I am unable to read what you said");
      }

    }

    /*---END PROGRAM IF EXIT MESSAGED ENTERED---*/
    else {

      /*---FREE ALL MEMORY ALLOCATED---*/
      free(user_input);
      destroy_hash_table(hashtable);

      printf("\n\n");
      return 0;
    }

    /*---PRINT NEW LINE READY FOR NEXT INPUT---*/
    printf("\n");

  }
}
