 static BOOST_FORCEINLINE T perm2_ ( __m256i const& a0, __m256i const& a1, Mask const&)
 {
   return _mm256_permute2f128_si256(a0, a1, Mask::value);
 }