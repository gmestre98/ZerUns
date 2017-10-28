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
void PuzzlesReading(PuzzleNode *head)
{
  int binary = -1;
  while(head != NULL)
  {
    binary = ReadLine(head);
    binary = ReadCol(head);
    binary = ReadSums(head);
    if(binary == head->content.binary)
    {
      head->content.result = 1;
    }
    else if(binary != -1)
    {
      head->content.result = -1;
    }
    binary = -1;
    head = head->next;
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
int ReadLine(PuzzleNode *Node)
{
  int binary = -1;
  int l = Node->content.line - 1;
  int c = Node->content.col - 1;
  if(l < Node->content.size -2)
  {
    if((Node->content.matrix[l+1][c] + Node->content.matrix[l+2][c])%2 == 0)
    {
      binary = (Node->content.matrix[l+1][c])/2;
    }
  }
  if(l < Node->content.size - 1  && l > 0)
  {
    if((Node->content.matrix[l-1][c] + Node->content.matrix[l+1][c])%2 == 0)
    {
      binary = (Node->content.matrix[l+1][c])/2;
    }
  }
  if(l > 1)
  {
    if((Node->content.matrix[l-2][c] + Node->content.matrix[l-1][c])%2 == 0)
    {
      binary = (Node->content.matrix[l-1][c])/2;
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
int ReadCol(PuzzleNode *Node)
{
  int binary = -1;
  int l = Node->content.line - 1;
  int c = Node->content.col - 1;

  if(c < Node->content.size -2)
  {
    if((Node->content.matrix[l][c+1] + Node->content.matrix[l][c+2])%2 == 0)
    {
      binary = (Node->content.matrix[l][c+1])/2;
    }
  }
  if(c < Node->content.size - 1  && c > 0)
  {
    if((Node->content.matrix[l][c-1] + Node->content.matrix[l][c+1])%2 == 0)
    {
      binary = (Node->content.matrix[l][c-1])/2;
    }
  }
  if(c > 1)
  {
    if((Node->content.matrix[l][c-1] + Node->content.matrix[l][c-2])%2 == 0)
    {
      binary = (Node->content.matrix[l-1][c])/2;
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
int ReadSums(PuzzleNode *Node)
{
  int binary = -1;
  int i = 0;
  int onesum = 0;
  int zerosum = 0;
  int ninecount = 0;
  int l = Node->content.line - 1;
  int c = Node->content.col - 1;
  /* line verification */
  for(i=0; i < Node->content.size; i++)
  {
    if(Node->content.matrix[i][c] != 9)
    {
      onesum += Node->content.matrix[i][c];
    }
    else
    {
      ninecount ++;
    }
  }
  zerosum = Node->content.size - ninecount - onesum;
  if(zerosum == (Node->content.size/2))
  {
    binary = 1;
  }
  else if(onesum == (Node->content.size/2))
  {
    binary = 0;
  }

  /* column verification */
  for(i=0; i < Node->content.size; i++)
  {
    if(Node->content.matrix[l][i] != 9)
    {
      onesum += Node->content.matrix[l][i];
    }
    else
    {
      ninecount ++;
    }
  }
  zerosum = Node->content.size - ninecount - onesum;
  if(zerosum == (Node->content.size/2))
  {
    binary = 1;
  }
  else if(onesum == (Node->content.size/2))
  {
    binary = 0;
  }
  return binary;
}
