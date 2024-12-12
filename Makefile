.PHONY: rebuild clean style

CC := gcc
CFLAGS := -I src/brick_game/tetris -I src/gui/cli -I . -std=c11 -Wall -Werror -Wpedantic

FRONT = src/gui/cli/frontend.c
BACK = $(wildcard $(LIB_SRC_DIR)/*.c)

LIB_SRC_DIR = src/brick_game/tetris
LIB_OBJ_FILES = $(patsubst $(LIB_SRC_DIR)/%.c, obj/%.o, $(BACK))

rebuild: clean tetris

tetris: s21_tetris.a
	$(CC) $(CFLAGS) tetris.c ${FRONT} obj/s21_tetris.a -lncurses -o tetris

s21_tetris.a: $(LIB_OBJ_FILES)
	ar rc obj/s21_tetris.a obj/*.o
	ranlib obj/s21_tetris.a

clean:
	rm -rf obj/*.o tetris a.out  obj/*.a

style:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n src/*/*/*.h src/*/*/*.c *.c *.h
	clang-format -i src/*/*/*.h src/*/*/*.c *.c *.h
	rm -rf .clang-format

obj/%.o: $(LIB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# TODO: dvi target that creates documentation using Doxygen
# TODO: dist target that creates zip with all files to build a game
# TODO: install and uninstall targets 