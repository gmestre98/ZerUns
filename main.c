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
    char str[100] = {0};

    if(argc < 2)
    {
        CRASH
    }
    strcpy(str, argv[1]);
    token = strtok(str, ".");
    while(token != NULL  &&  strcmp(token, "puz") != 0)
    {
      token = strtok(NULL, ".");
    }
    if(token == NULL)
    {
        CRASH
    }

    ReadData(argv[1]);
    exit(0);
}
