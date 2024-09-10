template<int shift, int active_bits> void Haar_invtransform_H_final_1_sse4_2_int32_t(void *_idata,
																			   const int istride,
																			   const char *odata,
																			   const int ostride,
																			   const int iwidth,
																			   const int iheight,
																			   const int ooffset_x,
																			   const int ooffset_y,
																			   const int owidth,
																			   const int oheight) {
  int32_t *idata = (int32_t *)_idata;
  const int skip = 1;
  const __m128i ONE = _mm_set1_epi32(1);
  const __m128i OFFSET = _mm_set1_epi32(1 << (active_bits - 1));

  (void)iwidth;
  (void)iheight;

  for (int y = ooffset_y; y < ooffset_y + oheight; y+=skip) {
    for (int x = ooffset_x; x < ooffset_x + owidth; x += 8) {
      __m128i D0 = _mm_load_si128((__m128i *)&idata[y*istride + x + 0]);
      __m128i D4 = _mm_load_si128((__m128i *)&idata[y*istride + x + 4]);

      __m128i A0 = _mm_unpacklo_epi32(D0, D4);
      __m128i A2 = _mm_unpackhi_epi32(D0, D4);

      __m128i E0 = _mm_unpacklo_epi32(A0, A2);
      __m128i O1 = _mm_unpackhi_epi32(A0, A2);

      __m128i X0 = _mm_sub_epi32(E0, _mm_srai_epi32(_mm_add_epi32(O1, ONE), 1));
      __m128i X1 = _mm_add_epi32(O1, X0);

      __m128i Z0 = _mm_unpacklo_epi32(X0, X1);
      __m128i Z4 = _mm_unpackhi_epi32(X0, X1);

      if (shift != 0) {
        Z0 = _mm_add_epi32(Z0, ONE);
        Z4 = _mm_add_epi32(Z4, ONE);
        Z0 = _mm_srai_epi32(Z0, shift);
        Z4 = _mm_srai_epi32(Z4, shift);
      }

      Z0 = _mm_add_epi32(Z0, OFFSET);
      Z4 = _mm_add_epi32(Z4, OFFSET);

      Z0 = _mm_slli_epi32(Z0, (16 - active_bits));
      Z4 = _mm_slli_epi32(Z4, (16 - active_bits));

      __m128i R = _mm_packus_epi32(Z0, Z4);

      R = _mm_srli_epi16(R, (16 - active_bits));
      _mm_store_si128((__m128i *)&odata[2*((y - ooffset_y)*ostride + x - ooffset_x)], R);
    }
  }
}