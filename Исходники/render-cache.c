static void
sfid_render_cache_rt_write_simd8_r_uint8_ymajor(struct thread *t,
        const struct sfid_render_cache_args *args)
{
    const int slice_y = args->rt.minimum_array_element * args->rt.qpitch;
    const int x = t->grf[1].uw[4];
    const int y = t->grf[1].uw[5] + slice_y;
    const int cpp = 1;

    void *base = ymajor_offset(args->rt.pixels, x, y, args->rt.stride, cpp);

    struct reg *src = &t->grf[args->src];

    __m256i r32 = _mm256_permute4x64_epi64(src[0].ireg, SWIZZLE(0, 2, 1, 3));

    __m128i lo = _mm256_extractf128_si256(r32, 0);
    __m128i hi = _mm256_extractf128_si256(r32, 1);
    __m128i r16 = _mm_packus_epi32(lo, hi);
    __m128i r8 = _mm_packus_epi16(r16, r16);

    /* FIXME: Needs masking. */
    *(uint32_t *) (base +  0) = _mm_extract_epi32(r8, 0);
    *(uint32_t *) (base + 16) = _mm_extract_epi32(r8, 1);
}