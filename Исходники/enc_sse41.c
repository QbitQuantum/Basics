// Hadamard transform
// Returns the weighted sum of the absolute value of transformed coefficients.
// w[] contains a row-major 4 by 4 symmetric matrix.
static int TTransform_SSE41(const uint8_t* inA, const uint8_t* inB,
                            const uint16_t* const w) {
  int32_t sum[4];
  __m128i tmp_0, tmp_1, tmp_2, tmp_3;

  // Load and combine inputs.
  {
    const __m128i inA_0 = _mm_loadu_si128((const __m128i*)&inA[BPS * 0]);
    const __m128i inA_1 = _mm_loadu_si128((const __m128i*)&inA[BPS * 1]);
    const __m128i inA_2 = _mm_loadu_si128((const __m128i*)&inA[BPS * 2]);
    // In SSE4.1, with gcc 4.8 at least (maybe other versions),
    // _mm_loadu_si128 is faster than _mm_loadl_epi64. But for the last lump
    // of inA and inB, _mm_loadl_epi64 is still used not to have an out of
    // bound read.
    const __m128i inA_3 = _mm_loadl_epi64((const __m128i*)&inA[BPS * 3]);
    const __m128i inB_0 = _mm_loadu_si128((const __m128i*)&inB[BPS * 0]);
    const __m128i inB_1 = _mm_loadu_si128((const __m128i*)&inB[BPS * 1]);
    const __m128i inB_2 = _mm_loadu_si128((const __m128i*)&inB[BPS * 2]);
    const __m128i inB_3 = _mm_loadl_epi64((const __m128i*)&inB[BPS * 3]);

    // Combine inA and inB (we'll do two transforms in parallel).
    const __m128i inAB_0 = _mm_unpacklo_epi32(inA_0, inB_0);
    const __m128i inAB_1 = _mm_unpacklo_epi32(inA_1, inB_1);
    const __m128i inAB_2 = _mm_unpacklo_epi32(inA_2, inB_2);
    const __m128i inAB_3 = _mm_unpacklo_epi32(inA_3, inB_3);
    tmp_0 = _mm_cvtepu8_epi16(inAB_0);
    tmp_1 = _mm_cvtepu8_epi16(inAB_1);
    tmp_2 = _mm_cvtepu8_epi16(inAB_2);
    tmp_3 = _mm_cvtepu8_epi16(inAB_3);
    // a00 a01 a02 a03   b00 b01 b02 b03
    // a10 a11 a12 a13   b10 b11 b12 b13
    // a20 a21 a22 a23   b20 b21 b22 b23
    // a30 a31 a32 a33   b30 b31 b32 b33
  }

  // Vertical pass first to avoid a transpose (vertical and horizontal passes
  // are commutative because w/kWeightY is symmetric) and subsequent transpose.
  {
    // Calculate a and b (two 4x4 at once).
    const __m128i a0 = _mm_add_epi16(tmp_0, tmp_2);
    const __m128i a1 = _mm_add_epi16(tmp_1, tmp_3);
    const __m128i a2 = _mm_sub_epi16(tmp_1, tmp_3);
    const __m128i a3 = _mm_sub_epi16(tmp_0, tmp_2);
    const __m128i b0 = _mm_add_epi16(a0, a1);
    const __m128i b1 = _mm_add_epi16(a3, a2);
    const __m128i b2 = _mm_sub_epi16(a3, a2);
    const __m128i b3 = _mm_sub_epi16(a0, a1);
    // a00 a01 a02 a03   b00 b01 b02 b03
    // a10 a11 a12 a13   b10 b11 b12 b13
    // a20 a21 a22 a23   b20 b21 b22 b23
    // a30 a31 a32 a33   b30 b31 b32 b33

    // Transpose the two 4x4.
    VP8Transpose_2_4x4_16b(&b0, &b1, &b2, &b3, &tmp_0, &tmp_1, &tmp_2, &tmp_3);
  }

  // Horizontal pass and difference of weighted sums.
  {
    // Load all inputs.
    const __m128i w_0 = _mm_loadu_si128((const __m128i*)&w[0]);
    const __m128i w_8 = _mm_loadu_si128((const __m128i*)&w[8]);

    // Calculate a and b (two 4x4 at once).
    const __m128i a0 = _mm_add_epi16(tmp_0, tmp_2);
    const __m128i a1 = _mm_add_epi16(tmp_1, tmp_3);
    const __m128i a2 = _mm_sub_epi16(tmp_1, tmp_3);
    const __m128i a3 = _mm_sub_epi16(tmp_0, tmp_2);
    const __m128i b0 = _mm_add_epi16(a0, a1);
    const __m128i b1 = _mm_add_epi16(a3, a2);
    const __m128i b2 = _mm_sub_epi16(a3, a2);
    const __m128i b3 = _mm_sub_epi16(a0, a1);

    // Separate the transforms of inA and inB.
    __m128i A_b0 = _mm_unpacklo_epi64(b0, b1);
    __m128i A_b2 = _mm_unpacklo_epi64(b2, b3);
    __m128i B_b0 = _mm_unpackhi_epi64(b0, b1);
    __m128i B_b2 = _mm_unpackhi_epi64(b2, b3);

    A_b0 = _mm_abs_epi16(A_b0);
    A_b2 = _mm_abs_epi16(A_b2);
    B_b0 = _mm_abs_epi16(B_b0);
    B_b2 = _mm_abs_epi16(B_b2);

    // weighted sums
    A_b0 = _mm_madd_epi16(A_b0, w_0);
    A_b2 = _mm_madd_epi16(A_b2, w_8);
    B_b0 = _mm_madd_epi16(B_b0, w_0);
    B_b2 = _mm_madd_epi16(B_b2, w_8);
    A_b0 = _mm_add_epi32(A_b0, A_b2);
    B_b0 = _mm_add_epi32(B_b0, B_b2);

    // difference of weighted sums
    A_b2 = _mm_sub_epi32(A_b0, B_b0);
    _mm_storeu_si128((__m128i*)&sum[0], A_b2);
  }
  return sum[0] + sum[1] + sum[2] + sum[3];
}