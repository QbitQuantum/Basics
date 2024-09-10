/* Test the 128-bit form */
static void
ssse3_test_phsubd128 (int *i1, int *i2, int *r)
{
  /* Assumes incoming pointers are 16-byte aligned */
  __m128i t1 = *(__m128i *) i1;
  __m128i t2 = *(__m128i *) i2;
  *(__m128i *) r = _mm_hsub_epi32 (t1, t2);
}