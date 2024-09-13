#include <cimgui.h>
#include <cute.h>
#include <dungeon_loop/common.h>
#include <dungeon_loop/game.h>
#include <dungeon_loop/game_state.h>
#include <dungeon_loop/input.h>
#include <stdio.h>
#include <stdlib.h>

void update(void* udata)
{
  GameState* state = (GameState*) udata;
  handle_input(state);
  game_update(state);
  game_draw(state);
}

int main(int argc, char* argv[])
{
  CF_UNUSED(argc);
  CF_DisplayID display_id = cf_default_display();
  CF_Rect display_size = cf_display_bounds(display_id);
  int scale = cf_min(display_size.w / CANVAS_WIDTH, display_size.h / CANVAS_HEIGHT) - 1;
  CF_Result result = cf_make_app("Dungeon Loop", display_id, 0, 0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale,
                                 CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, argv[0]);

  if (cf_is_error(result)) {
    printf("Error creating app: %s", result.details);
    return EXIT_FAILURE;
  }

  GameState state = {0};
  init_game_state(&state, scale);
  cf_set_update_udata(&state);
  cf_app_set_vsync(true);
  cf_app_init_imgui();

  while (cf_app_is_running()) {
    cf_app_update(update);

    igBegin("Dungeon Loop", NULL, 0);
    igText("Player pos: (%f, %f)", state.player_pos.x, state.player_pos.y);
    igEnd();

    cf_app_draw_onto_screen(true);
  }

  cf_destroy_app();

  return EXIT_SUCCESS;
}
