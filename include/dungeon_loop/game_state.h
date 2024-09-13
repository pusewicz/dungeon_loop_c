#pragma once

#include <cute.h>
#include "assets.h"

typedef struct GameState {
  int scale;
  int atlas_w, atlas_h;
  Atlas atlas;
  CF_V2 player_pos;
  CF_Sprite girl;
} GameState;

void init_game_state(GameState* state, int scale);
