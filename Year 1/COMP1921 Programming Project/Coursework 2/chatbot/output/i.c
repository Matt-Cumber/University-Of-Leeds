#include "output.h"

/*
  This file deals with outputs centred around the key word i
*/


/*---DECLARE GLOBAL VARIABLES USED---*/
int global_take_note = 0;
extern int global_bot_mood;


/*---FUNCTON FOR I TRIGGER WORDS---*/
int i_trigger_word(entry_t *hashtable[SIZE],char **words, int index) {

  /*---ENSURE WORDS ARE NOT NULL TO AVOID CRASHING---*/
  if(words[index+1] != NULL && words[index+2] != NULL) {
    /*---CHECK FOR TRIGGER PHRASES---*/
    if(strcmp(words[index+1],"like") == 0) {
      index = i_like_trigger(hashtable,words,index+2);
    }

    else if(strcmp(words[index+1],"am") == 0) {
      index = i_am_trigger(hashtable,words,index+2);
    }

    else if(strcmp(words[index+1],"have") == 0) {
      index = i_have_trigger(hashtable,words,index+2);
    }

    /*---ENSURE FURTHER WORDS ARE NOT NULL---*/
    else if(words[index+3] != NULL && words[index+4] != NULL) {
      /*---CHECK FOR TRIGGER PHRASES---*/
      if(strcmp(words[index+1],"do") == 0 && strcmp(words[index+2],"not") == 0 &&
        strcmp(words[index+3],"like") == 0) {
          index = i_do_not_like_trigger(hashtable,words,index+4);
        }
    }
  }

  char i[90] = "i*";
  int counter = index+1;
  char *data;

  /*---ITERATE THROUGH WORDS AGAIN LOOKING FOR DATA---*/
  while(words[counter] != NULL) {

    if(words[counter+1] != NULL) {
    if(strcmp(words[counter],"love") == 0 && strcmp(words[counter+1],"you") == 0) {
      printf("that made me happy I love you too");
      global_bot_mood = 5;
      index = index + 2;
    }
    else if(strcmp(words[counter],"hate") == 0 && strcmp(words[counter+1],"you") == 0) {
      printf("that made me sad");
      global_bot_mood = 4;
      index = index + 2;
    }
    }



    /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
    else if(check_word(hashtable,words[counter]) == false) {
        break;
    }
    strcat(i,words[counter]);
    data = get_entry_data(hashtable,i);
    if(data != NULL) {
      printf("%s ",data);
      return counter;
    }
    ++counter;
  }

  return index;
}


/*---FUNCTION FOR I PHRASE---*/
int i_like_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---INITIALISE HASH KEY---*/
  int counter;
  int reason = 0;
  char user_like[90] = "userlike*";
  char bot_like[90] = "botlike*";
  char like[90] = "";

  /*---CREATE KEY---*/
  strcat(user_like,words[index]);
  strcat(bot_like,words[index]);
  strcat(like,words[index]);
  counter = index+1;
  while(words[counter] != NULL) {

    /*---CHANGE VALUE OF REASON TO SINGINFY USER HAS POTENTIALLY GIVEN REASON---*/
    if((strcmp("as",words[counter]) == 0 || strcmp("because",words[counter]) == 0) && words[counter+1] != NULL) {
      reason = 1;
    }

    /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
    if(check_word(hashtable,words[counter]) == false) {
        break;
    }

    /*---KEEP ADDING WORDS TO EACH VARIABLE---*/
    strcat(user_like,words[counter]);
    strcat(bot_like,words[counter]);
    strcat(like,words[counter]);
    ++counter;
  }

  /*---IF DATA ALREADY EXISTS PRINT ERROR MESSAGE---*/
  if(get_entry_data(hashtable,user_like) != NULL) {
    printf("you already told me that ");
    return counter-1;
  }

  /*---OTHERWISE ADD THE DATA TO THE HASHTABLE---*/
  insert_into_hashtable(hashtable,user_like,"true");

  /*---ONLY PRINT MESSAGE IF FIRST TIME FOR THIS INPUT---*/
  if(global_take_note == 0) {

    /*---PRINT BOT REPSONSE IF THE BOT HAS OPINON ON SAME THING---*/
    if(get_entry_data(hashtable,bot_like) != NULL) {
      get_like_word();
      printf("%s ",get_entry_data(hashtable,bot_like));
    }

    /*---OTHERWSIE A GENERIC RESPONSE---*/
    else {
      get_note_word();
      printf("I'll take note of that ");
    }

    /*---IF NO REASON WAS GIVEN ASK THE USER---*/
    if(reason == 0) {
      printf("why do you like %s? ",like);
    }
    ++global_take_note;
  }
  return counter-1;
}


