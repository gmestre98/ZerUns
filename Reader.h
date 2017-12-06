/******************************************************************************
 *
 * File Name: Reader.h
 * Author:    Gonçalo Mestre nº 87005  &  Guilherme Guerreiro nº87010
 * Revision:  26 Oct 2017
 *
 * NAME
 *  Reader - Function definitios
 *
 * DESCRIPTION
 *  File containing the declaration of fuctions for the solving processes of the puzzles
 *
 *****************************************************************************/
#ifndef READER
#define READER
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Macros.h"


int Solve(Puzzle *);
int Solver(Puzzle*, int (*Verification) (Puzzle*));
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
int WrongPuzz2(Puzzle *);
int EqualLine(Puzzle *);
int EqualCol(Puzzle *);

#endif
