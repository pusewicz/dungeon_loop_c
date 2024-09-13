#include <cute.h>
#include <dungeon_loop/assets.h>
#include <stdint.h>

void get_png_wh(const char* path, int* w, int* h)
{
  size_t size = 0;
  void* data = cf_fs_read_entire_file_to_memory(path, &size);
  CF_ASSERT(data);
  cf_image_load_png_wh(data, (int) size, w, h);
  cf_free(data);
}

Atlas atlas_load(const char* path, int tile_size, int* w_out, int* h_out)
{
  static uint64_t image_id = 0;
  uint64_t base_id = image_id;
  int w, h;
  get_png_wh(path, &w, &h);
  w = w / tile_size;
  h = h / tile_size;
  if (w_out) *w_out = w;
  if (h_out) *h_out = h;

  int sub_image_count = w * h;
  CF_AtlasSubImage* sub_images = (CF_AtlasSubImage*) cf_alloc(sizeof(CF_AtlasSubImage) * sub_image_count);

  for (int i = 0; i < sub_image_count; ++i) {
    CF_AtlasSubImage* sub_image = sub_images + i;
    int x = i % w;
    int y = i / w;

    // Assign a unique id for each sub-image. This id must be unique across *all* sub-images across *all* atlases.
    // Using a static integer and incrementing works well.
    sub_image->image_id = image_id++;
    sub_image->w = tile_size;
    sub_image->h = tile_size;

    // Calculate normalized uv coordinates. Each uv coordinate is a number from
    // 0 to 1, where (0,0) is the top-left of the image, and (1,1) is the bottom right.
    // Flip y to match CF convention.
    sub_image->minx = (float) x / (float) w;       // Top-left X
    sub_image->miny = (float) (y + 1) / (float) h; // Top-left Y
    sub_image->maxx = (float) (x + 1) / (float) w; // Bottom-right X
    sub_image->maxy = (float) y / (float) h;       // Bottom-right Y
  }

  Atlas atlas;
  atlas.texture = cf_register_premade_atlas(path, sub_image_count, sub_images);
  atlas.base_id = base_id;

  return atlas;
}

CF_Sprite sub_sprite(uint64_t base_id, int index)
{
  return cf_make_premade_sprite(base_id + (uint64_t) index);
}
