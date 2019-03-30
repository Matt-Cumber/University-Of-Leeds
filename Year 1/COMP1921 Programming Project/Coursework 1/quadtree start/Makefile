
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/main

SRC= main.c

# generic build details

CC=      cc
COPT=    -g
CFLAGS= -lm -Wall
HEADS= treeStructure.h buildTree.h writeTree.h destroyTree.h tests.h valueTree.h

# compile to  object code

OBJ= $(SRC:.c=.o) buildTree.o writeTree.o destroyTree.o valueTree.o tests.o

.c.o:
	$(CC) $(COPT) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE)

# clean up compilation

clean::
	rm -f $(OBJ) $(EXE) *.o

# dependencies
val: $(OBJ)
	 valgrind --tool=memcheck --leak-check=full --quiet -v ./main

buildTree.o: treeStructure.h buildTree.h

writeTree.o: treeStructure.h writeTree.h

destroyTree.o: treeStructure.h destroyTree.h

tests.o: $(HEADS)

valueTree.o: treeStructure.h valueTree.h
