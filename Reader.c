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
 * Arguments: head of the puzzles list
 * Returns: nothing
 *
 * Description: Reads the puzzles finding the desired answer
 *
 *****************************************************************************/
void PuzzlesReading(Puzzle* Puzz)
{
  int binary = -1;
  binary = ReadLine(Puzz);
  binary = ReadCol(Puzz);
  binary = ReadSums(Puzz);
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
 * Arguments: PuzzleNode to read
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
    if((Puzz->matrix[l+1][c] + Puzz->matrix[l+2][c])%2 == 0)
    {
      binary = (Puzz->matrix[l+1][c])/2;
    }
  }
  if(l < Puzz->size - 1  && l > 0)
  {
    if((Puzz->matrix[l-1][c] + Puzz->matrix[l+1][c])%2 == 0)
    {
      binary = (Puzz->matrix[l+1][c])/2;
    }
  }
  if(l > 1)
  {
    if((Puzz->matrix[l-2][c] + Puzz->matrix[l-1][c])%2 == 0)
    {
      binary = (Puzz->matrix[l-1][c])/2;
    }
  }
  return binary;
}


/******************************************************************************
 * ReadCol()
 *
 * Arguments: PuzzleNode to read
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
    if((Puzz->matrix[l][c+1] + Puzz->matrix[l][c+2])%2 == 0)
    {
      binary = (Puzz->matrix[l][c+1])/2;
    }
  }
  if(c < Puzz->size - 1  && c > 0)
  {
    if((Puzz->matrix[l][c-1] + Puzz->matrix[l][c+1])%2 == 0)
    {
      binary = (Puzz->matrix[l][c-1])/2;
    }
  }
  if(c > 1)
  {
    if((Puzz->matrix[l][c-1] + Puzz->matrix[l][c-2])%2 == 0)
    {
      binary = (Puzz->matrix[l-1][c])/2;
    }
  }
  return binary;
}

/******************************************************************************
 * ReadSums()
 *
 * Arguments: PuzzleNode to read
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
