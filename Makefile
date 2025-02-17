.PHONY: rebuild clean style clean_record

CC = gcc
CFLAGS = -I src/brick_game/tetris -I src/gui/cli -std=c11 -Wall -Werror -Wpedantic

FRONT = src/gui/cli/frontend.c
BACK = $(wildcard $(LIB_SRC_DIR)/*.c)

LIB_SRC_DIR = src/brick_game/tetris
LIB_OBJ_FILES = $(patsubst $(LIB_SRC_DIR)/%.c, obj/%.o, $(BACK))

LDFLAGS = -lcheck -lsubunit -lm -lrt -lpthread

INSTALL_DIR = ../Brick_game

all: rebuild

rebuild: clean tetris

tetris: s21_tetris.a
	$(CC) $(CFLAGS) tetris.c ${FRONT} obj/s21_tetris.a -lncurses -lm -o tetris

s21_tetris.a: $(LIB_OBJ_FILES)
	ar rc obj/s21_tetris.a obj/*.o
	ranlib obj/s21_tetris.a

clean:
	rm -rf obj/*.o tetris a.out obj/*.a  obj/*.c docs

clean_record:
	rm -rf /tmp/.s21

obj/%.o: $(LIB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -g -c $< -o $@

dist: clean
	tar -czvf s21_tetris.tar.gz src tetris.c Doxyfile Makefile

# Can be used like this: 'make install DESTDIR=xyz', where xyz - path where you want your game installed
install: clean tetris
	if [ -z "$(DESTDIR)" ]; then \
		mkdir $(INSTALL_DIR); \
		mv tetris $(INSTALL_DIR)/.; \
		echo "Game installed to $(INSTALL_DIR)"; \
	else \
		mkdir $(DESTDIR); \
		mv tetris $(DESTDIR)/.; \
		echo "Game installed to $(DESTDIR)"; \
	fi
	
uninstall: clean_record
	if [ -z "$(DESTDIR)" ]; then \
		rm -rf $(INSTALL_DIR); \
	else \
		rm -rf $(DESTDIR); \
	fi
	