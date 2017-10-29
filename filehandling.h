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


FILE* OpenFile ( char *filename, char *mode );
int GetPuzzle(FILE *fp,PuzzleNode **head, PuzzleNode *puzzle);
PuzzleNode* CreateNode();
PuzzleNode* ReadData(char *filename);
void DeletePuzzleList(PuzzleNode **head);
void AddNode(PuzzleNode **head, PuzzleNode *node);
void SolutionWriter(PuzzleNode *, char *);

#endif
