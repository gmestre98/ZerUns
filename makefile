#
#  File name: makefile
#
#  Author: Gonçalo Mestre & Guilherme Guerreiro
#
#  Description: Makefile for the our intermidita AED project
#
#  Usage:
#     1) To generate the executable file for the program, run
#         $ make ZerUns
#
#     2) To clean all object files and the executable file, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -O3

#  Sources
SOURCES =  main.c filehandling.c Reader.c

#  Objects
OBJECTS = main.o filehandling.o Reader.o

zeruns: $(OBJECTS)
	gcc -g -o $@ $(OBJECTS)

filehandling.o: filehandling.h filehandling.c
Reader.o: Reader.h Reader.c

clean::
	rm -f *.o core a.out zeruns *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
