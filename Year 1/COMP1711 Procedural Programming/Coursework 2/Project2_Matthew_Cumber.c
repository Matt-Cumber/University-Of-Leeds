/*****************************************************************************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Matthew Cumber

Email: ll16m23c@leeds.ac.uk

Date: 12/11/17

******************************************************************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxqueuesize 60 // Defining max number of patients in queue as this number is used multiple times so is easy to change once rather than multiple times
#define maxarrayindex 59 // Arrays begin at 0 so the max array index is one less than array size
#define maxnumberofdoctorsrooms 10 // Defining max number of rooms available at the surgery
#define PASSWORD 2809 // Defining the password

int first = -1, last = -1; // Variable first will represnt the first patient in the queue, last will be the last patient in the queue. Set both to -1 to empty the queue as -1 is not an index of the array
int patientqueue[maxqueuesize]; // Creating an array of integers whihc will be the queue of patients. Array size equal to maxqueuesize
int patientID = 0; // Creating a variable which will store pateint ID's temporairly when they are entered into the system before they are added the the queue or sent to a doctors room
int doctorsroom = 0; // Creating a variable which will store a doctors room number temporarily when used in a command
int numberofpatientswaiting = 0; // This will count the number of patients in the queue. Set as 0 initially as the queue is empty
int rooms[maxnumberofdoctorsrooms-1]; // Creating an array which will represent the number of doctors rooms at the surgery. Array size equal to maxnumberofdoctorsrooms
int patientinroom[maxnumberofdoctorsrooms-1]; // Creating an array whihc will store the ID if a patient who is currently being seen by a doctor in a room

bool IsFull () // Function to check if the queue is full
{
  if (last == (first-1) || first == 0 && last == maxarrayindex)
   /* The queue can be full if first is at the start of the array i.e. index 0 and last is the maximum index of the array allowed as no more patients can be added to the queue without removing one first.
   The queue could also be full if the last index is one less than the first index as again here a patient cannot be added without removing one patient */

  {
    return true; // Then, since this is a boolean function, will return true if the queue is full
  }
  else
  {
    return false; // Return false if the queue is not full
  }
}

bool IsEmpty () // Function to check if the queue is empty
{
  if (first == -1 && last == -1) // The queue is empty iff first and last are both equal to -1
  {
    return true; // Then, since this is a boolean function, will return true
  }
  else
  {
    return false; // If the queue is not empty the function returns false
  }
}

int First() // This function returns the patient ID of the patient who is first in the queue
{
  if (IsEmpty())
  {
    return; // Returns nothing since the queue is empty
  } // Firstly, the function calls on the IsEmpty function to check the queue is not empty. If it is empty the function returns true and the if statement becomes true
  else
  {
    return patientqueue[first]; // If the queue is not empty then the function returns the patient ID in the array with an index equal to that of first
  }
}

int Last() // This function returns the patient ID of the patient who is last in the queue
{
  if (IsEmpty())
  {
    return; // Returns nothing since the queue is empty
  } // Firstly, the function calls on the IsEmpty function to check the queue is not empty. If it is empty the function returns true and the if statement becomes true
  else
  {
    return patientqueue[last]; // If the queue is not empty then the function returns the patient ID in the array with an index equal to that of last
  }
}

bool ValidPatientID(int n) // This function validates a patients ID
{
  if (n>999 || n<1) /* A patient's Id is three digits long so it will never be greater than 999, also the ID is a positive number and there is no patient 0 as this is used as examples in the help function,
  hence ID's cannot be less than 1 */
  {
    printf("That is not a valid ID number. Please enter a three digit number that is not 0.\n"); // If the ID is not valid, firstly the function prints the ID number is invalid
    return false; // Secondly the function returns false to signify an invalid number has been entered
  }
  else
  {
    return true; // If the ID is valid, the the function returns true
  }
}

bool VerifyPassword() // This function is used to verify the password used by doctors
{
  int password = 0; // Declare variable password to store the password the user enters
  printf("Please enter the password to authorise this command : "); // Ask the user to enter the password
  scanf("%d", &password); // store the users input to password
  if (password==PASSWORD) // checks if password is equal to the correct password currenlty 2809
  {
    return true; // If the password is equal to 2809 then returns true to signify a correct password
  }
  else
  {
    printf("The password is incorrect. \n"); // Prints the password is inorrect if it does not equal to 2809
    return false; // then returns false;
  }
}

