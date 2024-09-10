 BOOST_FORCEINLINE
 __m256i shuffle(__m256i const lower, __m256i const upper)
 {
   return _mm256_castpd_si256(
     _mm256_shuffle_pd( _mm256_castsi256_pd(lower), _mm256_castsi256_pd(upper)
                   , _MM_SHUFFLE(upper_i1, upper_i0, lower_i1, lower_i0)
                   )
   );
 }