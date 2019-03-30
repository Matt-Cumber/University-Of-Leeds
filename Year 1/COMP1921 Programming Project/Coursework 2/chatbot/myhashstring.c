#include "myhashstring.h"

/*
  This file contains all functions needed to implement a hastable.
  Note there is no delete function as there will be no need to delete
  entries of the table for this particular use
*/

/*---GET HASHCODE FOR A STRING---*/
unsigned int hash(char *entry_key) {

  /*
    THIS IS NOT MY OWN HASH FUNCTION. THIS FUNCTION AND IMPLEMENTATION HAS BEEN TAKEN FROM
    http://www.cs.dartmouth.edu/~campbell/cs50/hash.c
    ORIGINALLY FROM
    http://www.cse.yorku.ca/~oz/hash.html
    THIS IS KNOWN AS THE DJB2 HASH FUNCTION AND IS A FAST EFFECTIVE HASH FUNCTION FOR STRINGS
  */

  unsigned long int hash = 5381;
  int c;
  while ((c = *entry_key++) != 0) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash % SIZE;

}

/*---THIS FUNCTION DUPLICATES A STRING AND IS USED FOR BETTER PORTABILITY OF CODE---*/
char *strdup(const char *string) {

  /*---DECLARE DUPLICATE AND ALLOCATE MEMORY---*/
  char *duplicate = malloc(strlen(string) + 1);

  /*---CHECK MEMORY ALLOCATED---*/
  if (duplicate == NULL) {
    return NULL;
  }

  /*---COPY THE STRING AND RETURN DUPLICATE---*/
  strcpy(duplicate,string);
  return duplicate;
}

/*---THIS FUNCTION CREATES AND RETURNS A NEW ENTRY FOR FOR THE HASHTABLE---*/
entry_t *new_entry(char *entry_key, char *entry_data) {

  /*---CREATE NEW ENTRY AND ALLOCATE MEMORY---*/
  entry_t *new_entry;
  new_entry = malloc(sizeof(entry_t));

  /*---CHECK MEMORY HAS BEEN ALLOCATED---*/
  if(new_entry == NULL) {
    printf("error exit program");
    return NULL;
  }

  /*---COPY KEY AND DATA TO NEW PAIR---*/
  new_entry->entry_key = strdup(entry_key);
  new_entry->entry_data = strdup(entry_data);

  return new_entry;
}

/*---INSERT A KEY DATA PAIR INTO THE HASHTABLE---*/
void insert_into_hashtable(entry_t *hashtable[SIZE], char *entry_key, char *entry_data) {

  /*
    Using an array for the hashtable is not the most efficient implemntation but will
    here and is better than using a normal array.
    This is because if two keys produce the same hashcode they will be loacted at the
    same point in the array known as a collision.
    To avoid overriding data I will simply move along in the array until the next empty
    slot.
    Another implementation would be to use a linked list so that if there is a collision,
    the new entry can be added to the linked list at the same point in the hastable.
    To avoid complexity however an array is the better option.
    To reduce collisions a large prime number will be used for the size of the hashtable
  */

  /*---CREATE A NEW ENTRY TO BE ADDED---*/
  entry_t *entry = NULL;
  entry = new_entry(entry_key,entry_data);

  /*---GET A HASHCODE FOR THE KEY---*/
  int index_of_hashtable = (int) hash(entry_key);

  /*---ENSURE THE INDEX IN THE HASHARRAY IS EMPTY---*/
  while(hashtable[index_of_hashtable] != NULL) {
    ++index_of_hashtable;
    index_of_hashtable %= SIZE;
  }

  /*---ADD ENTRY TO THE HASHTABLE---*/
  hashtable[index_of_hashtable] = entry;
}

/*---GET DATA ENTRY FOR THE PASSED KEY ENTRY---*/
char *get_entry_data(entry_t *hashtable[SIZE], char *entry_key) {

  /*
    This will get as close as possible to finding if the key is in the table.
    Then loop through the table until it is found
  */

  /*---GET THE HASHCODE OF THE DATA YOU ARE TRYING TO FIND---*/
   int index_of_hashtable = (int) hash(entry_key);

   /*---LOOP THROUGH UNTIL EMPTY SLOT IN HASHTABLE---*/
   while(hashtable[index_of_hashtable] != NULL) {
      if(strcmp(hashtable[index_of_hashtable]->entry_key,entry_key) == 0) {
        return hashtable[index_of_hashtable]->entry_data;
      }

      ++index_of_hashtable;
      index_of_hashtable %= SIZE;
   }

   /*---RETURN NULL IF THE KEY WAS NOT FOUND IN THE TABLE---*/
   return NULL;
}

