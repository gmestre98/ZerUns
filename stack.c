#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


Stack *stack = NULL;


void InitStack()
{
  stack = malloc(sizeof(Stack));
  if(stack == NULL)
  	CRASH
  stack->top = NULL;
  stack->size = 0;
}

void Push(Item *item)
{
	item->next = stack->top;
	stack->top = item;
}


Item *Pop()
{
	Item *ret = stack->top;
	if(isEmpty() != 1)
  {
    stack->top = stack->top->next;
  }
	return ret;
}

void FreeStack()
{
	Item *aux;

	while(isEmpty() != 1)
	{
		aux = stack->top->next;
		free(stack->top);
		stack->top = aux;
	}
	free(stack);
}

int isEmpty()
{
	if(stack->top == NULL)
		return 1;
	return 0;
}