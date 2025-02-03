#ifndef BACKEND_H_
#define BACKEND_H_

/**
 * @file backend.h
 *
 * @brief Declaration of functions that allocate or free memory, initialize
 * structures, check collision.
 */

#include <stdlib.h>
#include <time.h>

#include "def.h"

/**
 * @brief Pixel in the middle of the game screen.
 *
 * Used for initializing starting coordinates of the piece.
 */
#define SPAWN_PIXEL 12

/**
 * @brief Initialize all valuable information for new game.
 *
 * @param parameters Pointer to structure that contains all information used in
 * game logic.
 */
void initialize_game(Params_t *parameters);

/**
 * @brief Initialize game field.
 *
 * Allocate memory for game field(20*10 matrix) and initialize it with zeros.
 *
 * @param game Pointer to structure that stores game field matrix.
 */
void init_field(GameInfo_t *game);

/**
 * @brief Initialize next piece.
 *
 * Randomly generate block type and rotation position, initialize starting
 * coordinates, on first run allocates memory.
 *
 * @param prms Pointer to structure with all information used in game logic.
 */
void init_next_piece(Params_t *prms);

/**
 * @brief Fill 5x5 matrix according to block type and rotation of next piece.
 *
 * @param prms Pointer to structure with all information used in game logic.
 */
void get_next(Params_t *prms);

/**
 * @brief Transfer next piece to current.
 */
void transfer_next_piece();

/**
 * @brief Clear field matrix.
 *
 * @param prms Pointer to structure with all information used in game logic.
 */
void clear_field(Params_t *prms);

/**
 * @brief Clear next piece matrix.
 *
 * @param game Pointer to structure that stores next piece matrix.
 */
void clear_next(GameInfo_t *game);

/**
 * @brief Free memory for next piece matrix.
 *
 * @param game Pointer to structure that stores next piece matrix.
 */
void free_next(GameInfo_t *game);

/**
 * @brief Free memory for game field matrix.
 *
 * @param game Pointer to structure that stores game field matrix.
 */
void free_field(GameInfo_t *game);

/**
 * @brief Get access to Params_t struct with static fields.
 *
 * Initializes static fields for Params_t struct and returns a copy for further
 * use in game logic.
 *
 * @return Copy of Params_t with static fields.
 */
Params_t get_params();

/**
 * @brief Shifts falling piece one row down.
 */
void down_shift();

/**
 * @brief Checks for collisions on the field.
 *
 * @param piece Struct that stores all information about current falling piece.
 *
 * @return True if no collision is detected.
 */
bool check_collision(BrickInfo_t piece);

/**
 * @brief Checks for collisions with game borders.
 *
 * @param y Vertical coordinates of a block.
 *
 * @param x Horizontal coordinates of a block.
 *
 * @return True if no collision is detected.
 */
bool check_borders_collision(int y, int x);

/**
 * @brief Checks for collisions with blocks already on the field.
 *
 * @param y Vertical coordinates of a block.
 *
 * @param x Horizontal coordinates of a block.
 *
 * @return True if no collision is detected.
 */
bool check_field_collision(int y, int x);

/**
 * @brief Generate random number between two numbers.
 *
 * @param a First number.
 *
 * @param b Second number.
 *
 * @return Generated number between ```a``` and ```b```.
 */
int get_random_number(int a, int b);

/**
 * @brief Copy contents of one 2x2 matrix to another one.
 *
 * @param original_matrix Matrix to be copied.
 *
 * @param new_matrix Matrix to copy to.
 *
 * @param rows Number of rows in matrices.
 *
 * @param cols Number of columns in matrices.
 */
void copy_matrix(int **original_matrix, int **new_matrix, int rows, int cols);

/**
 * @brief Free all allocated memory for game.
 *
 * @param parameters Pointer to structure with all information used in game
 * logic.
 */
void free_resources(Params_t *parameters);

/**
 * @brief Calculate lowest possible position for falling piece.
 *
 * @param prms Pointer to structure with all information used in game
 * logic.
 */
int get_lowest_position(Params_t *prms);

/**
 * @brief Reinitialize all game parameters for new game.
 *
 * @param prms Pointer to structure with all information used in game
 * logic.
 */
void reinitialize_game(Params_t *prms);

#endif  // BACKEND_H_