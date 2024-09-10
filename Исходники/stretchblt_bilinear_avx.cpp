// 16bpp general R/G/B, usually 5/6/5 or 5/5/5
static inline __m256i stretchblt_line_bilinear_pixel_blend_avx_rgb16(const __m256i cur,const __m256i nxt,const __m256i mul,const __m256i rmask,const uint16_t rshift,const __m256i gmask,const uint16_t gshift,const __m256i bmask,const uint16_t bshift) {
    __m256i rc,gc,bc;
    __m256i rn,gn,bn;
    __m256i d,sum;

    rc = _mm256_and_si256(_mm256_srli_epi16(cur,rshift),rmask);
    gc = _mm256_and_si256(_mm256_srli_epi16(cur,gshift),gmask);
    bc = _mm256_and_si256(_mm256_srli_epi16(cur,bshift),bmask);

    rn = _mm256_and_si256(_mm256_srli_epi16(nxt,rshift),rmask);
    gn = _mm256_and_si256(_mm256_srli_epi16(nxt,gshift),gmask);
    bn = _mm256_and_si256(_mm256_srli_epi16(nxt,bshift),bmask);

    d = _mm256_sub_epi16(rn,rc);
    sum = _mm256_slli_epi16(_mm256_add_epi16(rc,_mm256_mulhi_epi16(_mm256_add_epi16(d,d),mul)),rshift);

    d = _mm256_sub_epi16(gn,gc);
    sum = _mm256_add_epi16(_mm256_slli_epi16(_mm256_add_epi16(gc,_mm256_mulhi_epi16(_mm256_add_epi16(d,d),mul)),gshift),sum);

    d = _mm256_sub_epi16(bn,bc);
    sum = _mm256_add_epi16(_mm256_slli_epi16(_mm256_add_epi16(bc,_mm256_mulhi_epi16(_mm256_add_epi16(d,d),mul)),bshift),sum);

    return sum;
}