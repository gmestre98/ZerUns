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
#include <time.h>
#include "Reader.h"
#include "stack.h"


/******************************************************************************
 * Solve()
 *
 * Arguments: Puzzle with the data to read
 * Returns: 1 if the puzzle is solved, -1 if there is no solution
 *
 * Description: Reads the puzzle finding the desired answer
 *
 *****************************************************************************/
 int Solve(Puzzle *Puzz)
{
  int ret = 0;
  InitStack();
  if(Puzz->variant == 1)
  {
    ret = Solver(Puzz, WrongPuzz);
  }
  if(Puzz->variant == 2)
  {
    ret = Solver(Puzz, WrongPuzz2);
  }
  FreeStack();
  return ret;
}


/******************************************************************************
 * Solver()
 *
 * Arguments: Puzzle with the data to read
 * Returns: 1 if the puzzle is solved, -1 if there is no solution
 *
 * Description: Reads the puzzle finding the desired answer
 *
 *****************************************************************************/
 int Solver(Puzzle* Puzz, int (*Verification) (Puzzle *))
 {
   int endstack = 0;

    while(FullPuzz(Puzz) == 0)
    {
      /*Filling the obvious cases with the first 2 rules */
    	FillLine(Puzz);
      FillCol(Puzz);
      FillSumsLine(Puzz);
			FillSumsCols(Puzz);
      if(FullPuzz(Puzz) == 0)
      {
        FillRandom(Puzz);     /*If the puzzle is not full we fill a random pos */
      }

      endstack = CleanErrors(Puzz, Verification); /*Correcting the error in the puzzle */
      if(endstack == 1)
      {
        return -1;
      }
    }
    return 1;
 }


Changes *ChangeType(char type, int l, int c, int value)
{
	Changes *changes = NULL;
	changes = (Changes *)malloc(sizeof(Changes));
  if(changes == NULL)
  {
  	exit(0);
 	}
  changes->type = type;
 	changes->line = l;
  changes->col = c;
  changes->value = value;
  changes->next = NULL;
  return changes;
}


/******************************************************************************
 * FillLine()
 *
 * Arguments: The Puzzle
 * Returns: 1 if anything was filled or 0 if not
 *
 * Description: If there are any places to be filled by line conditions, this
 *              function fills them
 *
 *****************************************************************************/
void FillLine(Puzzle* Puzz)
{
  int l;
  int c;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      if(Puzz->matrix[l][c] == 9)
      {
        if(c > 1)
        {
          if(Puzz->matrix[l][c-1] != 9  &&  Puzz->matrix[l][c-2] != 9  &&
              Puzz->matrix[l][c-1] == Puzz->matrix[l][c-2])
          {
            Puzz->matrix[l][c] = (Puzz->matrix[l][c-1] + 1)%2;
            Push(ChangeType('r', l, c, Puzz->matrix[l][c]));
          }
        }
        if(c > 0  &&  c < Puzz->size - 1)
        {
          if(Puzz->matrix[l][c-1] != 9  &&  Puzz->matrix[l][c+1] != 9  &&
              Puzz->matrix[l][c-1] == Puzz->matrix[l][c+1])
          {
            Puzz->matrix[l][c] = (Puzz->matrix[l][c+1] + 1)%2;
            Push(ChangeType('r', l, c, Puzz->matrix[l][c]));
          }
        }
        if(c < Puzz->size - 2)
        {
          if(Puzz->matrix[l][c+1] != 9  &&  Puzz->matrix[l][c+2] != 9  &&
              Puzz->matrix[l][c+1] == Puzz->matrix[l][c+2])
          {
            Puzz->matrix[l][c] = (Puzz->matrix[l][c+2] + 1)%2;
            Push(ChangeType('r', l, c, Puzz->matrix[l][c]));
          }
        }
      }
    }
  }
}


/******************************************************************************
 * FillCol()
 *
 * Arguments: The Puzzle
 * Returns: 1 if anything was filled or 0 if not
 *
 * Description: If there are any places to be filled by column conditons, they
 *              will be filled
 *
 *****************************************************************************/
