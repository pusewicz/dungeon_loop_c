// Functions to handle the state of the game

#include <dungeon_loop/common.h>
#include <dungeon_loop/game_state.h>

void init_game_state(GameState* state, int scale)
{
  state->scale = scale;
  state->girl = cf_make_demo_sprite();
  state->atlas = atlas_load("assets/2bitsunrise_b.png", 16, &state->atlas_w, &state->atlas_h);
  CF_ASSERT(state->atlas_w > 0);
  CF_ASSERT(state->atlas_h > 0);
  cf_sprite_play(&state->girl, "spin");
  state->player_pos = cf_v2(0, 0);
}
