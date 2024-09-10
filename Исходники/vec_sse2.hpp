 static inline __m128d gen_ones(void)
 {
     __m128d x = gen_zero();
     __m128d ones = _mm_cmpeq_pd(x, x);
     return ones;
 }