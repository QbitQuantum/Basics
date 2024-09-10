ldcomplex
casinl(ldcomplex z) {
	long double x, y, t, R, S, A, Am1, B, y2, xm1, xp1, Apx;
	int ix, iy, hx, hy;
	ldcomplex ans;

	x = LD_RE(z);
	y = LD_IM(z);
	hx = HI_XWORD(x);
	hy = HI_XWORD(y);
	ix = hx & 0x7fffffff;
	iy = hy & 0x7fffffff;
	x = fabsl(x);
	y = fabsl(y);

	/* special cases */

	/* x is inf or NaN */
	if (ix >= 0x7fff0000) {	/* x is inf or NaN */
		if (isinfl(x)) {	/* x is INF */
			LD_IM(ans) = x;
			if (iy >= 0x7fff0000) {
				if (isinfl(y))
					/* casin(inf + i inf) = pi/4 + i inf */
					LD_RE(ans) = pi_4 + pi_4_l;
				else	/* casin(inf + i NaN) = NaN + i inf */
					LD_RE(ans) = y + y;
			} else	/* casin(inf + iy) = pi/2 + i inf */
				LD_RE(ans) = pi_2 + pi_2_l;
		} else {		/* x is NaN */
			if (iy >= 0x7fff0000) {
				/* INDENT OFF */
				/*
				 * casin(NaN + i inf) = NaN  + i inf
				 * casin(NaN + i NaN) = NaN  + i NaN
				 */
				/* INDENT ON */
				LD_IM(ans) = y + y;
				LD_RE(ans) = x + x;
			} else {
				/* INDENT OFF */
				/* casin(NaN + i y  ) = NaN  + i NaN */
				/* INDENT ON */
				LD_IM(ans) = LD_RE(ans) = x + y;
			}
		}
		if (hx < 0)
			LD_RE(ans) = -LD_RE(ans);
		if (hy < 0)
			LD_IM(ans) = -LD_IM(ans);
		return (ans);
	}

	/* casin(+0 + i 0) = 0 + i 0. */
	if (x == zero && y == zero)
		return (z);

	if (iy >= 0x7fff0000) {	/* y is inf or NaN */
		if (isinfl(y)) {	/* casin( x + i inf ) = 0 + i inf */
			LD_IM(ans) = y;
			LD_RE(ans) = zero;
		} else {		/* casin( x + i NaN ) = NaN + i NaN */
			LD_IM(ans) = x + y;
			if (x == zero)
				LD_RE(ans) = x;
			else
				LD_RE(ans) = y;
		}
		if (hx < 0)
			LD_RE(ans) = -LD_RE(ans);
		if (hy < 0)
			LD_IM(ans) = -LD_IM(ans);
		return (ans);
	}

	if (y == zero) {	/* region 1: y=0 */
		if (ix < 0x3fff0000) {	/* |x| < 1 */
			LD_RE(ans) = asinl(x);
			LD_IM(ans) = zero;
		} else {
			LD_RE(ans) = pi_2 + pi_2_l;
			if (ix >= ip1)	/* |x| >= i386 ? 2**65 : 2**114 */
				LD_IM(ans) = ln2 + logl(x);
			else if (ix >= 0x3fff8000)	/* x > Acrossover */
				LD_IM(ans) = logl(x + sqrtl((x - one) * (x +
					one)));
			else {
				xm1 = x - one;
				LD_IM(ans) = log1pl(xm1 + sqrtl(xm1 * (x +
					one)));
			}
		}
	} else if (y <= E * fabsl(x - one)) {	/* region 2: y < tiny*|x-1| */
		if (ix < 0x3fff0000) {	/* x < 1 */
			LD_RE(ans) = asinl(x);
			LD_IM(ans) = y / sqrtl((one + x) * (one - x));
		} else {
			LD_RE(ans) = pi_2 + pi_2_l;
			if (ix >= ip1)	/* i386 ? 2**65 : 2**114 */
				LD_IM(ans) = ln2 + logl(x);
			else if (ix >= 0x3fff8000)	/* x > Acrossover */
				LD_IM(ans) = logl(x + sqrtl((x - one) * (x +
					one)));
			else
				LD_IM(ans) = log1pl((x - one) + sqrtl((x -
					one) * (x + one)));
		}
	} else if (y < Foursqrtu) {	/* region 3 */
		t = sqrtl(y);
		LD_RE(ans) = pi_2 - (t - pi_2_l);
		LD_IM(ans) = t;
	} else if (E * y - one >= x) {	/* region 4 */
		LD_RE(ans) = x / y;	/* need to fix underflow cases */
		LD_IM(ans) = ln2 + logl(y);
	} else if (ix >= 0x5ffb0000 || iy >= 0x5ffb0000) {
		/* region 5: x+1 and y are both (>= sqrt(max)/8) i.e. 2**8188 */
		t = x / y;
		LD_RE(ans) = atanl(t);
		LD_IM(ans) = ln2 + logl(y) + half * log1pl(t * t);
	} else if (x < Foursqrtu) {
		/* region 6: x is very small, < 4sqrt(min) */
		A = sqrtl(one + y * y);
		LD_RE(ans) = x / A;	/* may underflow */
		if (iy >= 0x3fff8000)	/* if y > Acrossover */
			LD_IM(ans) = logl(y + A);
		else
			LD_IM(ans) = half * log1pl((y + y) * (y + A));
	} else {	/* safe region */
		y2 = y * y;
		xp1 = x + one;
		xm1 = x - one;
		R = sqrtl(xp1 * xp1 + y2);
		S = sqrtl(xm1 * xm1 + y2);
		A = half * (R + S);
		B = x / A;
		if (B <= Bcrossover)
			LD_RE(ans) = asinl(B);
		else {		/* use atan and an accurate approx to a-x */
			Apx = A + x;
			if (x <= one)
				LD_RE(ans) = atanl(x / sqrtl(half * Apx * (y2 /
					(R + xp1) + (S - xm1))));
			else
				LD_RE(ans) = atanl(x / (y * sqrtl(half * (Apx /
					(R + xp1) + Apx / (S + xm1)))));
		}
		if (A <= Acrossover) {
			/* use log1p and an accurate approx to A-1 */
			if (x < one)
				Am1 = half * (y2 / (R + xp1) + y2 / (S - xm1));
			else
				Am1 = half * (y2 / (R + xp1) + (S + xm1));
			LD_IM(ans) = log1pl(Am1 + sqrtl(Am1 * (A + one)));
		} else {
			LD_IM(ans) = logl(A + sqrtl(A * A - one));
		}
	}

	if (hx < 0)
		LD_RE(ans) = -LD_RE(ans);
	if (hy < 0)
		LD_IM(ans) = -LD_IM(ans);

	return (ans);
}