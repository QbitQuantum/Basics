static INLINE void highbd_idct32_4x32_quarter_2_stage_4_to_6(
    __m128i *const step1 /*step1[16]*/, __m128i *const out /*out[16]*/) {
  __m128i step2[32];

  // stage 4
  step2[8] = step1[8];
  step2[15] = step1[15];
  highbd_butterfly_sse2(step1[14], step1[9], cospi_24_64, cospi_8_64, &step2[9],
                        &step2[14]);
  highbd_butterfly_sse2(step1[10], step1[13], cospi_8_64, cospi_24_64,
                        &step2[13], &step2[10]);
  step2[11] = step1[11];
  step2[12] = step1[12];

  // stage 5
  step1[8] = _mm_add_epi32(step2[8], step2[11]);
  step1[9] = _mm_add_epi32(step2[9], step2[10]);
  step1[10] = _mm_sub_epi32(step2[9], step2[10]);
  step1[11] = _mm_sub_epi32(step2[8], step2[11]);
  step1[12] = _mm_sub_epi32(step2[15], step2[12]);
  step1[13] = _mm_sub_epi32(step2[14], step2[13]);
  step1[14] = _mm_add_epi32(step2[14], step2[13]);
  step1[15] = _mm_add_epi32(step2[15], step2[12]);

  // stage 6
  out[8] = step1[8];
  out[9] = step1[9];
  highbd_butterfly_sse2(step1[13], step1[10], cospi_16_64, cospi_16_64,
                        &out[10], &out[13]);
  highbd_butterfly_sse2(step1[12], step1[11], cospi_16_64, cospi_16_64,
                        &out[11], &out[12]);
  out[14] = step1[14];
  out[15] = step1[15];
}