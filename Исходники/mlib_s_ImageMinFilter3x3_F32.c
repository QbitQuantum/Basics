mlib_status
F_NAME(
    mlib_f32 *dst,
    const mlib_f32 *src,
    mlib_s32 dlb,
    mlib_s32 slb,
    mlib_s32 wid,
    mlib_s32 hgt)
{
    mlib_u8 *buff, *buff1;
    mlib_u8 *sl, *sp0, *sp1, *sp2, *sp3, *dl;
    __m128 *dp0, *dp1;
    __m128 aa, bb, c0, c1, c2, cc, d0, d1, d2, dd, r0, r1, t0, t1;
    __m128 e_mask, mask;
    mlib_s32 i, j, wid16, tail;

    wid = (wid - 2) * SSIZE;
    wid16 = (wid + 15) & ~15;
    buff = __mlib_malloc(2 * wid16);
    buff1 = buff + wid16;

    sl = (mlib_u8 *)src;
    /* dst ptrs skip top j and left col */
    dl = (mlib_u8 *)dst + dlb + SSIZE;

    tail = wid & 15;

    ((mlib_d64 *)&e_mask)[0] =
        ((mlib_d64 *)((__m128 *) mlib_mask128i_arr + tail))[0];
    ((mlib_d64 *)&e_mask)[1] =
        ((mlib_d64 *)((__m128 *) mlib_mask128i_arr + tail))[1];

    sp0 = buff;
    sp1 = buff1;
    sp2 = sl;
    sp3 = sp2 + slb;
    sl += 2 * slb;


    for (i = 0; i < wid; i += 16) {
        c0 = _mm_loadu_ps((mlib_f32 *)sp2);
        c1 = _mm_loadu_ps((mlib_f32 *)(sp2 + SSIZE));
        c2 = _mm_loadu_ps((mlib_f32 *)(sp2 + 2 * SSIZE));
        d0 = _mm_loadu_ps((mlib_f32 *)sp3);
        d1 = _mm_loadu_ps((mlib_f32 *)(sp3 + SSIZE));
        d2 = _mm_loadu_ps((mlib_f32 *)(sp3 + 2 * SSIZE));

        cc = C_COMP(c0, c1);
        dd = C_COMP(d0, d1);
        cc = C_COMP(cc, c2);
        dd = C_COMP(dd, d2);


        _mm_storeu_ps((mlib_f32 *)sp0, cc);
        _mm_storeu_ps((mlib_f32 *)sp1, dd);

        sp0 += 16;
        sp1 += 16;
        sp2 += 16;
        sp3 += 16;
    }

    for (j = 0; j <= (hgt - 2 - 2); j += 2) {
        dp0 = (void *)dl;
        dp1 = (void *)(dl + dlb);
        sp0 = buff;
        sp1 = buff1;
        sp2 = sl;
        sp3 = sp2 + slb;

        /*
         *    line0:     aa
         *    line1:     bb
         *    line2:  c0 c1 c2
         *    line3:  d0 d1 d2
         */

        for (i = 0; i <= wid - 16; i += 16) {

            aa = _mm_loadu_ps((mlib_f32 *)sp0);
            bb = _mm_loadu_ps((mlib_f32 *)sp1);
            c0 = _mm_loadu_ps((mlib_f32 *)sp2);
            c1 = _mm_loadu_ps((mlib_f32 *)(sp2 + SSIZE));
            c2 = _mm_loadu_ps((mlib_f32 *)(sp2 + 2 * SSIZE));
            d0 = _mm_loadu_ps((mlib_f32 *)sp3);
            d1 = _mm_loadu_ps((mlib_f32 *)(sp3 + SSIZE));
            d2 = _mm_loadu_ps((mlib_f32 *)(sp3 + 2 * SSIZE));

            cc = C_COMP(c0, c1);
            dd = C_COMP(d0, d1);
            cc = C_COMP(cc, c2);
            dd = C_COMP(dd, d2);

            bb = C_COMP(bb, cc);
            r0 = C_COMP(aa, bb);
            r1 = C_COMP(bb, dd);


            _mm_storeu_ps((mlib_f32 *)sp0, cc);
            _mm_storeu_ps((mlib_f32 *)sp1, dd);

            _mm_storeu_ps((mlib_f32 *)dp0, r0);
            dp0++;
            _mm_storeu_ps((mlib_f32 *)dp1, r1);
            dp1++;

            sp0 += 16;
            sp1 += 16;
            sp2 += 16;
            sp3 += 16;
        }

        if (tail) {
            aa = _mm_loadu_ps((mlib_f32 *)sp0);
            bb = _mm_loadu_ps((mlib_f32 *)sp1);
            c0 = _mm_loadu_ps((mlib_f32 *)sp2);
            c1 = _mm_loadu_ps((mlib_f32 *)(sp2 + SSIZE));
            c2 = _mm_loadu_ps((mlib_f32 *)(sp2 + 2 * SSIZE));
            d0 = _mm_loadu_ps((mlib_f32 *)sp3);
            d1 = _mm_loadu_ps((mlib_f32 *)(sp3 + SSIZE));
            d2 = _mm_loadu_ps((mlib_f32 *)(sp3 + 2 * SSIZE));

            cc = C_COMP(c0, c1);
            dd = C_COMP(d0, d1);
            cc = C_COMP(cc, c2);
            dd = C_COMP(dd, d2);

            bb = C_COMP(bb, cc);
            r0 = C_COMP(aa, bb);
            r1 = C_COMP(bb, dd);

            _mm_storeu_ps((mlib_f32 *)sp0, cc);
            _mm_storeu_ps((mlib_f32 *)sp1, dd);

            t0 = _mm_loadu_ps((mlib_f32 *)dp0);
            t1 = _mm_loadu_ps((mlib_f32 *)dp1);
            t0 =
                _mm_or_ps(_mm_and_ps(e_mask, r0),
                          _mm_andnot_ps(e_mask, t0));
            t1 =
                _mm_or_ps(_mm_and_ps(e_mask, r1),
                          _mm_andnot_ps(e_mask, t1));
            _mm_storeu_ps((mlib_f32 *)dp0, t0);
            _mm_storeu_ps((mlib_f32 *)dp1, t1);
        }

        sl += 2 * slb;
        dl += 2 * dlb;
    }

    /* last line */

    if (j == (hgt - 3)) {
        dp0 = (void *)dl;
        dp1 = (void *)(dl + dlb);
        sp0 = buff;
        sp1 = buff1;
        sp2 = sl;

        for (i = 0; i <= wid - 16; i += 16) {
            aa = _mm_loadu_ps((mlib_f32 *)sp0);
            bb = _mm_loadu_ps((mlib_f32 *)sp1);
            c0 = _mm_loadu_ps((mlib_f32 *)sp2);
            c1 = _mm_loadu_ps((mlib_f32 *)(sp2 + SSIZE));
            c2 = _mm_loadu_ps((mlib_f32 *)(sp2 + 2 * SSIZE));

            cc = C_COMP(c0, c1);
            cc = C_COMP(cc, c2);

            r0 = C_COMP(aa, bb);
            r0 = C_COMP(r0, cc);

            _mm_storeu_ps((mlib_f32 *)dp0, r0);
            dp0++;

            sp0 += 16;
            sp1 += 16;
            sp2 += 16;
        }

        if (tail) {
            aa = _mm_loadu_ps((mlib_f32 *)sp0);
            bb = _mm_loadu_ps((mlib_f32 *)sp1);
            c0 = _mm_loadu_ps((mlib_f32 *)sp2);
            c1 = _mm_loadu_ps((mlib_f32 *)(sp2 + SSIZE));
            c2 = _mm_loadu_ps((mlib_f32 *)(sp2 + 2 * SSIZE));

            c1 = C_COMP(c0, c1);
            cc = C_COMP(c1, c2);

            r0 = C_COMP(aa, bb);
            r0 = C_COMP(r0, cc);

            t0 = _mm_loadu_ps((mlib_f32 *)dp0);
            t0 =
                _mm_or_ps(_mm_and_ps(e_mask, r0),
                          _mm_andnot_ps(e_mask, t0));
            _mm_storeu_ps((mlib_f32 *)dp0, t0);
        }
    }

    __mlib_free(buff);

    return (MLIB_SUCCESS);
}