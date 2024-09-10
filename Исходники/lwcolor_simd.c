void LW_FUNC_ALIGN convert_lw48_to_yuy2_sse41( int thread_id, int thread_num, void *param1, void *param2 )
{
    /* LW48 -> YUY2 using SSE4.1 */
    COLOR_PROC_INFO *cpip = (COLOR_PROC_INFO *)param1;
    int start = (cpip->h *  thread_id     ) / thread_num;
    int end   = (cpip->h * (thread_id + 1)) / thread_num;
    int w     = cpip->w;
    BYTE *ycp_line   = (BYTE *)cpip->ycp    + start * cpip->line_size;
    BYTE *pixel_line = (BYTE *)cpip->pixelp + start * w * 2;
    __m128i x0, x1, x2, x3, x5, x6, x7;
    static const char LW_ALIGN(16) SHUFFLE_Y[16] = { 0, 1, 6, 7, 12, 13, 2, 3, 8, 9, 14, 15, 4, 5, 10, 11 };
    for( int y = start; y < end; y++ )
    {
        BYTE *ycp      = ycp_line;
        BYTE *yuy2_ptr = pixel_line;
        for( int x = 0, i_step = 0; x < w; x += i_step, ycp += i_step*6, yuy2_ptr += i_step*2 )
        {
            x5 = _mm_loadu_si128((__m128i *)(ycp +  0));
            x6 = _mm_loadu_si128((__m128i *)(ycp + 16));
            x7 = _mm_loadu_si128((__m128i *)(ycp + 32));

            x0 = _mm_blend_epi16(x5, x6, 0x80+0x10+0x02);
            x0 = _mm_blend_epi16(x0, x7, 0x20+0x04);

            x1 = _mm_blend_epi16(x5, x6, 0x40+0x20+0x01);
            x1 = _mm_blend_epi16(x1, x7, 0x10+0x08);

            x0 = _mm_shuffle_epi8(x0, _mm_load_si128((__m128i*)SHUFFLE_Y));
            x1 = _mm_alignr_epi8(x1, x1, 2);
            x1 = _mm_shuffle_epi32(x1, _MM_SHUFFLE(1,2,3,0));

            x0 = _mm_srli_epi16(x0, 8);
            x1 = _mm_srli_epi16(x1, 8);

            x5 = _mm_loadu_si128((__m128i *)(ycp + 48));
            x6 = _mm_loadu_si128((__m128i *)(ycp + 64));
            x7 = _mm_loadu_si128((__m128i *)(ycp + 80));

            x2 = _mm_blend_epi16(x5, x6, 0x80+0x10+0x02);
            x2 = _mm_blend_epi16(x2, x7, 0x20+0x04);

            x3 = _mm_blend_epi16(x5, x6, 0x40+0x20+0x01);
            x3 = _mm_blend_epi16(x3, x7, 0x10+0x08);

            x2 = _mm_shuffle_epi8(x2, _mm_load_si128((__m128i*)SHUFFLE_Y));
            x3 = _mm_alignr_epi8(x3, x3, 2);
            x3 = _mm_shuffle_epi32(x3, _MM_SHUFFLE(1,2,3,0));

            x2 = _mm_srli_epi16(x2, 8);
            x3 = _mm_srli_epi16(x3, 8);

            x0 = _mm_packus_epi16(x0, x2);
            x1 = _mm_packus_epi16(x1, x3);

            _mm_storeu_si128((__m128i*)(yuy2_ptr +  0), _mm_unpacklo_epi8(x0, x1));
            _mm_storeu_si128((__m128i*)(yuy2_ptr + 16), _mm_unpackhi_epi8(x0, x1));

            int remain = w - x;
            i_step = (remain >= 16);
            i_step = (i_step<<4) + (remain & ((~(0-i_step)) & 0x0f));
        }
        ycp_line   += cpip->line_size;
        pixel_line += w*2;
    }
}