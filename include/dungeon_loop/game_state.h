#pragma once

#include <cute_math.h>

typedef struct GameState {
  CF_V2 player_pos;
} GameState;

GameState* create_game_state(void);
void destroy_game_state(GameState* state);
void update_game_state(GameState* state);
void render_game_state(const GameState* state);
