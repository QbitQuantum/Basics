/*---------------------------------------------------------------------------*/
pstatus_t sse2_yCbCrToRGB_16s16s_P3P3(
    const INT16 *pSrc[3],
    int srcStep,
    INT16 *pDst[3],
    int dstStep,
    const prim_size_t *roi)	/* region of interest */
{
    __m128i zero, max, r_cr, g_cb, g_cr, b_cb, c4096;
    __m128i *y_buf, *cb_buf, *cr_buf, *r_buf, *g_buf, *b_buf;
    int srcbump, dstbump, yp, imax;

    if (((ULONG_PTR) (pSrc[0]) & 0x0f)
            || ((ULONG_PTR) (pSrc[1]) & 0x0f)
            || ((ULONG_PTR) (pSrc[2]) & 0x0f)
            || ((ULONG_PTR) (pDst[0]) & 0x0f)
            || ((ULONG_PTR) (pDst[1]) & 0x0f)
            || ((ULONG_PTR) (pDst[2]) & 0x0f)
            || (roi->width & 0x07)
            || (srcStep & 127)
            || (dstStep & 127))
    {
        /* We can't maintain 16-byte alignment. */
        return general_yCbCrToRGB_16s16s_P3P3(pSrc, srcStep,
                                              pDst, dstStep, roi);
    }

    zero = _mm_setzero_si128();
    max = _mm_set1_epi16(255);

    y_buf  = (__m128i*) (pSrc[0]);
    cb_buf = (__m128i*) (pSrc[1]);
    cr_buf = (__m128i*) (pSrc[2]);
    r_buf  = (__m128i*) (pDst[0]);
    g_buf  = (__m128i*) (pDst[1]);
    b_buf  = (__m128i*) (pDst[2]);

    r_cr = _mm_set1_epi16(22986);	/*  1.403 << 14 */
    g_cb = _mm_set1_epi16(-5636);	/* -0.344 << 14 */
    g_cr = _mm_set1_epi16(-11698);	/* -0.714 << 14 */
    b_cb = _mm_set1_epi16(28999);	/*  1.770 << 14 */
    c4096 = _mm_set1_epi16(4096);
    srcbump = srcStep / sizeof(__m128i);
    dstbump = dstStep / sizeof(__m128i);

#ifdef DO_PREFETCH
    /* Prefetch Y's, Cb's, and Cr's. */
    for (yp=0; yp<roi->height; yp++)
    {
        int i;
        for (i=0; i<roi->width * sizeof(INT16) / sizeof(__m128i);
                i += (CACHE_LINE_BYTES / sizeof(__m128i)))
        {
            _mm_prefetch((char*)(&y_buf[i]),  _MM_HINT_NTA);
            _mm_prefetch((char*)(&cb_buf[i]), _MM_HINT_NTA);
            _mm_prefetch((char*)(&cr_buf[i]), _MM_HINT_NTA);
        }
        y_buf  += srcbump;
        cb_buf += srcbump;
        cr_buf += srcbump;
    }
    y_buf  = (__m128i*) (pSrc[0]);
    cb_buf = (__m128i*) (pSrc[1]);
    cr_buf = (__m128i*) (pSrc[2]);
#endif /* DO_PREFETCH */

    imax = roi->width * sizeof(INT16) / sizeof(__m128i);
    for (yp=0; yp<roi->height; ++yp)
    {
        int i;
        for (i=0; i<imax; i++)
        {
            /* In order to use SSE2 signed 16-bit integer multiplication
             * we need to convert the floating point factors to signed int
             * without losing information.
             * The result of this multiplication is 32 bit and we have two
             * SSE instructions that return either the hi or lo word.
             * Thus we will multiply the factors by the highest possible 2^n,
             * take the upper 16 bits of the signed 32-bit result
             * (_mm_mulhi_epi16) and correct this result by multiplying
             * it by 2^(16-n).
             *
             * For the given factors in the conversion matrix the best
             * possible n is 14.
             *
             * Example for calculating r:
             * r = (y>>5) + 128 + (cr*1.403)>>5             // our base formula
             * r = (y>>5) + 128 + (HIWORD(cr*(1.403<<14)<<2))>>5   // see above
             * r = (y+4096)>>5 + (HIWORD(cr*22986)<<2)>>5     // simplification
             * r = ((y+4096)>>2 + HIWORD(cr*22986)) >> 3
             */

            /* y = (y_r_buf[i] + 4096) >> 2 */
            __m128i y, cb, cr, r, g, b;
            y = _mm_load_si128(y_buf + i);
            y = _mm_add_epi16(y, c4096);
            y = _mm_srai_epi16(y, 2);
            /* cb = cb_g_buf[i]; */
            cb = _mm_load_si128(cb_buf + i);
            /* cr = cr_b_buf[i]; */
            cr = _mm_load_si128(cr_buf + i);

            /* (y + HIWORD(cr*22986)) >> 3 */
            r = _mm_add_epi16(y, _mm_mulhi_epi16(cr, r_cr));
            r = _mm_srai_epi16(r, 3);

            /* r_buf[i] = MINMAX(r, 0, 255); */
            _mm_between_epi16(r, zero, max);
            _mm_store_si128(r_buf + i, r);

            /* (y + HIWORD(cb*-5636) + HIWORD(cr*-11698)) >> 3 */
            g = _mm_add_epi16(y, _mm_mulhi_epi16(cb, g_cb));
            g = _mm_add_epi16(g, _mm_mulhi_epi16(cr, g_cr));
            g = _mm_srai_epi16(g, 3);

            /* g_buf[i] = MINMAX(g, 0, 255); */
            _mm_between_epi16(g, zero, max);
            _mm_store_si128(g_buf + i, g);

            /* (y + HIWORD(cb*28999)) >> 3 */
            b = _mm_add_epi16(y, _mm_mulhi_epi16(cb, b_cb));
            b = _mm_srai_epi16(b, 3);
            /* b_buf[i] = MINMAX(b, 0, 255); */
            _mm_between_epi16(b, zero, max);
            _mm_store_si128(b_buf + i, b);
        }
        y_buf  += srcbump;
        cb_buf += srcbump;
        cr_buf += srcbump;
        r_buf += dstbump;
        g_buf += dstbump;
        b_buf += dstbump;
    }

    return PRIMITIVES_SUCCESS;
}