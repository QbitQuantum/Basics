/* -----------------------------------
 *     weighted_merge_chroma_yuy2
 * -----------------------------------
 */
static void weighted_merge_chroma_yuy2_sse2(BYTE *src, const BYTE *chroma, int pitch, int chroma_pitch,int width, int height, int weight, int invweight )
{
  __m128i round_mask = _mm_set1_epi32(0x4000);
  __m128i mask = _mm_set_epi16(weight, invweight, weight, invweight, weight, invweight, weight, invweight);
  __m128i luma_mask = _mm_set1_epi16(0x00FF);

  int wMod16 = (width/16) * 16;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < wMod16; x += 16) {
      __m128i px1 = _mm_load_si128(reinterpret_cast<const __m128i*>(src+x)); 
      __m128i px2 = _mm_load_si128(reinterpret_cast<const __m128i*>(chroma+x)); 

      __m128i src_lo = _mm_unpacklo_epi16(px1, px2); 
      __m128i src_hi = _mm_unpackhi_epi16(px1, px2); 

      src_lo = _mm_srli_epi16(src_lo, 8);
      src_hi = _mm_srli_epi16(src_hi, 8);

      src_lo = _mm_madd_epi16(src_lo, mask);
      src_hi = _mm_madd_epi16(src_hi, mask);

      src_lo = _mm_add_epi32(src_lo, round_mask);
      src_hi = _mm_add_epi32(src_hi, round_mask);

      src_lo = _mm_srli_epi32(src_lo, 15);
      src_hi = _mm_srli_epi32(src_hi, 15);

      __m128i result_chroma = _mm_packs_epi32(src_lo, src_hi);
      result_chroma = _mm_slli_epi16(result_chroma, 8);

      __m128i result_luma = _mm_and_si128(px1, luma_mask);
      __m128i result = _mm_or_si128(result_chroma, result_luma);

      _mm_store_si128(reinterpret_cast<__m128i*>(src+x), result);
    }

    for (int x = wMod16; x < width; x+=2) {
      src[x+1] = (chroma[x+1] * weight + src[x+1] * invweight + 16384) >> 15;
    }

    src += pitch;
    chroma += chroma_pitch;
  }
}