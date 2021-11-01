#
# File: Makefile
# Creator: George Ferguson
# Created: Thu Jun 30 11:00:49 2016
# Time-stamp: <Tue Aug  8 10:34:37 EDT 2017 ferguson>
#

SRC = main.c cdh.c cp.c csg.c snap.c
OBJ = $(SRC:.c=.o) # replace .c with .o
PROGRAMS = main

CFLAGS = -g -std=c99 -Wall -Werror

programs: $(OBJ)
	gcc $(OBJ) -o $(PROGRAMS)

%.o: %.c
	gcc -c $(<) $(CFLAGS)

clean:
	-rm $(PROGRAMS) *.o
