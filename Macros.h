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
 *  File containing the important Macros definitions for the project
 *
 *****************************************************************************/

#ifndef MACRO
#define MACRO
#include <stdlib.h>
#include <stdio.h>
#define CRASH exit(0);
#define ZERO return 0;
#define ONE return 1;

typedef struct Puzzle{
    int size;
    int variant;
    int **matrix;
}Puzzle;

#endif
