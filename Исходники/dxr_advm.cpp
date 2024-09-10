void lines_scale2(const unsigned char *src, unsigned y, unsigned char *dst1, unsigned char *dst2, unsigned nPix)
{
   const unsigned char
      *u = src + ((y-1) & 7)*sc2lines_width,
      *m = src + ((y+0) & 7)*sc2lines_width,
      *l = src + ((y+1) & 7)*sc2lines_width;

   for (unsigned i = 0; i < nPix; i += 8) {

      __m64 uu = *(__m64*)(u+i);
      __m64 ll = *(__m64*)(l+i);
      __m64 cmp = _mm_cmpeq_pi8(uu,ll);

      if (_mm_movemask_pi8(cmp) != 0xFF) {

         __m128i mm = _mm_loadu_si128((__m128i*)(m+i-4));
         __m128i uu = _mm_loadu_si128((__m128i*)(u+i-4));
         __m128i ll = _mm_loadu_si128((__m128i*)(l+i-4));

         __m128i md = _mm_slli_si128(mm,1);
         __m128i mf = _mm_srli_si128(mm,1);
         __m128i maskall = _mm_or_si128(_mm_cmpeq_epi8(md,mf), _mm_cmpeq_epi8(uu,ll));

         __m128i e0, e1, v1, v2, v3;

         e0 = _mm_cmpeq_epi8(md,uu);
         e0 = _mm_andnot_si128(maskall, e0);
         e0 = _mm_srli_si128(e0,4);
         e0 = _mm_unpacklo_epi8(e0, _mm_setzero_si128());

         e1 = _mm_cmpeq_epi8(mf,uu);
         e1 = _mm_andnot_si128(maskall, e1);
         e1 = _mm_srli_si128(e1,4);
         e1 = _mm_unpacklo_epi8(_mm_setzero_si128(), e1);

         e0 = _mm_or_si128(e0, e1);

         v1 = _mm_srli_si128(mm,4);
         v1 = _mm_unpacklo_epi8(v1,v1);
         v2 = _mm_srli_si128(uu,4);
         v2 = _mm_unpacklo_epi8(v2,v2);

         _mm_store_si128((__m128i*)(dst1 + 2*i), _mm_or_si128( _mm_and_si128(e0,v2), _mm_andnot_si128(e0,v1) ) );

         e0 = _mm_cmpeq_epi8(md,ll);
         e0 = _mm_andnot_si128(maskall, e0);
         e0 = _mm_srli_si128(e0,4);
         e0 = _mm_unpacklo_epi8(e0, _mm_setzero_si128());

         e1 = _mm_cmpeq_epi8(mf,ll);
         e1 = _mm_andnot_si128(maskall, e1);
         e1 = _mm_srli_si128(e1,4);
         e1 = _mm_unpacklo_epi8(_mm_setzero_si128(), e1);

         e0 = _mm_or_si128(e0, e1);

         v3 = _mm_srli_si128(ll,4);
         v3 = _mm_unpacklo_epi8(v3,v3);

         _mm_store_si128((__m128i*)(dst2 + 2*i), _mm_or_si128( _mm_and_si128(e0,v3), _mm_andnot_si128(e0,v1) ) );

      } else {

         __m64 v0 = *(__m64*)(m+i);
         __m128i v1 = _mm_movpi64_epi64(v0);
         v1 = _mm_unpacklo_epi8(v1,v1);
         _mm_store_si128((__m128i*)(dst1 + 2*i), v1);
         _mm_store_si128((__m128i*)(dst2 + 2*i), v1);
      }
   }
}