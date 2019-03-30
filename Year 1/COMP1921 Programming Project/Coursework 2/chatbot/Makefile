
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/chatbot

SRC= main.c input.c format.c validate.c myhashstring.c output/output.c output/do.c output/going.c output/how.c output/i.c output/my.c output/went.c output/what.c output/who.c output/why.c output/you.c

# generic build details

CC=      gcc
COPT=    -g
CFLAGS= -Wall

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(COPT) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE)

# clean up compilation

clean::
	rm -f *.o output/*.o

# dependencies

input.o: input.h

format.o: format.h

validate.o: validate.h

myhashstring.o: myhashstring.h

output.o: output/output.h output/do.c output/going.c output/how.c output/i.c output/my.c output/went.c output/what.c output/who.c output/why.c output/you.c
