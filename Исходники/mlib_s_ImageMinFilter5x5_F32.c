mlib_status
F_NAME(
    mlib_f32 *dst,
    const mlib_f32 *src,
    mlib_s32 dlb,
    mlib_s32 slb,
    mlib_s32 wid,
    mlib_s32 hgt)
{
	mlib_u8 *pbuff, *buff0, *buff1, *buff2, *buff3, *buffT;
	mlib_u8 *sl, *sp0, *sp1, *sp2, *sp3, *sp4, *sp5, *dl;
	__m128 *dp0, *dp1;
	__m128 aa, bb, cc, dd, e0, e1, e2, e3, e4, ee, f0, f1, f2, f3, f4, ff,
	    r0, r1, t0, t1;
	__m128 e_mask;
	mlib_s32 i, j, wid16, tail;

	wid = (wid - KSIZE1) * SSIZE;
	wid16 = (wid + 15) & ~15;
	pbuff = __mlib_malloc(4 * wid16);
	buff0 = pbuff;
	buff1 = buff0 + wid16;
	buff2 = buff1 + wid16;
	buff3 = buff2 + wid16;

	sl = (mlib_u8 *)src;
	dl = (mlib_u8 *)dst + 2 * (dlb + SSIZE);

	tail = wid & 15;

	((mlib_d64 *)&e_mask)[0] =
		((mlib_d64 *)((__m128 *) mlib_mask128i_arr + tail))[0];
	((mlib_d64 *)&e_mask)[1] =
		((mlib_d64 *)((__m128 *) mlib_mask128i_arr + tail))[1];

	for (j = 0; j < 2; j++) {
		sp0 = buff0;
		sp1 = buff1;
		sp4 = sl;
		sp5 = sl + slb;
		sl += 2 * slb;

		for (i = 0; i < wid; i += 16) {
			e0 = _mm_loadu_ps((mlib_f32 *)sp4);
			e1 = _mm_loadu_ps((mlib_f32 *)(sp4 + SSIZE));
			e2 = _mm_loadu_ps((mlib_f32 *)(sp4 + 2 * SSIZE));
			e3 = _mm_loadu_ps((mlib_f32 *)(sp4 + 3 * SSIZE));
			e4 = _mm_loadu_ps((mlib_f32 *)(sp4 + 4 * SSIZE));
			f0 = _mm_loadu_ps((mlib_f32 *)sp5);
			f1 = _mm_loadu_ps((mlib_f32 *)(sp5 + SSIZE));
			f2 = _mm_loadu_ps((mlib_f32 *)(sp5 + 2 * SSIZE));
			f3 = _mm_loadu_ps((mlib_f32 *)(sp5 + 3 * SSIZE));
			f4 = _mm_loadu_ps((mlib_f32 *)(sp5 + 4 * SSIZE));

			ee = C_COMP(e0, e1);
			ff = C_COMP(f0, f1);
			e2 = C_COMP(e2, e3);
			f2 = C_COMP(f2, f3);
			ee = C_COMP(ee, e4);
			ff = C_COMP(ff, f4);
			ee = C_COMP(ee, e2);
			ff = C_COMP(ff, f2);

			_mm_storeu_ps((mlib_f32 *)sp0, ee);
			_mm_storeu_ps((mlib_f32 *)sp1, ff);

			sp0 += 16;
			sp1 += 16;
			sp4 += 16;
			sp5 += 16;
		}

		buffT = buff0;
		buff0 = buff2;
		buff2 = buffT;
		buffT = buff1;
		buff1 = buff3;
		buff3 = buffT;
	}

	for (j = 0; j <= (hgt - KSIZE1 - 2); j += 2) {
		dp0 = (void *)dl;
		dp1 = (void *)(dl + dlb);
		sp0 = buff0;
		sp1 = buff1;
		sp2 = buff2;
		sp3 = buff3;
		sp4 = sl;
		sp5 = sl + slb;

/*
 *    line0:        aa
 *    line1:        bb
 *    line2:        cc
 *    line3:        dd
 *    line4:  e0 e1 e2 e3 e4
 *    line5:  f0 f1 f2 f3 f4
 */

		for (i = 0; i <= wid - 16; i += 16) {
			aa = _mm_loadu_ps((mlib_f32 *)sp0);
			bb = _mm_loadu_ps((mlib_f32 *)sp1);
			cc = _mm_loadu_ps((mlib_f32 *)sp2);
			dd = _mm_loadu_ps((mlib_f32 *)sp3);
			e0 = _mm_loadu_ps((mlib_f32 *)sp4);
			e1 = _mm_loadu_ps((mlib_f32 *)(sp4 + SSIZE));
			e2 = _mm_loadu_ps((mlib_f32 *)(sp4 + 2 * SSIZE));
			e3 = _mm_loadu_ps((mlib_f32 *)(sp4 + 3 * SSIZE));
			e4 = _mm_loadu_ps((mlib_f32 *)(sp4 + 4 * SSIZE));
			f0 = _mm_loadu_ps((mlib_f32 *)sp5);
			f1 = _mm_loadu_ps((mlib_f32 *)(sp5 + SSIZE));
			f2 = _mm_loadu_ps((mlib_f32 *)(sp5 + 2 * SSIZE));
			f3 = _mm_loadu_ps((mlib_f32 *)(sp5 + 3 * SSIZE));
			f4 = _mm_loadu_ps((mlib_f32 *)(sp5 + 4 * SSIZE));

			ee = C_COMP(e0, e1);
			ff = C_COMP(f0, f1);
			e2 = C_COMP(e2, e3);
			f2 = C_COMP(f2, f3);
			ee = C_COMP(ee, e4);
			ff = C_COMP(ff, f4);
			ee = C_COMP(ee, e2);
			ff = C_COMP(ff, f2);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			bb = C_COMP(bb, dd);

			r0 = C_COMP(aa, bb);
			r1 = C_COMP(bb, ff);

			_mm_storeu_ps((mlib_f32 *)sp0, ee);
			_mm_storeu_ps((mlib_f32 *)sp1, ff);

			_mm_storeu_ps((mlib_f32 *)dp0, r0);
			dp0++;
			_mm_storeu_ps((mlib_f32 *)dp1, r1);
			dp1++;

			sp0 += 16;
			sp1 += 16;
			sp2 += 16;
			sp3 += 16;
			sp4 += 16;
			sp5 += 16;
		}

		if (tail) {
			aa = _mm_loadu_ps((mlib_f32 *)sp0);
			bb = _mm_loadu_ps((mlib_f32 *)sp1);
			cc = _mm_loadu_ps((mlib_f32 *)sp2);
			dd = _mm_loadu_ps((mlib_f32 *)sp3);
			e0 = _mm_loadu_ps((mlib_f32 *)sp4);
			e1 = _mm_loadu_ps((mlib_f32 *)(sp4 + SSIZE));
			e2 = _mm_loadu_ps((mlib_f32 *)(sp4 + 2 * SSIZE));
			e3 = _mm_loadu_ps((mlib_f32 *)(sp4 + 3 * SSIZE));
			e4 = _mm_loadu_ps((mlib_f32 *)(sp4 + 4 * SSIZE));
			f0 = _mm_loadu_ps((mlib_f32 *)sp5);
			f1 = _mm_loadu_ps((mlib_f32 *)(sp5 + SSIZE));
			f2 = _mm_loadu_ps((mlib_f32 *)(sp5 + 2 * SSIZE));
			f3 = _mm_loadu_ps((mlib_f32 *)(sp5 + 3 * SSIZE));
			f4 = _mm_loadu_ps((mlib_f32 *)(sp5 + 4 * SSIZE));

			ee = C_COMP(e0, e1);
			ff = C_COMP(f0, f1);
			e2 = C_COMP(e2, e3);
			f2 = C_COMP(f2, f3);
			ee = C_COMP(ee, e4);
			ff = C_COMP(ff, f4);
			ee = C_COMP(ee, e2);
			ff = C_COMP(ff, f2);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			bb = C_COMP(bb, dd);

			r0 = C_COMP(aa, bb);
			r1 = C_COMP(bb, ff);

			_mm_storeu_ps((mlib_f32 *)sp0, ee);
			_mm_storeu_ps((mlib_f32 *)sp1, ff);

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

		buffT = buff0;
		buff0 = buff2;
		buff2 = buffT;
		buffT = buff1;
		buff1 = buff3;
		buff3 = buffT;

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
		sp4 = sl;

		for (i = 0; i <= wid - 16; i += 16) {
			aa = _mm_loadu_ps((mlib_f32 *)sp0);
			bb = _mm_loadu_ps((mlib_f32 *)sp1);
			cc = _mm_loadu_ps((mlib_f32 *)sp2);
			dd = _mm_loadu_ps((mlib_f32 *)sp3);
			e0 = _mm_loadu_ps((mlib_f32 *)sp4);
			e1 = _mm_loadu_ps((mlib_f32 *)(sp4 + SSIZE));
			e2 = _mm_loadu_ps((mlib_f32 *)(sp4 + 2 * SSIZE));
			e3 = _mm_loadu_ps((mlib_f32 *)(sp4 + 3 * SSIZE));
			e4 = _mm_loadu_ps((mlib_f32 *)(sp4 + 4 * SSIZE));

			ee = C_COMP(e0, e1);
			e2 = C_COMP(e2, e3);
			ee = C_COMP(ee, e4);
			ee = C_COMP(ee, e2);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			bb = C_COMP(bb, dd);

			r0 = C_COMP(aa, bb);

			_mm_storeu_ps((mlib_f32 *)dp0, r0);
			dp0++;

			sp0 += 16;
			sp1 += 16;
			sp2 += 16;
			sp3 += 16;
			sp4 += 16;
		}

		if (tail) {
			aa = _mm_loadu_ps((mlib_f32 *)sp0);
			bb = _mm_loadu_ps((mlib_f32 *)sp1);
			cc = _mm_loadu_ps((mlib_f32 *)sp2);
			dd = _mm_loadu_ps((mlib_f32 *)sp3);
			e0 = _mm_loadu_ps((mlib_f32 *)sp4);
			e1 = _mm_loadu_ps((mlib_f32 *)(sp4 + SSIZE));
			e2 = _mm_loadu_ps((mlib_f32 *)(sp4 + 2 * SSIZE));
			e3 = _mm_loadu_ps((mlib_f32 *)(sp4 + 3 * SSIZE));
			e4 = _mm_loadu_ps((mlib_f32 *)(sp4 + 4 * SSIZE));

			ee = C_COMP(e0, e1);
			e2 = C_COMP(e2, e3);
			ee = C_COMP(ee, e4);
			ee = C_COMP(ee, e2);

			bb = C_COMP(bb, cc);
			dd = C_COMP(dd, ee);
			bb = C_COMP(bb, dd);

			r0 = C_COMP(aa, bb);

			t0 = _mm_loadu_ps((mlib_f32 *)dp0);
			t0 =
			    _mm_or_ps(_mm_and_ps(e_mask, r0),
			    _mm_andnot_ps(e_mask, t0));
			_mm_storeu_ps((mlib_f32 *)dp0, t0);
		}
	}

	__mlib_free(pbuff);

	return (MLIB_SUCCESS);
}