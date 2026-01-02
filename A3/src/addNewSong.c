#include "../include/givenA3.h"

/*
Task 2 function. Adds a new song to the start of the given linked list if beginOrEnd is 1; adds it to the end of the given LL if beginOrEnd is 2
Returns True for success and False if it fails for any reason
*/

bool addNewSong(A3Song **headLL, int beginOrEnd){

  //Initializing variables
  char newSongName [MAX_LENGTH];
  A3Song * temp;
  A3Song * newSong;
  int randNum;
  int duplicate = 0;
  int i;


  //Getting seed for random number
  srand (time(NULL));

  getchar();

  //Getting input of the name of the new song from the user
  printf("Song Name: ");
  fgets(newSongName,MAX_LENGTH,stdin);
  newSongName [strlen(newSongName)-1] = '\0';

  printf("\n");

  //Returning false to indicate invalid beginning or end value passed
  if (beginOrEnd != 1 && beginOrEnd != 2){

    return false;

  }

  //Dynamically allocating memory for a new song
  newSong = malloc (sizeof(A3Song));

  //Populating with songName and NULL for nextSong
  newSong->nextSong = NULL;
  strcpy(newSong->songName, newSongName);

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

  //Loop to generate 21 random notes
  for (i = 0; i < 21; i++){

    randNum = rand() % 7 + 1; //Generating a random number between 1 and 7, then using a conditional statement to assign one of the notes

    if (randNum == 1){

      strcpy(newSong->songNotes[i], "do");

    }
    else if (randNum == 2){

      strcpy(newSong->songNotes[i], "re");

    }
    else if (randNum == 3){

      strcpy(newSong->songNotes[i], "mi");

    }
    else if (randNum == 4){

      strcpy(newSong->songNotes[i], "fa");

    }
    else if (randNum == 5){

      strcpy(newSong->songNotes[i], "sol");

    }
    else if (randNum == 6){

      strcpy(newSong->songNotes[i], "la");

    }
    else if (randNum == 7){

      strcpy(newSong->songNotes[i], "ti");

    }

  }

  //Printing the song information
  printf("Song ID: %d\n", newSong->songId);
  printf("Song Name: %s\n", newSong->songName);
  printf("Notes: ");

  for (i = 0; i < 21; i++){

    printf("%s", newSong->songNotes[i]);

    if (i != 20){
      printf(".");
    }

  }

  printf("\n\n");


  temp = * headLL;

  //If the list is empty, adding the new song as the first in the list
  if (temp == NULL){

    * headLL = newSong;

    printf("First song in playlist!\n\n");

  }
  else if (beginOrEnd == 1){ //Adding the new song to the beginning of the list

    newSong->nextSong = * headLL;
    * headLL = newSong;

    printf("Song added at the beginning!\n\n");

  }
  else if (beginOrEnd == 2){ //Adding the new song to the end of the list

    //While loop to navigate to the last song in the list
    while (temp->nextSong != NULL){

      temp = temp->nextSong;

    }

    temp->nextSong = newSong;

    printf("Song added at the end!\n\n");

  }

  return true;

}
