static INLINE __m128i load_coefficients(const tran_low_t *coeff_ptr) {
  if (sizeof(tran_low_t) == 4) {
    return _mm_setr_epi16((int16_t)coeff_ptr[0], (int16_t)coeff_ptr[1],
                          (int16_t)coeff_ptr[2], (int16_t)coeff_ptr[3],
                          (int16_t)coeff_ptr[4], (int16_t)coeff_ptr[5],
                          (int16_t)coeff_ptr[6], (int16_t)coeff_ptr[7]);
  } else {
    return _mm_load_si128((const __m128i *)coeff_ptr);
  }
}