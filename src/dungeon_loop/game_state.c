// Functions to handle the state of the game

#include <dungeon_loop/common.h>
#include <dungeon_loop/game_state.h>

void init_game_state(GameState* state)
{
  state->girl = cf_make_demo_sprite();
  cf_sprite_play(&state->girl, "spin");
  state->player_pos = cf_v2(0, 0);
}
