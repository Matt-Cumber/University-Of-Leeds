#include "memory_management.h"
#include <math.h>

/*This function prints the blocks as a list*/
void printblocks(blockheader *head){

  blockheader *block = head;

  printf("---------------------------\n");

  while(block != NULL){
    printf("start of block: %d\n",block);
    printf("size: %d\n",block->size);
    printf("isfree: %d\n",block->isfree);
    printf("prev: %d\n",block->previous);
    printf("next: %d\n---------------------------\n",block->next);
    block = block->next;
  }
}

/*Split a block into two*/
void split_block(blockheader* block, int size) {
  /* create a new block and move the
    pointer to the start of the block*/
  blockheader *newblock = block;
  newblock = (blockheader *)((char*) newblock + size);

  /*assign data to new block*/
  newblock->size = block->size - size;
  newblock->isfree = true;
  newblock->next = block->next;
  newblock->previous = block;

  /*update data on old block*/
  block->size = size;
  block->isfree = false;
  block->next = newblock;
  block->previous = block->previous;
}

/*merge two free blocks together
  the blocks will become one block starting from the beginning
  of the one closest to the head of the list*/
void merge_block(blockheader *freeblock){

  /*Check if the previous block exists and is free
    if it is combine the size of the two blocks
    change the next of the new free larger block
    check if there is a next block in the list and change
    that blocks previous to the new larger block*/
  blockheader *previous = freeblock->previous;
  if(previous != NULL && previous->isfree == true) {
    previous->size = previous->size + freeblock->size;
    previous->next = freeblock->next;
    if(freeblock->next != NULL) {
      (freeblock->next)->previous = previous;
    }
  }

  /*Check if the next block exists and is free
    if it is combine the size of the two blocks
    change the next of the new free larger block
    check if there is a next block in the list and change
    that blocks previous to the new larger block*/
  blockheader *next = freeblock->next;
  if(next != NULL && next->isfree == true) {
    freeblock->size = freeblock->size + next->size;
    freeblock->next = next->next;
    if(next->next != NULL) {
      (next->next)->previous = freeblock;
    }
  }
}

/*Malloc will need to find free blocks for the new memory
  to be allocated
  This fucntion returns a pointer to the free block
  or to the end of the list*/
blockheader* find_free_block(blockheader *head, int size) {

  //create new blocks to store data
  blockheader *p = head;
  blockheader *temp_p = NULL;

  /*Iterate through the list checking if each block is free
    and if the size of the block is big enough for the new
    memory
    Return pointer to block if it meets these conditions
    each iteration store pointer to current block so not to
    return NULL pointer if no block meets conditions*/
  while(p != NULL) {
    if((p->size >= (int) size + sizeof(blockheader))
    && (p->isfree == true)) {
      return p;
    } else {
      temp_p = p;
      p = p->next;
    }
  }
  return temp_p;
}

/*malloc, allocate memory and return pointer to that memory*/
void * _malloc(size_t size){

  /*return NULL if the size is not a valid number*/
  if(size <= 0) return NULL;

    blockheader *return_val;

  /*create a multiplier to be used in system call sbrk
    This multiplier will ensure enough memory is given for
    the maloc call*/
  double sbrkmulti = 1;
  double multi = 1;
  /*If the size of the block to be created is exactly equal
    to the size of one block set the multiplier to 2
    Otherwise mulitplier is cieling of size/4096*/
  if(size+sizeof(blockheader) == 4096) {
    sbrkmulti = 2;
  } else {
    multi = (double)(size+sizeof(blockheader))/4096;
    sbrkmulti = ceil(multi);
  }

  //If this is the first time calling malloc
  if(head == NULL) {

    //Create first Block
    void *startofblock = sbrk(4096*sbrkmulti);
    head = (blockheader *) startofblock;
    head->size = 4096*sbrkmulti;
    head->isfree = false;
    head->next = NULL;
    head->previous = NULL;

    /*Need to split the first block into two blocks
      with one block in use at the beginning and
      a free block after with the remaining amount
      of memory */
    split_block(head,size + sizeof(blockheader));

    /*return a pointer to the start of the memory
      to be used in a program
      This is the start of the head + the size of
      the block header*/
    return_val = (blockheader *)((char*)head+sizeof(blockheader));
    return return_val;

  }

  /*Run if maloc has been called at least once before
    Attempt to find a block which is free
    create a new block*/
  blockheader *ptr = find_free_block(head,size);
  blockheader *newblock = NULL;

  /*If the size of the returned block is not big
    enough for the new memory allocation, this means
    ptr is pointing to the end of the list.
    This means the heap needs to be increased to add blocks
    for the new memeory*/
  if(ptr->size < (int)size) {

    /*extend the heap until there is enough space to
      allocate the new memory
      this is done by creating new blocks at the
      end of the list*/
    while(ptr->size < ((int)size + (int) sizeof(blockheader))) {
      newblock = (blockheader *) sbrk(4096);
      newblock->size = 4096;
      newblock->isfree = true;
      newblock->next = NULL;
      newblock->previous = ptr;
      ptr->next = newblock;
      merge_block(newblock); //Merge the new block
    }

    //split the new large enough block
    split_block(ptr,size + sizeof(blockheader));

    /*return a pointer to the start of the allocated
      memory in the new block*/
    return_val = (blockheader *)((char*)ptr+sizeof(blockheader));
    return return_val;

  } else {

    /*The returned block has a size big enough for the
      new memory*/
       newblock = ptr;
       newblock->size = ptr->size;
       newblock->isfree = false;
       newblock->next = ptr->next;
       newblock->previous = ptr->previous;

       //split the new block
       split_block(newblock,size + sizeof(blockheader));

       /*return a pointer to the start of the allocated
         memory in the new block*/
       return_val = (blockheader *)((char*)newblock+sizeof(blockheader));
       return return_val;
     }
}

/*free sets the value of isfree within a block header
  to true and merges any other free blocks next to
  the newly freed block
  free will also call sbrk(-4096) when there is a free
  page of memory not being used*/
void _free(void * ptr) {

  //Return if ptr is null as cannot be freed
  if(ptr == NULL) {
    return;
  }

  /*get the pointer to the start of the block to be freed
    then set the free value to true and merge with any
    surrounding blocks*/
  blockheader *free_me = (blockheader *)((char*)ptr-sizeof(blockheader));
  free_me->isfree = true;
  merge_block(free_me);

  /*create a test to see if the new free block is at the end
    of the list and if it has a size greater than 4096
    If this is the case and as long as the block is not the head
    of the list the the heap can be reduced by a page
    This is done by calling sbrk(-4096) and shrinking the size
    of the freed block by 4096*/
  int test_condition = (int)((char*)sbrk(0)-(char*)free_me);
  if(free_me ->next == NULL && test_condition > 4096
    && free_me != head) {
    free_me->size = free_me->size - 4096;
    sbrk(-4096);
  }
}

int main() {

  /*assign memory to void pointers*/
  void *p = _malloc(2000);
  void *q = _malloc(100);
  void *r = _malloc(200);
  void *s = _malloc(100);
  void *t = _malloc(5000);

  /*print memory blocks*/
  printf("\n----blocks after _malloc---\n\n");
  printblocks(head);

  /*free some pointers*/
  _free(q);
  _free(t);

  /*print memory blocks to check how free worked*/
  printf("\n----blocks after _free-----\n\n");
  printblocks(head);
  return 0;
}
