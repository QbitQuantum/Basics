static void
sse3_test_movsldup_reg_subsume (float *i1, float *r)
{
  __m128 t1 = _mm_load_ps (i1);
  __m128 t2 = _mm_moveldup_ps (t1);

  _mm_storeu_ps (r, t2);
}