void Clear() // This function clears the queue by making first and last equal to -1
{
  int i = 0; // Declare i for use in loop

  first = -1; // Assigning -1 to first
  last = -1; // Assigning -1 to last
  numberofpatientswaiting = 0; // The queue has been cleared so there are now 0 patients waiting

  while (i<maxqueuesize) // This loop assigns zero to the whole array
    {
      patientqueue[i] = 0;
      i++; // Increment i for new iteration
    }
}

void Print () // This function will print all the patients ID's which are waiting in the queue
{
  int i = first; // Assign first to i which will be used in a loop

  if (VerifyPassword()) // Calls upon verifypassword function and if true proceeds with the function
    {
      if (IsEmpty()) // Calls on IsEmpty fucntion
      {
        printf("The queue is empty. \n"); // Print the queue is empty if IsEmpty is true
        return; // If IsEmpty is true the return and end the function since there is no queue to print
      }

      else
      {
        printf("There are currently %d patient(s) who are waiting to be seen. They are :\n", numberofpatientswaiting); // If there are patients in the queue, prints the number of number of patients who are waiting


        while (1) // create Infinite loop
        {
          if (i==last) // If i is equal to last then this is the last patient ID to be print
          {
            printf("%d", patientqueue[i]); // Then print the ID of the last patient without a comma as they are the last in the queue
            i++; // Still increment i so that in the next iteration the condition is false and the loop ends
          }
          else // If i does not equal last
          {
            if (i==maxarrayindex) // Checks if i is at the end of the array
              {
                printf("%d, ", patientqueue[i]); // If it is print the ID at i
                i=0; // The set i back to 0
              }

            else // If it is not at the end of the array then
              {
                printf("%d, ", patientqueue[i]); // Print the ID of the patient in the ith index of the array
                i++; // Increment i to be able to print the next patient waiting in the queue
              }
          }
          if(i==last+1) // If i=last+1 then there are no more pateints left to be printed
            {
              break; // So breaks the loop
            }
        }
      }
    }
    printf("\n"); // Print new line so command prompt is on new line
}

void ExitSystem () // This function is used to exit the system
{
  if (VerifyPassword()) // Calls upon verifypassword function and if correct exit the system
   {
     printf("The system will now termninate have a good day\n"); // Prints goodbye message
     exit(0); // Exit program
   }
}

void Help() // This function prins all the information about each command in order to help the user
{
  printf ("Please read the following commands carefully:\n\n If you have just arrived you must check in before being seen by a doctor at which point you will either be added to the queue of patients or be told to go to a room to see a doctor immediately. Do this by \n entering the letter 'i' followed by your patient ID which is the unique three digit integer given to you. If you do not know your patient ID or are yet to be given one, please ask someone at reception and\n they will attend to your needs. \n\n  Example:  >>>> i 000\n\n If you have already checked in and would like to view your position in the queue enter the letter 'p' followed by your patient ID.\n\n  Example:  >>>> p 000\n\n If you have checked in and would like to leave before seeing any of our doctors enter the letter 'q' followed by your patient ID.\n\n  Example:  >>>> q 000\n\n If you would like to view how many doctors we currently have working at the surgery and which particular rooms are currently staffed enter the letter 'd'.\n\n  Example:  >>>> d\n\n Patients need not read any further.\n If you are a doctor or member of staff you may also use the following commands. Before the commands are run you will be asked to verify your status by entering the password.\n\n To discharge a patient which has been seen to enter the letter 'o' followed by the ID of the patient which has been seen to.\n\n  Example:  >>>> o 000\n\n To notify the system you are ready to see a patient enter the letter 'r' followed by the room number you are currently in.\n\n  Example:  >>>> r 0\n\n If you would like to leave your room and see no more patients enter the letter 'a' followed by the room number you are in.\n\n  Example:  >>>> a 0\n\n If you would like to see the list of patients currently waiting in the queue enter the letter 'w'.\n\n  Example:  >>>> w\n\n If you would like to terminate the program as the surgery is closed or no more patients are to be seen enter the letter 'x'.\n\n  Example:  >>>> x\n\n"); // Long help message dispalyed to user ");
  // Long help messaged displayed to user (Side note not sure why \n are not a different colour)
}

