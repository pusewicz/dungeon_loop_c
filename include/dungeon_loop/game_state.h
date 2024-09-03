#pragma once

#include <cute_math.h>

typedef struct GameState {
  CF_V2 player_pos;
} GameState;

void init_game_state(GameState* state);
