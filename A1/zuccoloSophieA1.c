#include "givenA1.h"
#include "helper.h"

/*Task 1
Reads the information from a1Data.txt into an array of struct Animal
Parameters are a string of a file name and the array of struct Animal
Returns 1 upon successful operation or -1 upon abnormal exit
*/
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]){

  int i, j;
  FILE* fptr;

  //Opening file in read mode
  fptr = fopen(fName,"r");

  //Checking for error in opening file
  if (fptr == NULL){

    printf("Error: File could not be read\n");
    return -1;

  }

  //Loop to read all 100 samples into the array
  for (i = 0; i < NUM_SAMPLES; i++){

    //Reading animal name
    fscanf(fptr,"%s",dataZoo[i].animalName);

    //Reading array of features
    for (j = 0; j < NUM_FEATURES; j++){

      fscanf(fptr,"%d",&dataZoo[i].features[j]);

    }

    //Reading class
    fscanf(fptr,"%d",&dataZoo[i].classLabel);

  }

  //Closing file
  fclose(fptr);
  return 1;

}

/*Helper function
Reads the information from testData.csv into an array of struct Animal
Parameters are a string of a file name and the array of struct Animal
Returns 1 upon successful operation or -1 upon abnormal exit
I referenced a helpful video from the YouTube channel Portfolio Courses on how to read a CSV file into an array of structs
Here is the link: https://www.youtube.com/watch?v=rbVt5v8NNe8
*/
int readTestData (char fName [30], struct Animal testData [NUM_TEST_DATA]){

  int i, j;
  FILE* fptr;

  //Opening file in read mode
  fptr = fopen(fName,"r");

  //Checking for error in opening file
  if (fptr == NULL){

    printf("Error: testData File could not be read\n");
    return -1;

  }

  //Loop to read all 20 samples into the array
  for (i = 0; i < NUM_TEST_DATA; i++){

    //Reading animal name, scanning up to 50 characters (MAX_LENGTH_ANIMAL_NAME) and stopping at the first comma
    fscanf(fptr,"%50[^,],",testData[i].animalName);

    //Reading array of features. Comma in fscanf due to csv file
    for (j = 0; j < NUM_TEST_DATA; j++){

      fscanf(fptr,"%d,",&testData[i].features[j]);

    }

    //Reading class. Comma in fscanf due to csv file
    fscanf(fptr,"%d",&testData[i].classLabel);

  }

  //Closing file
  fclose(fptr);
  return 1;

}

/*Task 2
Computes three distance measures between two vectors of animal features
Parameters are two int array vectors and call-by-reference pointers to the three distance measures
Returns void
*/
void distanceFunctions (int vector1 [NUM_FEATURES],
                        int vector2 [NUM_FEATURES],
                        float * euclideanDistance,
                        int * hammingDistance,
                        float * jaccardSimilarity
){

  //Initializing variables for calculating the results
  float eucSum = 0;
  int i;
  int hamCount = 0;
  int jac11 = 0;
  int jac00 = 0;


  for (i = 0; i < NUM_FEATURES; i++){

    //Calculating Euclidean distance, summing the difference between features squared
    eucSum = eucSum + pow((vector1[i]-vector2[i]),2);

    //Calculating Hamming distance, counting differing values between vectors
    if (vector1[i] != vector2[i]){
      hamCount++;
    }

    //Calculating Jaccard Similarity, counting 1-1 and 0-0 matches
    if (vector1[i] == 1 && vector2[i] == 1){
      jac11++;
    }
    else if (vector1[i] == 0 && vector2[i] == 0){
      jac00++;
    }

  }

  //Applying final operations to find distances, returning via call-by-reference
  * euclideanDistance = sqrt(eucSum);
  * hammingDistance = hamCount;
  * jaccardSimilarity = (float)jac11/(NUM_FEATURES-jac00);

}

