#include "../include/givenA3.h"

/*
Task 1 function. Creates a playlist using data given in the file named MusicalTunes.csv".
Returns -1 if the file cannot be read, the number of songs inserted into the playlist otherwise
*/

int createPlayList(A3Song ** headLL, char fileName[MAX_LENGTH]){

  //Initializing variables
  int i;
  char buffer [200]; //Buffer for reading lines from the file
  char * token = NULL; //Token for strtok
  int numRead = 0;
  int randNum;
  int duplicate = 0;
  A3Song * newSong = NULL;
  A3Song * temp;

  FILE * fptr;

  //Getting seed for random number
  srand (time(NULL));

  //Opening file in read mode
  fptr = fopen (fileName,"r");

  //Checking for error in opening file
  if (fptr == NULL){

    printf("Error: CSV File could not be read\n");
    return -1;

  }

  //Getting first header line, not saving it anywhere
  fgets (buffer, 200, fptr);
  buffer [strlen(buffer)-1] = '\0';

  //Loop to read from the file. fgets returns NULL if end of file is reached
  while (fgets (buffer, 200, fptr) != NULL){

    /*I was getting an error where simply removing the new line from the end of the string due to fgets wasn't working
    This function fixed it. I learned about it here: https://gist.github.com/noc-tur-a/72fd9bc10442ca1329e6de6879b0c287*/
    buffer [strcspn(buffer, "\r\n")] = 0;

    i = 0;

    //Dynamically allocating memory for a new song
    newSong = malloc (sizeof(A3Song));

    //Using strtok to break up the line by the commas
    token = strtok (buffer,",");

    strcpy(newSong->songName, token); //the first token is the name of the song
    newSong->nextSong = NULL;

    //Using a do while loop to generate a unique random ID
    do{

      duplicate = 0;

      //Using the given algorithm to generate the ID: length of the song name + a random integer between 1 - 1000 (both inclusive)
      randNum = strlen(newSong->songName) + rand() % 1000 + 1;

      temp = * headLL;

      //While loop to navigate the existing list and check IDs
      while (temp != NULL){

        if (temp->songId == randNum){
          duplicate = 1;
        }
        temp = temp->nextSong;

      }

    } while (duplicate == 1); //Will loop until a unique ID is generated

    newSong->songId = randNum; //Assigning the validated random number to the new song

    //Loop to tokenize the rest of the line and save each note into the array songNotes
    while (i < 21){

      token = strtok (NULL, ",");
      strcpy(newSong->songNotes[i], token);
      i++;

    }


    temp = * headLL;

    //If the list is empty, assigning the new song to be the head
    if (temp == NULL){

      * headLL = newSong;
      temp = * headLL;

    }
    else {

      //While loop to get to the last song in the list
      while (temp->nextSong != NULL){

        temp = temp->nextSong;

      }

      //Adding new song to the end
      temp->nextSong = newSong;

    }

    numRead++; //Counting the number of songs read

  }

  //Closing file
  fclose(fptr);
  return numRead;

}
