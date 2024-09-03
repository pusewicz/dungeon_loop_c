// Functions to handle the state of the game

#include "dungeon_loop/state.h"
#include "dungeon_loop/common.h"

GameState g_state = {0};

void state_reset()
{
  g_state = (GameState){0};
  g_state.player_pos = cf_v2(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2);
}
