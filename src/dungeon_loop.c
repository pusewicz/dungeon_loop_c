#include <stdio.h>
#include "cute.h"

int main(int argc, char* argv[]) {
  CF_Result result = cf_make_app("Dungeon Loop", cf_default_display(), 0, 0, 320, 240, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, argv[0]);
  if(cf_is_error(result)) {
    printf("Error creating app: %s", result.details);
    return EXIT_FAILURE;
  }

  CF_Sprite girl = cf_make_demo_sprite();
  cf_sprite_play(&girl, "spin");
  cf_sprite_set_scale(&girl, cf_v2(4,4));

  while(cf_app_is_running()) {
    cf_app_update(NULL);
    cf_sprite_update(&girl);
    cf_sprite_draw(&girl);
    cf_app_draw_onto_screen(true);
  }
  return EXIT_SUCCESS;
}