/*---FUNCTION FOR I PHRASE---*/
int i_am_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---DECLARE VARIABLES---*/
  int counter;
  char i_am[90] = "iam*";
  char *data;

  /*---CREATE HASH KEY---*/
  strcat(i_am,words[index]);

  /*---GET DATA FOR KEY---*/
  data = get_entry_data(hashtable,i_am);

  /*---PRINT DATA IF POSSIBLE---*/
  if(data != NULL) {
    printf("%s ",data);
    return index;
  }

  /*---GO THROUGH REST OF WORDS AND KEEP TRYING TO GET DATA---*/
  else {
    counter = index+1;
    while(words[counter] != NULL) {
      if(check_word(hashtable,words[counter]) == false) {
          break;
      }
      strcat(i_am,words[counter]);
      data = get_entry_data(hashtable,i_am);

      /*---PRINT DATA IF NOT NULL AFTER GOING THROUGH WORDS---*/
      if(data != NULL) {
        printf("%s ",data);
        return counter-1;
      }

      ++counter;
    }

  }

  /*---PRINT GENERIC REPLY TO I AM---*/
  printf("okay ");
  return counter-1;
}


/*---FUNCTION FOR I PHRASE---*/
int i_do_not_like_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---INITIALISE HASH KEY---*/
  int counter;
  int reason = 0;
  char user_like[90] = "userlike*";
  char bot_like[90] = "botlike*";
  char like[90] = "";

  /*---CREATE KEY---*/
  strcat(user_like,words[index]);
  strcat(bot_like,words[index]);
  strcat(like,words[index]);
  counter = index+1;
  while(words[counter] != NULL) {

    /*---CHANGE VALUE OF REASON TO SINGINFY USER HAS POTENTIALLY GIVEN REASON---*/
    if((strcmp("as",words[counter]) == 0 || strcmp("because",words[counter]) == 0) && words[counter+1] != NULL) {
      reason = 1;
    }

    /*---STOP ITERATING THROUGH WORDS IF A STOP WORD COMES UP---*/
    if(check_word(hashtable,words[counter]) == false) {
        break;
    }

    /*---KEEP ADDING WORDS TO EACH VARIABLE---*/
    strcat(user_like,words[counter]);
    strcat(bot_like,words[counter]);
    strcat(like,words[counter]);
    ++counter;
  }

  /*---IF DATA ALREADY EXISTS PRINT ERROR MESSAGE---*/
  if(get_entry_data(hashtable,user_like) != NULL) {
    printf("you already told me that ");
    return counter-1;
  }

  /*---OTHERWISE ADD THE DATA TO THE HASHTABLE---*/
  insert_into_hashtable(hashtable,user_like,"false");

  /*---ONLY PRINT MESSAGE IF FIRST TIME FOR THIS INPUT---*/
  if(global_take_note == 0) {

    /*---PRINT BOT REPSONSE IF THE BOT HAS OPINON ON SAME THING---*/
    if(get_entry_data(hashtable,bot_like) != NULL) {
      get_like_word();
      printf("%s ",get_entry_data(hashtable,bot_like));
    }

    /*---OTHERWSIE A GENERIC RESPONSE---*/
    else {
      get_note_word();
      printf("I'll take note of that ");
    }

    /*---IF NO REASON WAS GIVEN ASK THE USER---*/
    if(reason == 0) {
      printf("why do you not like %s? ",like);
    }
    ++global_take_note;
  }
  return counter-1;
}



/*---FUNCTION FOR I PHRASE---*/
int i_have_trigger(entry_t *hashtable[SIZE],char **words, int index) {

  /*---DECLARE DATA AND KEY---*/
  char have[90] = "have*";
  char *data = "";

  /*---GET KEY---*/
  strcat(have,words[index]);

  /*---GET DATA---*/
  data = get_entry_data(hashtable,have);

  /*---PRINT DATA---*/
  if(data != NULL) {
    printf("%s ",data);
  }

  else {
    int counter = index+1;

    /*---ITERATE THROUGH WORDS LOOKING FOR DATA---*/
    while(words[counter] != NULL) {
      strcpy(have,"have*");
      strcat(have,words[counter]);
      data = get_entry_data(hashtable,have);
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
