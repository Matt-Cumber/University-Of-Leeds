#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*---DEFINE MACROS---*/
#define SIZE 3851
#define MAX_LENGTH_INPUT 80

/*---DEFINE STRUCT DATATYPE---*/
struct entry {
  char *entry_key;
  char *entry_data;
};

typedef struct entry entry_t;


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

entry_t *new_entry(char *entry_key, char *entry_data) {
  entry_t *new_entry;
  new_entry = malloc(sizeof(entry_t));

  if(new_entry == NULL) {
    printf("error exit program");
    return NULL;
  }

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
  entry = newpair(entry_key,entry_data);

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
   printf("get index : %d\n",index_of_hashtable);

   /*---LOOP THROUGH UNTIL EMPTY SLOT IN HASHTABLE---*/
   while(hashtable[index_of_hashtable] != NULL) {
     printf("entry key %s\n",entry_key);
     printf("hash key %s\n",hashtable[index_of_hashtable]->entry_key);
      if(strcmp(hashtable[index_of_hashtable]->entry_key,entry_key) == 0) {
        return hashtable[index_of_hashtable]->entry_data;
      }

      ++index_of_hashtable;
      index_of_hashtable %= SIZE;
      printf("index_of_hashtable : %d\n",index_of_hashtable);
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

  /*---ADD HASH KEY AND DATA PAIRS---*/
  insert_into_hashtable(hashtable,"cats","I hate cats");
  insert_into_hashtable(hashtable,"dogs","I love dogs");
  insert_into_hashtable(hashtable,"cars","I like cars");
  insert_into_hashtable(hashtable,"books","I like to read");
  insert_into_hashtable(hashtable,"football","I hate football");
  insert_into_hashtable(hashtable,"racing","I like racing");
  insert_into_hashtable(hashtable,"rally","I love rally");
  insert_into_hashtable(hashtable,"boxing","I like boxing");

}

void destroy_hash_table(entry_t *hashtable[SIZE]) {
  int i = 0;
  for (i = 0; i < SIZE; ++i) {
    if (hashtable[i] != NULL) {
      free(hashtable[i]->entry_key);
      free(hashtable[i]->entry_data);
      free(hashtable[i]);
    }
  }
}


/*---TRY AND FIND HASH VALUE FOR WORDS IN STRING---*/
bool try_hash(entry_t *hashtable[SIZE], char *string) {
  /*---CREATE A COPY OF PASSED STRING SO THAT THE PASSED STRING IS NOT MODIFIED---*/
  char copy_of_string[MAX_LENGTH_INPUT];
  memset(copy_of_string,'\0',sizeof(copy_of_string));
  strcpy(copy_of_string,string);

  /*---CREATE VARIABLE TO STORE WORDS AND HASH VALUE---*/
  char *word;
  const char *delimeter = ",";
  char *data;

  int successful_hash = 0;

  /*---GET FIRST WORD---*/
  word = strtok(copy_of_string,delimeter);

  /*---LOOP THROUGH ALL WORDS IN STRING---*/
  while(word != NULL) {

    /*---GET HASH DATA FOR WORD---*/
    data = get_entry_data(hashtable,word);

    /*---IF THE HASH WAS SUCCESSFUL PRINT THE DATA--*/
    if(data != NULL) {
      printf("%s",data);
      successful_hash = 1;
    }

    /*---GET NEXT WORD---*/
    word = strtok(NULL,delimeter);
  }

  /*---CHECK FOR A SUCCESSFUL HASH---*/
  if(successful_hash == 1) {
    return true;
  }

  /*---RETURN FALSE IF NO WORDS PRODUCED A HAS REPSONSE---*/
  else {
    return false;
  }
}


 int main() {
   char *user_input;
   entry_t *hashtable[SIZE];

   /*---INITIALISE HASHTABLE---*/
   init_hashtable(hashtable);

   printf("init\n\n");

   user_input = "train";

   bool process_decider;

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "cats";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "football";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "dogs";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "boxing";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "racing";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "cars";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "rally";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   user_input = "books";

   process_decider = try_hash(hashtable,user_input);

   if(process_decider == false) {
     printf("do not understand");
   }

   printf("\n\n");

   destroy_hash_table(hashtable);
 }
