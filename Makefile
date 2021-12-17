CC = gcc
OBJ = main.o
HEADER = *.h
CFLAGS = -Wall -lSDL

hello: $(OBJ)
<tab>$(CC) $(OBJ) -o $@

main.o: src/main.cpp $(HEADER)
$(CC) $(CFLAGS) $< -o $@

clean:
rm -rf *o hello