bool IsNotInQueue (int n) // Function to determine if a patient is not in the queue
{
  int i = first; // Declare i to be used in loop and assign value of first

   while (1) // create infite loop
    {
      if (patientqueue[i]==n) // Checks if the value at the array index of i is equal to n
        {
          return false; // Return false if the patient ID was found to be in the queue
        }

      else // If it is not equal then
        {
          if (last==maxarrayindex) // Checks if last is at the end of the array
            {
              i++; // If it is then simply increment i
            }

          else // If last is not then
            {
              if (i==maxarrayindex) // Checks if i is at the maximum index of the array
                {
                  i=0; // If it is and then last is behind first in the array so i must go back to o
                }

              else // If i is not the max index in the array
                {
                  i++; // Increment i for next iteration
                }
            }
        }
        if(i==last+1) // if i is equal to last plus one then there are no more pateints to check
          {
            break; // So break loop
          }
      }
  return true; // Return true if the Patient ID was not found in the queue
}

bool IsNotInRoom(int n) // This function checks to see if a patient is already in a room
{
  int i =0; // Declare variable for use in loop

  while (i<maxnumberofdoctorsrooms) // While i is less than maxnumberofdoctorsrooms
    {
      if (patientinroom[i]==n) // Checks if the value in patient room i is equal to the ID of the patient
        {
          return false; // If the patients ID is the same as the value of patientinroom[i] then return false as the patient is in a room
        }

      else // If they are not equal then
        {
          i++; // Increment i for next iteration
        }
    }
  return true; // Return true if the ID was not found in any of the rooms
}

int Position (int n) // Function to find the position of a patient in the queue
{
  if (ValidPatientID(n)) // Verify patient ID before finding position
  {
    if (IsNotInQueue(n)) // Checks to see if the ID is in the queue
    {
      printf("You are not in the queue. \n"); // If they are not in the queue then prints message to tell user
    }

    else // If they are in the queue then
    {
      int i = first; // Declare variable i to be used in loop and assign value of first to i
      int count = 1; // Declare variable count to count the position of the patient in the queue. Initialize to 1 as this is the first position in the queue as 0 is not possible

      if (n==patientqueue[first]) // Checks to see if the patient is first in the queue
        {
          printf("You are first in the queue. \n"); // If patient is first in the queue, then prints statement telling user they are first in the queue
          return count; // Returns count
        }

      else // If patient is not first in the queue then this is run
      {

        if (n==patientqueue[last]) // Checks to see if the patient is last in the queue
          {
            count = last;
            printf("You are last in the queue of %d people. \n", numberofpatientswaiting); /* If patient is last in the queue, then prints statement telling user they are last in
            the queue and tells them how many people are in the queue */
            return count;
          }

          else // If ID is not first or last then
            {

              while (1) // Creates infinite loop
                {

                  if (n==patientqueue[i]) // Checks if the ID is equal to the ID in array positon i
                    {
                      printf("You are position %d in the queue. \n", count); // If it is tell user position in queue
                      return count; // Return count which is the position of the patient in the queue once they are found
                    }

                  else // if it is not in that position then
                  {
                    if (i==maxarrayindex) // Check if i is at the max possible index of the array
                      {
                        i = 0; // If it is then i must circle back to 0
                        count++; // This counts as a position in the queue so increment count
                      }

                    else // If i is not equal to the max array index then
                      {
                        i++; // Increment i for new iteration
                        count++; // Increment count as the patient was not found
                      }
                  }
                  if(i==last+1) // If i is equal to last plus one then breaks loop
                    {
                      break; // Breaks loop
                    }
                }
            }
      }
    }
  }
}

