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

  	if ( fscanf ( fp, "%d %d %d %d", &puzzle->content.size, &puzzle->content.line, &puzzle->content.col, &puzzle->content.binary ) == 4 )
  	{
  		puzzle->content.matrix = (int**) malloc(sizeof(int*)*puzzle->content.size);
  		if(puzzle->content.matrix==NULL)
  			exit( 0 );
  		for(l=0; l<puzzle->content.size; l++)
  		{
  			puzzle->content.matrix[l] = (int*) malloc(sizeof(int)*puzzle->content.size);
  			if(puzzle->content.matrix[l]==NULL)
  				exit( 0 );
  		}	
  	}
  	else
  		exit( 0 );
  	for(l=(puzzle->content.size-1); l >=0; l--)
  	{
  		for(c=0; c<puzzle->content.size; c++)
  		{
  			if(fscanf(fp, "%d", &puzzle->content.matrix[l][c])!=1)
  				exit( 0 );
  			if(puzzle->content.matrix[l][c]==0)
  				puzzle->content.matrix[l][c]=-1;
  		}
  	}
  	return;
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
void DeletePuzzleList(PuzzleNode *head)
{
	PuzzleNode *aux=head;
	int l;

	while(aux!=NULL)
	{
		aux=aux->next;
		for(l=0; l<head->content.size; l++)
			free(head->content.matrix[l]);
		free(head->content.matrix);
		free(head);
		head=aux;
	}
	head=NULL;
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
PuzzleNode* CreateNode(PuzzleNode *head)
{
	PuzzleNode *newnode, *aux;
	newnode= (PuzzleNode*) malloc(sizeof(Puzzle));
	if(newnode==NULL)
		exit( 0 );
	newnode->content.size=0;
	newnode->content.line=0;
	newnode->content.col=0;
	newnode->content.binary=0;
	newnode->content.matrix=NULL;
	newnode->content.result=0;
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