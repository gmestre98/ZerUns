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

Stack *stack;     /* Pointer to the stack where the changes are saved */

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
  stack = InitStack();
  if(Puzz->variant == 1)
  {
    ret = Solver1(Puzz, 1, 1, 1, 1);
  }
  if(Puzz->variant == 2)
  {
    /*ret = Solver2(Puzz, 1, 1, 1, 1);*/
  }
  FreeMaStack();
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
 int Solver1(Puzzle* Puzz, int l, int c, int sl, int sc)
 {
    int endstack = 0;
    int ret = 0;

    /*Filling the obvious cases with the first 2 rules */
    while(l > 0  ||  c > 0  ||  sl > 0  ||  sc > 0)
    {
      l = FillLine(Puzz);
      c = FillCol(Puzz);
      sl = FillSumsLine(Puzz);
      sc = FillSumsCols(Puzz);
    }
    if(WrongPuzz(Puzz))  /* Function that verifies if we created an error */
    {
      endstack = CleanErrors(Puzz); /*Correcting the error in the puzzle */
      if(endstack == 1)
      {
        return -1;
      }
    }
    if(FullPuzz(Puzz) == 0)
    {
      FillRandom(Puzz);     /*If the puzzle is not full we fill a random pos */
      ret = Solver1(Puzz, 1, 1, 1, 1);
    }
    else
    {
      return 1;
    }
    return ret;
 }


/******************************************************************************
 * InitStack()
 *
 * Arguments:
 * Returns: The stack
 *
 * Description: Initializes the Stack used to save the changes in the matrix
 *
 *****************************************************************************/
Stack *InitStack()
{
  Stack *stack = malloc(sizeof(Stack));
  stack->top = NULL;
  return stack;
}


/******************************************************************************
 * Push()
 *
 * Arguments: type of the change to the matrix
 *            line of the change to the matrix
 *            column of the change to the matrix
 *            value introduced in the matrix
 * Returns: nothing
 *
 * Description: Adds the node with the changes aplied to the matrix
 *
 *****************************************************************************/
void Push(char type, int line, int col, int value)
{
  Changes *changes = NULL;
  changes = (Changes *)malloc(sizeof(Changes));
  if(changes == NULL)
  {
    exit(0);
  }
  changes->type = type;
  changes->line = line;
  changes->col = col;
  changes->value = value;
  changes->next = stack->top;
  stack->top = changes;
  return;
}


/******************************************************************************
 * Pop()
 *
 * Arguments: nothing
 * Returns: Node popped
 *
 * Description: Removes the first node of the matrix
 *****************************************************************************/
Changes* Pop()
{
  Changes *changes = stack->top;

  if(stack->top != NULL)
  {
    stack->top = stack->top->next;
  }
  return changes;
}

/******************************************************************************
 * FreeMaStack()
 *
 * Arguments: nothing
 * Returns: Node popped
 *
 * Description: Removes the first node of the matrix
 *****************************************************************************/