void Enqueue (int n) // Function to enqueue a patient ID
{
  switch (last) // Switch on last
   {
    case -1 : // If last is equal to -1 then the queue must be empty
      first = 0; // Start queue at beginning of array i.e. array index 0
      last = 0; // Since there is only one patient in the queue, last should also = 0
      patientqueue[0] = n; // Assign the patient ID which is being enqueued to array the value at array index 0 of the patientqueue array
      numberofpatientswaiting++; // Since a patient has been added to the queue, the number of patients waiting must be incremented
      break; // Break switch

    case maxarrayindex : // If last is equal to the maximum index of the patient queue array this could mean two things
      if (first==0) // Checks to see if first is equal to 0
        {
          printf("The queue is full please come back at a later date. \n"); // The queue is full if first is equal to 0 as there will be no storage space to add a new patient to the queue without dequeueing one patient
          break; // Break switch
        }

      else // Second outcome is that first does not equal to 0 whihc means the queue is not yet full, so last must loop back around to the beginning of the array
        {
          last = 0; // Assign 0 to last
          patientqueue[0] = n; // Assign the patient ID which is being enqueued to array the value at array index 0 of the patientqueue array
          numberofpatientswaiting++; // Since a patient has been added to the queue, the number of patients waiting must be incremented
          break; // Break switch
        }
    default : // If last does not meet any of the special cases the default is run
      if (last==(first-1)) // Checks to see if last is one less than first
        {
          printf("The queue is full please come back at a later date. \n"); // The queue is full since there is no more space for additional patients since last is one less than first
          break; // Break switch
        }

      else // If last is not one less than first then
        {
          last++; // Increment last by one since there is one more patient in the queue
          patientqueue[last] = n; // Assign the patient ID which is being enqueued to the array value with an array index of last in the patientqueue array
          numberofpatientswaiting++; // Since a patient has been added to the queue, the number of patients waiting must be incremented
          break; // Break switch
        }
  }
}

int Dequeue() // This function removes the first patient from the queue
{
  int tempid = 0; // Create a variable which will temporarily store the ID of the first patient in the queue
  tempid = patientqueue[first]; // Assign the ID of the patient first in the queue to tempid

  switch (first) // Switch on global variable first
  {
    case -1 : // First can only be -1 if the queue is empty
      printf("There is nothing to dequeue. \n"); // Since the queue is empty, prints there is nothing to dequeue
      return; // Return nothing since the queue is empty
      break; // Break switch

    case maxarrayindex : // If first equals the last possible index of the array , it must loop back around and become zero
      first = 0; // Assigning 0 to first so that the new first patient is in index 0 of the queue array
      numberofpatientswaiting--; // Once a patient is dequeued, the number of patients waiting is decreased by one
      return tempid; // Function returns the id of the patient which was dequeued
      break; // Break switch

    default : // If first does not meet any of the special cases above, default is run
      if (first==last) // If first equals last i.e. there is only one item in the queue
      {
        Clear(); // Since dequeueing a patient makes the queue empty, the queue should be cleared
        return tempid; // Function returns the id of the patient which was dequeued
      }
      else
      {
        first++; // Increment first by one since there is one less patient in the queue
        numberofpatientswaiting--; // Once a patient is dequeued, the number of patients waiting is decreased by one
        return tempid; // Function returns the id of the patient which was dequeued
      }
  }
}

int IDInRoom (int n) // This function returns the room number a patient is in assuming they are in one of the rooms
{
  int i = 0; // Declare variable i for use in loop

  while (i<maxnumberofdoctorsrooms) // While i is less than the maxnumberofdoctorsrooms
    {
      if (patientinroom[i]==n) // Checks if the ID matches that in room i
        {
          return i+1; // If they are eual then return i+1 as i is the index of the array so i+1 is the room number
        }
      else // If they are not equal then
        {
          i++; // Increment i for new iteration
        }
    }
}

bool IsRoomAvailable () // This fucntion checks to see if any of the doctors rooms are available
{
  int i = 0; // Declare i for use in loop

  while (i<maxnumberofdoctorsrooms) // While i is less than  maxnumberofdoctorsrooms
    {
      if (rooms[i]==1) // Checks to see if a room is equal to 1 which signifies there is a ready doctor
        {
          return true; // If there is a ready doctor in the room then return true as there are available rooms
        }

      else // If the room is not available
        {
          i++; // Increment i for new iteration
        }
    }
  return false; // Return false if no rooms arer available
}

