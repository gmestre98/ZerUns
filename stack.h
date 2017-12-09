#ifndef STACK
#define STACK
#include <stdlib.h>
#include <stdio.h>
#include "Reader.h"


typedef struct _stack
{
	Item *top;
	int size;
} Stack;

void InitStack();
void Push(Item*);
Item *Pop();
void FreeStack();
int isEmpty();
#endif