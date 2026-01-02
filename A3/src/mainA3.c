#include "../include/givenA3.h"

/*
Main Program
Contains the menu that can call each task. Returns 0
*/
int main(){

  //Initializing variables

  char buffer [50]; //Buffer string for getting input from the keyboard in the main menu
  char whichNote [NOTE_LENGTH];
  char givenSongName [MAX_LENGTH];
  char fileName [MAX_LENGTH] = "MusicalTunes.csv"; //Hardcoding the file name
  int menuInt, i, invalidType, beginOrEnd, songFound, numNotes, givenSongId;
  int numRead = 0;
  bool added;
  A3Song * headLL = NULL; //Pointer for the head of the linked list


  //Do while loop for main menu. Exits when 9 is entered
  do{

    menuInt = 0;
    invalidType = 0;

    //Printing main menu options
    printf ("=======================================================\n");
    printf ("1. Create a new playlist\n");
    printf ("2. Add a new song to an existing playlist\n");
    printf ("3. Play all songs in the given playlist\n");
    printf ("4. Play a song from the playlist, given its id\n");
    printf ("5. Play a song from the playlist, given its name\n");
    printf ("6. Count the number of occurrences of a note in a given song\n");
    printf ("7. Delete a song from the playlist, given its id\n");
    printf ("8. Delete the entire playlist\n");
    printf ("9. Exit\n");
    printf ("=======================================================\n");

    //Getting input of choice in menu from the user with fgets
    printf ("Enter your choice: ");
    fgets (buffer,50,stdin);
    buffer [strlen(buffer)-1] = '\0';


    /*This portion of code to manually convert a string to an integer is inspired by Geeks for Geeks:
    https://www.geeksforgeeks.org/convert-string-to-int-in-c/. I wanted more control to distinguish between
    an invalid type vs. an invalid value than any of the built in functions I could find had */

    //Loop to go through each character of the user's input
    for (i = 0; buffer[i] != '\0'; i++){

      //Checking to see if the ASCII value of the character is in the range of the char values for 0-9
      if (buffer[i] >= 48 && buffer[i] <= 57){

        //Appending the new digit to the number. Subtracting 48 from the ASCII value gives the actual value of the digit
        menuInt = menuInt * 10 + (buffer[i] - 48);

      }
      else { //If any value other than a digit is encountered, the input is of invalid type and the loop is exited

        invalidType = 1;
        break;

      }

    }

    if (invalidType == 1){ //Invalid type output

      printf("Invalid Type!!\n");

    }
    else if (menuInt == 1){ //Menu option 1

      numRead = createPlayList(&headLL,fileName); //Calling Task 1 Function
      printf("Number of songs in the playlist: %d\n\n", numRead); //Printing returned number of songs read

    }

    else if (menuInt == 2){ //Menu option 2

      printf("Enter the value for beginOrEnd: ");
      scanf("%d",&beginOrEnd);
      added = addNewSong (&headLL, beginOrEnd); //Calling Task 2 Function

      //Checking if returned value indicates error
      if (added == false){

        printf("Invalid beginOrEnd value passed!\n\n");

      }

    }
    else if (menuInt == 3){ //Menu option 3

      playPlayList (headLL); //Calling Task 3 Function

    }
    else if (menuInt == 4){ //Menu option 4

      printf("Enter the id of the song you want to play: ");
      scanf("%d",&givenSongId);
      printf("\n");

      songFound = playSongGivenId(headLL, givenSongId); //Calling Task 4 Function

      //Checking if returned value indicates no song found
      if (songFound == -1){

        printf("No song found!\n\n");

      }

    }
    else if (menuInt == 5){ //Menu option 5

      printf("Enter the name of the song you want to play: ");
      fgets(givenSongName,MAX_LENGTH,stdin); //fgets is used to accomodate song titles with spaces
      givenSongName [strlen(givenSongName)-1] = '\0';

      printf("\n");

      songFound = playSongGivenName(headLL, givenSongName); //Calling Task 5 Function

      //Checking if returned value indicates no song found
      if (songFound == -1){

        printf("No song found!\n\n");

      }

    }
    else if (menuInt == 6){ //Menu option 6

      printf("Enter the id of the song you want to count the notes in: ");
      scanf("%d",&givenSongId);
      printf("Enter the note you want to count: ");
      scanf("%s",whichNote); //scanf is used since FAQ specifies only inputs of valid type will be tested, and notes are max 3 letters with no spaces

      numNotes = countNotesInASong (headLL, givenSongId, whichNote); //Calling Task 6 Function

      //Checking if returned value indicates error (invalid note or no song found)
      if (numNotes == -1){

        printf("\nSong not found!\n\n");

      }
      else{

        printf("\nNumber of times the note appears: %d\n\n", numNotes); //Printing returned number of occurrances of the note

      }

    }
    else if (menuInt == 7){ //Menu option 7

      printf("Enter the id of the song you want to delete: ");
      scanf("%d",&givenSongId);
      printf("\n");

      songFound = deleteASongGivenId(&headLL, givenSongId); //Calling Task 7 Function

      //Checking if returned value indicates no song found
      if (songFound == -1){

        printf("No song found!\n\n");

      }
      else if (songFound == 1){

        printf("Song Deleted!\n\n");

      }

    }
    else if (menuInt == 8){ //Menu option 8

      deletePlayList(&headLL); //Calling Task 8 Function
      printf("\nDeleting Playlist\n\n");

    }
    else if (menuInt != 9){ //Any other invalid choice. != 9 prevents it from saying invalid choice when 9 is selected

      printf ("Invalid Choice!!\n");

    }


  } while (menuInt != 9); //Loop exits when 9 is entered

  deletePlayList(&headLL); //Task 8 is called just in case to avoid memory leaks
  printf("\nExiting...\n");

  return 0;

}



