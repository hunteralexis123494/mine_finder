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
#include <time.h>


/*Use this file to implement the functions you have listed in your header file*/
int printMenu( )
{
  int option;
  
  printf("**************************************************************\n\n");
  printf("               Welcome to Avoid the Mines                     \n\n");
  printf("        Please choose one of the options below.               \n\n");
  printf("        1. Read the board information from a file             \n\n");
  printf("        2. Randomly generate the board information            \n\n");
  printf("        3. Randomly generate the board and play basic         \n\n");
  printf("        4. Randomly generate the board and play advanced      \n\n");
  printf("                Type 1, 2, 3, or 4 and return                 \n\n");
  printf("**************************************************************\n\n");
    
  scanf("%d", &option);
    
  return option;
}

void readData(FILE* input, int ** boardSpace, int row, int col)
{
  //Reading data from input file to store in boardSpace
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      fscanf(input, "%d", &boardSpace[i][j]);
    }
  }
}

int** allocateMemory(int row, int col)
{
  //Creating temporary dbl ptr to have boardSize initialized in main
  int **tempPtr;
  // Allocating memory to store space for rows
  tempPtr = (int**) calloc(row,  sizeof(int*));
  // Allocating memory to store space for columns
  int i = 0;
  for (i = 0; i < row; i++)
  {
    tempPtr[i] = (int *) calloc (col, sizeof(int));
  }

  return tempPtr;
}

void checkIfMine(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  printf("\n");

  // Checking to see if an element is a mine. 
  // If one is, it will be changed to -1.
  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      if(inBoard[i][j] == 1)
      {
        outBoard[i][j] = -1;
      }
    }
  }
}

void checkLeft(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks left if it isn't the first column and if element isn't a mine
      if(j != 0 && inBoard[i][j] != 1)
      {
        if(inBoard[i][j-1] == 1)
        {
          count++;
          outBoard[i][j] += count;
          count = 0;
        }
      }
    }
  }
}

void checkRight(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks right if it isn't the last column and if element isn't is a mine
      if(j != col-1 && inBoard[i][j] != 1)
      {
        if(inBoard[i][j+1] == 1)
        {
          count++;
          outBoard[i][j] += count;
          count = 0;
        }
      }
    }
  }
}

void checkTop(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks if it isn't the first row and if element isn't a mine
      if(i != 0 && inBoard[i][j] != 1)
      {
        if(inBoard[i-1][j] == 1)
        {
          count++;
          outBoard[i][j] += count;
          count = 0;
        }
      }
    }
  }
}

void checkBottom(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks if it isn't the last row and if element isn't a mine
      if(i != row-1 && inBoard[i][j] != 1)
      {
        if(inBoard[i+1][j] == 1)
        {
          count++;
          outBoard[i][j] += count;
          count = 0;
        }
      }
    }
  }
}

void checkTopLeft(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks if element isn't a mine
      if(inBoard[i][j] != 1)
      {
        // Checks if it isn't the first row and column
        if(i != 0)
        {
          if (j != 0)
          {
            // Checks if top-left element isn't a mine
            if(inBoard[i-1][j-1] == 1)
            {
              count++;
              outBoard[i][j] += count;
              count = 0;
            }
          }
        }
      }
    }
  }
}
void checkBottomLeft(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks if element isn't a mine
      if(inBoard[i][j] != 1)
      {
        // Checks if it isn't the last row and first column
        if(i != row-1)
        {
          if (j != 0)
          {
            // Checks if bottom-left element isn't a mine
            if(inBoard[i+1][j-1] == 1)
            {
              count++;
              outBoard[i][j] += count;
              count = 0;
            }
          }
        }
      }
    }
  }
}

void checkBottomRight(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks if element isn't a mine
      if(inBoard[i][j] != 1)
      {
        // Checks if it isn't the last row and last column
        if(i != row-1)
        {
          if(j != col-1)
          {
            // Checks if bottom-right element isn't a mine
            if(inBoard[i+1][j+1] == 1)
            {
              count++;
              outBoard[i][j] += count;
              count = 0;
            }
          }
        }
      }
    }
  }
}

