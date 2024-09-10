mlib_status
F_NAME(
    mlib_d64 *dst,
    const mlib_d64 *src,
    mlib_s32 dlb,
    mlib_s32 slb,
    mlib_s32 wid,
    mlib_s32 hgt)
{
	mlib_u8 *pbuff, *buff0, *buff1, *buff2, *buff3, *buff4, *buff5, *buffT;
	mlib_u8 *sl, *sp0, *sp1, *sp2, *sp3, *sp4, *sp5, *sp6, *sp7, *dl;
	__m128d *dp0, *dp1;
	__m128d aa, bb, cc, dd, ee, ff, r0, r1, t0, t1;
	__m128d g0, g1, g2, g3, g4, g5, g6, gg;
	__m128d h0, h1, h2, h3, h4, h5, h6, hh;
	__m128d e_mask;
	mlib_s32 i, j, wid16, tail;

	wid = (wid - KSIZE1) * SSIZE;
	wid16 = (wid + 15) & ~15;
	pbuff = __mlib_malloc(KSIZE1 * wid16);
	buff0 = pbuff;
	buff1 = buff0 + wid16;
	buff2 = buff1 + wid16;
	buff3 = buff2 + wid16;
	buff4 = buff3 + wid16;
	buff5 = buff4 + wid16;

	sl = (mlib_u8 *)src;
	dl = (mlib_u8 *)dst + (KSIZE1 / 2) * (dlb + SSIZE);

	tail = wid & 15;

	((mlib_d64 *)&e_mask)[0] =
		((mlib_d64 *)((__m128d *) mlib_mask128i_arr + tail))[0];
	((mlib_d64 *)&e_mask)[1] =
		((mlib_d64 *)((__m128d *) mlib_mask128i_arr + tail))[1];

	for (j = 0; j < 3; j++) {
		sp0 = buff4;
		sp1 = buff5;
		sp6 = sl;
		sp7 = sl + slb;
		sl += 2 * slb;

		for (i = 0; i < wid; i += 16) {
			g0 = _mm_loadu_pd((mlib_d64 *)sp6);
			g1 = _mm_loadu_pd((mlib_d64 *)(sp6 + SSIZE));
			g2 = _mm_loadu_pd((mlib_d64 *)(sp6 + 2 * SSIZE));
			g3 = _mm_loadu_pd((mlib_d64 *)(sp6 + 3 * SSIZE));
			g4 = _mm_loadu_pd((mlib_d64 *)(sp6 + 4 * SSIZE));
			g5 = _mm_loadu_pd((mlib_d64 *)(sp6 + 5 * SSIZE));
			g6 = _mm_loadu_pd((mlib_d64 *)(sp6 + 6 * SSIZE));
			h0 = _mm_loadu_pd((mlib_d64 *)sp7);
			h1 = _mm_loadu_pd((mlib_d64 *)(sp7 + SSIZE));
			h2 = _mm_loadu_pd((mlib_d64 *)(sp7 + 2 * SSIZE));
			h3 = _mm_loadu_pd((mlib_d64 *)(sp7 + 3 * SSIZE));
			h4 = _mm_loadu_pd((mlib_d64 *)(sp7 + 4 * SSIZE));
			h5 = _mm_loadu_pd((mlib_d64 *)(sp7 + 5 * SSIZE));
			h6 = _mm_loadu_pd((mlib_d64 *)(sp7 + 6 * SSIZE));

			gg = C_COMP(g0, g1);
			hh = C_COMP(h0, h1);
			g2 = C_COMP(g2, g3);
			h2 = C_COMP(h2, h3);
			g4 = C_COMP(g4, g5);
			h4 = C_COMP(h4, h5);
			gg = C_COMP(gg, g2);
			hh = C_COMP(hh, h2);
			gg = C_COMP(gg, g4);
			hh = C_COMP(hh, h4);
			gg = C_COMP(gg, g6);
			hh = C_COMP(hh, h6);

			_mm_storeu_pd((mlib_d64 *)sp0, gg);
			_mm_storeu_pd((mlib_d64 *)sp1, hh);

			sp0 += 16;
			sp1 += 16;
			sp6 += 16;
			sp7 += 16;
		}

		if (j < 2) {
			buffT = buff0;
			buff0 = buff2;
			buff2 = buff4;
			buff4 = buffT;
			buffT = buff1;
			buff1 = buff3;
			buff3 = buff5;
			buff5 = buffT;
		}
	}

	for (j = 0; j <= (hgt - KSIZE1 - 2); j += 2) {
		dp0 = (void *)dl;
		dp1 = (void *)(dl + dlb);
		sp0 = buff0;
		sp1 = buff1;
		sp2 = buff2;
		sp3 = buff3;
		sp4 = buff4;
		sp5 = buff5;
		sp6 = sl;
		sp7 = sl + slb;

/*
 *    line0:           aa
 *    line1:           bb
 *    line2:           cc
 *    line3:           dd
 *    line4:           ee
 *    line5:           ff
 *    line4:  g0 g1 g2 g3 g4 g5 g6
 *    line5:  h0 h1 h2 h3 h4 h5 h6
 */

		for (i = 0; i <= wid - 16; i += 16) {
			g0 = _mm_loadu_pd((mlib_d64 *)sp6);
			g1 = _mm_loadu_pd((mlib_d64 *)(sp6 + SSIZE));
			g2 = _mm_loadu_pd((mlib_d64 *)(sp6 + 2 * SSIZE));
			g3 = _mm_loadu_pd((mlib_d64 *)(sp6 + 3 * SSIZE));
			g4 = _mm_loadu_pd((mlib_d64 *)(sp6 + 4 * SSIZE));
			g5 = _mm_loadu_pd((mlib_d64 *)(sp6 + 5 * SSIZE));
			g6 = _mm_loadu_pd((mlib_d64 *)(sp6 + 6 * SSIZE));
			h0 = _mm_loadu_pd((mlib_d64 *)sp7);
			h1 = _mm_loadu_pd((mlib_d64 *)(sp7 + SSIZE));
			h2 = _mm_loadu_pd((mlib_d64 *)(sp7 + 2 * SSIZE));
			h3 = _mm_loadu_pd((mlib_d64 *)(sp7 + 3 * SSIZE));
			h4 = _mm_loadu_pd((mlib_d64 *)(sp7 + 4 * SSIZE));
			h5 = _mm_loadu_pd((mlib_d64 *)(sp7 + 5 * SSIZE));
			h6 = _mm_loadu_pd((mlib_d64 *)(sp7 + 6 * SSIZE));

			gg = C_COMP(g0, g1);
			hh = C_COMP(h0, h1);
			g2 = C_COMP(g2, g3);
			h2 = C_COMP(h2, h3);
			g4 = C_COMP(g4, g5);
			h4 = C_COMP(h4, h5);
			gg = C_COMP(gg, g2);
			hh = C_COMP(hh, h2);
			gg = C_COMP(gg, g4);
			hh = C_COMP(hh, h4);
			gg = C_COMP(gg, g6);
			hh = C_COMP(hh, h6);

			aa = _mm_loadu_pd((mlib_d64 *)sp0);
			bb = _mm_loadu_pd((mlib_d64 *)sp1);
			cc = _mm_loadu_pd((mlib_d64 *)sp2);
			dd = _mm_loadu_pd((mlib_d64 *)sp3);
			ee = _mm_loadu_pd((mlib_d64 *)sp4);
			ff = _mm_loadu_pd((mlib_d64 *)sp5);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			ff = C_COMP(ff, gg);
			bb = C_COMP(bb, dd);
			bb = C_COMP(bb, ff);

			r0 = C_COMP(aa, bb);
			r1 = C_COMP(bb, hh);

			_mm_storeu_pd((mlib_d64 *)sp0, gg);
			_mm_storeu_pd((mlib_d64 *)sp1, hh);

			_mm_storeu_pd((mlib_d64 *)dp0, r0);
			dp0++;
			_mm_storeu_pd((mlib_d64 *)dp1, r1);
			dp1++;

			sp0 += 16;
			sp1 += 16;
			sp2 += 16;
			sp3 += 16;
			sp4 += 16;
			sp5 += 16;
			sp6 += 16;
			sp7 += 16;
		}

		if (tail) {
			g0 = _mm_loadu_pd((mlib_d64 *)sp6);
			g1 = _mm_loadu_pd((mlib_d64 *)(sp6 + SSIZE));
			g2 = _mm_loadu_pd((mlib_d64 *)(sp6 + 2 * SSIZE));
			g3 = _mm_loadu_pd((mlib_d64 *)(sp6 + 3 * SSIZE));
			g4 = _mm_loadu_pd((mlib_d64 *)(sp6 + 4 * SSIZE));
			g5 = _mm_loadu_pd((mlib_d64 *)(sp6 + 5 * SSIZE));
			g6 = _mm_loadu_pd((mlib_d64 *)(sp6 + 6 * SSIZE));
			h0 = _mm_loadu_pd((mlib_d64 *)sp7);
			h1 = _mm_loadu_pd((mlib_d64 *)(sp7 + SSIZE));
			h2 = _mm_loadu_pd((mlib_d64 *)(sp7 + 2 * SSIZE));
			h3 = _mm_loadu_pd((mlib_d64 *)(sp7 + 3 * SSIZE));
			h4 = _mm_loadu_pd((mlib_d64 *)(sp7 + 4 * SSIZE));
			h5 = _mm_loadu_pd((mlib_d64 *)(sp7 + 5 * SSIZE));
			h6 = _mm_loadu_pd((mlib_d64 *)(sp7 + 6 * SSIZE));

			gg = C_COMP(g0, g1);
			hh = C_COMP(h0, h1);
			g2 = C_COMP(g2, g3);
			h2 = C_COMP(h2, h3);
			g4 = C_COMP(g4, g5);
			h4 = C_COMP(h4, h5);
			gg = C_COMP(gg, g2);
			hh = C_COMP(hh, h2);
			gg = C_COMP(gg, g4);
			hh = C_COMP(hh, h4);
			gg = C_COMP(gg, g6);
			hh = C_COMP(hh, h6);

			aa = _mm_loadu_pd((mlib_d64 *)sp0);
			bb = _mm_loadu_pd((mlib_d64 *)sp1);
			cc = _mm_loadu_pd((mlib_d64 *)sp2);
			dd = _mm_loadu_pd((mlib_d64 *)sp3);
			ee = _mm_loadu_pd((mlib_d64 *)sp4);
			ff = _mm_loadu_pd((mlib_d64 *)sp5);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			ff = C_COMP(ff, gg);
			bb = C_COMP(bb, dd);
			bb = C_COMP(bb, ff);

			r0 = C_COMP(aa, bb);
			r1 = C_COMP(bb, hh);

			_mm_storeu_pd((mlib_d64 *)sp0, gg);
			_mm_storeu_pd((mlib_d64 *)sp1, hh);

			t0 = _mm_loadu_pd((mlib_d64 *)dp0);
			t1 = _mm_loadu_pd((mlib_d64 *)dp1);
			t0 =
			    _mm_or_pd(_mm_and_pd(e_mask, r0),
			    _mm_andnot_pd(e_mask, t0));
			t1 =
			    _mm_or_pd(_mm_and_pd(e_mask, r1),
			    _mm_andnot_pd(e_mask, t1));
			_mm_storeu_pd((mlib_d64 *)dp0, t0);
			_mm_storeu_pd((mlib_d64 *)dp1, t1);
		}

		buffT = buff0;
		buff0 = buff2;
		buff2 = buff4;
		buff4 = buffT;
		buffT = buff1;
		buff1 = buff3;
		buff3 = buff5;
		buff5 = buffT;

		sl += 2 * slb;
		dl += 2 * dlb;
	}

/* last line */

	if (j == (hgt - KSIZE1 - 1)) {
		dp0 = (void *)dl;
		dp1 = (void *)(dl + dlb);
		sp0 = buff0;
		sp1 = buff1;
		sp2 = buff2;
		sp3 = buff3;
		sp4 = buff4;
		sp5 = buff5;
		sp6 = sl;

		for (i = 0; i <= wid - 16; i += 16) {
			g0 = _mm_loadu_pd((mlib_d64 *)sp6);
			g1 = _mm_loadu_pd((mlib_d64 *)(sp6 + SSIZE));
			g2 = _mm_loadu_pd((mlib_d64 *)(sp6 + 2 * SSIZE));
			g3 = _mm_loadu_pd((mlib_d64 *)(sp6 + 3 * SSIZE));
			g4 = _mm_loadu_pd((mlib_d64 *)(sp6 + 4 * SSIZE));
			g5 = _mm_loadu_pd((mlib_d64 *)(sp6 + 5 * SSIZE));
			g6 = _mm_loadu_pd((mlib_d64 *)(sp6 + 6 * SSIZE));

			gg = C_COMP(g0, g1);
			g2 = C_COMP(g2, g3);
			g4 = C_COMP(g4, g5);
			gg = C_COMP(gg, g2);
			gg = C_COMP(gg, g4);
			gg = C_COMP(gg, g6);

			aa = _mm_loadu_pd((mlib_d64 *)sp0);
			bb = _mm_loadu_pd((mlib_d64 *)sp1);
			cc = _mm_loadu_pd((mlib_d64 *)sp2);
			dd = _mm_loadu_pd((mlib_d64 *)sp3);
			ee = _mm_loadu_pd((mlib_d64 *)sp4);
			ff = _mm_loadu_pd((mlib_d64 *)sp5);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			ff = C_COMP(ff, gg);
			bb = C_COMP(bb, dd);
			bb = C_COMP(bb, ff);

			r0 = C_COMP(aa, bb);

			_mm_storeu_pd((mlib_d64 *)dp0, r0);
			dp0++;

			sp0 += 16;
			sp1 += 16;
			sp2 += 16;
			sp3 += 16;
			sp4 += 16;
			sp5 += 16;
			sp6 += 16;
		}

		if (tail) {
			g0 = _mm_loadu_pd((mlib_d64 *)sp6);
			g1 = _mm_loadu_pd((mlib_d64 *)(sp6 + SSIZE));
			g2 = _mm_loadu_pd((mlib_d64 *)(sp6 + 2 * SSIZE));
			g3 = _mm_loadu_pd((mlib_d64 *)(sp6 + 3 * SSIZE));
			g4 = _mm_loadu_pd((mlib_d64 *)(sp6 + 4 * SSIZE));
			g5 = _mm_loadu_pd((mlib_d64 *)(sp6 + 5 * SSIZE));
			g6 = _mm_loadu_pd((mlib_d64 *)(sp6 + 6 * SSIZE));

			gg = C_COMP(g0, g1);
			g2 = C_COMP(g2, g3);
			g4 = C_COMP(g4, g5);
			gg = C_COMP(gg, g2);
			gg = C_COMP(gg, g4);
			gg = C_COMP(gg, g6);

			aa = _mm_loadu_pd((mlib_d64 *)sp0);
			bb = _mm_loadu_pd((mlib_d64 *)sp1);
			cc = _mm_loadu_pd((mlib_d64 *)sp2);
			dd = _mm_loadu_pd((mlib_d64 *)sp3);
			ee = _mm_loadu_pd((mlib_d64 *)sp4);
			ff = _mm_loadu_pd((mlib_d64 *)sp5);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			ff = C_COMP(ff, gg);
			bb = C_COMP(bb, dd);
			bb = C_COMP(bb, ff);

			r0 = C_COMP(aa, bb);

			t0 = _mm_loadu_pd((mlib_d64 *)dp0);
			t0 =
			    _mm_or_pd(_mm_and_pd(e_mask, r0),
			    _mm_andnot_pd(e_mask, t0));
			_mm_storeu_pd((mlib_d64 *)dp0, t0);
		}
	}

	__mlib_free(pbuff);

	return (MLIB_SUCCESS);
}