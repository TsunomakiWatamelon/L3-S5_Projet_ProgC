CC = gcc
CFLAGS = -Wall -ansi -pedantic
LFLAGS = -lMLV
OBJ = Terrain.o

EXEC: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@ -g

%.o: ./src/%.c ./include/%.h
	$(CC) -o $@ -c -g $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ./EXEC