void checkTopRight(int** inBoard, int** outBoard, int row, int col)
{
  int i, j;
  int count = 0;

  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      // Checks if element isn't a mine
      if(inBoard[i][j] != 1)
      {
        // Checks if it isn't the first row and last column
        if(i != 0)
        {  
          if(j != col-1)
          {
            // Checks if top-right element isn't a mine
            if(inBoard[i-1][j+1] == 1)
            {
              count++;
              outBoard[i][j] += count;
              count = 0;
            }
          }
        }
      }
    }
  }
}

void checkNeighbors(int **inBoard, int **outBoard, int row, int col)
{
  int i = 0; 
  int j = 0;

  // Initializing all elements of outBoard to 0
  for (i = 0; i < row; i++) 
  {
    for (j = 0; j < col; j++)
    {
      outBoard[i][j] = 0;
    }
  }

  checkIfMine(inBoard, outBoard, row, col);
  
  checkLeft(inBoard, outBoard, row, col);
  
  checkRight(inBoard, outBoard, row, col);

  checkTop(inBoard, outBoard, row, col);

  checkBottom(inBoard, outBoard, row, col);

  checkTopLeft(inBoard, outBoard, row, col);
  
  checkBottomLeft(inBoard, outBoard, row, col);

  checkTopRight(inBoard, outBoard, row, col);
  
  checkBottomRight(inBoard, outBoard, row, col);
} 

void printOutput(FILE* outPtr, int ** outBoard, int row, int col)
{
  int i, j;

  for (i = 0; i < row; i++)
  {
    for (j = 0; j < col; j++)
    {
      if(outBoard[i][j] == -1)
      {
        fprintf(outPtr, "%c ", 'X');
      }
      else
      {
        fprintf(outPtr, "%d ", outBoard[i][j]);
      }
    }
    fprintf(outPtr, "%c", '\n');
  }
}

void printOut(int ** outBoard, int row, int col)
{
  int i, j;

  for (i = 0; i < row; i++)
  {
    for (j = 0; j < col; j++)
    {
      if (outBoard[i][j] == -1)
      {
        printf("%c ", 'X');
      }
      else
      {
        printf("%d ", outBoard[i][j]);
      }
    }
    printf ("\n");
  }
}

void option1(FILE* inPtr, FILE* outPtr, int row, int col, int** inBoard, int** outBoard)
{
  readData (inPtr, inBoard, row, col);
  readData (inPtr, outBoard, row, col);
  
  checkNeighbors (inBoard, outBoard, row, col);
  
  readData (outPtr, outBoard, row, col);
  
  printOutput (outPtr, outBoard, row, col);
  printOut (outBoard, row, col);
}

void getHW(int* height, int* width)
{ 
  int reEnter = 1;
  
  printf ("Enter the Height and Width you wish the board to be!\n");
  printf ("The Height and Width should be between 5 - 20\n");
  printf ("You must place a space between the height and width.\n");

  while (reEnter == 1)
  {
    scanf ("%d %d", height, width);

    if ((*height < 5 || *height > 20) || (*width < 5 || *width > 20))
    {
      printf("The height and width must have a minimum of 5 and a maximum of 20\n");
      printf("Re-enter your height and width\n");
    }
    else 
    {
      reEnter = 0;
    }
  }
}

void generateBoard(int height, int width, int** genBoard)
{
  int i, j, n;
  int randomI, randomJ;
  
  // Initializing all elements of genBoard to 0
  for (i = 0; i < height; i++) 
  {
    for (j = 0; j < width; j++)
    {
      genBoard[i][j] = 0;
    }
  }

  int max = height * width * 0.15;

  // Initializes random number generator
  srand(time(NULL));
  
  int mineCount = 0;
  
  // Guarantees that the mines aren't placed in the same position more than once
  while (mineCount != max)
  {
    // Gets random position for row and column
    // Places mine in random position
    for (n = 0; n < max; n++)
    {
      randomI = rand() % height;
      randomJ = rand() % width;
      genBoard[randomI][randomJ] = 1;
    }
    for (i = 0; i < height; i++)
    {
      for (j = 0; j < width; j++)
      {
        if (genBoard[i][j] == 1)
        {
          mineCount++;
        }
      }
    }
  }
}

