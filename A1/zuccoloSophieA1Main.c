#include "givenA1.h"
#include "helper.h"

/*
Main program. Parameters take command line input.
Can select tasks from a menu to test
Returns 0 upon sucessful execution and -1 if an error is encountered in reading from a file or from tasks being called in an incorrect order
*/
int main(int argc, char ** argv){

  //Initializing variables
  int result, resultTestData;
  int i, j;
  int userChoice = 0;
  int task1Called = 0;
  //Arrays of structs to store animal data
  struct Animal zooData[NUM_SAMPLES];
  struct Animal testData[NUM_TEST_DATA];
  //String of the name of the test data file
  char fName[30] = "testData.csv";

  //Variables to call by reference for task 2
  float euclideanDistance;
  int hammingDistance;
  float jaccardSimilarity;

  int kNearestNeighbors [NUM_SAMPLES];
  int kToShow;

  //Sample vectors to test various tasks
  int vector1[NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
  int vector2[NUM_FEATURES] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1};

  //Do while loop for main menu, exits if a number greater than 5 or less than 1 is entered
  do{

    printf("Here is the menu - enter a number between 1 and 5\n\nEnter your choice: ");
    scanf("%d",&userChoice);

    //Calling task 1
    if (userChoice == 1){

      //Reading from data file in command line, ends program if unsucessful
      result = readFromFile(argv[1],zooData);
      if (result == -1){
        return -1;
      }

      //Printing the array of structs, populated with animal data
      for (j = 0; j < NUM_SAMPLES; j++){
        printf("%s ",zooData[j].animalName);
        for (i = 0; i < NUM_FEATURES; i++){
          printf("%d ",zooData[j].features[i]);
        }
        printf("%d\n",zooData[j].classLabel);
      }

      //Reading from test data file, ends program if unsucessful
      printf("\nBonus: reading data from testData.csv\n");
      resultTestData = readTestData(fName,testData);
      if (resultTestData == -1){
        return -1;
      }

      //Printing the array of structs, populated with test animal data
      for (j = 0; j < NUM_TEST_DATA; j++){
        printf("%s ",testData[j].animalName);
        for (i = 0; i < NUM_FEATURES; i++){
          printf("%d ",testData[j].features[i]);
        }
        printf("%d\n",testData[j].classLabel);
      }
      printf("\n");

      //Setting the variable that task 1 has been called, so that other tasks can now be called
      task1Called = 1;

    }
    else if (userChoice == 2){ //Calling task 2

      //Exiting program in error if called before task 1
      if (task1Called == 0){
        printf("Error: Task 1 must be called before Tasks 2-5\n");
        return -1;
      }

      //Testing task 2 with vectors 1 and 2
      distanceFunctions(vector1,vector2,&euclideanDistance,&hammingDistance,&jaccardSimilarity);
      printf("Euclidean Distance: %f\nHamming Distance: %d\nJaccard Similarity: %f\n\n",euclideanDistance,hammingDistance,jaccardSimilarity);

    }
    else if (userChoice == 3){ //Calling task 3

      //Exiting program in error if called before task 1
      if (task1Called == 0){
        printf("Error: Task 1 must be called before Tasks 2-5\n");
        return -1;
      }

      //Getting number of k Nearest Neighbors to show
      printf("Enter number of k Nearest Neighbors to show: ");
      scanf("%d",&kToShow);
      printf("\n");

      //Displaying nearest neighbors for vector 1 with Euclidean Distance
      printf("Nearest neighbors for new sample with Euclidean Distance: ");
      findKNearestNeighbors(zooData,vector1,kToShow,1,kNearestNeighbors);
      for (i = 0; i < kToShow; i++){
        printf("%d ",kNearestNeighbors[i]);
      }
      printf("\n");

      //Displaying nearest neighbors for vector 1 with Hamming Distance
      printf("Nearest neighbors for new sample with Hamming Distance: ");
      findKNearestNeighbors(zooData,vector1,kToShow,2,kNearestNeighbors);
      for (i = 0; i < kToShow; i++){
        printf("%d ",kNearestNeighbors[i]);
      }
      printf("\n");

      //Displaying nearest neighbors for vector 1 with Jaccard Similarity
      printf("Nearest neighbors for new sample with Jaccard Similarity: ");
      findKNearestNeighbors(zooData,vector1,kToShow,3,kNearestNeighbors);
      for (i = 0; i < kToShow; i++){
        printf("%d ",kNearestNeighbors[i]);
      }
      printf("\n\n");

    }
    else if (userChoice == 4){ //Calling task 4

      //Exiting program in error if called before task 1
      if (task1Called == 0){
        printf("Error: Task 1 must be called before Tasks 2-5\n");
        return -1;
      }

      //Predicting the class of vector 1 with k = 5, using all 3 distance functions
      printf("\nThe predicted class is: %d\n\n",predictClass(zooData,vector1,1,5));
      printf("\nThe predicted class is: %d\n\n",predictClass(zooData,vector1,2,5));
      printf("\nThe predicted class is: %d\n\n",predictClass(zooData,vector1,3,5));

    }
    else if (userChoice == 5){ //Calling task 5

      //Exiting program in error if called before task 1
      if (task1Called == 0){
        printf("Error: Task 1 must be called before Tasks 2-5\n");
        return -1;
      }

      //Measuring the accurary of the predictions with the test data with k = 5, using all 3 distance functions
      printf("\n");
      printf("The accuracy for the test data is %f\n",findAccuracy(zooData,1,testData,5));
      printf("The accuracy for the test data is %f\n",findAccuracy(zooData,2,testData,5));
      printf("The accuracy for the test data is %f\n\n",findAccuracy(zooData,3,testData,5));

    }

  }while (userChoice >= 1 && userChoice <= 5);

  printf("Goodbye\n");

  return 0;
}