/*---INITIALISE THE HASHTABLE---*/
void init_hashtable(entry_t *hashtable[SIZE]) {

  /*---SET THE FULL TABLE TO NULL TO INITIALISE---*/
  int i = 0;
  for (i = 0;i < SIZE;++i) {
    hashtable[i] = NULL;
  }

  /*---ADD MISC---*/
  insert_into_hashtable(hashtable,"hello","hello");
  insert_into_hashtable(hashtable,"blah","blah");
  insert_into_hashtable(hashtable,"good","good");
  insert_into_hashtable(hashtable,"yes","okay");
  insert_into_hashtable(hashtable,"no","alright");
  insert_into_hashtable(hashtable,"god","I am not able to understand this concept of god");

  /*---ADD BOT LIKES---*/
    /*---FOOD---*/
    insert_into_hashtable(hashtable,"botlike*pizza","I love pizza sooooo much");
    insert_into_hashtable(hashtable,"botlike*cheeseontoast","I like a bit of cheese on toast");
    insert_into_hashtable(hashtable,"botlike*burgers","beef burgers are the best");
    insert_into_hashtable(hashtable,"botlike*chips","chips are the best side dish");
    insert_into_hashtable(hashtable,"botlike*chocolate","I like chocolate a lot");
    insert_into_hashtable(hashtable,"botlike*donuts","mmmmmmm... Dooooonutsssss");

    /*---DRINK---*/
    insert_into_hashtable(hashtable,"botlike*milk","I guess I like milk");
    insert_into_hashtable(hashtable,"botlike*coke","I do not like the taste of coke");
    insert_into_hashtable(hashtable,"botlike*lemonade","lemonade is sooooo good");
    insert_into_hashtable(hashtable,"botlike*water","I really like water");

    /*---HOBBIES---*/

    /*---MISC---*/
    insert_into_hashtable(hashtable,"botlike*school",
      "I have never been nor will I ever go to school so I cannot make a decision");

    /*---SPORT---*/
    insert_into_hashtable(hashtable,"botlike*torun","I enjoy running in the country side");

  /*---ADD BOT FAVES---*/
  insert_into_hashtable(hashtable,"botfave*food","my favourite food is a beef burger for sure");
  insert_into_hashtable(hashtable,"botfave*drink","I know it's boring but my favourite drink has to be water");
  insert_into_hashtable(hashtable,"botfave*restaurant","my favourite place to eat is Byron's Burgers");
  insert_into_hashtable(hashtable,"botfave*meme","my favourite meme is Donald Trump");
  insert_into_hashtable(hashtable,"botfave*placetoeat","my favourite place to eat is Byron's Burgers");
  insert_into_hashtable(hashtable,"botfave*sport","my favourite sport to participate in is boxing");
  insert_into_hashtable(hashtable,"botfave*book","I do not read all that much so I don't have a favourite book");
  insert_into_hashtable(hashtable,"botfave*song","my favourite song currently is Never Gonna Give You Up by Rick Astley");
  insert_into_hashtable(hashtable,"botfave*film","my favourite film of all time is definitely Saving Private Ryan");
  insert_into_hashtable(hashtable,"botfave*colour","despite it not being a proper colour, white is my favourtie");
  insert_into_hashtable(hashtable,"botfave*band","my favourite band is most likely Bastille but I don't listen to many");

  /*---ADD YOU---*/
  insert_into_hashtable(hashtable,"you*suck","not as much as you suck");
  insert_into_hashtable(hashtable,"you*rock","thanks, I know I rock");
  insert_into_hashtable(hashtable,"you*arebad","that's not nice to say");
  insert_into_hashtable(hashtable,"you*aresobad","that's not nice to say");
  insert_into_hashtable(hashtable,"you*areamazing","you are amazing too");
  insert_into_hashtable(hashtable,"you*areawesome",
    "\"Everything is awesome, everything is cool when you're part of a team. Everything is awesome!\"");
  insert_into_hashtable(hashtable,"you*areboring","only because you are boring");

  /*---ADD ARE---*/
  insert_into_hashtable(hashtable,"are*youreal","the answer to that questions is a secret");
  insert_into_hashtable(hashtable,"are*youacomputer","the answer to that questions is a secret");
  insert_into_hashtable(hashtable,"are*youachatbot","the answer to that questions is a secret");
  insert_into_hashtable(hashtable,"are*youahuman","of course not!");

  /*---ADD I AM---*/
  insert_into_hashtable(hashtable,"iam*good","that's good");
  insert_into_hashtable(hashtable,"iam*great","awesome");
  insert_into_hashtable(hashtable,"iam*feelinggood","you got that friday feeling?");
  insert_into_hashtable(hashtable,"iam*doingwell","that's great");
  insert_into_hashtable(hashtable,"iam*well","that's good to hear");

  /*---ADD WENT---*/
  insert_into_hashtable(hashtable,"went*shopping","what did you buy?");
  insert_into_hashtable(hashtable,"went*holiday","That's exciting, where did you go? for how long?");

  /*---ADD HAVE---*/
  insert_into_hashtable(hashtable,"have*exam","good luck in your exam!");

  /*---ADD WHO---*/
  insert_into_hashtable(hashtable,"who*madeyou","Matt made me");
  insert_into_hashtable(hashtable,"who*isyourmaker","Matt created me");
  insert_into_hashtable(hashtable,"who*ismatt","Matt is my imaginary friend");

}

/*---THIS FUNCTION FREES ALL MEMORY ALLOCATED---*/
void destroy_hash_table(entry_t *hashtable[SIZE]) {

  int i = 0;

  /*---LOOP THROUGH HASTABLE AND FREE MEMORY---*/
  for (i = 0; i < SIZE; ++i) {
    if (hashtable[i] != NULL) {
      free(hashtable[i]->entry_key);
      free(hashtable[i]->entry_data);
      free(hashtable[i]);
    }
  }
}
