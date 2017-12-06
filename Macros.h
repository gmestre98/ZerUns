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
 *  File containing the important Macros definitions and Typedefs for the project
 *
 *****************************************************************************/

#ifndef MACRO
#define MACRO
#include <stdlib.h>
#include <stdio.h>
#define CRASH exit(0);

typedef struct Puzzle{
    int size;
    int variant;
    int **matrix;
}Puzzle;

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
#endif
