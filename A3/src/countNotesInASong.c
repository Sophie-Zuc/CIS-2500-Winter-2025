#include "../include/givenA3.h"

/*
Task 6 function. Counts the number of occurrences of a note in a given song.
Returns the number of times a given note appears in the song identified by givenSongId, -1 if song not found.
*/

int countNotesInASong(A3Song *headLL, int givenSongId, char whichNote[4]){

  A3Song * temp = headLL;

  int songFound = -1;
  int i;
  int numNotes = 0;

  //Conditional statement using strcmp to check if the note is invalid and return -1
  if (strcmp("do",whichNote) != 0 && strcmp("re",whichNote) != 0 && strcmp("mi",whichNote) != 0 && strcmp("fa",whichNote) != 0 && strcmp("sol",whichNote) != 0 && strcmp("la",whichNote) != 0 && strcmp("ti",whichNote) != 0){

    getchar();
    return -1;

  }

  //Loop to go through every song in the playlist
  while (temp != NULL){

    //Checking if the current song's ID is a match with the target. Breaking from the loop will then cause temp to point to the matching song
    if (temp->songId == givenSongId){
      songFound = 1;
      break;
    }

    temp = temp->nextSong;

  }

  if (songFound == 1){

    //Loop to count the number of occurrences of the specified note using strcmp if a matching song is found
    for (i = 0; i < 21; i++){

      if (strcmp(whichNote, temp->songNotes[i]) == 0){

        numNotes++;

      }

    }

    getchar();
    return numNotes;

  }
  else { //Returning -1 to indicate no song with matching ID found

    getchar();
    return -1;

  }

}
