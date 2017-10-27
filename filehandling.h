#ifndef MANAGE_FILES
#define MANAGE_FILES
#include "Macros.h"


FILE* OpenFile ( char *filename, char *mode );
int GetPuzzle(FILE *fp,PuzzleNode **head, PuzzleNode *puzzle);
PuzzleNode* CreateNode();
PuzzleNode* ReadData(char *filename);
void DeletePuzzleList(PuzzleNode **head);
void AddNode(PuzzleNode **head, PuzzleNode *node);

#endif