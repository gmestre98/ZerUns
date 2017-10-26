#include <stdlib.h>
#include <stdio.h>
#define PRINTERROR(...) ( fprintf(stderr,__VA_ARGS__));
#define CRASH exit(0);

typedef struct Puzzle{
	int size;
	int line;
	int col;
	int binary;
	int **matrix;
	int result;
} Puzzle;

typedef struct PuzzleNode{
	struct Puzzle content;
	struct Puzzle *next;
} PuzzleNode;
