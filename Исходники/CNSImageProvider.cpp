/**
 * Internal subroutine for cnsResponse.
 * Load 2 x 8 image pixel and convert to 16 bit, also generates 1 pixel shifts for later filter computation.
 * img[i] contains src[i], imgL[i] contains src[i-1] and, imgR[i] contains src[i+1], i = 0..7
 * when interpreting __m128i as unsigned short[8].
 * lastScr is the __m128i directly before the current one (src), which is directly folllowed by nextSrc
 */
ALWAYSINLINE static void load2x8PixelUsingSSE(__m128i& imgL, __m128i& img, __m128i& imgR,
  __m128i& imgL2, __m128i& img2, __m128i& imgR2,
  __m128i& lastSrc, __m128i& src,  const __m128i* const nextSrcP)
{
  const __m128i nextSrc = _mm_load_si128(nextSrcP);

  //imgL = _mm_unpacklo_epi8(_mmauto_add_epi8(_mmauto_srli_si_all(lastSrc, 15), _mmauto_slli_si_all(src, 1)), _mm_setzero_si128());
  imgL = _mm_unpacklo_epi8(_mm_alignr_epi8(src, lastSrc, 15), _mm_setzero_si128());
  img = _mm_unpacklo_epi8(src, _mm_setzero_si128());
  imgR = _mm_unpacklo_epi8(_mm_srli_si128(src, 1), _mm_setzero_si128());

  imgL2 = _mm_unpacklo_epi8(_mm_srli_si128(src, 7), _mm_setzero_si128());
  img2 = _mm_unpacklo_epi8(_mm_srli_si128(src, 8), _mm_setzero_si128());
  //imgR2 = _mm_unpacklo_epi8(_mmauto_add_epi8(_mmauto_srli_si_all(src, 9), _mmauto_slli_si_all(nextSrc, 7)), _mm_setzero_si128());
  imgR2 = _mm_unpacklo_epi8(_mm_alignr_epi8(nextSrc, src, 9), _mm_setzero_si128());

  lastSrc = src;
  src = nextSrc;
}