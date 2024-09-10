inline static short
sse3_dot_prod (const uint16_t *p1,
               const uint16_t *p2,
               size_t          size)
{
  unsigned long res[4];
  unsigned int  i;

  __m128i* mp1  = (__m128i *)p1;
  __m128i* mp2  = (__m128i *)p2;
  __m128i  mres = _mm_set_epi32 (0, 0, 0, 0);

  for (i = 0; i < size; i += 8)
    {

      __m128i mreg1 = _mm_loadu_si128 (mp1);
      __m128i mreg2 = _mm_loadu_si128 (mp2);
      __m128i xlo1  = _mm_unpacklo_epi16 (mreg1, _mm_set1_epi16 (0));
      __m128i xlo2  = _mm_unpacklo_epi16 (mreg2, _mm_set1_epi16 (0));
      __m128i mtmp  = _mm_mullo_epi32 (xlo1, xlo2);
      mres          = _mm_add_epi32 (mres, mtmp);

      __m128i xhi1 = _mm_unpackhi_epi16 (mreg1, _mm_set1_epi16 (0));
      __m128i xhi2 = _mm_unpackhi_epi16 (mreg2, _mm_set1_epi16 (0));
      mtmp         = _mm_mullo_epi32 (xhi1, xhi2);
      mres         = _mm_add_epi32 (mres, mtmp);

      /*
      __m128i xlo1  = _mm_unpacklo_epi16 (_mm_loadu_si128 (mp1), _mm_set1_epi16 (0));
      __m128i xlo2  = _mm_unpacklo_epi16 (_mm_loadu_si128 (mp2), _mm_set1_epi16 (0));
      __m128i mtmp  = _mm_mullo_epi32 (xlo1, xlo2);
      mres          = _mm_add_epi32 (mres, mtmp);

      __m128i xhi1  = _mm_unpackhi_epi16 (_mm_loadu_si128 (mp1), _mm_set1_epi16 (0));
      __m128i xhi2  = _mm_unpackhi_epi16 (_mm_loadu_si128 (mp2), _mm_set1_epi16 (0));
      mtmp          = _mm_mullo_epi32 (xhi1, xhi2);
      mres          = _mm_add_epi32 (mres, mtmp);
      */

      mp1++;
      mp2++;
    }

  __m128i* pmres = (__m128i *)res;
  _mm_storeu_si128 (pmres, mres);

  return res[0]+res[1]+res[2]+res[3];
}