void
swizzle (const void *a, vector4_t * b, vector4_t * c)
{
  b->v = _mm_loadl_pi (b->v, (__m64 *) a);
  c->v = _mm_loadl_pi (c->v, ((__m64 *) a) + 1);
}