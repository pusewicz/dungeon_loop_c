#pragma once

#include <cute.h>

typedef struct GameState {
  int scale;
  CF_V2 player_pos;
  CF_Sprite girl;
} GameState;

void init_game_state(GameState* state);
