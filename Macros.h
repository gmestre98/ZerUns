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

typedef struct Puzzle{
    int size;
    int line;
    int col;
    int binary;
    int **matrix;
    int result;
}Puzzle;

typedef struct PuzzleNode{
    struct Puzzle content;
    struct PuzzleNode* next;
}PuzzleNode;
#endif
