#include "input.h"

/*
  This file is used to get the users input only
*/

char *get_input() {

/*---DECLARE VARIABLES---*/
int i = 0;
int character;
char *input;

/*---ALLOCATE MEMORY TO INPUT SO IT CAN BE RETURNED---*/
input = malloc(MAX_LENGTH_INPUT + 1);

/*---CHECK MEMORY ALLOCATION WAS SUCCESSFUL---*/
if(input == NULL) {
  return NULL;
}

/*---GET USER INPUT---*/
while((i < MAX_LENGTH_INPUT) && ((character = getchar()) != '\n')
        && (character != EOF))
{
  input[i] = character;
  ++i;
}
/*---ENSURE INPUT IS TERMINATED STRING---*/
input[i] = '\0';

return input;

}


/*---SAVE INPUTS TO A FILE TO SEE WHAT USERS TYPE IN---*/
void save_inputs_to_file(char *input) {

  /*---CREATE VARIABLES---*/
  FILE *file;

  /*---OPEN FILE IN READ ONLY---*/
  file = fopen("pastinputs.txt","r");

  /*---CHECK FILE WAS SUCCESSFULLY OPENED---*/
  if (file == NULL) {
    printf("File couldn't be opened\n\a\a");
    fclose(file);
    exit(0);
  }

  /*---CREATE MEMORY TO STORE A LINE FROM FILE AND ADD NEW LINE CHARACTER TO INPUT---*/
  char line[90];
  strcat(input,"\n");

  /*---CHECK IF INPUT IS ALREADY IN THE FILE---*/
  while (fgets(line,sizeof(line),file)) {
    if(strcmp(input,line) == 0) {

      /*---STOP READING THE FILE IF IT IS ALREADY IN THE TEXT FILE---*/
      fclose(file);
      return;
    }
  }

  fclose(file);

  /*---RE-OPEN FILE IN APPEND MODE---*/
  file = fopen("pastinputs.txt","a");

  /*---ADD INPUT TO FILE---*/
  fputs(input,file);
  fclose(file);

  return;
}
