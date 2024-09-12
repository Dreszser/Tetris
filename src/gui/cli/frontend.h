#ifndef FRONTEND_H
#define FRONTEND_H

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "fsm.h"

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

void print_rectangle(int x_begin, int y_begin, int x, int y);
void print_starting_message();
void clear_field();

void print_stats(GameInfo_t);
void print_field(GameInfo_t);
void print_piece(PlayerPos_t);

void window_init();

#endif  // FRONTEND_H