int FirstAvailableRoom() // This function returns the first room available assuming there is at least one room available
{
  int i = 0; // Declare i for use in loop

  while (i<maxnumberofdoctorsrooms) // while i is less than  maxnumberofdoctorsrooms
    {
      if (rooms[i]==1) // Checks if room corresponding to array index i is available i.e. has a value of 1
        {
          return i+1; // If yes then return i+1 as this will be the room number available
        }

      else // If that room is not available
        {
          i++; // Increment i for new iteration
        }
    }
}

void PatientCheckIn(int n) // This function checks in a patient
{
  int i = 0; // Declare variable i to be used in function

  if (ValidPatientID(n)) // Checks to see if the patient ID is valid
  {
    if (IsNotInQueue(n)) // Checks to see if the patient is already in the queue if the ID was valid
      {
        if (IsNotInRoom(n)) // Calls on fucntion IsNotInRoom to see if the id is in a room or not
          {
            if (IsFull())
              {
                printf("The queue is full please come back at a later date. \n"); // The queue is full since there is no more space for additional patients
                return;
              }

            else
              {
                printf("Welcome patient %d. \n", n); // Prints welcome message

                if (IsRoomAvailable()) // If they are not in a room then checks if there is an available room
                  {
                    printf("Please proceed to room %d to be seen immediately.\n", FirstAvailableRoom()); /* If there is an available room the print message telling the patient to go to the first available room.
                    This is done by calling on FirstAvailableRoom */

                    i = FirstAvailableRoom()-1; // Assign value of index of the rooms array, the first available room to i
                    rooms[i] = -1; // Make the doctors room have a patient in it
                    patientinroom[i] = n; // Assign the ID of the patient to the docotrs room
                  }

                else
                  {
                    printf("All doctors are currently busy. Please proceed to the waiting area. \n"); // Print statement to tell user to wait
                    Enqueue(n); // Calls on enqueue function to check in patient if the ID is not already in the queue

                    if (IsNotInQueue(n)) // Checks to see if the patient is in the queue
                      {
                        return; // If they are not in the queue then end the function
                      }

                    else // If in the queue then
                      {
                        Position(n); // Tell the user when they check in where they are in the queue
                      }
                  }
              }

          }

        else // If the id was in a room then
          {
            printf("Patient %d is already in room %d.\n", n, IDInRoom(n)); // Print that the id is already in a room and which room they are in
          }
      }

    else // If they are in the queue then
      {
        printf("You are already in the queue.\n"); // If they are in the queue prints message to say they are in the queue
        Position(n); // Calls on function Position and prints postion of patient in the queue
      }
    }
}

int FindIDPositionInArray(int n) // This function finds the position of an ID in the array
{
  int i = first; // Declare i for use in loop, assign first so loop starts at first
  int position = first ; // Declare position to be returned, assign first so position is the same as index array which is different to function position which is position in queue

  while (1) // Infinite loop
  {
    if(patientqueue[i]==n) // Checks if value at index i in array is the same as the patient ID
      {
        return position; // If they are the same return the postion of the ID in the array
      }
    else // If they are not the same then
    {
      if (i==maxarrayindex) // Checks if i is the max index in the array
        {
          i = 0; // If it is then it must loop backl around to 0
          position = 0; // Position in the array will also be zero
        }

      else // If i is not the max index of the array
        {
          position++; // Increment position since the ID was not in the last position
          i++; // Increment i for new iteration
        }
    }
    if(i==last+1) // Checks if i is equal to last plus one
      {
        break; // Breaks loop if it is
      }
  }
}

void MoveQueue(int n) // This function moves the queue such that all values beyond n are moved down one position in the queue
{
  int i = n; // Declare i for use in loop and assign value of n

  while (i<last) // Loop while i is less than last since the value will be decreased by one and dont want to go to last so that a number not in the queue is not included in new queue
    {
      patientqueue[i] = patientqueue[i+1]; // Assign value of an index in the array to the index before
      patientqueue[i+1] = 0; // Assign zero to the index no longer in the queue
      i++; // Increment i for new iteration
    }

  last--; // Last will have been moved down by one so needs to be decremented
  numberofpatientswaiting--; // Since an ID has been overwritten and all ID's after have moved down by one, the number of patients waiting will be decreased by one
}

