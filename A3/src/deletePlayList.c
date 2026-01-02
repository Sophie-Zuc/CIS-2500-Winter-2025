#include "../include/givenA3.h"

/*
Task 8 function. Removes every song from the playlist
Returns void
*/

void deletePlayList(A3Song **headLL){

  A3Song * temp = * headLL;

  //Loop to go through every song in the playlist
  while (* headLL != NULL){

    temp = * headLL; //saving the current head in temp
    * headLL = (* headLL)->nextSong; //changing the head of the list to the next song
    free(temp); //freeing the previous head

  }

}
