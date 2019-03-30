/*****************************************************************************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Matthew Cumber

Email: ll131m23c@leeds.ac.uk

Date: 7/12/17

******************************************************************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

char framebuffer[31][61]; // create framebuffer used to store and print universe

struct Pair{
  int pair_id; // id pf the pair
  int id1; // id of star 1
  int id2; // id of star 2
  char name1[40]; // name of star 1 in pair
  char name2[40]; // name of star 2 in pair
  double x1; // x coordinate of star 1
  double x2; // x coordinate of star 2
  double y1; // y coordinate of star 1
  double y2; // y cooridnate of star 2
  double d; // distance between star 1 and 2
}; // defining a struct to hold data on pairs of stars

 struct Star{
   double x; // x-coordinate of a star
   double y; // y-coordinate of a star
   char name[40]; // name of a star
   int id; // id of a star
   int paired; // this value will be used to determine if a star is in a pair. this value will either be a 1 for in a pair or 0 if not in a pair
   char symbol; // star symbol, '.' if not paired, '*' if paired
 }; // defining a struct type called star to hold variables a star contains
struct Star stars[1891]; // creating an array of stars
struct Pair pairs[945]; // creating an array of pairs of stars

int number_of_stars = 0; // initialize the number of stars in the universe to 0
int number_of_stars_created = 0; // initialize the number of stars created to 0
int number_of_pairs_created = 0; // initialize the number of pairs in the universe to 0

double x; // x coordinate of star
double y; // y coordinate of star

double min_distance_between_stars = 100; // variabled used to store the minimum distance between of two stars from all stars, assign large number to a minimum so that the first distance will always be less
double temp_min_distance_between_stars = 0; // declare variable used for storing a temporary minimum distance to compare to actual minimum distance
int temp_closest_pair_id_star1 = -1; // variable used to temporarily store the id of a star, initially negative so that it is an invalid id
int temp_closest_pair_id_star2 = -1; // variable used to temporarily store the id of a star, initially negative so that it is an invalid id
char temp_star1_name[40]; // used to temporarily store a stars name
char temp_star2_name[40]; // used to temporarily store a stars name

char search_name[40]; // this stores input from user during show command so the program can search for a star with the same name as the users input
char pair_names[80]; // this stores the name of two stars in the show command

char c; // declare a char to ensure fgets waits for input used in Name function

void WriteAt(int x, int y, const char str[]) // function to write the string str beginning at corodinates x and y
{
  int j = x; // create in j for use in loop tpo iterate through x coordinates
  for(int i=0;i<strlen(str);++i) // loop through characters in string
  {
    if(j<0) // if trying to print string not in framebuffer
      {
        j=0; // set j to 0 so that the string can begin to be copied to the framebuffer from the start of the frame buffer array x cooridnate
        framebuffer[y][j] = str[i]; // copy the character in the string passed through the fucntion to the frame buffer
        ++j; // increment j before new iteration in for loop to move to next x coordinate
      }
    else{
      if(j==60) // if j i.e. the x coordinate is equal to the last index of the frame buffer
        {
          framebuffer[y][j] = str[i]; // print final character
          return; // return to prevent attempt at trying to access memory of framebuffer array which doesn't exist to prevent segmentation fualt
        }
        else{
          framebuffer[y][j] = str[i]; // otherwise if no special condition is met just print character to correct framebuffer position
          ++j; // increment j for new iteration
        }
    }
  }
}

void Refresh() // this function refreshes the terminal by clearing the screen and putting the cursor to the top left corner
{
  system("clear"); // clears terminal
  for(int i=0;i<31;++i) // loop to iterate through y coordinates
    {for(int j=0;j<61;++j) // loop to iterate through x coordinates
      printf("%c", framebuffer[i][j]); // assign space to current location in framebuffer

      printf("\n"); // print new line for next row
    }
}

void Initialize() // Initializes variables
{
  number_of_pairs_created=0; // reset the number of pairs and stars created
  number_of_stars_created=0;
}

void Clear() // this function clears the framebuffer by assigning ' ' to all possible combinations of indexes
{
  for(int i=0;i<31;++i) // loop to iterate through y coordinates
    for(int j=0;j<61;++j) // loop to iterate through x coordinates
      framebuffer[i][j] = ' '; // assign space to current location in framebuffer
}

void Plot(int x, int y, char c) // this function assigns c to the location [y][x] in the framebuffer i.e plots a star or pair
{
  framebuffer[y][x] = c;
}

double Distance(double x1, double y1, double x2, double y2) // calculates and returns the distance between two stars
{
  double distance = 0; // initialize a variable called distance
  distance = sqrt((pow((x2-x1),2) + pow((y2-y1),2))); // formula to calculate the distance between two points
  return distance; // return the distance between the points
}

void Name() // Finds the closest pairs of stars and allows user to name them
{
  char choice[10]; // used to decide between a users choice later on

  for(int i=0; i<number_of_stars_created;++i) // loop to iterate through stars
    {
      for(int j=0; j<number_of_stars_created;++j) // loop to compare all stars to star i
        {
          if(stars[i].paired==1) // check if paired value of star i is a 1 or a 0
            {
              j=number_of_stars_created; // stop iterating and comparing stars with star i as it is already in a pair
            }
          else{
            if(stars[i].id==stars[j].id) // check if the stars i and j have the same id
              {
                // if they have the same id move to the next star
              }
            else{
              if(stars[j].paired==1) // check if the star which is being compared to is already in a pair
                {
                  // if the star is already in a pair move to the next star
                }
              else{
                  temp_min_distance_between_stars = Distance(stars[i].x, stars[i].y, stars[j].x, stars[j].y); // calculate distance between star i and j and temporarily store this
                if(temp_min_distance_between_stars<min_distance_between_stars) // check if the newly calculated distance is less than the current minimum distance between
                  {
                    min_distance_between_stars = temp_min_distance_between_stars; // store the distance between the stars if it is the smallest so far
                    temp_closest_pair_id_star1 = stars[i].id; // store the id of star i
                    temp_closest_pair_id_star2 = stars[j].id; // store the id of star j
                  }
                else{
                  // move to next star
                }
              } // end final else

            } // end second else
          } // end first else
    } // end second for loop
  } // end first for loop
  // message to ask user if they want to name stars
  printf("The closest pair of stars are stars %d and %d.\nThey are %d light years apart.\nWould you like to name them? (enter y for yes, n for no) : ", temp_closest_pair_id_star1, temp_closest_pair_id_star2, (int) min_distance_between_stars); // ask user if they would like to name stars

 while(true) // loop to prevent user inputting an invalid choice
 {
  scanf(" %s", &choice); // user inputs their choice
  if(strcmp("n", choice)==0) // compare users input to "no"
  {
    return; // if no then do not name the stars and end the function using return
  }
  else{
    if(strcmp("y", choice)==0) // compare users input top "y"
    {
        while (c != '\n' && c != EOF) // clears input stream
        {c = getchar();}
      c = 'a'; // assign a character to c so that it is not \n or EOF in order so that when Name is called again the while loop
      printf("Enter your name : ");
      fgets(temp_star1_name, sizeof(temp_star1_name), stdin); // reads line of input from user for name of first star
      temp_star1_name[strlen(temp_star1_name)-1] = '\0'; // remove last character from input as this will be \n and is not part of the string
      printf("Enter your partners name : ");
      fgets(temp_star2_name, sizeof(temp_star2_name), stdin); // reads line of input from user for name of second star
      temp_star2_name[strlen(temp_star2_name)-1] = '\0';  // remove last character from input as this will be \n and is not part of the string
      pairs[number_of_pairs_created].id1 = temp_closest_pair_id_star1; // copy id of star 1 to pair id1
      pairs[number_of_pairs_created].id2 = temp_closest_pair_id_star2; // copy id of star 2 to pair id2
      pairs[number_of_pairs_created].d = min_distance_between_stars; // copy the distance between the stars to the pair d
      pairs[number_of_pairs_created].pair_id = number_of_pairs_created; // assign the number of pairs cerated to the id as this will never be the same each time a pair is made
      for(int i=0;i<number_of_stars_created;++i) // for loop to iterate through all stars
        {
          if(stars[i].id==temp_closest_pair_id_star1) // if the star in the loop has the same id as that stored for the first star of which the min distance was calculated, then
            {
              stars[i].paired = 1; // assign 1 to star i's paired value to identify it is now in a pair
              stars[i].symbol = '*'; // change the stars symbol so it is now a paired star
              Plot((int)stars[i].x, (int)stars[i].y, '*'); // plot the stars new symbol to the frame buffer in the stars coordinates
              strcpy(stars[i].name, temp_star1_name); // copy the name of the temp star top the name of star i
              strcpy(pairs[number_of_pairs_created].name1, stars[i].name); // copy the name of the star in the pair to the name of the first star in the correct pair of the pairs array
              pairs[number_of_pairs_created].x1 = stars[i].x; // copy the stars x coordinate to the pairs array
              pairs[number_of_pairs_created].y1 = stars[i].y; // copy the stars y coordinate to the pairs array
            }
          else{
            if(stars[i].id==temp_closest_pair_id_star2) // if the star in the loop has the same id as that stored for the second star of which the min distance was calculated, then
              {
                stars[i].paired = 1; // assign 1 to star i's paired value to identify it is now in a pair
                stars[i].symbol = '*'; // change the stars symbol so it is now a paired star
                Plot((int)stars[i].x, (int)stars[i].y, '*'); // plot the stars new symbol to the frame buffer in the stars coordinates
                strcpy(stars[i].name, temp_star2_name); // copy the name of the temp star top the name of star i
                strcpy(pairs[number_of_pairs_created].name2, stars[i].name); // copy the name of the star in the pair to the name of the first star in the correct pair of the pairs array
                pairs[number_of_pairs_created].x2 = stars[i].x; // copy the stars x coordinate to the pairs array
                pairs[number_of_pairs_created].y2 = stars[i].y; // copy the stars y coordinate to the pairs array
              }
          }
          // If neither of these are satisfied then move onto the next star
        }
      ++number_of_pairs_created; // increment number of pairs as there is now an additional pair
      min_distance_between_stars = 100; // reset min distance to a large value for when Name is called on again
      printf("You have now successfuly created a pair of stars named after you are your partner.\n"); // print success message
      return;
    }
    else{
      printf("Please enter y or n : "); // prints error message saying enter "y" or "n"
    }
  }
}
} // end Name function

int StarHere(double x, double y) // This function checks if a star already has the randomly generated corodinates
{
  for(int i=0;i<number_of_stars_created;++i) // loops through all generated stars
    {
      if(x == stars[i].x && y == stars[i].y) // checks if the coordinates match exaclty
        {
          return 1; // return 1 if a star already has the generated coordinates
        }
    }
    return 0; // return 0 if they are new coordinates
}

int SearchName(const char str[]) // search if a star is exaclty the same as a string passed through the function
{
  for(int i=0;i<number_of_pairs_created;++i) // iterate through all named stars i.e all stars in a pair
    {
      if(strcmp(str, pairs[i].name1) == 0 || strcmp(str, pairs[i].name2) == 0) // if str is exaclty the same as name1 or name2 the return 0 as true
        return 0;
    }
  return 1; // return 1 if no stars have that name to signify false
}

int main()
{
  time_t t;
  srand((unsigned) time(&t)); // seeding random number generator

  int universe = 0; // if a universe is in the frame buffer then variable universe == 1, otherwise ==0
Clear(); // initialize frame buffer

  printf("Welcome to Create'O'Universe! Enter a command to begin.\n"); // print welcome message

char command[4]; // create an array of characters fro the commands to be stored in as strings

  while(true) // create infinite loop for a cli interface
  {
    printf(">>>>"); // prints promt to user program is ready for input
    scanf(" %s", &command); // read input from user as string stored to command array

    if(strcmp("bang", command) == 0) // compare users input with bang command, if they are the same strcmp = 0
      {
        scanf(" %d", &number_of_stars); // user inputs the number of stars they want to be in the universe
          while(true) // loop for validating user input
            {
              if(number_of_stars>1891 || number_of_stars<0) // if the user wants to create a universe with a negativenumber of stars do not allow, and if they exceed the maximum allowed in the frame buffer, prevent this to avoid segmentation fualt
                {
                  printf("That is not a valid number of stars. The maximum is 1891 and the minimum is 0.\nEnter new number of stars : "); // print error message
                  scanf(" %d", &number_of_stars); // get new input if the original input was invalid
                }
                else{
                  break; // end validation loop if input is allowed
                }
            }
        Clear(); // clear frame buffer i.e remove old universe from the frame buffer before a new universe is created
        Initialize(); // Initialize variables
        printf("Bang!\n"); // print bang to signify that the bang command has worked
        universe = 1; // change universe to 1 as a universe has been create
        for(int i=0;i<number_of_stars;++i) // loop used to create new stars
          {
            x = rand () % 61; // assigns a random number from 0-60 to x
            y = rand () % 31; // assigns a random number from 0-30 to y
            while(true) // create loop for verifying coordinates
            {
              if(StarHere(x,y)==1) // check if StarHere returns 1
                {
                  x = rand () % 61; // generate new coordinates if they already exist
                  y = rand () % 31;
                }
              else{
                break; // otherwise break while loop and run rest of bang command
              }
            }

            stars[i].x = x; // assigns x to star i's x coordinate
            stars[i].y = y; // assigns y to star i's y coordinate
            stars[i].id = i; // assigns i to the id of star i
            stars[i].paired = 0; // assign 0 to star i's paired value to indicate it is not in a pair as it has just been created
            stars[i].name[0] = ' '; // defualt the name of the star to a single space character
            stars[i].symbol = '.'; // change the stars symbol to . as it has just been created and not in a pair
            Plot((int)x, (int)y, '.'); // store the star i.e '.' in the frame buffer with indexes corresponding to the stars coordinates such that coordinates (10,20) are stored in framebuffer[20][10]
            ++number_of_stars_created;
          } // end for loop
      } // end if for bang command

      else{
        if(strcmp("list", command) == 0) // compare users input with list command, if they are the same strcmp = 0
          {
            if(number_of_stars_created==0) // if there are no stars in the universe
              {
                printf("There are no stars in the current universe. Create one with a bang!\n"); // tell user to create a universe
              }
            else{
              for(int i=0;i<number_of_stars_created;++i) // loop to iterate through all the stars in the universe. note the first star is star 0
              {
                if(stars[i].name[0]==' ') // if the star has the same name as that initialized then it has no name by defualt
                  {
                    printf("Star no. %d\nStar has no name\ncoordinates (%f,%f)\n", stars[i].id, stars[i].x, stars[i].y); // prints the star id of star i first, the it's coordinates
                  }
                else{
                  printf("Star no. %d\nStar is named %s\ncoordinates (%f,%f)\n", stars[i].id, stars[i].name, stars[i].x, stars[i].y); // prints the star id of star i first, the it's coordinates
                }
              }
            }

          }

          else{
            if(strcmp("quit", command) == 0) // compare users input with quit command, if they are the same strcmp = 0
            {
              system("clear"); // clears the users terminal since they are no longer running the program and so the terminal is not over crowded
              printf("Thank you for playing Create'O'Universe! Hope you had fun.\n"); // prints goodbye message to user
              break; // breaks the while loop which in turn terminates the program
            }

            else{
              if(strcmp("name", command) == 0) // compare users input with name command, if they are the same strcmp = 0
              {
                if(number_of_stars_created % 2 != 0) // check if the number of stars is even
                  {
                    if(number_of_pairs_created==((number_of_stars_created-1)/2)) // in the case the number of stars is not even, check if the number of pairs is equal to half of the number of stars minus one
                      {
                        printf("All possible pairs have been made. No more pairs can be created. How about creating a new universe!\n"); // if the number of pairs is half, then no more pairs can be made as there are not two free stars just one. sp print message saying no more pairs available
                      }
                    else{ // if there are two ore more stars unpaired then
                      Name(); // find the closest pair of stars and name them
                    }
                  } // end for loop 1 within name command
                else{ // if the number of stars is even
                  if(number_of_pairs_created==(number_of_stars_created)/2) // check if the number of pairs is half the number of stars
                    {
                      printf("All possible pairs have been made. No more pairs can be created. How about creating a new universe!\n"); // if it is then all pairs have been made and no stars remain
                    }
                  else{ // if they are not equal then
                    Name(); // find the closest pair of stars and name them
                  }
                } // end else even number of stars
              } // end if for name command
              else{
                if (strcmp("draw", command) == 0) // compare users input with draw command, if they are the same strcmp = 0
                  {
                    if(universe==0)
                      {
                        printf("Create a universe with a bang! before drawing one.\n");
                      }
                    else{
                      Clear(); // reset the frame buffer to remove star names
                      for(int i=0;i<number_of_stars_created;++i)
                        Plot((int)stars[i].x, (int)stars[i].y, stars[i].symbol); // replot the stars before drawing them
                        Refresh(); // refresh terminal and prints framebuffer

                    }
                  }
                else{
                  if(strcmp("pairs", command) == 0) // compare users input with pairs command, if they are the same strcmp = 0
                    {
                      if(number_of_pairs_created==0) // check if thereare no pairs made
                        {
                          printf("There are no pairs. Use the name command to make a pair.\n"); // print message to tell user to make a pair before printing all pairs
                        }
                      else{
                        printf("----------------------------------------------------------\n");
                        for(int i=0;i<number_of_pairs_created;++i) // loop through all pairs
                          {
                            printf("Pair %d\nStars in pair are no. %d and %d\nThey are %d light years from each other\nStar %d is called %s with coordinates (%f,%f)\nStar %d is called %s with coordinates (%f,%f)\n----------------------------------------------------------\n", pairs[i].pair_id, pairs[i].id1, pairs[i].id2, (int)pairs[i].d, pairs[i].id1, pairs[i].name1, pairs[i].x1, pairs[i].y1, pairs[i].id2, pairs[i].name2, pairs[i].x2, pairs[i].y2);
                          } // prints all pairs
                      }

                    }
                    else{
                      if(strcmp("show", command) == 0) // compare users input with show command, if they are the same strcmp = 0
                        {
                          while (c != '\n' && c != EOF) // clears input stream
                          {c = getchar();}
                          c = 'a'; // assign a character to c so that it is not \n or EOF in order so that when Name is called again the while loop
                          printf("Enter the name of the star you would like to be shown : ");
                          fgets(search_name, sizeof(search_name), stdin);
                          search_name[strlen(search_name)-1] = '\0'; // removes the last character from the search string as this will be \n
                              if(SearchName(search_name) == 0) // compare the users input string with the names of all stars in a pair using SearchName function
                                {
                                  for(int i=0;i<number_of_pairs_created;++i)
                                    {
                                      if(strcmp(search_name,pairs[i].name1) == 0 || strcmp(search_name,pairs[i].name2) == 0)
                                        {
                                          strcpy(pair_names, pairs[i].name1);
                                          strcat(pair_names, " & ");
                                          strcat(pair_names, pairs[i].name2); // format pairnames into "star1name & star2name"
                                          if(pairs[i].y1>pairs[i].y2) // check which star is closer to the bottom of the frame buffer
                                            {
                                              if(pairs[i].y1 == 30) // if the corodinate of the lower star is at the bottom of the framebuffer
                                                {

                                                  Refresh(); // print the entire frame buffer as it is
                                                  for(int j=0;j<(int)(pairs[i].x1)-strlen(pair_names)/2;++j)
                                                    {
                                                      printf(" "); // print enough spaces to centralise the names of the two stars under the x coordinate of the lower star
                                                    }
                                                  printf("%s\n", pair_names); // then print the names of the stars
                                                }
                                              else{
                                                WriteAt((int)(pairs[i].x1)-strlen(pair_names)/2,(int)(pairs[i].y1)+1,pair_names); // write the names of the stars below the lowest star and centralise the names
                                                Refresh(); // print the frame buffer which now stores the names
                                              }
                                            }
                                          else{ // same as above but with the stars having the same y corodinate or star 2 being lower
                                            if(pairs[i].y2 == 30)
                                              {
                                                Refresh();
                                                for(int j=0;j<(int)(pairs[i].x2)-strlen(pair_names)/2;++j)
                                                {
                                                  printf(" ");
                                                }
                                                printf("%s\n", pair_names);
                                              }
                                            else{
                                              WriteAt((int)(pairs[i].x2)-strlen(pair_names)/2,(int)(pairs[i].y2)+1,pair_names);
                                              Refresh();
                                            }
                                          }
                                        }
                                    }
                                }
                              else{
                                  printf("Star not found.\n"); // if the name was not found print message
                                }
                                // at end of command
                                  memset(pair_names,0,sizeof(pair_names)); // clear the array which holds the names of the stars shown so that a new pair can be stored in the array
                                  Clear(); // clear the framebuffer to remove star names
                                  for(int i=0;i<number_of_stars_created;++i)
                                    Plot(stars[i].x,stars[i].y,stars[i].symbol); // replot all stars

                          } // end show command

                      else{
                        if(strcmp("save", command) == 0) // compare users input with save command, if they are the same strcmp = 0
                          {
                            FILE *universefile = NULL;
                              universefile = fopen ("universe.bin","wb"); // open file
                              if (universefile!=NULL) // if the file was successfully opened then
                              {
                               fwrite(&stars, sizeof(struct Star), 1891, universefile); // save all structs containing star data
                                fwrite(&number_of_stars_created, sizeof(number_of_stars_created), 1, universefile); // save the number of stars created
                                fwrite(&pairs, sizeof(struct Pair), 945, universefile); // save all data on pairs
                                fwrite(&number_of_pairs_created, sizeof(number_of_pairs_created), 1, universefile); // save the number of pairs created
                                fclose(universefile); // close the file as it is no longer needed
                                printf("Universe saved!\n"); // print successful save message
                              }
                              else{
                                printf("Error saving file.\n"); // print message to signify there was an error
                              }
                          }
                          else{
                            if(strcmp("load", command) == 0) // compare users input with load command, if they are the same strcmp = 0
                              {
                                Clear(); // clear the framebuffer vefore loading
                                FILE *universefile = NULL;
                                  universefile = fopen ("universe.bin","rb"); // open the file
                                  if (universefile!=NULL)
                                  {
                                    fread(&stars, sizeof(struct Star), 1891, universefile); // read all strcuts with star data
                                    fread(&number_of_stars_created, sizeof(number_of_stars_created), 1, universefile); // read number of stars created
                                    fread(&pairs, sizeof(struct Pair), 945, universefile); // read all structs with pair data
                                    fread(&number_of_pairs_created, sizeof(number_of_pairs_created), 1, universefile); // read number of pairs
                                    printf("Universe loaded!\n"); // print successful load message
                                    for(int i=0;i<number_of_stars_created;++i)
                                    Plot(stars[i].x,stars[i].y,stars[i].symbol); // replot the stars just loaded
                                    fclose(universefile); // close the file no longer needed
                                  }
                                  else{
                                    printf("Error saving file.\n"); // print error message if file was not opened correclty
                                  }
                              }
                              else{
                                // the message below is printed if the user input a command which doesnt exactly match the predetermined inputs and lists all valid commands with a brief description of their use
                                printf("That is not a command. All commands are case sensitive and are:\n'bang' (creates universe), 'list' (lists all stars in universe), 'name' (finds closest pair of stars if available and allows for them to be named), 'pairs' (lists all stars that are in a pair)\n'draw' (prints universe to screen), show (shows where a named star is), 'save' (saves universe to your computer), 'load' (restores a previously saved universe that is stored on your computer)\nand 'quit' (terminates the program)\n");
                              } // end final else
                          } // end eighth else

                      } // end seventh else
                    } // end sixth else

                } // end fith else

              } // end fourth else

            } // end of third else

          } // end of second else

      } // end of first else

  } // end of while loop
}
