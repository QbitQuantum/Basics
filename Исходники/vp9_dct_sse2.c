void vp9_short_fdct4x4_sse2(int16_t *input, int16_t *output, int pitch) {
  // The 2D transform is done with two passes which are actually pretty
  // similar. In the first one, we transform the columns and transpose
  // the results. In the second one, we transform the rows. To achieve that,
  // as the first pass results are transposed, we tranpose the columns (that
  // is the transposed rows) and transpose the results (so that it goes back
  // in normal/row positions).
  const int stride = pitch >> 1;
  int pass;
  // Constants
  //    When we use them, in one case, they are all the same. In all others
  //    it's a pair of them that we need to repeat four times. This is done
  //    by constructing the 32 bit constant corresponding to that pair.
  const __m128i k__cospi_p16_p16 = _mm_set1_epi16(cospi_16_64);
  const __m128i k__cospi_p16_m16 = pair_set_epi16(cospi_16_64, -cospi_16_64);
  const __m128i k__cospi_p24_p08 = pair_set_epi16(cospi_24_64, cospi_8_64);
  const __m128i k__cospi_m08_p24 = pair_set_epi16(-cospi_8_64, cospi_24_64);
  const __m128i k__DCT_CONST_ROUNDING = _mm_set1_epi32(DCT_CONST_ROUNDING);
  const __m128i k__nonzero_bias_a = _mm_setr_epi16(0, 1, 1, 1, 1, 1, 1, 1);
  const __m128i k__nonzero_bias_b = _mm_setr_epi16(1, 0, 0, 0, 0, 0, 0, 0);
  const __m128i kOne = _mm_set1_epi16(1);
  __m128i in0, in1, in2, in3;
  // Load inputs.
  {
    in0  = _mm_loadl_epi64((const __m128i *)(input +  0 * stride));
    in1  = _mm_loadl_epi64((const __m128i *)(input +  1 * stride));
    in2  = _mm_loadl_epi64((const __m128i *)(input +  2 * stride));
    in3  = _mm_loadl_epi64((const __m128i *)(input +  3 * stride));
    // x = x << 4
    in0 = _mm_slli_epi16(in0, 4);
    in1 = _mm_slli_epi16(in1, 4);
    in2 = _mm_slli_epi16(in2, 4);
    in3 = _mm_slli_epi16(in3, 4);
    // if (i == 0 && input[0]) input[0] += 1;
    {
      // The mask will only contain wether the first value is zero, all
      // other comparison will fail as something shifted by 4 (above << 4)
      // can never be equal to one. To increment in the non-zero case, we
      // add the mask and one for the first element:
      //   - if zero, mask = -1, v = v - 1 + 1 = v
      //   - if non-zero, mask = 0, v = v + 0 + 1 = v + 1
      __m128i mask = _mm_cmpeq_epi16(in0, k__nonzero_bias_a);
      in0 = _mm_add_epi16(in0, mask);
      in0 = _mm_add_epi16(in0, k__nonzero_bias_b);
    }
  }
  // Do the two transform/transpose passes
  for (pass = 0; pass < 2; ++pass) {
    // Transform 1/2: Add/substract
    const __m128i r0 = _mm_add_epi16(in0, in3);
    const __m128i r1 = _mm_add_epi16(in1, in2);
    const __m128i r2 = _mm_sub_epi16(in1, in2);
    const __m128i r3 = _mm_sub_epi16(in0, in3);
    // Transform 1/2: Interleave to do the multiply by constants which gets us
    //                into 32 bits.
    const __m128i t0 = _mm_unpacklo_epi16(r0, r1);
    const __m128i t2 = _mm_unpacklo_epi16(r2, r3);
    const __m128i u0 = _mm_madd_epi16(t0, k__cospi_p16_p16);
    const __m128i u2 = _mm_madd_epi16(t0, k__cospi_p16_m16);
    const __m128i u4 = _mm_madd_epi16(t2, k__cospi_p24_p08);
    const __m128i u6 = _mm_madd_epi16(t2, k__cospi_m08_p24);
    const __m128i v0 = _mm_add_epi32(u0, k__DCT_CONST_ROUNDING);
    const __m128i v2 = _mm_add_epi32(u2, k__DCT_CONST_ROUNDING);
    const __m128i v4 = _mm_add_epi32(u4, k__DCT_CONST_ROUNDING);
    const __m128i v6 = _mm_add_epi32(u6, k__DCT_CONST_ROUNDING);
    const __m128i w0 = _mm_srai_epi32(v0, DCT_CONST_BITS);
    const __m128i w2 = _mm_srai_epi32(v2, DCT_CONST_BITS);
    const __m128i w4 = _mm_srai_epi32(v4, DCT_CONST_BITS);
    const __m128i w6 = _mm_srai_epi32(v6, DCT_CONST_BITS);
    // Combine and transpose
    const __m128i res0 = _mm_packs_epi32(w0, w2);
    const __m128i res1 = _mm_packs_epi32(w4, w6);
    // 00 01 02 03 20 21 22 23
    // 10 11 12 13 30 31 32 33
    const __m128i tr0_0 = _mm_unpacklo_epi16(res0, res1);
    const __m128i tr0_1 = _mm_unpackhi_epi16(res0, res1);
    // 00 10 01 11 02 12 03 13
    // 20 30 21 31 22 32 23 33
    in0 = _mm_unpacklo_epi32(tr0_0, tr0_1);
    in2 = _mm_unpackhi_epi32(tr0_0, tr0_1);
    // 00 10 20 30 01 11 21 31      in0 contains 0 followed by 1
    // 02 12 22 32 03 13 23 33      in2 contains 2 followed by 3
    if (0 == pass) {
      // Extract values in the high part for second pass as transform code
      // only uses the first four values.
      in1 = _mm_unpackhi_epi64(in0, in0);
      in3 = _mm_unpackhi_epi64(in2, in2);
    } else {
      // Post-condition output and store it (v + 1) >> 2, taking advantage
      // of the fact 1/3 are stored just after 0/2.
      __m128i out01 = _mm_add_epi16(in0, kOne);
      __m128i out23 = _mm_add_epi16(in2, kOne);
      out01 = _mm_srai_epi16(out01, 2);
      out23 = _mm_srai_epi16(out23, 2);
      _mm_storeu_si128((__m128i *)(output + 0 * 4), out01);
      _mm_storeu_si128((__m128i *)(output + 2 * 4), out23);
    }
  }
}