void Remove(int n) // This function removes a particular ID from the queue
{
  if (ValidPatientID(n)) // Checks to see if the patient ID is valid
    {
      if (IsNotInQueue(n)) // If the ID is valid checks to see if this ID is in the queue
        {
          printf("This ID is not in the queue. \n"); // Errir message to say the ID trying to be removed is not in the queue
          return; // Return to escape function
        }

      else // If the ID is in the queue then
        {
              if (FindIDPositionInArray(n)==first && first!=last) // Checks to see if the ID is first in the queue
                {
                  patientqueue[first] = 0; // Set value in array no longer in the queue to zero
                  first++; // If the ID is first then simply increment first by one so the previous second in the queue is now first
                  numberofpatientswaiting--; // Since a patient has been removed from the queue, decrement the number of patients waiting by one;
                  printf("You have been removed from the queue. Thank you for your visit. \n"); // Print goodbye message to patient and thank for vsiit
                  return; // Return to escape function
                }

              else // If the ID is not first then
                {
                  if (FindIDPositionInArray(n)==last) // Checks to see if the ID is last in the queue
                    {
                      if (first==last) // Checks to see if the ID is the only patient in the queue
                        {
                          Clear(); // Since the queue will be empty
                          printf("You have been removed from the queue. Thank you for your visit. \n"); // Print goodbye message to patient and thank for vsiit
                          return; // Return to escape function
                        }

                      else
                        {
                          if(last==0 && first!=0) // If the last item is at the begiining of the array and first is somewhere else in the array
                            {
                              patientqueue[last] = 0; // Then set the removed value in the array to 0
                              last = maxarrayindex; // Last must go back to the end of the array
                              numberofpatientswaiting--; // There is one less patient so decrement numberofpatientswaiting
                              printf("You have been removed from the queue. Thank you for your visit. \n"); // Print goodbye message to patient and thank for vsiit
                              return; // Return to escape function
                            }
                          else
                            {
                              patientqueue[last] = 0; // Set the value in the array to 0 as it is no longer in the queue
                              last--; // If the ID was last in the queue simply decrement last by one so that the previous second to last pateint is now last in the queue
                              numberofpatientswaiting--; // Since a patient has been removed from the queue, decrement the number of patients waiting by one;
                              printf("You have been removed from the queue. Thank you for your visit. \n"); // Print goodbye message to patient and thank for vsiit
                              return; // Return to escape function
                            }

                    }
                  }

                  else // If the ID is not first or last then
                    {
                      MoveQueue(FindIDPositionInArray(n)); /* Calls on function MoveQueue first. Then fucntion FindIDPositionInArray. The FindIDPositionInArray fucntion will return the index of the ID in the queue array
                       which is trying to be removed. Then the MoveQueue function takes this value and moves the queue whilst removing the patient which no longer needs to be in the queue*/
                       printf("You have been removed from the queue. Thank you for your visit. \n"); // Print goodbye message to patient and thank for vsiit
                      return; // Return to escape function
                    }
                }
            }
        }
    }

bool ValidDoctorRoom(int n) // This function checks if a doctors room number entered is valid
{
  if (n<(maxnumberofdoctorsrooms+1) && n>0) // Checks if the room number entered is greater than 0 and less than the max number of rooms + 1
    {
      return true; // If valid then return true
    }

  else // If the room number is not valid then
    {
      printf("Room number is invalid. We only have ten doctors rooms.\n"); // print error message saying room not valid
      return false; // Return false
    }
}

