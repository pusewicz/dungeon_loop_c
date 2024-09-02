#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL3/SDL.h>
#include "cute.h"

int main(int argc, char* argv[]) {
  printf("Hello from %s %d\n", CF_VERSION_STRING_COMPILED, SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT);
  CF_Result result = cf_make_app("Dungeon Loop", cf_default_display(), 0, 0, 320, 240, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, argv[0]);
  if(cf_is_error(result)) {
    printf("Error creating app");
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
