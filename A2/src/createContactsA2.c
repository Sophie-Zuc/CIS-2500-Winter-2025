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
Task 1 function, takes a filename as its only parameter and writes new contacts into it. Returns void
*/
void createContacts (char * fileName){

  struct contact newContact;
  int empId = 0;
  long currentPos;

  //Declaring pointers to store first name, last name, and email using dynamic memory allocation on the heap
  char * fName;
  char * lName;
  char * email;

  //Static char array buffer for yes/no menu input
  char buffer [50];

  FILE * fptr;

  //Opening file in ab+ mode for both reading and appending in binary. If the file does not exist, it will be created.
  fptr = fopen (fileName, "ab+");

  //Checking for an error in opening the file. This can happen if the command line arguments are missing when running the program
  if (fptr == NULL){

    /*the program is completely exited to avoid segmentation fault.
    The user would have to start from the beginning anyway to run the program correctly*/
    printf("Error in opening file\n");
    exit(1);

  }

  //Do while loop to enter as many new contacts as the user wants to
  do{

    //Getting user input for menu choice with fgets
    printf ("Do you wish to enter a new contact (Yes or No)?: ");
    fgets (buffer,50,stdin);
    buffer [strlen(buffer)-1] = '\0';

    //Proceeding with entering a new contact if any capitalization of yes is entered
    if ((buffer[0] == 'y' || buffer[0] == 'Y') && (buffer[1] == 'e' || buffer[1] == 'E') && (buffer[2] == 's' || buffer[2] == 'S') && (buffer[3] == '\0')){

      //Allocating space dynamically to the pointers to store string input
      fName = malloc (50*sizeof(char));
      lName = malloc (50*sizeof(char));
      email = malloc (50*sizeof(char));

      //Setting position to the end of the file and storing in a variable
      fseek (fptr, 0, SEEK_END);
      currentPos = ftell (fptr);

      //Getting contact information from user

      do{

        printf("Employee Id: ");
        scanf("%d",&empId);

      } while (empId < 1 || empId > 9999); //Do while loop to ensure valid id number is entered (in correct range)

      getchar();

      printf("First Name: ");
      fgets (fName,50,stdin);
      fName [strlen(fName)-1] = '\0';

      printf("Last Name: ");
      fgets (lName,50,stdin);
      lName [strlen(lName)-1] = '\0';

      printf("Email: ");
      fgets (email,50,stdin);
      email [strlen(email)-1] = '\0';

      //Using Task 3 function to determine if a contact with the same id already exists
      if (searchContacts(fileName,empId) == 1){

        //This condition is to follow the FAQ requirement "Duplicate Contact ID should not be created and saved into the file"
        printf("A contact with this id already exists. The new contact will not be saved into the file\n");

        free (fName);
        free (lName);
        free (email);

      }
      else{

        //Populating the struct contact variable with where the starting position values of each piece of contact information will be in the file

        currentPos = currentPos + sizeof(struct contact); //adding size of the struct
        newContact.empIdPosn = currentPos; //id will start right after the struct

        currentPos = currentPos + sizeof(int); //adding size of the id number
        newContact.firstNamePosn = currentPos; //first name will start after the id number

        currentPos = currentPos + sizeof(char)*(strlen(fName)+1); //strlen +1 is to account for the null character
        newContact.lastNamePosn = currentPos;

        currentPos = currentPos + sizeof(char)*(strlen(lName)+1);
        newContact.emailPosn = currentPos;

        currentPos = currentPos + sizeof(char)*(strlen(email)+1);
        newContact.next = currentPos; //the next contact will start after the email

        //Writing the populated struct and all contact information into the file
        fwrite (&newContact, sizeof(struct contact), 1, fptr);
        fwrite (&empId, sizeof(int), 1, fptr);
        fwrite (fName, sizeof(char)*(strlen(fName)+1), 1, fptr);
        fwrite (lName, sizeof(char)*(strlen(lName)+1), 1, fptr);
        fwrite (email, sizeof(char)*(strlen(email)+1), 1, fptr);

        free (fName);
        free (lName);
        free (email);

      }

    }

    printf("\n");

  } while (strcmp("No",buffer) != 0); //Loop will exit when "No" is entered with exact capitalization

  fclose (fptr);

}


