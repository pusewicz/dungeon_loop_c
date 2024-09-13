#include <cute.h>

typedef struct Atlas
{
  CF_Texture texture;
  uint64_t base_id;
} Atlas;

Atlas atlas_load(const char* path, int tile_size, int* w_out, int* h_out);
