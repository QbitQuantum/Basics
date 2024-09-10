void polynomial(float *ret, const float *const r_values, int num) {
  // r*r*r*(10+r*(-15+r*6));

  __m256 const_6 = _mm256_set1_ps(6.0f);
  __m256 const_neg_15 = _mm256_set1_ps(-15.0f);
  __m256 const_10 = _mm256_set1_ps(10.0f);
  // constants

  const int loop_factor = 8;

  for (int i = 0; i < num; i+=loop_factor) {

#ifdef USE_IACA
  IACA_START
#endif
    __m256 r;
    __m256 left;
    __m256 right;
    // aligned load of 256 bits r
    r = _mm256_load_ps(&r_values[i]);
    left = _mm256_mul_ps(r, r); // r * r
#ifndef __FMA__

    right = _mm256_mul_ps(r, const_6); // r * 6
    left = _mm256_mul_ps(left, r); // r * r * r
    right = _mm256_add_ps(right, const_neg_15); //-15 + r * 6
    right = _mm256_mul_ps(right, r); //r * (-15 + r * 6)
    right = _mm256_add_ps(right, const_10); //10 + (r * (-15 + r * 6))

#else
    right = _mm256_fmadd_ps(r, const_6, const_neg_15);
    left = _mm256_mul_ps(left, r);

    right = _mm256_fmadd_ps(r, right, const_10);

#endif
    right = _mm256_mul_ps(right, left); // r*r*r *(10 + r * (-15 + r * 6))

    _mm256_store_ps(&ret[i], right); // store 8 values to ret[i]

  }
#ifdef USE_IACA
  IACA_END
#endif
}