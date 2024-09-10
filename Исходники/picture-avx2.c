static void satd_8bit_4x4_dual_avx2(
  const pred_buffer preds, const kvz_pixel * const orig, unsigned num_modes, unsigned *satds_out) 
{

  __m256i original = _mm256_broadcastsi128_si256(_mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)orig)));
  __m256i pred = _mm256_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)preds[0]));
  pred = _mm256_inserti128_si256(pred, _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)preds[1])), 1);

  __m256i diff_lo = _mm256_sub_epi16(pred, original);

  original = _mm256_broadcastsi128_si256(_mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)(orig + 8))));
  pred = _mm256_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)(preds[0] + 8)));
  pred = _mm256_inserti128_si256(pred, _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)(preds[1] + 8))), 1);

  __m256i diff_hi = _mm256_sub_epi16(pred, original);

  //Hor
  __m256i row0 = _mm256_hadd_epi16(diff_lo, diff_hi);
  __m256i row1 = _mm256_hsub_epi16(diff_lo, diff_hi);

  __m256i row2 = _mm256_hadd_epi16(row0, row1);
  __m256i row3 = _mm256_hsub_epi16(row0, row1);

  //Ver
  row0 = _mm256_hadd_epi16(row2, row3);
  row1 = _mm256_hsub_epi16(row2, row3);

  row2 = _mm256_hadd_epi16(row0, row1);
  row3 = _mm256_hsub_epi16(row0, row1);

  //Abs and sum
  row2 = _mm256_abs_epi16(row2);
  row3 = _mm256_abs_epi16(row3);

  row3 = _mm256_add_epi16(row2, row3);

  row3 = _mm256_add_epi16(row3, _mm256_shuffle_epi32(row3, KVZ_PERMUTE(2, 3, 0, 1) ));
  row3 = _mm256_add_epi16(row3, _mm256_shuffle_epi32(row3, KVZ_PERMUTE(1, 0, 1, 0) ));
  row3 = _mm256_add_epi16(row3, _mm256_shufflelo_epi16(row3, KVZ_PERMUTE(1, 0, 1, 0) ));

  unsigned sum1 = _mm_extract_epi16(_mm256_castsi256_si128(row3), 0);
  sum1 = (sum1 + 1) >> 1;

  unsigned sum2 = _mm_extract_epi16(_mm256_extracti128_si256(row3, 1), 0);
  sum2 = (sum2 + 1) >> 1;

  satds_out[0] = sum1;
  satds_out[1] = sum2;
}