void DoctorReady(int n) // This function makes a room with a doctor in it ready for patients to be seen immediately
{
  if (ValidDoctorRoom(n)) // Calls on function ValidDoctorRoom to check room number is valid
    {
      if (VerifyPassword()) // If valid room calls on function to verify password
        {
          if (rooms[n-1]==-1) // If correct password checks to see if the room has a patient
            {
              printf("Discharge patient %d first. \n", patientinroom[n-1]); // Print message to say rooms has a patient in it that must be discharged first
            }

          else // If room does not have a patient already being seen
            {
              if (rooms[n-1]==0 || rooms[n-1]==2) // Checks to see if room is vacant or if there is a doctor who has recently dishcarged a patient
                {
                  if (IsEmpty()) // If vacant or equal to 2, calls on function IsEmpty to check if the queue is empty
                    {
                      rooms[n-1] = 1; // If it is empty then assign value 1 to room n to signify doctor is ready as no patients are waiting to be seen
                      return; // End function
                    }

                  else // If queue is not empty then
                    {
                      rooms[n-1] = -1; // Assign -1 to doctors room to signify there is now a patient being seen
                      patientinroom[n-1] = patientqueue[first]; // Assign ID of first patient to the room the doctor is in
                      printf("Patient %d please go to room %d to be seen. \n", patientqueue[first], (n)); // Print statement to tell first patient in queue which room to go to
                      Dequeue(); // Dequeue first patient as they are now being seen
                    }
                }
            }
        }
    }
  return; // End funtion
}

void DoctorAway(int n) // This function makes a doctors room vacant
{
  if (ValidDoctorRoom(n)) // Calls on fucntion ValidDoctorRoom to check room number is valid
    {
      if (VerifyPassword()) // If valid doctor room calls on function to verify the password
        {
          if (rooms[n-1]==-1) // If password valid checks to see if there is a pateint in the room
            {
              printf("Discharge pateint %d before leaving. \n", patientinroom[n-1]); // If a patient is in the room, prints message to tell doctor to discharge the pateint in the room they are trying to vacate
            }

          else // If patient not in room then
            {
              if (rooms[n-1]==0) // Checks to see if the room is already vacant
                {
                  printf("There are no doctors in this room. \n"); // If the room is already vacant, print message to tell user
                }

              else // If the room is not vacant
                {
                  rooms[n-1] = 0; // Assign value 0 to room n to signify doctor is away and room is now vacant
                  printf("Goodbye doctor. \n"); // Print goodbye message
                  return; // End fucntion
                }
            }
        }
    }
  return; // End function
}

void AvailableDoctors() // This function Figures out how many doctors there are at the surgery and which rooms they are in
{
  int i = 0; // Declare i for use in first loop
  int j = 0; // Declare j for use in second loop
  int countdoc = 0; // Declare countdoc to count doctors in the surgery
  int countprint = 0; // Declare variable to be used to count how many doctors rooms have been printed. This is to help with user friendly formatting

  while (i<maxnumberofdoctorsrooms) // While i is less than the maximum number of doctors rooms at the surgery
    {
      if (rooms[i]==0) // Checks if room i has a value of 0
        {
          i++; // If the room i has a value of 0, this means the room is vacant so there is no doctor in the room. Therefore just increment i for new iteration
        }

      else  // If room i does not have a value of 0 then
        {
          countdoc++; // this means there is a doctor in the room. Therefore  increment countdoc
          i++; // Increment i for new iteration
        }
    }

    printf("There are currently %d doctor(s) working at the surgery. \n", countdoc); // Print statement to say how many doctors there are

    if (countdoc==0) // Checks to see if there are no doctors
      {
        return; // Exit function
      }

    else // If count doc does not equal 0 then function must print all available rooms
      {
        printf("They are in room(s) : "); // Print beginning of sentence for room numbers

        while (j<maxnumberofdoctorsrooms) // While j less than max number of doctors rooms at surgery
          {
            if (rooms[j]==0) // Checks if the rooms is vacant
              {
                j++; // If room vacant then increment j
              }

            else // If room not vacant
              {
                if (countdoc==1) // Checks to see if the number of doctors currently available is 1
                  {
                    printf("%d", (j+1)); // If only one doctor is availble then prints single room for best formatting
                    j++; // Increment j for new iteration
                  }

                else // If there is more than one room then
                  {
                    if (countprint==(countdoc-1)) // Checks to see if countprint is one less than countdoc
                      {
                        printf("and %d", (j+1)); // Prints final room as this is the last room there is since all doctors rooms have been printed except one
                        j++; // Increment j for next iteration
                      }

                    else // If count print is not one less than count doc then
                      {
                        printf("%d, ", (j+1)); //print the room number
                        j++; // Increment j for new iteration
                        countprint++; // Increment countprint since a room number has been printed
                      }
                  }
              }
          }
      }
  printf(".\n"); // Print new line so command prompt is on a new line
}

