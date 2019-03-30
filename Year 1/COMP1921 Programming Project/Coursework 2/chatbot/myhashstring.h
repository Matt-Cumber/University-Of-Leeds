#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---DEFINE MACROS---*/
#define SIZE 3851

/*---DEFINE STRUCT DATATYPE---*/
struct entry {
  char *entry_key;
  char *entry_data;
};

typedef struct entry entry_t;

/*---DEFINE FUNCTIONS---*/
char *duplicate_string(char *string);

unsigned int hash(char *entry_key);

char *strdup(const char *string);

entry_t *new_entry(char *entry_key, char *entry_data);

void insert_into_hashtable(entry_t *hashtable[SIZE], char *entry_key, char *entry_data);

char *get_entry_data(entry_t *hashtable[SIZE], char *entry_key);

void init_hashtable(entry_t *hashtable[SIZE]);

void destroy_hash_table(entry_t *hashtable[SIZE]);
