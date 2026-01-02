/*
Student Name: Sophie Zuccolo
Student ID: 1293676
Due Date: February 28th, 2025
Course: CIS*2500
I have exclusive control over this submission via my password.
By including this header comment, I certify that:
1) I have read and understood the policy on academic integrity.
2) I have completed Moodle's module on academic integrity.
3) I have achieved at least 80% on the academic integrity quiz
I assert that this work is my own. I have appropriate acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written
by me in its entirety.
*/

#include "../include/givenA2.h"

/*
Main program takes a file name through the command line. Begins by calling createContacts,
then enters the main menu, a do while loop, which can call all three functions
*/

int main(int argc, char * argv []){

  int errorCheck;
  int keyId;
  int matchFound;

  //Buffer string for getting input from the keyboard in the main menu
  char buffer [50];

  /*Calling Task 1 function with file name given in command line.
  It is called before entering the second menu, which means the file is always created*/
  createContacts (argv[1]);

  //Do while loop for main menu
  do{

    //Getting input of choice in menu from the user with fgets
    printf ("Enter a choice:\n1 to print, 2 to search, 3 to create more, -1 to exit: ");
    fgets (buffer,50,stdin);
    buffer [strlen(buffer)-1] = '\0';

    //Conditional statement for option 1, strcmp used since input was with fgets
    if (strcmp("1",buffer) == 0){

      //Calling Task 2 function with file name given in command line
      errorCheck = readContacts (argv[1]);

      //Printing error message if function call returned -1
      if (errorCheck == -1){
        printf("Error: Cannot open file\n");
      }

    }
    else if (strcmp("2",buffer) == 0){ //Conditional statement for option 2

      //Do while loop to validate id to search within correct range
      do{

        printf("Enter the id to search: ");
        scanf("%d",&keyId);

      } while (keyId < 1 || keyId > 9999);

      //Calling Task 3 function with file name given in command line and the validated id to search for
      matchFound = searchContacts (argv[1],keyId);

      /*The function will print the contact with the matching id if found and return 1. Otherwise,
      an appropriate message is printed depending on if the return value indicated error or no match found*/
      if (matchFound == -1){
        printf("Error: Cannot open file\n");
      }
      else if (matchFound == 0){
        printf("No match found!\n");
      }

      getchar();

    }
    else if (strcmp("3",buffer) == 0){ //Conditional statement for option 3

      printf("\n");

      //Calling Task 1 function with file name given in command line.
      createContacts (argv[1]);

    }

    printf("\n");

  } while (strcmp("-1",buffer) != 0); //Loop will exit if the user enters -1

  printf("\nExiting...\n");

  return 0;

}
