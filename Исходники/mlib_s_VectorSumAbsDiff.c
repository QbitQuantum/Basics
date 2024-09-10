mlib_status
__mlib_VectorSumAbsDiff_S8_Sat(
    mlib_d64 *z,
    const mlib_s8 *x,
    const mlib_s8 *y,
    mlib_s32 n)
{
    if (n <= 0)
        return (MLIB_FAILURE);

    mlib_s32 i, nstep, ax, ay, n1, n2, n3, diff, sum = 0;
    mlib_s8 *px = (mlib_s8 *)x, *py = (mlib_s8 *)y;
    __m128i zero, xbuf, ybuf, zbuf, mext, mbuf;
    zero = _mm_setzero_si128();
    zbuf = zero;

    nstep = 16 / sizeof (mlib_s8);
    ax = (mlib_addr)x & 15;
    ay = (mlib_addr)y & 15;
    n1 = ((16 - ax) & 15) / sizeof (mlib_s8);
    n2 = (n - n1) / nstep;
    n3 = n - n1 - n2 * nstep;

    if (n2 < 1) {
        for (i = 0; i < n; i++) {
            diff = (mlib_s32)(*px++) - (*py++);
            sum += ABS_VALUE(diff);
        }
        *z = sum;
    } else {
        for (i = 0; i < n1; i++) {
            diff = (mlib_s32)(*px++) - (*py++);
            sum += ABS_VALUE(diff);
        }
        if (ax == ay) {
            for (i = 0; i < n2; i++) {
                xbuf = _mm_load_si128((__m128i *)px);
                ybuf = _mm_load_si128((__m128i *)py);
                mext = _mm_cmpgt_epi8(ybuf, xbuf);
                mbuf = _mm_sub_epi8(xbuf, ybuf);
                mbuf = _mm_xor_si128(mbuf, mext);
                mbuf = _mm_sub_epi8(mbuf, mext);
                mbuf = _mm_sad_epu8(mbuf, zero);
                zbuf = _mm_add_epi64(zbuf, mbuf);
                px += nstep;
                py += nstep;
            }
        } else {
            for (i = 0; i < n2; i++) {
                xbuf = _mm_load_si128((__m128i *)px);
                ybuf = _mm_loadu_si128((__m128i *)py);
                mext = _mm_cmpgt_epi8(ybuf, xbuf);
                mbuf = _mm_sub_epi8(xbuf, ybuf);
                mbuf = _mm_xor_si128(mbuf, mext);
                mbuf = _mm_sub_epi8(mbuf, mext);
                mbuf = _mm_sad_epu8(mbuf, zero);
                zbuf = _mm_add_epi64(zbuf, mbuf);
                px += nstep;
                py += nstep;
            }
        }
        for (i = 0; i < n3; i++) {
            diff = (mlib_s32)(*px++) - (*py++);
            sum += ABS_VALUE(diff);
        }

        mlib_d64 dsum = sum;
        long long pz[2];
        _mm_storeu_si128((__m128i *)pz, zbuf);
        dsum += pz[0];
        dsum += pz[1];
        *z = dsum;
    }
    return (MLIB_SUCCESS);
}