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
Task 2 function, takes a filename as its only parameter and prints all employee records stored in it in the
same sequence as it was created. The function returns -1 if the file cannot be opened or is corrupt for some reason.
*/
int readContacts (char * fileName){

  FILE * fptr;

  int flag = 1;
  int numRead = 0;
  struct contact newContact;

  int empId = 0;

  //Declaring pointers to store first name, last name, and email on the heap when reading from file
  char * fName;
  char * lName;
  char * email;

  //Opening the file for reading in binary mode
  fptr = fopen (fileName, "rb");

  //Returning -1 if there is an error in opening the file
  if (fptr == NULL){

    return -1;

  }

  //Allocating space dynamically to the pointers to store strings when reading from file
  fName = malloc (50*sizeof(char));
  lName = malloc (50*sizeof(char));
  email = malloc (50*sizeof(char));

  //Setting position to the beginning of the file
  fseek (fptr, 0, SEEK_SET);

  printf("\n\nPrinting Employee records saved on file:\n\n");

  //Loop will terminate when the first fread returns 0 (when the end of the file is reached)
  while (flag != 0){

    //fread returns the number of items successfully read. It returns 0 if no items are read because of an error or end of file.
    flag = fread (&newContact, sizeof(struct contact), 1, fptr);

    //If it's not the end of file, reading and printing the rest of the information from the file for the contact
    if (flag != 0){

      printf("***********************************************************\n");

      printf("Employee Id: ");
      fread (&empId, (newContact.firstNamePosn - newContact.empIdPosn), 1, fptr);

      printf("%d\n",empId);

      printf("First Name: ");
      fread (fName, (newContact.lastNamePosn - newContact.firstNamePosn), 1, fptr); //amount of bits to read calculated using data from the struct

      printf("%s\n",fName);

      printf("Last Name: ");
      fread (lName, (newContact.emailPosn - newContact.lastNamePosn), 1, fptr);

      printf("%s\n",lName);

      printf("Email: ");
      fread (email, (newContact.next - newContact.emailPosn), 1, fptr);

      printf("%s\n",email);

      printf("***********************************************************\n\n");

      numRead++; //counting number of contacts read

    }

  }

  free (fName);
  free (lName);
  free (email);

  fclose (fptr);

  return numRead; //returning number of contacts read

}
