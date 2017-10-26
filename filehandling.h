#ifndef MANAGE_FILES
#define MANAGE_FILES
#include "Macros.h"


FILE* OpenFile ( char *filename, char *mode );
void GetPuzzle(FILE *fp, PuzzleNode *puzzle);
PuzzleNode* CreateNode(PuzzleNode *head);
PuzzleNode* ReadData(char *filename);

