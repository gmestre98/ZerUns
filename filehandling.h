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
 *  File containing the declaration of fuctions for the handling of all files
 *
 *****************************************************************************/
#ifndef MANAGE_FILES
#define MANAGE_FILES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Macros.h"
#include "Reader.h"


FILE* OpenFile (char*, char*);
int GetPuzzle(FILE*, Puzzle*);
void ResetPuzzle(Puzzle*);
void ReadData(char *filename);
void SolutionWriter(Puzzle*, char *, int);

#endif