void CheckOutPatient(int n) // This function  checks out a patient
{
  if (ValidPatientID(n)) // Calls on function ValidPatientID to validate the ID of the patient being checked out
    {
      if(IsNotInRoom(n)) // If the ID is valid checks to see if the patient is in a room
        {
          printf("This patient is not in any of the rooms. \n"); // If the patient is not in a room prints message to say this
        }

      else // If the patient is in a room
        {
          rooms[IDInRoom(n)-1] = 2; // Assign 2 to room in the doctors array which the patient was previously in, this gives chance for doctor to use a command before new patient arrives
          patientinroom[IDInRoom(n)-1] = 0; // Assign 0 to patient array for doctors rooms to signify a patient is no longer in that room. Calls on function IDInRoom top find the room number the patient is in
          printf("Patient %d has been successfully discharged. \n", n); // Prints message to say the patient has been successfully discharged
        }
    }
}

int main() // Main
{
  char cmnd; // Declare variable to store the command the user enters
  int i = 0; // Declare i for use in loop

  while (i<maxnumberofdoctorsrooms) // This loop assigns 0 to all doctors rooms and to patientinroom to show the doctors are vacant from a doctor and have no patients in them
  {
    rooms[i] = 0;
    patientinroom[i] = 0;
    i++; // Increment i for new iteration
  }

  printf("Welcome to the surgery. If this is your first time or you are unsure how to use our system, enter the letter h for help on how to use the various commands available to you. Otherwise enter your first command\n");
  // Print a welcome message

  while (1) // Infinte loop so system repeatedly asks for commands until the exit function is used
  {
  printf(">>>>"); // Print ">>>>" to sognify to the user the system is ready for a command to be entered
  scanf(" %c", &cmnd); // User inputs a letter which is stored to variable cmnd

  switch (cmnd) // This switch is used to differentiate between different commands the user enters
  {
  case 'i' : // If the user enters i
    scanf(" %d", &patientID); // store the users input to patient ID
    PatientCheckIn(patientID); // Call on function to check in patient
    break; // Breaks switch

  case 'p' : // If the user enters p
    scanf(" %d", &patientID); // store the users input to patient ID
    Position(patientID); // Calls on funtion to find the position of the ID entered
    break; // Breaks switch

  case 'q' : // If the user enters q
    scanf(" %d", &patientID); // store the users input to patient ID
    Remove(patientID); // Calls on function to remove this patient
    break; // Breaks switch

  case 'd' : //If user enters d
    AvailableDoctors(); // Calls on function AvailableDoctors
    break; // Break switch

  case 'h' : // If the user enters h
    Help(); // Calls on help function
    break; // Breaks switch

  case 'o' : // If user enters o
    scanf(" %d", &patientID); // store the users input to patient ID
    CheckOutPatient(patientID); // Calls on function to check out patient
    break; // Breaks switch

  case 'r' : // If user enters r
    scanf(" %d", &doctorsroom); // store the users input to doctorsroom
    DoctorReady(doctorsroom); // Calls on fucntion DoctorReady
    break; // Break switch

  case 'a' : // If user enters a
    scanf(" %d", &doctorsroom); // store the users input to doctorsroom
    DoctorAway(doctorsroom); // Calls on fucntion Doctoraway
    break; // Breaks switch

  case 'w' : // If the user enters w
    Print(); // Calls on function Print to print the entire queue
    break; // Breaks switch

  case 'x' : // If the user enters x
    ExitSystem(); // Call on funtion to exit system when the command x is input
    break; // Breaks switch

  default : // Case where the users input does not match with any of the predetermined commands
    printf("That is not a command.\n"); // Prints error message that the command does not exist
    break; // Breaks switch
  }

  }
  return 0;
}
