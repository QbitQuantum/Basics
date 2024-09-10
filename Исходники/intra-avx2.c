 /**
 * \brief Linear interpolation for 4 pixels. Returns 4 filtered pixels in lowest 32-bits of the register.
 * \param ref_main      Reference pixels
 * \param delta_pos     Fractional pixel precise position of sample displacement
 * \param x             Sample offset in direction x in ref_main array
 */
static INLINE __m128i filter_4x1_avx2(const kvz_pixel *ref_main, int16_t delta_pos, int x){

  int8_t delta_int = delta_pos >> 5;
  int8_t delta_fract = delta_pos & (32-1);
  __m128i sample0 = _mm_cvtsi32_si128(*(uint32_t*)&(ref_main[x + delta_int]));
  __m128i sample1 = _mm_cvtsi32_si128(*(uint32_t*)&(ref_main[x + delta_int + 1]));
  __m128i pairs = _mm_unpacklo_epi8(sample0, sample1);
  __m128i weight = _mm_set1_epi16( (delta_fract << 8) | (32 - delta_fract) );
  sample0 = _mm_maddubs_epi16(pairs, weight);
  sample0 = _mm_add_epi16(sample0, _mm_set1_epi16(16));
  sample0 = _mm_srli_epi16(sample0, 5);
  sample0 = _mm_packus_epi16(sample0, sample0);

  return sample0;
}

 /**
 * \brief Linear interpolation for 4x4 block. Writes filtered 4x4 block to dst.
 * \param dst           Destination buffer
 * \param ref_main      Reference pixels
 * \param sample_disp   Sample displacement per row
 * \param vertical_mode Mode direction, true if vertical
 */
static void filter_4x4_avx2(kvz_pixel *dst, const kvz_pixel *ref_main, int sample_disp, bool vertical_mode){