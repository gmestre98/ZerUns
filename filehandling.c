#include <stdlib.h>
#include <stdio.h>
#include "filehandling.h"
#include "Macros.h"

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
  FILE *f;
  f = fopen ( filename, mode );
  if ( f == NULL )
  {
  	exit ( 0 );
  }
  return (f);
}

/******************************************************************************
 * GetPuzzle()
 *
 * Arguments: fp - pointer to opened file
 *            puzzle - pointer to node which contains the struct that holds the puzzle info
 * Returns: nothing
 * Side-Effects: All the 0's read in the file matrix are changed into -1's in the node matrix.
 * If given invalid inputs, the program exits
 *
 * Description:
 *
 *****************************************************************************/
void GetPuzzle(FILE *fp, PuzzleNode *puzzle)
{
	int l, c;

  	if ( fscanf ( fp, "%d %d %d %d", puzzle->size, puzzle->line, puzzle->col, puzzle->binary ) == 4 )
  	{
  		puzzle->matrix = (int**) malloc(sizeof(int*)*puzzle->size);
  		if(puzzle->matrix==NULL)
  			exit( 0 );
  		for(l=0; l<puzzle->size; l++)
  		{
  			puzzle->matrix[l] = (int*) malloc(sizeof(int)*puzzle->size);
  			if(puzzle->matrix[l]==NULL)
  				exit( 0 );
  		}	
  	}
  	else
  		exit( 0 );
  	for(l=(puzzle->size-1); l >=0; l--)
  	{
  		for(c=0; c<puzzle->size; c++)
  		{
  			if(fscanf(fp, "%d", puzzle->matrix[l][c])!=1)
  				exit( 0 );
  			if(matrix[l][c]==0)
  				matrix[l][c]=-1;
  		}
  	}
  	return;
}

/******************************************************************************
 * CreateNode()
 *
 * Arguments: head - pointer to the first node
 * Returns: pointer to new node
 * Side-Effects: Allocs mem to another node and inserts it into the bottom of the list.
 *
 * Description:
 *
 *****************************************************************************/
PuzzleNode* CreateNode(PuzzleNode *head);
{
	PuzzleNode *newnode, *aux;
	newnode= (PuzzleNode*) malloc(sizeof(Puzzle));
	if(newnode==NULL)
		exit( 0 );
	newnode->size=0;
	newnode->line=0;
	newnode->col=0;
	newnode->binary=0;
	newnode->matrix=NULL;
	newnode->result=0;
	if(head==NULL)
		head=newnode;
	else
	{
		aux=head;
		while(aux->next!=NULL)
			aux=aux->next;
		aux->next=newnode;
	}
	return(newnode);
}

/******************************************************************************
 * ReadData()
 *
 * Arguments: filename - name of the file containing the puzzles
 * Returns: pointer to the puzzle listing
 * Side-Effects: none
 *
 * Description: Creates a list with all puzzles given in the file. Returns the pointer to that list
 *
 *****************************************************************************/
PuzzleNode* ReadData(char *filename)
{
	FILE *fp=NULL;
	PuzzleNode *head=NULL;
	fp=OpenFile(filename, "r");

	while(!feof(fp))
		GetPuzzle(fp, CreateNode(head));
	fclose(fp);
	return(head);
}