void parallel_vectorised_matmul(struct complex ** A, struct complex ** B, struct complex ** C, int a_rows, int a_cols, int b_cols) {
  #pragma omp parallel for
  for (int i = 0; i < a_rows; i++) {
    for (int k = 0; k < a_cols; k++) {
      struct complex r = A[i][k];

      __m128 a_real = _mm_set1_ps(r.real);
      __m128 a_imag = _mm_set1_ps(r.imag);

      for (int j = 0; j < b_cols; j += 2) {
        __m128 b_complex = _mm_load_ps((float*) &B[k][j]);

        __m128 real_times_b = _mm_mul_ps(a_real, b_complex);
        __m128 imag_times_b = _mm_mul_ps(a_imag, b_complex);
        imag_times_b = _mm_shuffle_ps(imag_times_b, imag_times_b, _MM_SHUFFLE(2, 3, 0, 1));

        __m128 addsub = _mm_addsub_ps(real_times_b, imag_times_b);

        __m128 current_c = _mm_load_ps((float*) &C[i][j]);
        _mm_store_ps((float*) &C[i][j], _mm_add_ps(current_c, addsub));
      }
    }
  }
}