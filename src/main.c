#include "cute.h"
#include "cute_app.h"
#include "cute_draw.h"
#include "dungeon_loop/common.h"
#include "dungeon_loop/game_state.h"
#include "dungeon_loop/input.h"
#include "dungeon_loop/math.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
  CF_DisplayID display_id = cf_default_display();
  CF_Rect display_size = cf_display_bounds(display_id);
  int scale = min(display_size.w / CANVAS_WIDTH, display_size.h / CANVAS_HEIGHT) - 1;

  CF_Result result = cf_make_app("Dungeon Loop", display_id, 0, 0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale,
                                 CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, argv[0]);

  if (cf_is_error(result)) {
    printf("Error creating app: %s", result.details);
    return EXIT_FAILURE;
  }

  GameState* state = create_game_state();
  CF_Sprite girl = cf_make_demo_sprite();
  cf_sprite_play(&girl, "spin");

  while (cf_app_is_running()) {
    cf_app_update(NULL);

    handle_input(state);

    girl.transform.p = state->player_pos;
    cf_sprite_update(&girl);
    cf_draw_scale_v2(cf_v2(scale, scale));
    cf_sprite_draw(&girl);
    cf_app_draw_onto_screen(true);
  }
  return EXIT_SUCCESS;
}