void FillCol(Puzzle* Puzz)
{
  int l;
  int c;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      if(Puzz->matrix[l][c] == 9)
      {
        if(l > 1)
        {
          if(Puzz->matrix[l-1][c] != 9  &&  Puzz->matrix[l-2][c] != 9  &&
              Puzz->matrix[l-1][c] == Puzz->matrix[l-2][c])
          {
            Puzz->matrix[l][c] = (Puzz->matrix[l-1][c] + 1)%2;
            Push(ChangeType('r', l, c, Puzz->matrix[l][c]));
            
          }
        }
        if(l > 0  &&  l < Puzz->size - 1)
        {
          if(Puzz->matrix[l-1][c] != 9  &&  Puzz->matrix[l+1][c] != 9  &&
              Puzz->matrix[l-1][c] == Puzz->matrix[l+1][c])
          {
            Puzz->matrix[l][c] = (Puzz->matrix[l+1][c] + 1)%2;
            Push(ChangeType('r', l, c, Puzz->matrix[l][c]));
          }
        }
        if(l < Puzz->size - 2)
        {
          if(Puzz->matrix[l+1][c] != 9  &&  Puzz->matrix[l+2][c] != 9  &&
              Puzz->matrix[l+1][c] == Puzz->matrix[l+2][c])
          {
            Puzz->matrix[l][c] = (Puzz->matrix[l+2][c] + 1)%2;
            Push(ChangeType('r', l, c, Puzz->matrix[l][c]));
          }
        }
      }
    }
  }
}


/******************************************************************************
 * FillSumsLine()
 *
 * Arguments: The Puzzle
 * Returns: 1 if anything was filled or 0 if not
 *
 * Description: Fills cases using the parity rule for lines
 *
 *****************************************************************************/
void FillSumsLine(Puzzle* Puzz)
{
  int l;
  int c;
  int sumline = 0;
  int sumlinezer = 0;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      sumline += (Puzz->matrix[l][c])%9;
      sumlinezer += (Puzz->matrix[l][c] +1)%2;
    }
    if(sumline == (Puzz->size)/2)
    {
      for(c = 0; c < Puzz->size; c++)
      {
        if(Puzz->matrix[l][c] == 9)
        {
          Puzz->matrix[l][c] = 0;
          Push(ChangeType('r', l, c, 0));
        }
      }
    }
    else if(sumlinezer == (Puzz->size)/2)
    {
      for(c = 0; c < Puzz->size; c++)
      {
        if(Puzz->matrix[l][c] == 9)
        {
          Puzz->matrix[l][c] = 1;
          Push(ChangeType('r', l, c, 1));
        }
      }
    }
    sumline = 0;
    sumlinezer = 0;
  }
}


/******************************************************************************
 * FillSumsCols()
 *
 * Arguments: The Puzzle
 * Returns: 1 if anything was filled or 0 if not
 *
 * Description:Fills cases using the parity rule for columns
 *
 *****************************************************************************/
void FillSumsCols(Puzzle* Puzz)
{
  int l;
  int c;
  int sumline = 0;
  int sumlinezer = 0;

  for(c = 0; c < Puzz->size; c++)
  {
    for(l = 0; l < Puzz->size; l++)
    {
      sumline += (Puzz->matrix[l][c])%9;
      sumlinezer += (Puzz->matrix[l][c] +1)%2;
    }
    if(sumline == (Puzz->size)/2)
    {
      for(l = 0; l < Puzz->size; l++)
      {
        if(Puzz->matrix[l][c] == 9)
        {
          Puzz->matrix[l][c] = 0;
          Push(ChangeType('r', l, c, 0));
        }
      }
    }
    else if(sumlinezer == (Puzz->size)/2)
    {
      for(l = 0; l < Puzz->size; l++)
      {
        if(Puzz->matrix[l][c] == 9)
        {
          Puzz->matrix[l][c] = 1;
          Push(ChangeType('r', l, c, 1));
        }
      }
    }
    sumline = 0;
    sumlinezer = 0;
  }
}


/******************************************************************************
 * FullPuzz()
 *
 * Arguments: The Puzzle
 * Returns: 1 if the puzzle is full, 0 if not
 *
 * Description: Verifies if the puzzle is complete
 *
 *****************************************************************************/
int FullPuzz(Puzzle* Puzz)
{
  int l = 0;
  int c = 0;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      if(Puzz->matrix[l][c] == 9)
      {
        return 0;
      }
    }
  }
  return 1;
}


/******************************************************************************
 * WrongPuzz()
 *
 * Arguments: The Puzzle
 * Returns: 1 if any rule is violated, 0 if not
 *
 * Description: Verifies if any of the rules was violated
 *
 *****************************************************************************/
