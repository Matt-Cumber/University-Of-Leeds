#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>


typedef struct blockheader{
  int size;
  bool isfree;
  struct blockheader *next;
  struct blockheader *previous;
} blockheader;

blockheader *head = NULL;

void * _malloc(size_t size);

void _free(void * ptr);

blockheader* find_free_block(blockheader *head, int size);

void printblocks(blockheader *head);

void merge_block(blockheader *block);

void split_block(blockheader* block, int size);
