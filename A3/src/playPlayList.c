#include "../include/givenA3.h"

/*
Task 3 function. Plays (prints) all songs in the playlist, each song separated by a newline.
Each note in a song is separated by a '.', For example, Do.Re.Mi. and so on
Returns void
*/

void playPlayList(A3Song *headLL){

  A3Song * temp;
  int i;

  //Condition for if the linked list is empty
  if (headLL == NULL){

    printf("The playlist is empty\n\n");
    return;

  }

  temp = headLL;

  //While loop to go through every song in the playlist
  while (temp != NULL){

    //Printing the information of a song
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

    temp = temp->nextSong; //Moving to the next song

  }


}
