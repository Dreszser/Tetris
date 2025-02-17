#ifndef SCORE_AND_TIME_H_
#define SCORE_AND_TIME_H_

/**
 * @file score_and_time.h
 *
 * @brief Implementation of functions that work with scores, field blocks and
 * time intervals between shifting.
 */

/**
 * @brief POSIX source to compile clock_gettime function with -std=c11 flag.
 * Without it or with -std=gnu11 everything compiles fine.
 */
#define _POSIX_C_SOURCE 200809L

#include <math.h>
#include <stdio.h>
#include <time.h>

#include "def.h"

/**
 * @brief Stores the piece on the field.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 *
 * @return 1 if successful, 0 if the piece is higher than the top
 * border(game over).
 */
bool store_piece(Params_t *prms);

/**
 * @brief Deletes all filled lines.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void delete_possible_lines(Params_t *prms);

/**
 * @brief Deletes line specified by v_coord.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 * @param v_coord Number of row in the game field matrix to be deleted.
 */
void clear_line(Params_t *prms, int v_coord);

/**
 * @brief Get score based on number of deleted lines.
 *
 * @param lines Number of deleted lines.
 *
 * @return 100 for 1 line, 300 for 2, 700 for 3 and 1500
 * for 4 lines.
 */
int get_score(int lines);

/**
 * @brief Update level based on the current score.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void update_level(Params_t *prms);

/**
 * @brief Calculate game tick time(interval between downshifts) based on the
 * current level.
 *
 * @return Unsigned number in ms(1000 on level 0).
 */
unsigned calculate_tick_interval();

/**
 * @brief Calculate current monotonic time in ms.
 *
 * Represents the time monotonically increased since the system boot.
 *
 * @return Unsigned number in ms.
 */
unsigned long get_current_time_in_ms();

/**
 * @brief Gets saved high score.
 *
 * Opens a save file and writes its contents to Params_t.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void get_high_score(Params_t *prms);

/**
 * @brief Saves new high score.
 *
 * Creates or opens already existing save file and writes new high score into
 * it.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void save_high_score(Params_t *prms);

#endif  // SCORE_AND_TIME_H_
