#ifndef FRONTEND_H
#define FRONTEND_H

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "lib_specification.h"

#define SPACE 1
#define GAME_W 22
#define INDICATORS_W 22

#define HEIGHT 22

#define WIDTH GAME_W + INDICATORS_W + 2 * SPACE

#define WIN_NEXT_H 8
#define WIN_W INDICATORS_W - 4

#define WIN_I_H 3

#define WIN_SPACE 2
#define WIN_INTERVAL WIN_I_H
#define WIN_NEXT_INTERVAL WIN_NEXT_H

#define ESCAPE 27
#define ENTER_KEY 10

void print_rectangle(int x_begin, int y_begin, int vertical_coords,
                     int horizontal_coords);

void print_starting_message(WINDOW *message);
void print_pause_message(WINDOW *message);
void print_game_over_message(WINDOW *message);

void print_stats(WINDOW *next, WINDOW *score, GameInfo_t game);
void print_field(WINDOW *board, GameInfo_t game);
void print_game(WINDOW *board, WINDOW *next, WINDOW *score, WINDOW *message);

void print_pause(WINDOW *message);
void print_start(WINDOW *messgae);
void print_game_over(WINDOW *message);

void window_init();

bool get_action(UserAction_t *key);

#endif  // FRONTEND_H