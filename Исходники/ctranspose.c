inline void transpose_4x4block_AVX_64(double* A, double* B, const size_t lda,
                                   const size_t ldb) {
    __m256d row0 = _mm256_load_pd(&A[0*ldb]);
    __m256d row1 = _mm256_load_pd(&A[1*ldb]);
    __m256d row2 = _mm256_load_pd(&A[2*ldb]);
    __m256d row3 = _mm256_load_pd(&A[3*ldb]);
    __m256d tmp3, tmp2, tmp1, tmp0;
    tmp0 = _mm256_unpacklo_pd(row0, row1);
    tmp1 = _mm256_unpackhi_pd(row0, row1);
    tmp2 = _mm256_unpacklo_pd(row2, row3);
    tmp3 = _mm256_unpackhi_pd(row2, row3);
    row0 = _mm256_permute2f128_pd(tmp0, tmp2, 0x20);
    row1 = _mm256_permute2f128_pd(tmp1, tmp3, 0x20);
    row2 = _mm256_permute2f128_pd(tmp0, tmp2, 0x31);
    row3 = _mm256_permute2f128_pd(tmp1, tmp3, 0x31);
    _mm256_store_pd(&B[0*lda], row0);
    _mm256_store_pd(&B[1*lda], row1);
    _mm256_store_pd(&B[2*lda], row2);
    _mm256_store_pd(&B[3*lda], row3);

}