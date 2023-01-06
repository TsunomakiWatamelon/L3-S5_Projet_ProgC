CC = gcc
CFLAGS = -Wall -ansi -pedantic
LFLAGS = -lMLV
OBJ = obj/Terrain.o obj/Test.o obj/Collision.o

bin/EXEC: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) -g

obj/%.o: ./src/%.c ./include/%.h
	$(CC) -o $@ -c -g $< $(CFLAGS)

clean:
	rm -rf obj/*.o

mrproper: clean
	rm -rf ./EXEC