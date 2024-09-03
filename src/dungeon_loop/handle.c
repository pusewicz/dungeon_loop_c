#include "dungeon_loop/common.h"
#include "dungeon_loop/state.h"
#include <cute.h>

void handle_input()
{
  if (cf_key_just_pressed(CF_KEY_W)) g_state.player_pos.y += 1;
  if (cf_key_just_pressed(CF_KEY_S)) g_state.player_pos.y -= 1;
  if (cf_key_just_pressed(CF_KEY_A)) g_state.player_pos.x -= 1;
  if (cf_key_just_pressed(CF_KEY_D)) g_state.player_pos.x += 1;
}
