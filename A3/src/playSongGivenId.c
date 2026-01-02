#include "../include/givenA3.h"

/*
Task 4 function. Plays (prints) a song, given its id givenSongId.
Returns -1 if song not found; 1 if found
*/

int playSongGivenId(A3Song *headLL, int givenSongId){

  A3Song * temp = headLL;

  int songFound = -1;
  int i;

  //Loop to navigate through the entire playlist and compare each ID with the given to find
  while (temp != NULL){

    if (temp->songId == givenSongId){
      songFound = 1;
      break; //breaking the loop will have temp pointing to the song that matches
    }

    temp = temp->nextSong;

  }

  //Conditional statement to print the song information if found
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

  getchar();

  return songFound; //Returning the resulting 1 or -1 value

}
