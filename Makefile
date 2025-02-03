.PHONY: rebuild clean style clean_record

CC = gcc
CFLAGS = -I src/brick_game/tetris -I src/gui/cli -std=c11 -Wall -Werror -Wpedantic

FRONT = src/gui/cli/frontend.c
BACK = $(wildcard $(LIB_SRC_DIR)/*.c)

LIB_SRC_DIR = src/brick_game/tetris
LIB_OBJ_FILES = $(patsubst $(LIB_SRC_DIR)/%.c, obj/%.o, $(BACK))

LIB_OBJ_TEST_FILES = $(patsubst $(LIB_SRC_DIR)/%.c, $(LIB_SRC_DIR)/tests/%.o, $(BACK))
CHECK_FILES = $(wildcard $(LIB_SRC_DIR)/tests/*.check)

LDFLAGS = -lcheck -lsubunit -lm -lrt -lpthread

INSTALL_DIR = ../Brick_game

all: rebuild

rebuild: clean tetris

tetris: s21_tetris.a
	$(CC) $(CFLAGS) tetris.c ${FRONT} obj/s21_tetris.a -lncurses -lm -o tetris

s21_tetris.a: $(LIB_OBJ_FILES)
	ar rc obj/s21_tetris.a obj/*.o
	ranlib obj/s21_tetris.a

gcov_s21_tetris.a: $(LIB_OBJ_TEST_FILES)
	ar rc obj/gcov_s21_tetris.a $(LIB_SRC_DIR)/tests/*.o
	ranlib obj/gcov_s21_tetris.a
	rm -rf $(LIB_SRC_DIR)/tests/*.o 

clean:
	rm -rf obj/*.o tetris a.out obj/*.a  obj/*.c docs test report
	rm -rf $(LIB_SRC_DIR)/tests/*.gcda $(LIB_SRC_DIR)/tests/*.gcno
	rm -rf s21_tetris.tar.gz

clean_record:
	rm -rf /tmp/.s21

style:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n src/*/*/*.h src/*/*/*.c *.c
	clang-format -i src/*/*/*.h src/*/*/*.c *.c
	rm -rf .clang-format

obj/%.o: $(LIB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -g -c $< -o $@

src/brick_game/tetris/tests/%.o: $(LIB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) --coverage -c  $< -o $@

test: clean s21_tetris.a test.o 
	$(CC) $(CFLAGS) obj/test.o obj/s21_tetris.a -o test $(LDFLAGS)
	./test

test.o:
	checkmk clean_mode=1 $(CHECK_FILES) > obj/test.c
	$(CC) $(CFLAGS) -g -c obj/test.c -o obj/test.o

vg:
	valgrind --leak-check=full --track-origins=yes ./test

gcov_report: clean clean_record test.o gcov_s21_tetris.a  
	$(CC) $(CFLAGS) --coverage obj/test.o obj/gcov_s21_tetris.a -o test $(LDFLAGS)
	./test
	mkdir -p report
	gcovr --html-details report/index.html --html-medium-threshold 80 --html-high-threshold 95 --html-title "s21_tetris coverage report"

dvi:
	rm -rf docs
	doxygen -q Doxyfile
	open docs/html/index.html

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
	