#ifndef DEF_H_
#define DEF_H_

/**
 * @file def.h
 *
 * @brief Definitions of structs and enums that are used in game logic.
 */

#include "lib_specification.h"

/**
 * @brief Represents the state of FSM.
 */
typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING, /**< Shifting down one row if timer runs out. */
  ATTACH,   /**< Attaching falling piece to the field. */
  GAMEOVER,
  EXIT_STATE
} BrickState_t;

/**
 * @brief Struct that stores information about a falling piece or next piece.
 */
typedef struct {
  int block_type;        /**< Type of piece, one out of 7 types. */
  int rotation;          /**< Rotation, one out of 4 rotations. */
  int vertical_coords;   /**< Actual vertical coordinates of a piece on the
                            screen. */
  int horizontal_coords; /**< Actual horizontal coordinates of a piece on the
                            screen. */
} BrickInfo_t;

/**
 * @brief Struct that stores all valuable information for game logic.
 */
typedef struct {
  GameInfo_t *game_info; /**< Stores information about game field, next piece,
                            score, level etc. */
  BrickState_t *state;   /**< Current state of the FSM. */
  BrickInfo_t *current_figure; /**< Information about current falling piece. */
  BrickInfo_t *next_figure;    /**< Information about next piece. */
} Params_t;

/**
 * @brief Function used in FSM logic.
 *
 * @param prms Pointer to structure that contains all information used in
 * game logic.
 */
typedef void (*signals)(Params_t *prms);

#endif  // DEF_H_