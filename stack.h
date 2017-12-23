/******************************************************************************
 *
 * File Name: Stack.h
 * Author:    Gonçalo Mestre nº 87005  &  Guilherme Guerreiro nº87010
 * Revision:  26 Oct 2017
 *
 * NAME
 *  Stack - Important definitions
 *
 * DESCRIPTION
 *  File containing the important definitions for the stack implementation
 *
 *****************************************************************************/


#ifndef STACK
#define STACK
#include <stdlib.h>
#include <stdio.h>
#include "Reader.h"


typedef struct _stack
{
	Item *top;
} Stack;

void InitStack();
void Push(Item*);
Item *Pop();
void FreeStack();
int isEmpty();
#endif