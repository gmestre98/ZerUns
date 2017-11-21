/******************************************************************************
 *
 * File Name: Macros.h
 * Author:    Gonçalo Mestre nº 87005  &  Guilherme Guerreiro nº87010
 * Revision:  26 Oct 2017
 *
 * NAME
 *  Macros - Important definitions
 *
 * DESCRIPTION
 *  File containing the functions to handle the puzzles results
 *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Reader.h"


/******************************************************************************
 * PuzzlesReading()
 *
 * Arguments: Puzzle with teh data to read
 * Returns: nothing
 *
 * Description: Reads the puzzle finding the desired answer
 *
 *****************************************************************************/
void PuzzlesReading(Puzzle* Puzz)
{
  int binary = -1;
  if(Puzz->matrix[Puzz->line - 1][Puzz->col - 1] != 9)
  {
    if(Puzz->binary == Puzz->matrix[Puzz->line - 1][Puzz->col - 1])
    {
      Puzz->result = 1;
    }
    else
    {
      Puzz->result = -1;
    }
    return;
  }
  binary = ReadLine(Puzz);
  if(binary != -1)
  {
    if((ReadCol(Puzz) != -1  &&  ReadCol(Puzz) != binary)  ||
      (ReadSums(Puzz) != -1  &&  ReadSums(Puzz) != binary))
    {
      Puzz->result = -1;
      return;
    }
  }
  if(binary == -1)
  {
    binary = ReadCol(Puzz);
    if(binary != -1)
    {
      if(ReadSums(Puzz) != -1  &&  ReadSums(Puzz) != binary)
      {
        Puzz->result = -1;
        return;
      }
    }
  }
  if(binary == -1)
  {
    binary = ReadSums(Puzz);
  }
  if(binary == Puzz->binary)
  {
    Puzz->result = 1;
  }
  else if(binary != -1)
  {
    Puzz->result = -1;
  }
}

/******************************************************************************
 * ReadLine()
 *
 * Arguments: Puzzle with the data to read
 * Returns: The binary result from the reading of the lines
 *
 * Description: Reads the line of the puzzle for the chosen position
 *
 *****************************************************************************/
int ReadLine(Puzzle* Puzz)
{
  int binary = -1;
  int l = Puzz->line - 1;
  int c = Puzz->col - 1;
  if(l < Puzz->size -2)
  {
    if((Puzz->matrix[l+1][c] + Puzz->matrix[l+2][c])%2 == 0  &&
        Puzz->matrix[l+1][c] != 9  &&  Puzz->matrix[l+2][c] != 9)
    {
      binary = (((Puzz->matrix[l+1][c] + Puzz->matrix[l+2][c])/2)-1)*(-1);
    }
  }
  if(l < Puzz->size - 1  && l > 0)
  {
    if((Puzz->matrix[l-1][c] + Puzz->matrix[l+1][c])%2 == 0  &&
        Puzz->matrix[l+1][c] != 9  &&  Puzz->matrix[l-1][c] != 9)
    {
      binary = (((Puzz->matrix[l+1][c] + Puzz->matrix[l-1][c])/2)-1)*(-1);
    }
  }
  if(l > 1)
  {
    if((Puzz->matrix[l-2][c] + Puzz->matrix[l-1][c])%2 == 0  &&
        Puzz->matrix[l-1][c] != 9  &&  Puzz->matrix[l-2][c] != 9)
    {
      binary = (((Puzz->matrix[l-1][c] + Puzz->matrix[l-2][c])/2)-1)*(-1);
    }
  }
  return binary;
}


/******************************************************************************
 * ReadCol()
 *
 * Arguments: Puzzle with the data to read
 * Returns: The binary result from the reading of the columns
 *
 * Description: Reads the column of the puzzle for the chosen position
 *
 *****************************************************************************/
int ReadCol(Puzzle* Puzz)
{
  int binary = -1;
  int l = Puzz->line - 1;
  int c = Puzz->col - 1;

  if(c < Puzz->size -2)
  {
    if((Puzz->matrix[l][c+1] + Puzz->matrix[l][c+2])%2 == 0  &&
        Puzz->matrix[l][c+1] != 9  &&  Puzz->matrix[l][c+2] != 9)
    {
      binary = (((Puzz->matrix[l][c+1] + Puzz->matrix[l][c+2])/2)-1)*(-1);
    }
  }
  if(c < Puzz->size - 1  && c > 0)
  {
    if((Puzz->matrix[l][c-1] + Puzz->matrix[l][c+1])%2 == 0  &&
        Puzz->matrix[l][c+1] != 9  &&  Puzz->matrix[l][c-1] != 9)
    {
      binary = (((Puzz->matrix[l][c+1] + Puzz->matrix[l][c-1])/2)-1)*(-1);
    }
  }
  if(c > 1)
  {
    if((Puzz->matrix[l][c-1] + Puzz->matrix[l][c-2])%2 == 0  &&
        Puzz->matrix[l][c-1] != 9  &&  Puzz->matrix[l][c-2] != 9)
    {
      binary = (((Puzz->matrix[l][c-1] + Puzz->matrix[l][c-2])/2)-1)*(-1);
    }
  }
  return binary;
}

/******************************************************************************
 * ReadSums()
 *
 * Arguments: Puzzle with the data to read
 * Returns: The binary result from the reading of the sums
 *
 * Description: Reads the lines and columns of the puzzle for the sum
 *
 *****************************************************************************/
int ReadSums(Puzzle *Puzz)
{
  int binary = -1;
  int i = 0;
  int onesum = 0;
  int zerosum = 0;
  int ninecount = 0;
  int l = Puzz->line - 1;
  int c = Puzz->col - 1;
  /* line verification */
  for(i=0; i < Puzz->size; i++)
  {
    if(Puzz->matrix[i][c] != 9)
    {
      onesum += Puzz->matrix[i][c];
    }
    else
    {
      ninecount ++;
    }
  }
  zerosum = Puzz->size - ninecount - onesum;
  if(zerosum == (Puzz->size/2))
  {
    binary = 1;
  }
  else if(onesum == (Puzz->size/2))
  {
    binary = 0;
  }
  onesum = 0;
  zerosum = 0;
  ninecount = 0;
  /* column verification */
  for(i=0; i < Puzz->size; i++)
  {
    if(Puzz->matrix[l][i] != 9)
    {
      onesum += Puzz->matrix[l][i];
    }
    else
    {
      ninecount ++;
    }
  }
  zerosum = Puzz->size - ninecount - onesum;
  if(zerosum == (Puzz->size/2))
  {
    binary = 1;
  }
  else if(onesum == (Puzz->size/2))
  {
    binary = 0;
  }
  return binary;
}