int WrongPuzz(Puzzle* Puzz)
{
  if(WrongLine(Puzz)  ||  WrongCol(Puzz)  ||  WrongSum(Puzz))
  {
    return 1;
  }
  return 0;
}


/******************************************************************************
 * WrongLine()
 *
 * Arguments: The Puzzle
 * Returns: 1 if the first rule is violated for any line, 0 if not
 *
 * Description: Verifies if the first rule for lines was violated
 *
 *****************************************************************************/
int WrongLine(Puzzle* Puzz)
{
  int l = 0;
  int c = 0;
  int sumone = 0;
  int sumzer = 0;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      sumone += ((Puzz->matrix[l][c])%9);
      sumzer += ((Puzz->matrix[l][c] + 1)%2);
      if(c > 2)
      {
        sumone -= ((Puzz->matrix[l][c-3])%9);
        sumzer -= ((Puzz->matrix[l][c-3] + 1)%2);
      }
      if(sumone > 2 || sumzer > 2)
      {
        return 1;
      }
    }
    sumone = 0;
    sumzer = 0;
  }
  return 0;
}


/******************************************************************************
 * WrongCol()
 *
 * Arguments: The Puzzle
 * Returns: 1 if the first rule is violated for any column, 0 if not
 *
 * Description: Verifies if the first rule for columns was violated
 *
 *****************************************************************************/
int WrongCol(Puzzle *Puzz)
{
  int l = 0;
  int c = 0;
  int sumone = 0;
  int sumzer = 0;

  for(c = 0; c < Puzz->size; c++)
  {
    for(l = 0; l < Puzz->size; l++)
    {
      sumone = sumone + ((Puzz->matrix[l][c])%9);
      sumzer = sumzer + ((Puzz->matrix[l][c] + 1)%2);
      if(l > 2)
      {
        sumone = sumone - ((Puzz->matrix[l-3][c])%9);
        sumzer = sumzer - ((Puzz->matrix[l-3][c] + 1)%2);
      }
      if(sumone > 2 || sumzer > 2)
      {
        return 1;
      }
    }
    sumone = 0;
    sumzer = 0;
  }
  return 0;
}


/******************************************************************************
 * WrongSum()
 *
 * Arguments: The Puzzle
 * Returns: 1 if the parity rule was violated, 0 if not
 *
 * Description: Verifies if the parity rule was violated
 *
 *****************************************************************************/
int WrongSum(Puzzle *Puzz)
{
  int l = 0;
  int c = 0;
  int sumone = 0;
  int sumzer = 0;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      sumone += ((Puzz->matrix[l][c])%9);
      sumzer += ((Puzz->matrix[l][c] + 1)%2);
    }
    if(sumone > Puzz->size/2  ||  sumzer > Puzz->size/2)
    {
      return 1;
    }
    sumone = 0;
    sumzer = 0;
  }
  for(c = 0; c < Puzz->size; c++)
  {
    for(l = 0; l < Puzz->size; l++)
    {
      sumone += ((Puzz->matrix[l][c])%9);
      sumzer += ((Puzz->matrix[l][c] + 1)%2);
    }
    if(sumone > Puzz->size/2  ||  sumzer > Puzz->size/2)
    {
      return 1;
    }
    sumone = 0;
    sumzer = 0;
  }
  return 0;
}


/******************************************************************************
 * FindEmpty()
 *
 * Arguments: The Puzzle, a line and a column
 * Returns: nothing
 *
 * Description: Finds an empty position on the puzzle
 *
 *****************************************************************************/
void FindEmpty(Puzzle *Puzz, int *l, int *c)
{
  int a = 0;
  for(a = 0; a < Puzz->size; a++)
  {
    for(*l = a; *l < Puzz->size; *l = *l + 1)
    {
      for(*c = a; *c < Puzz->size; *c = *c + 1)
      {
        if(Puzz->matrix[*l][*c] == 9)
        {
          return;
        }
      }
    }
    for(*c = a; *c < Puzz->size; *c = *c + 1)
    {
      for(*l = a + 1; *l < Puzz->size; *l = *l + 1)
      {
        if(Puzz->matrix[*l][*c] == 9)
        {
          return;
        }
      }
    }
  }
}


/******************************************************************************
 * FillRandom()
 *
 * Arguments: The Puzzle
 * Returns: nothing
 *
 * Description: Fills a random empty position
 *
 *****************************************************************************/
