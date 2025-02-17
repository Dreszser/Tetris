#ifndef LIB_SPECIFICATION_H_
#define LIB_SPECIFICATION_H_

/**
 * @file lib_specification.h
 *
 * @brief Library specification from the task, can not be changed.
 *
 * This file contains structures and function declarations, that are used to
 * draw game scene in frontend.
 */

#include <stdbool.h>

/**
 * @brief Represents the signal that user can send by pressing a key on the
 * keyboard.
 */
typedef enum {
  Start = 0, /**< Enter key. */
  Pause,     /**< 'P' key. */
  Terminate, /**< Escape key. */
  Left,      /**< Left arrow key. */
  Right,     /**< Right arrow key. */
  Up,        /**< Up arrow key. */
  Down,      /**< Down arrow key. */
  Action     /**< Spacebar key. */
} UserAction_t;

/**
 * @brief Structure that contains all information for frontend to print the game
 * scene.
 */
typedef struct {
  int **field;    /**< Game field. */
  int **next;     /**< Next piece. */
  int score;      /**< Current score integer. */
  int high_score; /**< High score integer. */
  int level;      /**< Current level integer. */
  int speed;      /**< Current game speed integer. */
  int pause; /**< 0 - default; 1 - start state pause; 2 - pause; 3 - exit state;
                4 - game over. */
} GameInfo_t;

/**
 * @brief This function takes user input and calls corresponding function to
 * change FSM state.
 *
 * @param action User input.
 * @param hold Bool parameter responsible for keeping the button pressed.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Gathers all valuable resources for printing the game screen.
 *
 * Creates static GameInfo_t struct where field matrix has both
 * filled blocks and a falling piece.
 *
 * @return Copy of GameInfo_t.
 */
GameInfo_t updateCurrentState();

#endif  // LIB_SPECIFICATION_H_
