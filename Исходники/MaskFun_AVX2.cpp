static FORCE_INLINE void FlowInter_8px_AVX2(
        int w, PixelType *pdst,
        const PixelType *prefB, const PixelType *prefF,
        const int16_t *VXFullB, const int16_t *VXFullF,
        const int16_t *VYFullB, const int16_t *VYFullF,
        const uint8_t *MaskB, const uint8_t *MaskF,
        int nPelLog,
        const __m256i &dwords_time256, const __m256i &dwords_256_time256,
        const __m256i &dwords_ref_pitch, const __m256i &dwords_hoffsets) {

    __m256i dwords_w = _mm256_add_epi32(_mm256_set1_epi32(w << nPelLog), dwords_hoffsets);

    __m256i dstF = lookup_AVX2(VXFullF, VYFullF, prefF, w, dwords_time256, dwords_ref_pitch, dwords_w);
    __m256i dstB = lookup_AVX2(VXFullB, VYFullB, prefB, w, dwords_256_time256, dwords_ref_pitch, dwords_w);

    __m256i dstF0 = _mm256_i32gather_epi32((const int *)prefF, dwords_w, sizeof(PixelType));
    __m256i dstB0 = _mm256_i32gather_epi32((const int *)prefB, dwords_w, sizeof(PixelType));
    dstF0 = _mm256_and_si256(dstF0, _mm256_set1_epi32((1 << (sizeof(PixelType) * 8)) - 1));
    dstB0 = _mm256_and_si256(dstB0, _mm256_set1_epi32((1 << (sizeof(PixelType) * 8)) - 1));

    __m256i maskf = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i *)&MaskF[w]));
    __m256i maskb = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i *)&MaskB[w]));

    const __m256i dwords_255 = _mm256_set1_epi32(255);

    __m256i maskf_inv = _mm256_sub_epi32(dwords_255, maskf);
    __m256i maskb_inv = _mm256_sub_epi32(dwords_255, maskb);

    __m256i dstF_maskf_inv, dstB_maskb_inv, dstF0_maskb, dstB0_maskf;

    if (sizeof(PixelType) == 1) {
        dstF_maskf_inv = _mm256_mullo_epi16(dstF, maskf_inv);
        dstB_maskb_inv = _mm256_mullo_epi16(dstB, maskb_inv);

        dstF0_maskb = _mm256_mullo_epi16(dstF0, maskb);
        dstB0_maskf = _mm256_mullo_epi16(dstB0, maskf);
    } else {
        dstF_maskf_inv = _mm256_mullo_epi32(dstF, maskf_inv);
        dstB_maskb_inv = _mm256_mullo_epi32(dstB, maskb_inv);

        dstF0_maskb = _mm256_mullo_epi32(dstF0, maskb);
        dstB0_maskf = _mm256_mullo_epi32(dstB0, maskf);
    }

    __m256i f = _mm256_add_epi32(dstF0_maskb, dstB_maskb_inv);
    __m256i b = _mm256_add_epi32(dstB0_maskf, dstF_maskf_inv);

    if (sizeof(PixelType) == 1) {
        f = _mm256_mullo_epi32(f, maskf);
        b = _mm256_mullo_epi32(b, maskb);

        f = _mm256_add_epi32(f, dwords_255);
        b = _mm256_add_epi32(b, dwords_255);

        f = _mm256_srai_epi32(f, 8);
        b = _mm256_srai_epi32(b, 8);
    } else {
        const __m256i qwords_255 = _mm256_set1_epi64x(255);

        __m256i tempf = _mm256_mul_epu32(f, maskf);
        __m256i tempb = _mm256_mul_epu32(b, maskb);
        tempf = _mm256_add_epi64(tempf, qwords_255);
        tempb = _mm256_add_epi64(tempb, qwords_255);
        tempf = _mm256_srli_epi64(tempf, 8);
        tempb = _mm256_srli_epi64(tempb, 8);

        f = _mm256_srli_epi64(f, 32);
        b = _mm256_srli_epi64(b, 32);
        f = _mm256_mul_epu32(f, _mm256_srli_epi64(maskf, 32));
        b = _mm256_mul_epu32(b, _mm256_srli_epi64(maskb, 32));
        f = _mm256_add_epi64(f, qwords_255);
        b = _mm256_add_epi64(b, qwords_255);
        f = _mm256_srli_epi64(f, 8);
        b = _mm256_srli_epi64(b, 8);
        f = _mm256_or_si256(tempf, _mm256_slli_epi64(f, 32));
        b = _mm256_or_si256(tempb, _mm256_slli_epi64(b, 32));
    }

    f = _mm256_add_epi32(f, dstF_maskf_inv);
    b = _mm256_add_epi32(b, dstB_maskb_inv);

    f = _mm256_add_epi32(f, dwords_255);
    b = _mm256_add_epi32(b, dwords_255);

    f = _mm256_srai_epi32(f, 8);
    b = _mm256_srai_epi32(b, 8);

    if (sizeof(PixelType) == 1) {
        f = _mm256_madd_epi16(f, dwords_256_time256);
        b = _mm256_madd_epi16(b, dwords_time256);
    } else {
        f = _mm256_mullo_epi32(f, dwords_256_time256);
        b = _mm256_mullo_epi32(b, dwords_time256);
    }

    __m256i dst = _mm256_add_epi32(f, b);
    dst = _mm256_srai_epi32(dst, 8);

    dst = _mm256_packus_epi32(dst, dst);
    dst = _mm256_permute4x64_epi64(dst, 0xe8); // 0b11101000 - copy third qword to second qword
    __m128i dst128 = _mm256_castsi256_si128(dst);

    if (sizeof(PixelType) == 1) {
        dst128 = _mm_packus_epi16(dst128, dst128);
        _mm_storel_epi64((__m128i *)&pdst[w], dst128);
    } else {
        _mm_storeu_si128((__m128i *)&pdst[w], dst128);
    }
}