void option2(FILE* outPtr, int height, int width, int** genBoard, int** genBoardOut)
{
  generateBoard (height, width, genBoard);
  readData (outPtr, genBoardOut, height, width);
  checkNeighbors(genBoard, genBoardOut, height, width);
  printOutput (outPtr, genBoardOut, height, width);
  printOut(genBoardOut, height, width);
}

void option3(FILE* outPtr, int height, int width, int** genBoard, int** genBoardOut)
{
  generateBoard (height, width, genBoard);
  readData (outPtr, genBoardOut, height, width);
  checkNeighbors(genBoard, genBoardOut, height, width);
  printOutput (outPtr, genBoardOut, height, width);

  printf("\n");

  int i, j;
  int origHeight = height;
  int origWidth = width;
  int uncover = 1;
  int max = height * width * 0.15;
  
  int **genBoardDotted = allocateMemory (origHeight, origWidth);

  for (i = 0; i < origHeight; i++)
  {
    for (j = 0; j < origWidth; j++)
    {
      genBoardDotted[i][j] = '.';
    }
  }
  
  while (uncover == 1)
  {
    printf("   ");
    for (j = 0; j < origWidth; j++)
    {
      printf("%d ", j);
    }
    printf("\n\n");
    
    for (i = 0; i < origHeight; i++)
    {
      printf("%d  ", i);
      for (j = 0; j < origWidth; j++)
      {
        printf("%c ", genBoardDotted[i][j]);
      }
      printf("\n");
    }
    
    printf("What space do you want to uncover?\n");
    printf("Enter the row (0 - %d), a space, then the column (0 - %d).\n", origHeight-1, origWidth-1);
    scanf("%d %d", &height, &width);

    // -1 from genBoardOut indicates a mine. If element is a mine, the game is over.
    if (genBoardOut[height][width] == -1)
    {
      printf("You've stepped on a mine! Game over!\n");
      uncover = 0;
      printOut(genBoardOut, origHeight, origWidth);
    }
    
    // Uncovers the number of mines surrounding element. The max is 8.
    else
    {
      if (genBoardOut[height][width] == 0)
      {
        genBoardDotted[height][width] = '0';
      }
      if (genBoardOut[height][width] == 1)
      {
        genBoardDotted[height][width] = '1';
      }
      if (genBoardOut[height][width] == 2)
      {
        genBoardDotted[height][width] = '2';
      }
      if (genBoardOut[height][width] == 3)
      {
        genBoardDotted[height][width] = '3';
      }
      if (genBoardOut[height][width] == 4)
      {
        genBoardDotted[height][width] = '4';
      }
      if (genBoardOut[height][width] == 5)
      {
        genBoardDotted[height][width] = '5';
      }
      if (genBoardOut[height][width] == 6)
      {
        genBoardDotted[height][width] = '6';
      }
      if (genBoardOut[height][width] == 7)
      {
        genBoardDotted[height][width] = '7';
      }
      if (genBoardOut[height][width] == 8)
      {
        genBoardDotted[height][width] = '8';
      }
    }
    
    // Checks to see how many dots are remaining on the board  
    int dotCount = 0;
    for (i = 0; i < origHeight; i++)
    {
      for (j = 0; j < origWidth; j++)
      {
        if (genBoardDotted[i][j] == '.')
        {
          ++dotCount;
        }
      }
    }
    printf("\n");
    
    // Checks if the player beat the game. If player didn't hit the any (max) mines, he or she wins.
    if (dotCount == max)
    {
      printf("Congratulations! You beat the game!\n");
      uncover = 0;
      printOut(genBoardOut, origHeight, origWidth);
    }
  }
  
  free(genBoardDotted);
}
