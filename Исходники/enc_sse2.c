static void FTransformSSE2(const uint8_t* src, const uint8_t* ref,
                           int16_t* out) {
  const __m128i zero = _mm_setzero_si128();
  const __m128i seven = _mm_set1_epi16(7);
  const __m128i k7500 = _mm_set1_epi32(7500);
  const __m128i k14500 = _mm_set1_epi32(14500);
  const __m128i k51000 = _mm_set1_epi32(51000);
  const __m128i k12000_plus_one = _mm_set1_epi32(12000 + (1 << 16));
  const __m128i k5352_2217 = _mm_set_epi16(5352,  2217, 5352,  2217,
                                           5352,  2217, 5352,  2217);
  const __m128i k2217_5352 = _mm_set_epi16(2217, -5352, 2217, -5352,
                                           2217, -5352, 2217, -5352);

  __m128i v01, v32;

  // Difference between src and ref and initial transpose.
  {
    // Load src and convert to 16b.
    const __m128i src0 = _mm_loadl_epi64((__m128i*)&src[0 * BPS]);
    const __m128i src1 = _mm_loadl_epi64((__m128i*)&src[1 * BPS]);
    const __m128i src2 = _mm_loadl_epi64((__m128i*)&src[2 * BPS]);
    const __m128i src3 = _mm_loadl_epi64((__m128i*)&src[3 * BPS]);
    const __m128i src_0 = _mm_unpacklo_epi8(src0, zero);
    const __m128i src_1 = _mm_unpacklo_epi8(src1, zero);
    const __m128i src_2 = _mm_unpacklo_epi8(src2, zero);
    const __m128i src_3 = _mm_unpacklo_epi8(src3, zero);
    // Load ref and convert to 16b.
    const __m128i ref0 = _mm_loadl_epi64((__m128i*)&ref[0 * BPS]);
    const __m128i ref1 = _mm_loadl_epi64((__m128i*)&ref[1 * BPS]);
    const __m128i ref2 = _mm_loadl_epi64((__m128i*)&ref[2 * BPS]);
    const __m128i ref3 = _mm_loadl_epi64((__m128i*)&ref[3 * BPS]);
    const __m128i ref_0 = _mm_unpacklo_epi8(ref0, zero);
    const __m128i ref_1 = _mm_unpacklo_epi8(ref1, zero);
    const __m128i ref_2 = _mm_unpacklo_epi8(ref2, zero);
    const __m128i ref_3 = _mm_unpacklo_epi8(ref3, zero);
    // Compute difference.
    const __m128i diff0 = _mm_sub_epi16(src_0, ref_0);
    const __m128i diff1 = _mm_sub_epi16(src_1, ref_1);
    const __m128i diff2 = _mm_sub_epi16(src_2, ref_2);
    const __m128i diff3 = _mm_sub_epi16(src_3, ref_3);

    // Transpose.
    // 00 01 02 03   0 0 0 0
    // 10 11 12 13   0 0 0 0
    // 20 21 22 23   0 0 0 0
    // 30 31 32 33   0 0 0 0
    const __m128i transpose0_0 = _mm_unpacklo_epi16(diff0, diff1);
    const __m128i transpose0_1 = _mm_unpacklo_epi16(diff2, diff3);
    // 00 10 01 11   02 12 03 13
    // 20 30 21 31   22 32 23 33
    const __m128i v23 = _mm_unpackhi_epi32(transpose0_0, transpose0_1);
    v01 = _mm_unpacklo_epi32(transpose0_0, transpose0_1);
    v32 = _mm_shuffle_epi32(v23, _MM_SHUFFLE(1, 0, 3, 2));
    // a02 a12 a22 a32   a03 a13 a23 a33
    // a00 a10 a20 a30   a01 a11 a21 a31
    // a03 a13 a23 a33   a02 a12 a22 a32
  }

  // First pass and subsequent transpose.
  {
    // Same operations are done on the (0,3) and (1,2) pairs.
    // b0 = (a0 + a3) << 3
    // b1 = (a1 + a2) << 3
    // b3 = (a0 - a3) << 3
    // b2 = (a1 - a2) << 3
    const __m128i a01 = _mm_add_epi16(v01, v32);
    const __m128i a32 = _mm_sub_epi16(v01, v32);
    const __m128i b01 = _mm_slli_epi16(a01, 3);
    const __m128i b32 = _mm_slli_epi16(a32, 3);
    const __m128i b11 = _mm_unpackhi_epi64(b01, b01);
    const __m128i b22 = _mm_unpackhi_epi64(b32, b32);

    // e0 = b0 + b1
    // e2 = b0 - b1
    const __m128i e0 = _mm_add_epi16(b01, b11);
    const __m128i e2 = _mm_sub_epi16(b01, b11);
    const __m128i e02 = _mm_unpacklo_epi64(e0, e2);

    // e1 = (b3 * 5352 + b2 * 2217 + 14500) >> 12
    // e3 = (b3 * 2217 - b2 * 5352 +  7500) >> 12
    const __m128i b23 = _mm_unpacklo_epi16(b22, b32);
    const __m128i c1 = _mm_madd_epi16(b23, k5352_2217);
    const __m128i c3 = _mm_madd_epi16(b23, k2217_5352);
    const __m128i d1 = _mm_add_epi32(c1, k14500);
    const __m128i d3 = _mm_add_epi32(c3, k7500);
    const __m128i e1 = _mm_srai_epi32(d1, 12);
    const __m128i e3 = _mm_srai_epi32(d3, 12);
    const __m128i e13 = _mm_packs_epi32(e1, e3);

    // Transpose.
    // 00 01 02 03  20 21 22 23
    // 10 11 12 13  30 31 32 33
    const __m128i transpose0_0 = _mm_unpacklo_epi16(e02, e13);
    const __m128i transpose0_1 = _mm_unpackhi_epi16(e02, e13);
    // 00 10 01 11   02 12 03 13
    // 20 30 21 31   22 32 23 33
    const __m128i v23 = _mm_unpackhi_epi32(transpose0_0, transpose0_1);
    v01 = _mm_unpacklo_epi32(transpose0_0, transpose0_1);
    v32 = _mm_shuffle_epi32(v23, _MM_SHUFFLE(1, 0, 3, 2));
    // 02 12 22 32   03 13 23 33
    // 00 10 20 30   01 11 21 31
    // 03 13 23 33   02 12 22 32
  }

  // Second pass
  {
    // Same operations are done on the (0,3) and (1,2) pairs.
    // a0 = v0 + v3
    // a1 = v1 + v2
    // a3 = v0 - v3
    // a2 = v1 - v2
    const __m128i a01 = _mm_add_epi16(v01, v32);
    const __m128i a32 = _mm_sub_epi16(v01, v32);
    const __m128i a11 = _mm_unpackhi_epi64(a01, a01);
    const __m128i a22 = _mm_unpackhi_epi64(a32, a32);

    // d0 = (a0 + a1 + 7) >> 4;
    // d2 = (a0 - a1 + 7) >> 4;
    const __m128i b0 = _mm_add_epi16(a01, a11);
    const __m128i b2 = _mm_sub_epi16(a01, a11);
    const __m128i c0 = _mm_add_epi16(b0, seven);
    const __m128i c2 = _mm_add_epi16(b2, seven);
    const __m128i d0 = _mm_srai_epi16(c0, 4);
    const __m128i d2 = _mm_srai_epi16(c2, 4);

    // f1 = ((b3 * 5352 + b2 * 2217 + 12000) >> 16)
    // f3 = ((b3 * 2217 - b2 * 5352 + 51000) >> 16)
    const __m128i b23 = _mm_unpacklo_epi16(a22, a32);
    const __m128i c1 = _mm_madd_epi16(b23, k5352_2217);
    const __m128i c3 = _mm_madd_epi16(b23, k2217_5352);
    const __m128i d1 = _mm_add_epi32(c1, k12000_plus_one);
    const __m128i d3 = _mm_add_epi32(c3, k51000);
    const __m128i e1 = _mm_srai_epi32(d1, 16);
    const __m128i e3 = _mm_srai_epi32(d3, 16);
    const __m128i f1 = _mm_packs_epi32(e1, e1);
    const __m128i f3 = _mm_packs_epi32(e3, e3);
    // f1 = f1 + (a3 != 0);
    // The compare will return (0xffff, 0) for (==0, !=0). To turn that into the
    // desired (0, 1), we add one earlier through k12000_plus_one.
    const __m128i g1 = _mm_add_epi16(f1, _mm_cmpeq_epi16(a32, zero));

    _mm_storel_epi64((__m128i*)&out[ 0], d0);
    _mm_storel_epi64((__m128i*)&out[ 4], g1);
    _mm_storel_epi64((__m128i*)&out[ 8], d2);
    _mm_storel_epi64((__m128i*)&out[12], f3);
  }
}