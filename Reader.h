#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Macros.h"

typedef struct _changes{
  char type;
  int line;
  int col;
  int value;
  struct _changes *next;
}Changes;

typedef struct _stack{
  Changes *top;
}Stack;

int Solve(Puzzle *);
int Solver1(Puzzle*, int, int, int, int);
Stack *InitStack();
void Push(char, int, int, int);
Changes* Pop();
void FreeMaStack();
int FillLine(Puzzle *);
int FillCol(Puzzle *);
int FillSumsLine(Puzzle *);
int FillSumsCols(Puzzle *);
void FindEmpty(Puzzle *, int *, int *);
void FillRandom(Puzzle *);
int WrongPuzz(Puzzle *);
int WrongLine(Puzzle *);
int WrongCol(Puzzle *);
int WrongSum(Puzzle *);
int CleanErrors(Puzzle *);
int FullPuzz(Puzzle *);
int Solver2(Puzzle*, int, int, int, int);
int WrongPuzz2(Puzzle *);
int EqualLine(Puzzle *);
int EqualCol(Puzzle *);
