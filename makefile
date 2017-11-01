#
#  File name: makefile
#
#  Author: 2013 Fall Semester AED Team
#
#  Release date: 2013/10/04
#
#  Description: Makefile for the program lab03b
#
#  Usage:
#     1) To generate the executable file for the program lab03,
#       run
#         $ make
#
#     2) To clean all object files and the executable file of
#        lab03b, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall

LIBS = -lm -lSDL2 -lSDL2_ttf -lSDL2_image
#  Sources
SOURCES = main.c interface.c rules.c brain.c record.c game_manager.c

#  Objects
OBJECTS = main.o interface.o rules.o brain.o record.o game_manager.o

chess_ai: $(OBJECTS)
	gcc -o $@ $(OBJECTS) $(LIBS)

main.o: interface.h rules.h brain.h record.h game_manager.h


clean::
	rm -f *.o core a.out lab03b *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
