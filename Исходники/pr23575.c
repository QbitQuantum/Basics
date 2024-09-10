__m128d cross(__m128d tmp9)
{
  __m128d t1 = _mm_set1_pd(1.0);
  __m128d tmp10 = _mm_move_sd(t1, tmp9);
  return tmp10;
}