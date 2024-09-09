#include "fsm.h"

/* static signal fsm_table[7][8] = {
      {spawn, NULL, exitstate, NULL, NULL, NULL, NULL, NULL},
      {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
      {NULL, pause, exitstate, moveleft, moveright, NULL, movedown, rotate},
      {shifting, shifting, shifting, shifting, shifting, shifting, shifting,
       shifting},
      {attach, attach, attach, attach, attach, attach, attach, attach},
      {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
       gameover},
      {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
       exitstate, exitstate}};

void userInput(UserAction_t action, bool hold) { 
  signal act = NULL;
  static Params_t parameters;

  act = fsm_table[*parameters.state][action];

  if (act) act(&parameters);
} */
