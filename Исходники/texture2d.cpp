extern "C" void *Texture2D_create(Vec2i &size, void *data,
    uint32_t type, uint32_t flags)
{
  Texture2D *self = (Texture2D*) alignedMalloc(sizeof(Texture2D));
  self->size      = size;

  // Due to float rounding frac(x) can be exactly 1.0f (e.g. for very small
  // negative x), although it should be strictly smaller than 1.0f. We handle
  // this case by having sizef slightly smaller than size, such that
  // frac(x)*sizef is always < size.
  self->sizef = Vec2f(nextafter((float)size.x, -1.0f), nextafter((float)size.y, -1.0f));
  self->halfTexel = Vec2f(0.5f/size.x, 0.5f/size.y);
  self->data = data;
  self->get = Texture2D_get_addr(type, flags & TEXTURE_FILTER_NEAREST);

  return self;
}