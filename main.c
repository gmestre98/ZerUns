/******************************************************************************
 *
 * File Name: main.c
 * Author:    Gonçalo Mestre nº 87005  &  Guilherme Guerreiro nº87010
 * Revision:  26 Oct 2017
 *
 * NAME
 *  Main - Test algorithms to solve the puzzles
 *
 * DESCRIPTION
 *  Main file to call the algorithms to implement everything
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filehandling.h"
#include "Macros.h"
#include "Reader.h"


int main(int argc, char *argv[])
{
    char *token = NULL;
    char str[100];
    PuzzleNode *head = NULL;

    if(argc < 2)
    {
        CRASH
    }
    strcpy(str, argv[1]);
    token = strtok(str, ".");
    token = strtok(NULL, ".");
    if(strcmp(token, "puz") != 0)
    {
        CRASH
    }
    head = ReadData(argv[1]);
    PuzzlesReading(head);
    PrintShit(head);
    DeletePuzzleList(&head);
}
