#include "../include/givenA3.h"

/*
Task 7 function. Removes the song identified by givenSongId.
Returns -1 if song doesn't exist, 1 otherwise
*/

int deleteASongGivenId(A3Song **headLL, int givenSongId){

  A3Song * temp;
  A3Song * prev;

  //Returning -1 if the playlist is empty
  if (* headLL == NULL){

    getchar();
    return -1;

  }

  temp = * headLL;

  //If the target song is the first in the list, the next node in the list becomes the new head and the original head is freed
  if ((* headLL)->songId == givenSongId){

    * headLL = (* headLL)->nextSong;
    free (temp);
    getchar();
    return 1;

  }

  prev = temp; //A pointer is used to keep track of the previous song as well as the current one being compared
  temp = temp->nextSong;

  //Loop to go through each remaining song in the list
  while (temp != NULL){

    //Removing the song if a match is found
    if (temp->songId == givenSongId){

      prev->nextSong = temp->nextSong;
      free (temp);
      getchar();
      return 1;

    }

    prev = temp;
    temp = temp->nextSong;

  }

  getchar();
  return -1; //Returning -1 if no match is found at the end of this process

}
