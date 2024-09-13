#include <cute.h>
#include <dungeon_loop/draw.h>

// By default CF draws sprites at their center, but for pixel art it's often preferred to
// render sprites where (x,y) is the top-left pixel. This makes it easy to ensure the pixels don't get warped by rendering
// halfway between two pixels.
void draw_sprite(CF_Sprite sprite, float x, float y)
{
  cf_draw_push();
  x = roundf(x) + sprite.w * 0.5f;
  y = roundf(y) + sprite.h * 0.5f;
  cf_draw_translate(x, y);
  cf_draw_sprite(&sprite);
  cf_draw_pop();
}
