CC := gcc
CFLAGS := -I src/brick_game/tetris -I src/gui/cli -std=c99 -Wall -Werror -Wpedantic
OBJS := obj/frontend.o obj/tetris.o obj/fsm.o

FRONT = src/gui/cli/frontend.c
BACK = src/brick_game/tetris/tetris.c src/brick_game/tetris/fsm.c

rebuild: clean tetris

tetris: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

obj/tetris.o:
	$(CC) $(CFLAGS) -c src/brick_game/tetris/tetris.c -o $@

obj/fsm.o:
	$(CC) $(CFLAGS) -c src/brick_game/tetris/fsm.c -o $@

obj/frontend.o:
	$(CC) $(CFLAGS) -c ${FRONT} -o obj/frontend.o

clean:
	rm -rf obj/*.o tetris