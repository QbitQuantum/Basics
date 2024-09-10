/* For data organized into a row for each bit (8 * elem_size rows), transpose
 * the bytes. */
int64_t bshuf_trans_byte_bitrow_AVX(void* in, void* out, const size_t size,
         const size_t elem_size) {

    size_t hh, ii, jj, kk, mm;
    char* in_b = (char*) in;
    char* out_b = (char*) out;

    CHECK_MULT_EIGHT(size);

    size_t nrows = 8 * elem_size;
    size_t nbyte_row = size / 8;

    if (elem_size % 4) return bshuf_trans_byte_bitrow_SSE(in, out, size,
            elem_size);

    __m256i ymm_0[8];
    __m256i ymm_1[8];
    __m256i ymm_storeage[8][4];

    for (jj = 0; jj + 31 < nbyte_row; jj += 32) {
        for (ii = 0; ii + 3 < elem_size; ii += 4) {
            for (hh = 0; hh < 4; hh ++) {

                for (kk = 0; kk < 8; kk ++){
                    ymm_0[kk] = _mm256_loadu_si256((__m256i *) &in_b[
                            (ii * 8 + hh * 8 + kk) * nbyte_row + jj]);
                }

                for (kk = 0; kk < 4; kk ++){
                    ymm_1[kk] = _mm256_unpacklo_epi8(ymm_0[kk * 2],
                            ymm_0[kk * 2 + 1]);
                    ymm_1[kk + 4] = _mm256_unpackhi_epi8(ymm_0[kk * 2],
                            ymm_0[kk * 2 + 1]);
                }

                for (kk = 0; kk < 2; kk ++){
                    for (mm = 0; mm < 2; mm ++){
                        ymm_0[kk * 4 + mm] = _mm256_unpacklo_epi16(
                                ymm_1[kk * 4 + mm * 2],
                                ymm_1[kk * 4 + mm * 2 + 1]);
                        ymm_0[kk * 4 + mm + 2] = _mm256_unpackhi_epi16(
                                ymm_1[kk * 4 + mm * 2],
                                ymm_1[kk * 4 + mm * 2 + 1]);
                    }
                }

                for (kk = 0; kk < 4; kk ++){
                    ymm_1[kk * 2] = _mm256_unpacklo_epi32(ymm_0[kk * 2],
                            ymm_0[kk * 2 + 1]);
                    ymm_1[kk * 2 + 1] = _mm256_unpackhi_epi32(ymm_0[kk * 2],
                            ymm_0[kk * 2 + 1]);
                }

                for (kk = 0; kk < 8; kk ++){
                    ymm_storeage[kk][hh] = ymm_1[kk];
                }
            }

            for (mm = 0; mm < 8; mm ++) {

                for (kk = 0; kk < 4; kk ++){
                    ymm_0[kk] = ymm_storeage[mm][kk];
                }

                ymm_1[0] = _mm256_unpacklo_epi64(ymm_0[0], ymm_0[1]);
                ymm_1[1] = _mm256_unpacklo_epi64(ymm_0[2], ymm_0[3]);
                ymm_1[2] = _mm256_unpackhi_epi64(ymm_0[0], ymm_0[1]);
                ymm_1[3] = _mm256_unpackhi_epi64(ymm_0[2], ymm_0[3]);

                ymm_0[0] = _mm256_permute2x128_si256(ymm_1[0], ymm_1[1], 32);
                ymm_0[1] = _mm256_permute2x128_si256(ymm_1[2], ymm_1[3], 32);
                ymm_0[2] = _mm256_permute2x128_si256(ymm_1[0], ymm_1[1], 49);
                ymm_0[3] = _mm256_permute2x128_si256(ymm_1[2], ymm_1[3], 49);

                _mm256_storeu_si256((__m256i *) &out_b[
                        (jj + mm * 2 + 0 * 16) * nrows + ii * 8], ymm_0[0]);
                _mm256_storeu_si256((__m256i *) &out_b[
                        (jj + mm * 2 + 0 * 16 + 1) * nrows + ii * 8], ymm_0[1]);
                _mm256_storeu_si256((__m256i *) &out_b[
                        (jj + mm * 2 + 1 * 16) * nrows + ii * 8], ymm_0[2]);
                _mm256_storeu_si256((__m256i *) &out_b[
                        (jj + mm * 2 + 1 * 16 + 1) * nrows + ii * 8], ymm_0[3]);
            }
        }
    }
    for (ii = 0; ii < nrows; ii ++ ) {
        for (jj = nbyte_row - nbyte_row % 32; jj < nbyte_row; jj ++) {
            out_b[jj * nrows + ii] = in_b[ii * nbyte_row + jj];
        }
    }
    return size * elem_size;
}