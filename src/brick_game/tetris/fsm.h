#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdio.h>

#include "def.h"

void start(Params_t *prms);
void spawn(Params_t *prms);
void movedown(Params_t *prms);
void moveright(Params_t *prms);
void moveleft(Params_t *prms);
void shifting(Params_t *prms);
void attach(Params_t *prms);
void gameover(Params_t *prms);
void exitstate(Params_t *prms);
void pause(Params_t *prms);
void rotate(Params_t *prms);

#endif  // FSM_H