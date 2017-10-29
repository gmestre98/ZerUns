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
#include <string.h>
#include "filehandling.h"

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
FILE* OpenFile(char *filename, char *mode)
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
int GetPuzzle(FILE *fp, Puzzle *Puzzle)
{
	int l = 0;
  int c = 0;

  if ( fscanf ( fp, "%d %d %d %d", &Puzzle->size, &Puzzle->line, &Puzzle->col,
    &Puzzle->binary ) == 4)
  {
  	Puzzle->matrix = (int**)malloc(sizeof(int*)*(Puzzle->size));
		if(Puzzle->matrix == NULL)
    {
      CRASH
    }
  	for(l=0; l < Puzzle->size; l++)
  	{
  		Puzzle->matrix[l] = (int*)malloc(sizeof(int)*Puzzle->size);
  		if(Puzzle->matrix[l]==NULL)
      {
        CRASH
      }
  	}
  }
  else if(feof(fp))
  {
    free(Puzzle);
  	return 0;
  }
  else
  {
    CRASH
  }
	for(l = (Puzzle->size-1); l >=0; l--)
	{
		for(c = 0; c < Puzzle->size; c++)
		{
			if(fscanf(fp, "%d", &Puzzle->matrix[l][c])!=1)
      {
        CRASH
      }
		}
	}
	return 1;
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
void ResetPuzzle(Puzzle* Puzzle)
{
  Puzzle->size = 0;
  Puzzle->line = -1;
  Puzzle->col = -1;
  Puzzle->binary = -1;
  Puzzle->result = 0;
  Puzzle->matrix = NULL;
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
void ReadData(char *filename)
{
  int i = 0;
  int l = 0;
  FILE* fp = NULL;
	Puzzle* Puzz = NULL;

  Puzz = (Puzzle*)malloc(sizeof(Puzzle));
  if(Puzz == NULL)
  {
    CRASH
  }

	fp = OpenFile(filename, "r");
  ResetPuzzle(Puzz);
	while(GetPuzzle(fp, Puzz))
  {
    i++;
    PuzzlesReading(Puzz);
    SolutionWriter(Puzz, filename, i);
    for(l=0; l < Puzz->size; l++)
    {
      free(Puzz->matrix[l]);
    }
    free(Puzz->matrix);
    ResetPuzzle(Puzz);
  }
	fclose(fp);
}


/******************************************************************************
 * SolutionWriter()
 *
 * Arguments: Head of the puzzles list, name of the puzzles file
 * Returns: none
 * Side-Effects: none
 *
 * Description: Creates a file where the puzzles solutions are written
 *
 *****************************************************************************/
void SolutionWriter(Puzzle* Puzz, char *str, int Puzzleref)
{
  FILE *fp = NULL;
  char *token = NULL;
  char extension[] = ".sol";

  token = strtok(str, ".");
  strcat(token, extension);
  fp = OpenFile(token, "a");
  if(fp == NULL)
  {
    exit(0);
  }
  fprintf(fp, "Puzzle %d:\n", Puzzleref);
  fprintf(fp, "%d ", Puzz->size);
  fprintf(fp, "%d ", Puzz->line);
  fprintf(fp, "%d ", Puzz->col);
  fprintf(fp, "%d ", Puzz->binary);
  fprintf(fp, "%d\n\n", Puzz->result);
  fclose(fp);
}





/*
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
*/
