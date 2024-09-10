/* For data organized into a row for each bit (8 * elem_size rows), transpose
 * the bytes. */
int64_t bshuf_trans_byte_bitrow_sse2(void* in, void* out, const size_t size,
				     const size_t elem_size) {

    char* in_b = (char*) in;
    char* out_b = (char*) out;
    size_t nrows = 8 * elem_size;
    size_t nbyte_row = size / 8;
    size_t ii, jj;

    __m128i a0, b0, c0, d0, e0, f0, g0, h0;
    __m128i a1, b1, c1, d1, e1, f1, g1, h1;
    __m128 *as, *bs, *cs, *ds, *es, *fs, *gs, *hs;

    CHECK_MULT_EIGHT(size);

    for (ii = 0; ii + 7 < nrows; ii += 8) {
        for (jj = 0; jj + 15 < nbyte_row; jj += 16) {
            a0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 0)*nbyte_row + jj]);
            b0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 1)*nbyte_row + jj]);
            c0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 2)*nbyte_row + jj]);
            d0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 3)*nbyte_row + jj]);
            e0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 4)*nbyte_row + jj]);
            f0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 5)*nbyte_row + jj]);
            g0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 6)*nbyte_row + jj]);
            h0 = _mm_loadu_si128((__m128i *) &in_b[(ii + 7)*nbyte_row + jj]);


            a1 = _mm_unpacklo_epi8(a0, b0);
            b1 = _mm_unpacklo_epi8(c0, d0);
            c1 = _mm_unpacklo_epi8(e0, f0);
            d1 = _mm_unpacklo_epi8(g0, h0);
            e1 = _mm_unpackhi_epi8(a0, b0);
            f1 = _mm_unpackhi_epi8(c0, d0);
            g1 = _mm_unpackhi_epi8(e0, f0);
            h1 = _mm_unpackhi_epi8(g0, h0);


            a0 = _mm_unpacklo_epi16(a1, b1);
            b0 = _mm_unpacklo_epi16(c1, d1);
            c0 = _mm_unpackhi_epi16(a1, b1);
            d0 = _mm_unpackhi_epi16(c1, d1);

            e0 = _mm_unpacklo_epi16(e1, f1);
            f0 = _mm_unpacklo_epi16(g1, h1);
            g0 = _mm_unpackhi_epi16(e1, f1);
            h0 = _mm_unpackhi_epi16(g1, h1);


            a1 = _mm_unpacklo_epi32(a0, b0);
            b1 = _mm_unpackhi_epi32(a0, b0);

            c1 = _mm_unpacklo_epi32(c0, d0);
            d1 = _mm_unpackhi_epi32(c0, d0);

            e1 = _mm_unpacklo_epi32(e0, f0);
            f1 = _mm_unpackhi_epi32(e0, f0);

            g1 = _mm_unpacklo_epi32(g0, h0);
            h1 = _mm_unpackhi_epi32(g0, h0);

            /*  We don't have a storeh instruction for integers, so interpret */
            /*  as a float. Have a storel (_mm_storel_epi64). */
            as = (__m128 *) &a1;
            bs = (__m128 *) &b1;
            cs = (__m128 *) &c1;
            ds = (__m128 *) &d1;
            es = (__m128 *) &e1;
            fs = (__m128 *) &f1;
            gs = (__m128 *) &g1;
            hs = (__m128 *) &h1;

            _mm_storel_pi((__m64 *) &out_b[(jj + 0) * nrows + ii], *as);
            _mm_storel_pi((__m64 *) &out_b[(jj + 2) * nrows + ii], *bs);
            _mm_storel_pi((__m64 *) &out_b[(jj + 4) * nrows + ii], *cs);
            _mm_storel_pi((__m64 *) &out_b[(jj + 6) * nrows + ii], *ds);
            _mm_storel_pi((__m64 *) &out_b[(jj + 8) * nrows + ii], *es);
            _mm_storel_pi((__m64 *) &out_b[(jj + 10) * nrows + ii], *fs);
            _mm_storel_pi((__m64 *) &out_b[(jj + 12) * nrows + ii], *gs);
            _mm_storel_pi((__m64 *) &out_b[(jj + 14) * nrows + ii], *hs);

            _mm_storeh_pi((__m64 *) &out_b[(jj + 1) * nrows + ii], *as);
            _mm_storeh_pi((__m64 *) &out_b[(jj + 3) * nrows + ii], *bs);
            _mm_storeh_pi((__m64 *) &out_b[(jj + 5) * nrows + ii], *cs);
            _mm_storeh_pi((__m64 *) &out_b[(jj + 7) * nrows + ii], *ds);
            _mm_storeh_pi((__m64 *) &out_b[(jj + 9) * nrows + ii], *es);
            _mm_storeh_pi((__m64 *) &out_b[(jj + 11) * nrows + ii], *fs);
            _mm_storeh_pi((__m64 *) &out_b[(jj + 13) * nrows + ii], *gs);
            _mm_storeh_pi((__m64 *) &out_b[(jj + 15) * nrows + ii], *hs);
        }
        for (jj = nbyte_row - nbyte_row % 16; jj < nbyte_row; jj ++) {
            out_b[jj * nrows + ii + 0] = in_b[(ii + 0)*nbyte_row + jj];
            out_b[jj * nrows + ii + 1] = in_b[(ii + 1)*nbyte_row + jj];
            out_b[jj * nrows + ii + 2] = in_b[(ii + 2)*nbyte_row + jj];
            out_b[jj * nrows + ii + 3] = in_b[(ii + 3)*nbyte_row + jj];
            out_b[jj * nrows + ii + 4] = in_b[(ii + 4)*nbyte_row + jj];
            out_b[jj * nrows + ii + 5] = in_b[(ii + 5)*nbyte_row + jj];
            out_b[jj * nrows + ii + 6] = in_b[(ii + 6)*nbyte_row + jj];
            out_b[jj * nrows + ii + 7] = in_b[(ii + 7)*nbyte_row + jj];
        }
    }
    return size * elem_size;
}