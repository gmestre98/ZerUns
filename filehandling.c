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
 *  File containing the handling of all files
 *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "filehandling.h"
#include "Macros.h"
#include "Reader.h"

/******************************************************************************
 * OpenFile()
 *
 * Arguments: filename - pointer to string holding name of file to open
 *            mode - pointer to string holding mode to use for opening file
 * Returns: pointer to opened file
 * Side-Effects: exits if given file that cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/
FILE* OpenFile ( char *filename, char *mode )
{
  FILE *f = NULL;
  f = fopen (filename, mode);
  if ( f == NULL )
  {
  	CRASH
  }
  return (f);
}

/******************************************************************************
 * GetPuzzle()
 *
 * Arguments: fp - pointer to opened file
 *            puzzle - pointer to node which contains the struct that holds the
 *                     puzzle info
 * Returns: nothing
 * Side-Effects: All the 0's read in the file matrix are changed into -1's in
 *               the node matrix.
 * If given invalid inputs, the program exits
 *
 * Description:
 *
 *****************************************************************************/
int GetPuzzle(FILE *fp, PuzzleNode **head, PuzzleNode *puzzle)
{
	int l = 0;
    int c = 0;

  	if ( fscanf ( fp, "%d %d %d %d", &puzzle->content.size,
    &puzzle->content.line, &puzzle->content.col, &puzzle->content.binary ) == 4)
  	{
  		puzzle->content.matrix = (int**)malloc(sizeof(int*)*(puzzle->content.size));
  		if(puzzle->content.matrix == NULL)
      {
        CRASH
      }
  		for(l=0; l < puzzle->content.size; l++)
  		{
  			puzzle->content.matrix[l] = (int*)malloc(sizeof(int)*puzzle->content.size);
  			if(puzzle->content.matrix[l]==NULL)
        {
          CRASH
        }
  		}
  	}
  	else if(feof(fp))
  	{
  		free(puzzle);
  		return 0;
  	}
  	else
    {
      CRASH
    }

  	for(l = (puzzle->content.size-1); l >=0; l--)
  	{
  		for(c = 0; c < puzzle->content.size; c++)
  		{
  			if(fscanf(fp, "%d", &puzzle->content.matrix[l][c])!=1)
        {
          CRASH
        }
  		}
  	}
   	AddNode(head, puzzle);
		return 1;
}
/******************************************************************************
 * DeletePuzzleList()
 *
 * Arguments: head - pointer to the first node
 * Returns: nothing
 * Side-Effects: Frees all nodes from the list. Sets head pointer to NULL
 *
 * Description:
 *
 *****************************************************************************/
void DeletePuzzleList(PuzzleNode **head)
{
	PuzzleNode *aux = *head;
	int l;

	while(*head != NULL)
	{
		aux = (*head)->next;
		for(l = 0; l < (*head)->content.size; l++)
    {
			free((*head)->content.matrix[l]);
    }
		free((*head)->content.matrix);
		free(*head);
		*head = aux;
	}
	return;
}
/******************************************************************************
 * CreateNode()
 *
 * Arguments: none
 * Returns: pointer to new node
 * Side-Effects: Allocs mem to one puzzlenode struct and initializes it
 *
 * Description:
 *
 *****************************************************************************/
PuzzleNode* CreateNode()
{
	PuzzleNode *newnode;
	newnode = (PuzzleNode*)malloc(sizeof(PuzzleNode));
	if(newnode == NULL)
  {
    CRASH
  }
	newnode->content.size = 0;
	newnode->content.line = 0;
	newnode->content.col = 0;
	newnode->content.binary = 0;
	newnode->content.result = 0;
	newnode->content.matrix = NULL;
	newnode->next = NULL;
	return(newnode);
}

/******************************************************************************
 * CreateNode()
 *
 * Arguments: head - pointer to the first node
 * Returns: pointer to new node
 * Side-Effects: Adds node to the bottom of puzzles list
 *
 * Description:
 *
 *****************************************************************************/
void AddNode(PuzzleNode **head, PuzzleNode *node)
{
	PuzzleNode *aux = *head;

	if(node == NULL)
  {
    CRASH
  }
	if(*head == NULL)
	{
    *head = node;
  }
  else
	{
		while(aux->next != NULL)
		{
      aux = aux->next;
    }
    aux->next = node;
	}
	return;
}

/******************************************************************************
 * ReadData()
 *
 * Arguments: filename - name of the file containing the puzzles
 * Returns: pointer to the puzzle listing
 * Side-Effects: none
 *
 * Description: Creates a list with all puzzles given in the file.
 *              Returns the pointer to that list
 *
 *****************************************************************************/
PuzzleNode* ReadData(char *filename)
{
	FILE *fp = NULL;
	PuzzleNode *head = NULL;

	fp = OpenFile(filename, "r");
	while(GetPuzzle(fp, &head, CreateNode()));
	fclose(fp);
	return(head);
}


void PrintShit(PuzzleNode *head)
{
  int i, j;
  while(head != NULL)
  {
    printf("%d ", head->content.size);
    printf("%d ", head->content.line);
    printf("%d ", head->content.col);
    printf("%d\n", head->content.binary);
    for(i=head->content.size - 1 ; i >= 0; i--)
    {
      for(j=0; j < head->content.size; j++)
      {
        printf("%d", head->content.matrix[i][j]);
      }
      printf("\n");
    }
    printf("\n%d\n\n\n", head->content.result);
    head = head->next;
  }
}
