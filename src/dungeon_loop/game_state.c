// Functions to handle the state of the game

#include "dungeon_loop/game_state.h"
#include "dungeon_loop/common.h"

void init_game_state(GameState* state)
{
  state->player_pos = cf_v2(0, 0);
}
