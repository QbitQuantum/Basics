void av1_fdct32x32_1_sse2(const int16_t *input, tran_low_t *output,
                          int stride) {
  __m128i in0, in1, in2, in3;
  __m128i u0, u1;
  __m128i sum = _mm_setzero_si128();
  int i;

  for (i = 0; i < 8; ++i) {
    in0 = _mm_load_si128((const __m128i *)(input + 0));
    in1 = _mm_load_si128((const __m128i *)(input + 8));
    in2 = _mm_load_si128((const __m128i *)(input + 16));
    in3 = _mm_load_si128((const __m128i *)(input + 24));

    input += stride;
    u0 = _mm_add_epi16(in0, in1);
    u1 = _mm_add_epi16(in2, in3);
    sum = _mm_add_epi16(sum, u0);

    in0 = _mm_load_si128((const __m128i *)(input + 0));
    in1 = _mm_load_si128((const __m128i *)(input + 8));
    in2 = _mm_load_si128((const __m128i *)(input + 16));
    in3 = _mm_load_si128((const __m128i *)(input + 24));

    input += stride;
    sum = _mm_add_epi16(sum, u1);
    u0 = _mm_add_epi16(in0, in1);
    u1 = _mm_add_epi16(in2, in3);
    sum = _mm_add_epi16(sum, u0);

    in0 = _mm_load_si128((const __m128i *)(input + 0));
    in1 = _mm_load_si128((const __m128i *)(input + 8));
    in2 = _mm_load_si128((const __m128i *)(input + 16));
    in3 = _mm_load_si128((const __m128i *)(input + 24));

    input += stride;
    sum = _mm_add_epi16(sum, u1);
    u0 = _mm_add_epi16(in0, in1);
    u1 = _mm_add_epi16(in2, in3);
    sum = _mm_add_epi16(sum, u0);

    in0 = _mm_load_si128((const __m128i *)(input + 0));
    in1 = _mm_load_si128((const __m128i *)(input + 8));
    in2 = _mm_load_si128((const __m128i *)(input + 16));
    in3 = _mm_load_si128((const __m128i *)(input + 24));

    input += stride;
    sum = _mm_add_epi16(sum, u1);
    u0 = _mm_add_epi16(in0, in1);
    u1 = _mm_add_epi16(in2, in3);
    sum = _mm_add_epi16(sum, u0);

    sum = _mm_add_epi16(sum, u1);
  }

  u0 = _mm_setzero_si128();
  in0 = _mm_unpacklo_epi16(u0, sum);
  in1 = _mm_unpackhi_epi16(u0, sum);
  in0 = _mm_srai_epi32(in0, 16);
  in1 = _mm_srai_epi32(in1, 16);

  sum = _mm_add_epi32(in0, in1);
  in0 = _mm_unpacklo_epi32(sum, u0);
  in1 = _mm_unpackhi_epi32(sum, u0);

  sum = _mm_add_epi32(in0, in1);
  in0 = _mm_srli_si128(sum, 8);

  in1 = _mm_add_epi32(sum, in0);
  in1 = _mm_srai_epi32(in1, 3);
  store_output(&in1, output);
}