void FillRandom(Puzzle *Puzz)
{
  int l = 0;
  int c = 0;

  FindEmpty(Puzz, &l, &c);
  Push(ChangeType('a', l, c, Puzz->matrix[l][c] = 0));
}


/******************************************************************************
 * CleanErrors()
 *
 * Arguments: The Puzzle
 * Returns: 1 if the puzzle is unsolvable, 0 if the process will continue
 *
 * Description: Pops changes from the stack until is found a random filled
 *              position than changes it to the other binary or if it was
 *              already tried goes doing pops again
 *
 *****************************************************************************/
int CleanErrors(Puzzle *Puzz, int (*Verification) (Puzzle *))
{
  Changes *changes = NULL;

  while(Verification(Puzz))
  {
    while(isEmpty() == 0)
    {
    	changes = Pop();
      if(changes->type == 'a' && changes->value == 0)
      {
        changes->value = 1;
        Puzz->matrix[changes->line][changes->col] = 1;
        Push(changes);
        break;
      }
      else
      {
        Puzz->matrix[changes->line][changes->col] = 9;
        free(changes);
      }
    }
  }
  if(isEmpty() == 1)
  {
    return 1;
  }
  return 0;
}


 /******************************************************************************
  * WrongPuzz2()
  *
  * Arguments: The Puzzle
  * Returns: 1 if any rule is violated, 0 if not
  *
  * Description: Verifies if any of the rules was violated
  *
  *****************************************************************************/
int WrongPuzz2(Puzzle* Puzz)
{
  if(WrongLine(Puzz)  ||  WrongCol(Puzz)  ||  WrongSum(Puzz) || EqualLine(Puzz)
	  || EqualCol(Puzz))
  {
    return 1;
  }
  	return 0;
}


int EqualLine(Puzzle* Puzz)
{
	int a = 0;
  int l = 0;
  int c = 0;
  int f = 0;
  int counter = 0;
  int *lines = NULL;
  lines = (int *)malloc((Puzz->size) * sizeof(int));
  if(lines == NULL)
  {
    exit(0);
  }
  /* Initializing the lines vector */
  for(l = 0; l < Puzz->size; l++)
  {
    lines[l] = 1;
  }
  /* Getting the empty lines */
  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      if(Puzz->matrix[l][c] == 9)
      {
        f++;
        lines[l] = 0;
        break;
      }
    }
  }
  if(f >= Puzz->size - 1)
  {
    free(lines);
    return 0;
  }
  /* Finding the errors */
  for(l = 0; l < Puzz->size; l++)
  {
    if(lines[l] == 1)
    {
      for(c = l + 1; c < Puzz->size; c++)
      {
        if(lines[c] == 1)
        {
          for(a = 0; a < Puzz->size; a++)
          {
            if(Puzz->matrix[l][a] == Puzz->matrix[c][a])
            {
              counter ++;
            }
            else
            {
              break;
            }
          }
          if(counter == Puzz->size)
          {
            free(lines);
            return 1;
          }
          counter = 0;
        }
      }
      lines[l] = 0;
    }
  }
  free(lines);
  return 0;
}


int EqualCol(Puzzle* Puzz)
{
  int a = 0;
  int l = 0;
  int c = 0;
  int f = 0;
  int counter = 0;
  int *lines = NULL;
  lines = (int *)malloc((Puzz->size) * sizeof(int));
  if(lines == NULL)
  {
    exit(0);
  }
  /* Initializing the lines vector */
  for(l = 0; l < Puzz->size; l++)
  {
    lines[l] = 1;
  }
  /* Getting the empty lines */
  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      if(Puzz->matrix[c][l] == 9)
      {
        f++;
        lines[l] = 0;
        break;
      }
    }
  }
  if(f >= Puzz->size - 1)
  {
    free(lines);
    return 0;
  }
  /* Finding the errors */
  for(l = 0; l < Puzz->size; l++)
  {
    if(lines[l] == 1)
    {
      for(c = l + 1; c < Puzz->size; c++)
      {
        if(lines[c] == 1)
        {
          for(a = 0; a < Puzz->size; a++)
          {
            if(Puzz->matrix[a][l] == Puzz->matrix[a][c])
            {
              counter ++;
            }
            else
            {
              break;
            }
          }
          if(counter == Puzz->size)
          {
            free(lines);
            return 1;
          }
          counter = 0;
        }
      }
      lines[l] = 0;
    }
  }
  free(lines);
  return 0;
}
