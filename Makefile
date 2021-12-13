CC = g++
OBJ = main.o
HEADER = header.h
CFLAGS = -c -Wall 

hello: $(OBJ)
    $(CC) $(OBJ) -o $@

main.o: src/main.cpp $(HEADER)
    $(CC) $(CFLAGS) $< -o $@

clean:
    rm -rf *o hello