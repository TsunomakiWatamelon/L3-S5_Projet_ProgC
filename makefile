.PHONY: clean mrproper

CC = gcc
CFLAGS = -Wall -ansi -pedantic -Ofast
LFLAGS = -lMLV -lm
OBJ = obj/Terrain.o obj/Collision.o obj/Golem.o obj/Relic.o obj/Graphics.o obj/Player.o obj/MathTools.o obj/Main.o obj/Game.o obj/Score.o

bin/EXEC: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LFLAGS) -g

obj/%.o: ./src/%.c ./include/%.h
	$(CC) -o $@ -c -g $< $(CFLAGS)

clean:
	rm -rf obj/*.o

mrproper: clean
	rm -rf ./bin/EXEC