/*******************************
 *Alexis Hunter                *
 *ahunte4		       *
 *CPSC 1020 Fall 2017	       *
 *Due Date: 9-27-17	       *
 *Instructor: Dr. Yvon Feaster *
 *******************************/

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


int main(int argc, char *argv[])
{
  /*Create any variables need*/
  
  /*1.  Create a file pointer for the file that you will read from
   *2.  Check to make sure the file pointer is opened sucessfully */

  FILE *inPtr = fopen(argv[1], "r");
  if (inPtr == NULL) {
    printf("File failed to open for reading\n");
    return 1;
  }
  
  FILE *outPtr = fopen(argv[2], "w");
  if (outPtr == NULL) {
    printf("File failed to open for writing\n");
    return 1;
  }

  int rowNum;

  int colNum;

  /*Call printMenu() This starts the program.  The Selection returned will
  *determine the steps needed next.
  */
  int repeat = 1;
  while (repeat == 1)
  {
    int option = printMenu( );
  
    if (option == 1)
    {   
      //Reading the number of rows in input file and storing in rowNum
      fscanf (inPtr,"%d", &rowNum);
    
      //Reading the number of columns in input file and storing in colNum
      fscanf (inPtr,"%d", &colNum);
    
      // Initializing boardSize with allocated memory for rows and columns
      int **boardSize = allocateMemory (rowNum, colNum);

      // Initializing newBoard with allocated memory for rows and columns
      int **newBoard = allocateMemory (rowNum, colNum); 

      option1(inPtr, outPtr, rowNum, colNum, boardSize, newBoard);
  
      free(boardSize);
      free(newBoard);
    
      repeat = 0;
    }
    else if (option == 2)
    {   
      int *heightNum = (int*)malloc(1 * sizeof(int));
      int *widthNum = (int*)malloc(1 * sizeof(int));
    
      getHW(heightNum, widthNum);
    
      int **genBoard = allocateMemory (*heightNum, *widthNum);
      int **genBoardOut = allocateMemory (*heightNum, *widthNum);
    
      option2(outPtr, *heightNum, *widthNum, genBoard, genBoardOut);
    
      free(heightNum);
      free(widthNum);
      free(genBoard);
      free(genBoardOut);
    
      repeat = 0;
    }
    else if (option == 3)
    {  
      int *heightNum = (int*)malloc(1 * sizeof(int));
      int *widthNum = (int*)malloc(1 * sizeof(int));
    
      getHW(heightNum, widthNum);
    
      int **genBoard = allocateMemory (*heightNum, *widthNum);
      int **genBoardOut = allocateMemory (*heightNum, *widthNum);
      
      option3(outPtr, *heightNum, *widthNum, genBoard, genBoardOut);
      
      free(heightNum);
      free(widthNum);
      free(genBoard);
      free(genBoardOut);
      
      repeat = 0;
    }
    else if (option == 4)
    {
      printf("I have chosen not to do this option.\n\n");   
    }
    else 
    {
      printf("Invalid option. Type 1, 2, 3, 4 and return.\n\n");
    }
  }

  /*After everything is complete you should free any remaining allocated memory
   *and close and open file pointers.*/

  fclose (inPtr);
  fclose (outPtr);
  
  return 0;
}
