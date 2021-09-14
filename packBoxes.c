#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PACKAGES 24
#define MAX_BOXES 6
#define BOX_LENGTH 4
#define BOX_WIDTH 5
int packagesLeft = 24;
int numSmall = 0, numMedium = 0, numLarge = 0, numBoxes = 0;
float smallPrice = 0, mediumPrice = 0, largePrice = 0, tax = 0, total = 0, amountCharged = 0;
int num = 0;
char b[MAX_BOXES][BOX_WIDTH][BOX_LENGTH];

int main() {

  srand(time(NULL));	//Random time using time
  
  //Generate packages of different sizes randomly
  for(int i=0; i < 3; i++){
    num = (rand() % (packagesLeft - 0 + 1)) + 0;
    if(i==0){
      numSmall = num;
      packagesLeft -= num;
    }
    if(i==1){
      numMedium = num;
      packagesLeft -= num;
    }
    if(i==2){
      numLarge = packagesLeft;
      packagesLeft = 0;
    }
  }
  
  
  //Initialize 3D array
  for(int i=0; i<MAX_BOXES; i++){
    for(int w=0; w<BOX_WIDTH; w++){
      for(int l=0; l<BOX_LENGTH; l++){
        b[i][w][l] = '\0';
      }
    }
  }
  
  //Price calculations
  smallPrice = numSmall*5.99;
  mediumPrice = numMedium*10.99;
  largePrice = numLarge*19.99;
  total = smallPrice+mediumPrice+largePrice;
  tax = total*0.13;
  
  //Print statements for the receipt
  printf("\nOrder:  Small=%d", numSmall);
  printf(", Medium=%d", numMedium);
  printf(", Large=%d\n", numLarge);
  printf("\n\nSmall (%02d" " units)    $%6.2f\n", numSmall, smallPrice);
  printf("Medium (%02d" " units)   $%6.2f\n", numMedium, mediumPrice);
  printf("Large (%02d" " units)    $%6.2f\n", numLarge, largePrice);
  printf("-----------------------------");
  
  //Pack large packages. Must check upper left and lower right of a 2x2.
  for (int t=0; t<MAX_BOXES; t++){
    for(int i=0; i<BOX_WIDTH-1; i+=2){
      for(int j=0; j<BOX_LENGTH-1; j+=2){
        if(b[t][i][j]=='\0' && b[t][i+1][j+1]=='\0' && numLarge > 0){
          b[t][i][j] = 'L';
          b[t][i][j+1] = 'L';
          b[t][i+1][j] = 'L';
          b[t][i+1][j+1] = 'L';
          numLarge -= 1;
        }
        
        if(numLarge < 1){
          break;
        }
      }
    }
  }
  
  //Pack medium packages. Must check 1x2 or 2x1.
  for (int t=0; t<MAX_BOXES; t++){
    for(int i=0; i<BOX_WIDTH; i++){
      for(int j=0; j<BOX_LENGTH; j++){
        if(b[t][i][j] == '\0' && b[t][i][j+1] == '\0' && numMedium > 0){
          b[t][i][j] = 'M';
          b[t][i][j+1] = 'M';
          numMedium -= 1;
        }
        
        if(b[t][i][j]=='\0' && b[t][i+1][j]=='\0' && i+1<BOX_WIDTH && numMedium > 0){
          b[t][i+1][j] = 'M';
          b[t][i][j] = 'M';
          numMedium -= 1;
        }
        
        if(numMedium < 1){
          break;
        }
      }
    }
  }
  
  //Pack small packages. Anywhere there's a hole.
  for (int t=0; t<MAX_BOXES; t++){
    for(int i=0; i<BOX_WIDTH; i++){
      for(int j=0; j<BOX_LENGTH; j++){
        if(b[t][i][j] == '\0' && numSmall > 0){
          b[t][i][j] = 'S';
          numSmall -= 1;
        }
        
        if(numSmall < 1){
          break;
        }
      }
    }
  }
  
  //Find out how many boxes were used. If b[i][0][0] is filled then the box is considered used
  for (int t=0; t<MAX_BOXES; t++){
    if(b[t][0][0] != '\0'){
      numBoxes++;
    }
  }
  
  
  //Finish printing the receipt using newly calculated number of boxes used
  printf("\nTotal               $%6.2f\n", total);
  printf("Shipping (%d" " boxes)  $%6.2f\n", numBoxes, 1.49*numBoxes);
  printf("HST (13%)           $%6.2f\n", tax);
  printf("-----------------------------\n");
  printf("Amount Charged      $%6.2f\n", total+(1.49*numBoxes)+tax);
  printf("\n\nIndividual boxes are packed as follows:\n\n");
  
  //Print the entire 3D array
  for(int i=0; i<MAX_BOXES; i++){
    if(b[i][0][0] == '\0'){
          exit(1);
    }
    for(int j=0; j<BOX_WIDTH; j++){
      for(int k=0; k<BOX_LENGTH; k++){
        printf("%c", b[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
 
  return 0;
}