/*Task 3
Outputs an array called kNearestNeighbors that stores the indices of the
k nearest neighbors of newSample using the given whichDistanceFunction
Parameters are the array of struct Animal containing the given dataset, the features of a new data sample,
the number of neighbors to find, the index of which distance function, and an array that stores the indices
of the k nearest neighbors with the new sample
Returns void
Sorting function referenced from Programiz.com
https://www.programiz.com/dsa/bubble-sort
*/
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){

  float distancesEJ[2][NUM_SAMPLES];
  int distancesHI[2][NUM_SAMPLES];

  int i, j;
  float temp;
  int tempIndex = 0;

  /*Loop to populate two corresponding 2D arrays, one of floats for Euclidean distances and Jaccard similarities,
  and one of integers to store Hamming distances and indices*/
  for (i = 0; i < NUM_SAMPLES; i++){

    //Clearing row of Euclidean distance
    distancesEJ[0][i] = 0;
    //Populating row with indices
    distancesHI[1][i] = i;
    //Finding the distance of the new data sample with the ith data sample in zoo dataset
    distanceFunctions(newSample,dataZoo[i].features,&distancesEJ[0][i],&distancesHI[0][i],&distancesEJ[1][i]);

  }

  /*Sorting function referenced from Programiz.com
  https://www.programiz.com/dsa/bubble-sort
  Sorting distances in decreasing or increasing order, depending on the type of distance function
  Indices are maintained when swaps are made*/
  for (i = 0; i < NUM_SAMPLES-1; i++) {

    for (j = 0; j < NUM_SAMPLES-i-1; j++) {

      //Sorting based on Euclidean distance
      if (whichDistanceFunction == 1){

        //Swapping to get shortest distances first
        if (distancesEJ[0][j] > distancesEJ[0][j+1]){

          //Sorting Euclidean distances
          temp = distancesEJ[0][j];
          distancesEJ[0][j] = distancesEJ[0][j+1];
          distancesEJ[0][j+1] = temp;

          //Sorting indices accordingly
          tempIndex = distancesHI[1][j];
          distancesHI[1][j] = distancesHI[1][j+1];
          distancesHI[1][j+1] = tempIndex;

        }

      }
      else if (whichDistanceFunction == 2){  //Sorting based on Hamming distance

        //Swapping to get shortest distances first
        if (distancesHI[0][j] > distancesHI[0][j+1]){

          //Sorting Hamming distances
          temp = distancesHI[0][j];
          distancesHI[0][j] = distancesHI[0][j+1];
          distancesHI[0][j+1] = (int)temp;

          //Sorting indices accordingly
          tempIndex = distancesHI[1][j];
          distancesHI[1][j] = distancesHI[1][j+1];
          distancesHI[1][j+1] = tempIndex;

        }

      }
      else if (whichDistanceFunction == 3){ //Sorting based on Jaccard Similarity

        //Swapping to get highest similarities first
        if (distancesEJ[1][j] < distancesEJ[1][j+1]){

          temp = distancesEJ[1][j];
          distancesEJ[1][j] = distancesEJ[1][j+1];
          distancesEJ[1][j+1] = temp;

          //Sorting indices accordingly
          tempIndex = distancesHI[1][j];
          distancesHI[1][j] = distancesHI[1][j+1];
          distancesHI[1][j+1] = tempIndex;

        }

      }

    }

  }

  //Saving the indices associated with the first k distances in the sorted list to kNearestNeighbors array
  for (i = 0; i < k; i++){
    kNearestNeighbors[i] = distancesHI[1][i];
  }

}

/*Task 4
Predicts the class label of a given sample
Parameters are the array of struct Animal containing the given dataset, the features of a new data sample,
the index of which distance function to use, and the number of nearest neighbors to find
Returns the predicted class of the new sample
*/
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int whichDistanceFunction, int k){

  int kNearestNeighbors [NUM_SAMPLES];
  //array to store the number times each class label occurs
  int pollValues [NUM_CLASSES] = {0,0,0,0,0,0,0};
  int i;
  int commonClass = 0;
  int commonClassIndex = 0;

  //Finding the k nearest neighbors with the new sample
  findKNearestNeighbors(dataZoo,newSample,k,whichDistanceFunction,kNearestNeighbors);

  //Running a poll of the class labels of the nearest neigbors, keeping count in an array
  for (i = 0; i < k; i++){

    if (dataZoo[kNearestNeighbors[i]].classLabel == 1){
      pollValues[0]++;
    }
    else if (dataZoo[kNearestNeighbors[i]].classLabel == 2){
      pollValues[1]++;
    }
    else if (dataZoo[kNearestNeighbors[i]].classLabel == 3){
      pollValues[2]++;
    }
    else if (dataZoo[kNearestNeighbors[i]].classLabel == 4){
      pollValues[3]++;
    }
    else if (dataZoo[kNearestNeighbors[i]].classLabel == 5){
      pollValues[4]++;
    }
    else if (dataZoo[kNearestNeighbors[i]].classLabel == 6){
      pollValues[5]++;
    }
    else if (dataZoo[kNearestNeighbors[i]].classLabel == 7){
      pollValues[6]++;
    }

  }

  for (i = 0; i < NUM_CLASSES; i++){

    //Finding the class label with the most occurances, saving the corresponding index in the poll array
    //Will go in order of smallest class label to largerst, < accounts for ties and will return the smaller value
    if (commonClass < pollValues[i]){
      commonClass = pollValues[i];
      commonClassIndex = i;
    }

  }

  //Returning the index of the poll array + 1 to properly match the class labels 1-7
  return commonClassIndex + 1;

}

/*Task 5
Computes the accuracy of the k-nearest-neighbor ML algorithm using a test dataset
Parameters are the array of struct Animal containing the given dataset, the array of struct Animal containing the test dataset,
the index of which distance function to use, and the number of nearest neighbors to find
Returns a float of the accuracy percentage
*/
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], int whichDistanceFunction, struct Animal testData [NUM_TEST_DATA], int k){

  int i;
  //Arrays to store predictions of class labels and the corresponding real class labels
  int predictions [NUM_TEST_DATA] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int testClasses [NUM_TEST_DATA] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  float numCorrect = 0;

  for (i = 0; i < NUM_TEST_DATA; i++){

    //Predicting the class label of each animal in the test dataset
    predictions[i] = predictClass(dataZoo,testData[i].features,whichDistanceFunction,k);
    //Storing the class label of each animal in the test dataset
    testClasses[i] = testData[i].classLabel;

    //Printing the predictions to match the Expected Outputs document
    printf("%d ",predictions[i]);

    //Finding how many of the predictions are correct
    if (predictions[i] == testClasses[i]){

      numCorrect = numCorrect + 1;

    }

  }

  //Printing the number of correct predictions and the number of test data samples to match the Expected Outputs document
  printf("\n%.0f\n%d\n",numCorrect,NUM_TEST_DATA);
  //Returning the accuracy percentage as a float
  return (numCorrect/NUM_TEST_DATA);

}

