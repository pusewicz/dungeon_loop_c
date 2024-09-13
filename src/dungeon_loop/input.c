#include <dungeon_loop/common.h>
#include <dungeon_loop/game_state.h>
#include <cute.h>

void handle_input(GameState* state)
{
  if (cf_key_just_pressed(CF_KEY_W)) state->player_pos.y += 1;
  if (cf_key_just_pressed(CF_KEY_S)) state->player_pos.y -= 1;
  if (cf_key_just_pressed(CF_KEY_A)) state->player_pos.x -= 1;
  if (cf_key_just_pressed(CF_KEY_D)) state->player_pos.x += 1;
}
