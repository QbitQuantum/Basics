void transpose_out(__m128i& B0, __m128i& B1, __m128i& B2, __m128i& B3)
   {
   __m128i T0 = _mm_unpacklo_epi64(B0, B1);
   __m128i T1 = _mm_unpacklo_epi64(B2, B3);
   __m128i T2 = _mm_unpackhi_epi64(B0, B1);
   __m128i T3 = _mm_unpackhi_epi64(B2, B3);

   T0 = _mm_shuffle_epi32(T0, _MM_SHUFFLE(3, 1, 2, 0));
   T1 = _mm_shuffle_epi32(T1, _MM_SHUFFLE(3, 1, 2, 0));
   T2 = _mm_shuffle_epi32(T2, _MM_SHUFFLE(3, 1, 2, 0));
   T3 = _mm_shuffle_epi32(T3, _MM_SHUFFLE(3, 1, 2, 0));

   T0 = _mm_shufflehi_epi16(T0, _MM_SHUFFLE(3, 1, 2, 0));
   T1 = _mm_shufflehi_epi16(T1, _MM_SHUFFLE(3, 1, 2, 0));
   T2 = _mm_shufflehi_epi16(T2, _MM_SHUFFLE(3, 1, 2, 0));
   T3 = _mm_shufflehi_epi16(T3, _MM_SHUFFLE(3, 1, 2, 0));

   T0 = _mm_shufflelo_epi16(T0, _MM_SHUFFLE(3, 1, 2, 0));
   T1 = _mm_shufflelo_epi16(T1, _MM_SHUFFLE(3, 1, 2, 0));
   T2 = _mm_shufflelo_epi16(T2, _MM_SHUFFLE(3, 1, 2, 0));
   T3 = _mm_shufflelo_epi16(T3, _MM_SHUFFLE(3, 1, 2, 0));

   B0 = _mm_unpacklo_epi32(T0, T1);
   B1 = _mm_unpackhi_epi32(T0, T1);
   B2 = _mm_unpacklo_epi32(T2, T3);
   B3 = _mm_unpackhi_epi32(T2, T3);
   }