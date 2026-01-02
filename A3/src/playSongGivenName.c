#include "../include/givenA3.h"

/*
Task 5 function. Plays (prints) a song, given its name givenSongName.
Returns -1 if song not found; 1 if found
*/

int playSongGivenName(A3Song *headLL, char givenSongName[MAX_LENGTH]){

  int i;
  int songFound = -1; //songFound is originally set to -1 so that if the playlist is empty, it returns no song found
  A3Song * temp = headLL;

  //Loop to check each song in the list
  while (temp != NULL){

    songFound = 1;

    //If the current song is a different length from the target, they are not a match
    if (strlen(temp->songName) != strlen(givenSongName)){

      songFound = -1;

    }
    else{

      //Loop to compare each character of the two strings
      for (i = 0; i < strlen(givenSongName); i++){

        /*If any character differs, they are not a match
        The tolower function is used to make the comparison case-insensitive
        I learned about it from Geeks For Geeks: https://www.geeksforgeeks.org/case-insensitive-string-comparison-in-cpp/*/
        if (tolower(temp->songName[i]) != tolower(givenSongName[i])){

          songFound = -1;

        }

      }

    }

    //If a match is found, the loop is broken and temp will point to the matching song
    if (songFound == 1){

      break;

    }

    temp = temp->nextSong;

  }

  //Printing the song if a match is found
  if (songFound == 1){

    printf("Song ID: %d\n", temp->songId);
    printf("Song Name: %s\n", temp->songName);
    printf("Notes: ");

    for (i = 0; i < 21; i++){

      printf("%s", temp->songNotes[i]);

      if (i != 20){
        printf(".");
      }

    }

    printf("\n\n");

  }

  return songFound;

}
