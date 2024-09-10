// Make sure that including <xmmintrin.h> also makes <emmintrin.h>'s content available.
// This is an ugly hack for GCC compatibility.
__m128 test_xmmintrin_provides_emmintrin(__m128d __a, __m128d __b) {
  return _mm_add_sd(__a, __b);
}