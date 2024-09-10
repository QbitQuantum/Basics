inline static void histogram_helper_cs_rgb_helper_process_pixel_m128(
    const dt_dev_histogram_collection_params_t *const histogram_params, const float *pixel, uint32_t *histogram)
{
  const __m128 scale = _mm_set1_ps(histogram_params->mul);
  const __m128 val_min = _mm_setzero_ps();
  const __m128 val_max = _mm_set1_ps(histogram_params->bins_count - 1);

  assert(dt_is_aligned(pixel, 16));
  const __m128 input = _mm_load_ps(pixel);
  const __m128 scaled = _mm_mul_ps(input, scale);
  const __m128 clamped = _mm_max_ps(_mm_min_ps(scaled, val_max), val_min);

  const __m128i indexes = _mm_cvtps_epi32(clamped);

  __m128i values __attribute__((aligned(16)));
  _mm_store_si128(&values, indexes);

  const uint32_t *valuesi = (uint32_t *)(&values);

  histogram[4 * valuesi[0]]++;
  histogram[4 * valuesi[1] + 1]++;
  histogram[4 * valuesi[2] + 2]++;
}