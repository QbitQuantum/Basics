void ihevc_memcpy_mul_8_ssse3(UWORD8 *pu1_dst, UWORD8 *pu1_src, UWORD32 num_bytes)
{
    int col;
    for(col = num_bytes; col >= 8; col -= 8)
    {
        __m128i src_temp16x8b;
        src_temp16x8b = _mm_loadl_epi64((__m128i *)(pu1_src));
        pu1_src += 8;
        _mm_storel_epi64((__m128i *)(pu1_dst), src_temp16x8b);
        pu1_dst += 8;
    }
}