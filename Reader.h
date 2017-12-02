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

int Solver1(Puzzle*, int, int, int, int);
Stack *InitStack();
int FillLine(Puzzle *);
int FillCol(Puzzle *);
int FillSumsLine(Puzzle *);
int FillSumsCols(Puzzle *);
void FillRandom(Puzzle *);
int WrongPuzz(Puzzle *);
int WrongLine(Puzzle *);
int WrongCol(Puzzle *);
int WrongSum(Puzzle *);
int CleanErrors(Puzzle *);
int FullPuzz(Puzzle *);
int Solver2(Puzzle*, int, int, int, int);
