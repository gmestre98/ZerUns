/******************************************************************************
 *
 * File Name: Stack.c
 * Author:    Gonçalo Mestre nº 87005  &  Guilherme Guerreiro nº87010
 * Revision:  26 Oct 2017
 *
 * NAME
 *  Stack
 *
 * DESCRIPTION
 *  File containing the stack implementation fucntions
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


Stack *stack = NULL;

/******************************************************************************
 * InitStack()
 *
 * Arguments: none
 * Returns: none
 * Side-Effects: Initializes the stack pointer
 *
 * Description: Creates a stack
 *
 *****************************************************************************/
void InitStack()
{
  stack = malloc(sizeof(Stack));
  if(stack == NULL)
  	CRASH
  stack->top = NULL;
}

/******************************************************************************
 * Push()
 *
 * Arguments: ITEM
 * Returns: none
 * Side-Effects: Inserts item in stack
 *
 * Description: Push function of a stack
 *
 *****************************************************************************/
void Push(Item *item)
{
	item->next = stack->top;
	stack->top = item;
}

/******************************************************************************
 * Pop()
 *
 * Arguments: none
 * Returns: Item
 * Side-Effects: Removes item from stack
 *
 * Description: Pop function of a stack
 *
 *****************************************************************************/
Item *Pop()
{
	Item *ret = stack->top;
	if(isEmpty() != 1){
    stack->top = stack->top->next;
  }
	return ret;
}


/******************************************************************************
 * FreeStack()
 *
 * Arguments: none
 * Returns: none
 * Side-Effects: free's all of the stack, including stack struct
 *
 * Description:
 *
 *****************************************************************************/
void FreeStack()
{
	Item *aux;

	while(isEmpty() != 1){
		aux = stack->top->next;
		free(stack->top);
		stack->top = aux;
	}
	free(stack);
}

/******************************************************************************
 * isEmpty()
 *
 * Arguments: none
 * Returns: 1- stack is empty 0-is not
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/
int isEmpty()
{
	if(stack->top == NULL)
		ONE
	ZERO
}
