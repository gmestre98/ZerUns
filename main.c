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

int main(int argc, char *argv[])
{
    char *token = NULL;
    PuzzleNode *head = NULL;

    if(argc < 2)
    {
        PRINTERROR("Insuficient number of arguments!\n\n")
        CRASH
    }
    token = strtok(argv[1], ".");
    token = strtok(NULL, ".");
    if(strcmp(token, "puz") == 0)
    {
        PRINTERROR("Incorrect puzzle extension!\n\n");
        CRASH
    }
}
