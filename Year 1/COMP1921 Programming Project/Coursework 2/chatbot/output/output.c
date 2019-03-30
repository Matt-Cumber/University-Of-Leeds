#include "output.h"

/*
  This file is used to combine both output files in order to reply to the user
  There are also additional functions here some more comical others just generic
  and so do not have a place in the other two files.
  The other output files are only called within this file and were originally all in one file
  however this made the file over 1000 lines long so needed to be seperated
*/

/*---DECLARE GLOBAL VARIABLES USED---*/
int joke_index = 0;
extern int global_take_note;
extern int global_past_input_index;
extern int global_bot_mood;
extern char *global_past_inputs[MAX_PAST_INPUTS];

/*---THIS FUNCTION PRINTS LOTS OF HELPFUL MESSAGES TO THE USER---*/
void help_me_talk() {
  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("WRITE HELP MESSAGE\nAvoid emphasis on words for example using really like instead of like\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}


/*---THIS FUNCTION COMPARES THE STRING TO SET EXIT MESSAGES TO END THE PROGRAM---*/
bool exit_messages(char *string) {

  if(strcmp(string,"bye,") == 0) { printf("Nice to meet you, Goodbye! "); return true; }
  else if(strcmp(string,"good,bye,") == 0) { printf("Nice to meet you, Goodbye! "); return true; }
  else if(strcmp(string,"see,you,") == 0) { printf("Nice to meet you, Goodbye! "); return true; }
  else { return false; }
}


/*
  the next few functions will be used to print some random generic replies which each are used in special
  cases
*/

void get_note_word() {

    /*---SEEDING RANDOM NUMBER---*/
    time_t t;
    srand((unsigned) time(&t));

    /*---PICK REPLY---*/
    int decider = rand() % 4;

    /*---PRINT THE CORRESPONDING RESPONSE TO EACH VALUE---*/
    if(decider == 0) { printf("Fascinating "); }
    else if(decider == 1) { printf("Interesting "); }
    else if(decider == 2) { printf("Good to know "); }
    else if(decider == 3) { printf("Intriguing "); }
}

void get_like_word() {

    /*---SEEDING RANDOM NUMBER---*/
    time_t t;
    srand((unsigned) time(&t));

    /*---PICK REPLY---*/
    int decider = rand() % 4;

    /*---PRINT THE CORRESPONDING RESPONSE TO EACH VALUE---*/
    if(decider == 0) { printf("really? "); }
    else if(decider == 1) { printf("oh cool "); }
    else if(decider == 2) { printf("awesome "); }
    else if(decider == 3) { printf("great "); }
}


/*---FUNCTION TO TRY AND REPLY TO THE USER---*/
bool try_reply(entry_t *hashtable[SIZE], char *input) {

  /*---CREATE COPY OF INPUT---*/
  char copy_of_input[MAX_LENGTH_INPUT];
  memset(copy_of_input,'\0',sizeof(copy_of_input));
  strcpy(copy_of_input,input);

  /*---GET EACH WORD OF THE INPUT AND STORE IN WORDS ARRAY---*/
  char *words[strlen(input)];
  const char *delimeter = ",";
  words[0] = strtok(copy_of_input,delimeter);
  int i = 0;
  while(words[i] != NULL) {
    ++i;
    words[i] = strtok(NULL,delimeter);
  }

  /*---DECLARE VARIABLES---*/
  int temp_i;
  int count = 0;
  bool success = false;
  char *data;

  i = 0;

  /*---ITERATE THROUGH THE REST OF THE WORDS---*/
  while (words[i] != NULL) {

    /*----CHECK OF WORD IS HELP CODE---*/
    if(strcmp("helpmetalk",words[i]) == 0) {

      /*---DECLARE SUCCESS AS CHATBOT UNDERSTOOD INPUT---*/
      success = true;

      /*---PRINT HELP MESSAGE AND MOVE ONTO NEXT WORD IF NOT NULL---*/
      help_me_talk();
      if(words[i+1] != NULL) {
        ++i;
      }

      /*---IF NO FURTHER WORDS STOP LOOP TO AVOID CRASHING---*/
      else {
        break;
      }
    }

    if(words[i] != NULL) {

      /*---GET HASH DATA FOR WORD---*/
      data = get_entry_data(hashtable,words[i]);

      /*---PRINT HASH DATA FOR PARTICULAR WORD---*/
      if(data != NULL) {
        printf("%s ",data);
        success = true;
      }
    }

    /*---THIS IS A STANDARD REPLY IF THE USER ENTERS ONE WORD THAT CAN'T BE REPLIED TO---*/
    if(words[i+1] == NULL && get_entry_data(hashtable,words[i]) == NULL && i == 0) {
      printf("what's %s",words[i]);
      success = true;
      break;
    }

    if((strcmp("because",words[i]) == 0 || strcmp("as",words[i]) == 0) && words[i+1] != NULL) {
      success = true;
      printf("okay ");
      if(words[i+1] != NULL) {
        ++i;
      }

      /*---IF NO FURTHER WORDS STOP LOOP TO AVOID CRASHING---*/
      else {
        break;
      }
    }

    /*---CHECK FOR THANK YOU---*/
    if(words[i+1] != NULL) {
      if(strcmp("thank",words[i]) == 0 && strcmp("you",words[i+1]) == 0) {
        printf("you're welcome ");
        success = true;
        if(words[i+2] != NULL) {
          i = i+2;
        }

        /*---IF NO FURTHER WORDS STOP LOOP TO AVOID CRASHING---*/
        else {
          break;
        }
      }

      /*---CHECK FOR OTHER SHORT SPECIFIC PHRASES WITH PARTICULAR OUTPUTS---*/
      else if(words[i+2] != NULL && words[i+3] != NULL) {
        if(strcmp(words[i],"tell") == 0 && strcmp(words[i+1],"me") == 0 &&
          (strcmp(words[i+2],"a") == 0 || strcmp(words[i+2],"another") == 0) &&
          strcmp(words[i+3],"joke") == 0) {
            tell_a_joke();
            success = true;
            if(words[i+4] != NULL) {
              i = i+4;
            }

            else {
              break;
            }
          }

          /*---CHECK FOR DIFFERENT WAY OF REUQESTION FOR JOKE---*/
          if(words[i+4] != NULL) {
            if(strcmp(words[i],"tell") == 0 && strcmp(words[i+1],"me") == 0 &&
              (strcmp(words[i+2],"a") == 0 || strcmp(words[i+2],"another") == 0) &&
              strcmp(words[i+3],"different") == 0 && strcmp(words[i+4],"joke") == 0) {
                tell_a_joke();
                success = true;
                if(words[i+5] != NULL) {
                  i = i+5;
                }

                else {
                  break;
                }
              }
          }

          if (strcmp(words[i],"sing") == 0 && strcmp(words[i+1],"me") == 0 &&
          strcmp(words[i+2],"a") == 0 && strcmp(words[i+3],"song") == 0) {
            sing_a_song();
            success = true;
            if(words[i+4] != NULL) {
              i = i+4;
            }

            else {
              break;
            }
          }
      }
    }

    /*---ADD INPUT TO PAST INPUTS ARRAY---*/
    global_past_inputs[global_past_input_index] = input;
    ++global_past_input_index;

    /*---STORE i TEMPORARILY FOR COMPARISON---*/
    temp_i = i;

    /*---CHECK FOR TRIGGER WORDS---*/
    i = find_trigger_word(hashtable,words,i);

    /*---CHECK IF i HAS BEEN INCREASED---*/
    if(i > temp_i) {

      /*---PHRASE FOUND SO SUCCESSFUL FUNCTION---*/
      success = true;
    }

    /*---INCREMENT i FOR NEXT ITERATION---*/
    ++i;
  }

  global_take_note = 0;
  return success;
}


/*---FUNCTION TO FIND TRIGGER WORDS---*/
int find_trigger_word(entry_t *hashtable[SIZE],char **words,int index) {

  if(strcmp("what",words[index]) == 0) {
    index = what_trigger_word(hashtable,words,index);
  }

  else if(strcmp("how",words[index]) == 0) {
    index = how_trigger_word(hashtable,words,index);
  }

  else if(strcmp("who",words[index]) == 0) {
    index = who_trigger_word(hashtable,words,index);
  }

  else if(strcmp("do",words[index]) == 0) {
    index = do_trigger_word(hashtable,words,index);
  }

  else if(strcmp("went",words[index]) == 0) {
    index = went_trigger_word(hashtable,words,index);
  }

  else if(strcmp("going",words[index]) == 0) {
    index = going_trigger_word(hashtable,words,index);
  }

  else if(strcmp("i",words[index]) == 0) {
    index = i_trigger_word(hashtable,words,index);
  }

  else if(strcmp("you",words[index]) == 0) {
    index = you_trigger_word(hashtable,words,index);
  }

  else if(strcmp("why",words[index]) == 0) {
    index = why_trigger_word(hashtable,words,index);
  }

  else if(strcmp("my",words[index]) == 0) {
    index = my_trigger_word(hashtable,words,index);
  }

  else if(strcmp("change",words[index]) == 0) {
    index = change_trigger_word(hashtable,words,index);
  }

  else if(strcmp("are",words[index]) == 0) {
    index = are_trigger_word(hashtable,words,index);
  }

  return index;
}



/*---FUNCTION FOR CHANGE TRIGGER---*/
int change_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {
  if(words[index+1] != NULL && words[index+2] != NULL && words[index+3] != NULL) {
    if(strcmp("name",words[index+1]) == 0 && strcmp("to",words[index+2]) == 0) {

      /*---DELETE OLD NAME---*/
      int hash_index = hash("user*name");
      hashtable[hash_index] = NULL;

      /*---ADD THE NAME TO HASHTABLE---*/
      insert_into_hashtable(hashtable,"user*name",words[index+3]);
      printf("welcome %s ",words[index+3]);
      return index+3;
    }
  }
  return index;
}


/*---FUNCTION FOR ARE TRIGGER---*/
int are_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  /*---CHECK FOLLOWING WORDS ARE NOT NULL---*/
  if(words[index+1] != NULL) {

    /*---INITIALISE HASH KEY AND OTHER VARIABLES---*/
    char are[90] = "are*";
    char *data;
    int counter = index+2;

    /*---CREATE HASH KEY---*/
    strcat(are,words[index+1]);

    /*---PRINT DATA IF NOT NULL---*/
    data = get_entry_data(hashtable,are);
    if(data != NULL) {
      printf("%s ",data);
      return index+1;
    }

    /*---ADD REST OF WORDS TO KEY AND KEEP CHECKING FOR DATA---*/
    while(words[counter] != NULL) {
      if(check_word(hashtable,words[counter]) == false) {
          break;
      }
        strcat(are,words[counter]);
        data = get_entry_data(hashtable,are);

        /*---PRINT DATA WHEN NOT NULL---*/
        if(data != NULL) {
          printf("%s ",data);
          return counter-1;
        }
      ++counter;
    }
  }

  /*---ENSURE FURTHER WORDS ARE NOT NULL---*/
  if(words[index+1] != NULL && words[index+2] != NULL) {
    /*---CHECK FOR PARTICULAR PHRASE---*/
    if(strcmp(words[index+1],"you") == 0 && strcmp(words[index+2],"funny") == 0) {
      tell_a_joke();
      return index+2;
    }

    if(strcmp(words[index+1],"you") == 0 && strcmp(words[index+2],"going") == 0) {
      printf("no, unfortunately I don't have any legs! ");
      return index+2;
    }
  }
  return index;
}


/*---FUNCTION TO TELL USER JOKES---*/
void tell_a_joke() {
  /*
    These jokes are not mine and are taken from the website:
    http://www.danoah.com/2013/01/best-short-jokes-ever.html
  */

  char *jokes[5] = {"I never make mistakes…I thought I did once; but I was wrong",
  "The past, present and future walk into a bar. It was tense.",
  "Knock knock. Who’s there? Interrupting Cow. Interrupting Cow wh- MOOOOOOO!",
  "What did the green grape say to the purple grape? BREATHE!",
  "Where does a sheep go for a haircut? To the baaaaa baaaaa shop!"};

  if(joke_index > 4) {
    printf("I'm not that funny ");
  }
  else {
    printf("%s ",jokes[joke_index]);
    ++joke_index;
  }
}


/*---FUNCTION TO PRINT SONG LYRICS TO USER---*/
void sing_a_song() {
  printf("Never gonna give you up\nNever gonna let you down\n"
  "Never gonna run around and desert you\nNever gonna make you cry\n"
  "Never gonna say goodbye\nNever gonna tell a lie and hurt you\n"
  "Did you like my singing?");
}


/*---FUNCTION TO CHECK IF THE WORD PASSED IS A PARTICULAR TYPE---*/
bool check_word(entry_t *hashtable[SIZE], char *word) {
  if(strcmp("what",word) == 0 || strcmp("how",word) == 0 ||
    strcmp("who",word) == 0 || strcmp("do",word) == 0 ||
    strcmp("went",word) == 0 || strcmp("going",word) == 0 ||
    strcmp("i",word) == 0 || strcmp("you",word) == 0 ||
    strcmp("and",word) == 0 || strcmp("because",word) == 0 ||
    strcmp("but",word) == 0 || strcmp("also",word) == 0 ||
    get_entry_data(hashtable,word) != NULL) {

      /*---RETURN FALSE WHEN WORD IS A MATCH---*/
      return false;
    }

    else {
      return true;
    }
}


void next_entry_after_do_you_like(entry_t *hashtable[SIZE], char *like) {

  printf("\nin the alternate path\n");

  char *name2;
  char *user_input2;
  char user_like2[90] = "userlike*";

  name2 = get_entry_data(hashtable,"user*name");

  printf("\n");

  /*---START UI CHECKING IF NAME HAS BEEN MADE AND GET INPUT---*/
  if(name2 == NULL) {
    printf("\nME :\n");
  }

  else {
    printf("\nME (%s) :\n",name2);
  }

  user_input2 = get_input();
  printf("\n%s :\n",CHATBOT_NAME);

  /*---FORMAT INPUT FOR PROCESSING---*/
  format_string(user_input2);

  /*---CHECK USER TYPED SOMETHING---*/
  if(user_input2[0] == '\0') {
    printf("Type something for me to read");
  }

  /*---CHECK IF USER DID NOT ENTER AN EXIT MESSAGE---*/
  else if(exit_messages(user_input2) == false) {

    /*---VALIDATE THE INPUT---*/
    if(validate_string(user_input2) == true) {

      /*---CHECK IF THE SAME INPUT HAS BEEN MADE TWICE---*/
  //    if(check_past_inputs(user_input) == false) {

        /*---ENSURE PROGRAM DOESN'T CRASH BY TERMINATING AFTER MAX INPUTS REACHED---*/
        if(global_past_input_index == MAX_PAST_INPUTS) {
          printf("Sorry to leave so soon but I must go now. Lovely to meet you, good bye!\n\n");
          exit(0);
        }

        if(strncmp(user_input2,"yes",3) == 0) {
          strcat(user_like2,like);

          /*---IF DATA ALREADY EXISTS PRINT ERROR MESSAGE---*/
          if(get_entry_data(hashtable,user_like2) != NULL) {
            printf("you already told me that ");
            return;
          }

          /*---OTHERWISE ADD THE DATA TO THE HASHTABLE---*/
          insert_into_hashtable(hashtable,user_like2,"true");

          get_note_word();
          printf("I'll take note of that ");
        }

        if(strncmp(user_input2,"no",2) == 0) {
          strcat(user_like2,like);

          /*---IF DATA ALREADY EXISTS PRINT ERROR MESSAGE---*/
          if(get_entry_data(hashtable,user_like2) != NULL) {
            printf("you already told me that ");
            return;
          }

          /*---OTHERWISE ADD THE DATA TO THE HASHTABLE---*/
          insert_into_hashtable(hashtable,user_like2,"false");

          get_note_word();
          printf("I'll take note of that ");
        }

        printf("You didn't answer my question now I'm sad ");
        global_bot_mood = 4;

      }


    }
}
