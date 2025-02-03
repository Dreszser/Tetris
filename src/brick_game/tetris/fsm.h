#ifndef FSM_H
#define FSM_H

/**
 * @file fsm.h
 *
 * @brief Declaration of functions that change the state of FSM.
 */

#include "def.h"

/**
 * @brief Initialize new game.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void start(Params_t *prms);

/**
 * @brief Spawn new falling piece.
 *
 * Moves next piece to the game field and generates new next piece. If spawned
 * piece triggers collision, calls gameover.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void spawn(Params_t *prms);

/**
 * @brief Move falling piece all the way down and attach.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void movedown(Params_t *prms);

/**
 * @brief Move falling piece one block to the right if possible.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void moveright(Params_t *prms);

/**
 * @brief Move falling piece one block to the left if possible.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void moveleft(Params_t *prms);

/**
 * @brief Shifts falling piece one row down.
 *
 * If collision is detected, triggers Attach state.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void shifting(Params_t *prms);

/**
 * @brief Attaches falling piece to the board.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void attach(Params_t *prms);

/**
 * @brief Saves high score and shows game over screen.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void gameover(Params_t *prms);

/**
 * @brief Changes game state to exit.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void exitstate(Params_t *prms);

/**
 * @brief Changes pause value to pause the game.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void pause(Params_t *prms);

/**
 * @brief Rotates the piece.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
void rotate(Params_t *prms);

#endif  // FSM_H