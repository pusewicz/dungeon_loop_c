#include <dungeon_loop/game.h>
#include <dungeon_loop/game_state.h>

void game_update(GameState* state)
{
  state->girl.transform.p = state->player_pos;
  cf_sprite_update(&state->girl);
}

void game_draw(GameState* state)
{
  cf_draw_scale_v2(cf_v2(state->scale, state->scale));
  cf_sprite_draw(&state->girl);
}