void FreeMaStack()
{
  Changes *freed = NULL;
  while(stack->top != NULL)
  {
    freed = stack->top;
    stack->top = stack->top->next;
    free(freed);
  }
  free(stack->top);
  free(stack);
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
int FillLine(Puzzle* Puzz)
{
  int l = 0;
  int c = 0;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      if(c > 1)
      {
        if(Puzz->matrix[l][c-1] != 9  &&  Puzz->matrix[l][c-2] != 9  &&
            Puzz->matrix[l][c-1] == Puzz->matrix[l][c-2]  &&
            Puzz->matrix[l][c] == 9)
        {
          Push('r', l, c, Puzz->matrix[l][c] = (Puzz->matrix[l][c-1] + 1)%2);
          return 1;
        }
      }
      if(c > 0  &&  c < Puzz->size - 1)
      {
        if(Puzz->matrix[l][c-1] != 9  &&  Puzz->matrix[l][c+1] != 9  &&
            Puzz->matrix[l][c-1] == Puzz->matrix[l][c+1]  &&
            Puzz->matrix[l][c] == 9)
        {
          Push('r', l, c, Puzz->matrix[l][c] = (Puzz->matrix[l][c+1] + 1)%2);
          return 1;
        }
      }
      if(c < Puzz->size - 2)
      {
        if(Puzz->matrix[l][c+1] != 9  &&  Puzz->matrix[l][c+2] != 9  &&
            Puzz->matrix[l][c+1] == Puzz->matrix[l][c+2]  &&
            Puzz->matrix[l][c] == 9)
        {
          Push('r', l, c, Puzz->matrix[l][c] = (Puzz->matrix[l][c+2] + 1)%2);
          return 1;
        }
      }
    }
  }
  return 0;
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
int FillCol(Puzzle* Puzz)
{
  int l = 0;
  int c = 0;

  for(l = 0; l < Puzz->size; l++)
  {
    for(c = 0; c < Puzz->size; c++)
    {
      if(l > 1)
      {
        if(Puzz->matrix[l-1][c] != 9  &&  Puzz->matrix[l-2][c] != 9  &&
            Puzz->matrix[l-1][c] == Puzz->matrix[l-2][c]  &&
            Puzz->matrix[l][c] == 9)
        {
          Puzz->matrix[l][c] = (Puzz->matrix[l-1][c] + 1)%2;
          Push('r', l, c, Puzz->matrix[l][c]);
          return 1;
        }
      }
      if(l > 0  &&  l < Puzz->size - 1)
      {
        if(Puzz->matrix[l-1][c] != 9  &&  Puzz->matrix[l+1][c] != 9  &&
            Puzz->matrix[l-1][c] == Puzz->matrix[l+1][c]  &&
            Puzz->matrix[l][c] == 9)
        {
          Puzz->matrix[l][c] = (Puzz->matrix[l+1][c] + 1)%2;
          Push('r', l, c, Puzz->matrix[l][c]);
          return 1;
        }
      }
      if(l < Puzz->size - 2)
      {
        if(Puzz->matrix[l+1][c] != 9  &&  Puzz->matrix[l+2][c] != 9  &&
            Puzz->matrix[l+1][c] == Puzz->matrix[l+2][c]  &&
            Puzz->matrix[l][c] == 9)
        {
          Puzz->matrix[l][c] = (Puzz->matrix[l+2][c] + 1)%2;
          Push('r', l, c, Puzz->matrix[l][c]);
          return 1;
        }
      }
    }
  }
  return 0;
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
int FillSumsLine(Puzzle* Puzz)
{
  int l = 0;
  int c = 0;
  int sumline = 0;
  int sumlinezer = 0;
  int ret = 0;

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
          Push('r', l, c, 0);
          ret = 1;
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
          Push('r', l, c, 1);
          ret = 1;
        }
      }
    }
    sumline = 0;
    sumlinezer = 0;
  }
  return ret;
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
int FillSumsCols(Puzzle* Puzz)
{
  int l = 0;
  int c = 0;
  int sumline = 0;
  int sumlinezer = 0;
  int ret = 0;

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
          Push('r', l, c, 0);
          ret = 1;
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
          Push('r', l, c, 1);
          ret = 1;
        }
      }
    }
    sumline = 0;
    sumlinezer = 0;
  }
  return ret;
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
      sumone += (Puzz->matrix[l][c])%9;
      sumzer += (Puzz->matrix[l][c] + 1)%2;
      if(c > 2)
      {
        sumone -= (Puzz->matrix[l][c-3])%9;
        sumzer -= (Puzz->matrix[l][c-3] + 1)%2;
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
      sumone += (Puzz->matrix[l][c])%9;
      sumzer += (Puzz->matrix[l][c] + 1)%2;
      if(l > 2)
      {
        sumone -= (Puzz->matrix[l-3][c])%9;
        sumzer -= (Puzz->matrix[l-3][c] + 1)%2;
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
      sumone += (Puzz->matrix[l][c])%9;
      sumzer += (Puzz->matrix[l][c] + 1)%2;
    }
    if(sumone > Puzz->size  ||  sumzer > Puzz->size)
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
      sumone += (Puzz->matrix[l][c])%9;
      sumzer += (Puzz->matrix[l][c] + 1)%2;
    }
    if(sumone > Puzz->size  ||  sumzer > Puzz->size)
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
  for(*l = 0; *l < Puzz->size; *l = *l + 1)
  {
    for(*c = 0; *c < Puzz->size; *c = *c + 1)
    {
      if(Puzz->matrix[*l][*c] == 9)
      {
        if(*l + 1 < Puzz->size  &&  Puzz->matrix[(*l) + 1][*c] == 9)
        {
          *l = *l + 1;
          return;
        }
        else if(*c + 1 < Puzz->size  &&  Puzz->matrix[*l][(*c) + 1] == 9)
        {
          *c = *c + 1;
          return;
        }
        else
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
  Push('a', l, c, Puzz->matrix[l][c] = 0);
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
int CleanErrors(Puzzle *Puzz)
{
  Changes *changes = NULL;

    while(stack->top != NULL)
    {
      if(stack->top->type == 'a' && stack->top->value == 0)
      {
        stack->top->value = 1;
        Puzz->matrix[stack->top->line][stack->top->col] = 1;
        return 0;
      }
      else
      {
        changes = Pop();
        Puzz->matrix[changes->line][changes->col] = 9;
        free(changes);
      }
    }
    if(stack->top == NULL)
    {
      return 1;
    }
    return 0;
}
