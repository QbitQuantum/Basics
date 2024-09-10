AYCW_INLINE __m128i BS_SHR(__m128i v, int n)
{
   __m128i v1, v2;

   if ((n) >= 64)
   {
      v1 = _mm_srli_si128(v, 8);
      v1 = _mm_srli_epi64(v1, (n)-64);
   }
   else
   {
      v1 = _mm_srli_epi64(v, n);
      v2 = _mm_srli_si128(v, 8);
      v2 = _mm_slli_epi64(v2, 64 - (n));
      v1 = _mm_or_si128(v1, v2);
   }
   return v1;
}