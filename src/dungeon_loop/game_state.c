// Functions to handle the state of the game

#include "dungeon_loop/game_state.h"
#include "dungeon_loop/common.h"

GameState* create_game_state(void)
{
  GameState* state = malloc(sizeof(GameState));
  if (state) {
    state->player_pos = cf_v2(0, 0);
  }
  return state;
}

void destroy_game_state(GameState* state)
{
  free(state);
}

void update_game_state(GameState* state)
{
  // Update game logic here
}

void render_game_state(const GameState* state)
{
  // Render game based on state
}
