#ifndef MANAGE_FILES
#define MANAGE_FILES
#include "Macros.h"


FILE *OpenFile ( char *filename, char *mode );
int ReadValue (FILE *fp);
void ReadData(char *filename, PuzzleNode *head);
PuzzleNode *CreateNode();

