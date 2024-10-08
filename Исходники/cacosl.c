ldcomplex
cacosl(ldcomplex z) {
	long double x, y, t, R, S, A, Am1, B, y2, xm1, xp1, Apx;
	int ix, iy, hx, hy;
	ldcomplex ans;

	x = LD_RE(z);
	y = LD_IM(z);
	hx = HI_XWORD(x);
	hy = HI_XWORD(y);
	ix = hx & 0x7fffffff;
	iy = hy & 0x7fffffff;

	/* x is 0 */
	if (x == zero) {
		if (y == zero || (iy >= 0x7fff0000)) {
			LD_RE(ans) = pi_2 + pi_2_l;
			LD_IM(ans) = -y;
			return (ans);
		}
	}

	/* |y| is inf or NaN */
	if (iy >= 0x7fff0000) {
		if (isinfl(y)) {	/* cacos(x + i inf) =  pi/2 - i inf */
			LD_IM(ans) = -y;
			if (ix < 0x7fff0000) {
				LD_RE(ans) = pi_2 + pi_2_l;
			} else if (isinfl(x)) {
				if (hx >= 0)
					LD_RE(ans) = pi_4 + pi_4_l;
				else
					LD_RE(ans) = pi3_4 + pi3_4_l;
			} else {
				LD_RE(ans) = x;
			}
		} else {		/* cacos(x + i NaN) = NaN  + i NaN */
			LD_RE(ans) = y + x;
			if (isinfl(x))
				LD_IM(ans) = -fabsl(x);
			else
				LD_IM(ans) = y;
		}
		return (ans);
	}

	y = fabsl(y);

	if (ix >= 0x7fff0000) {	/* x is inf or NaN */
		if (isinfl(x)) {	/* x is INF */
			LD_IM(ans) = -fabsl(x);
			if (iy >= 0x7fff0000) {
				if (isinfl(y)) {
					/* INDENT OFF */
					/* cacos(inf + i inf) = pi/4 - i inf */
					/* cacos(-inf+ i inf) =3pi/4 - i inf */
					/* INDENT ON */
					if (hx >= 0)
						LD_RE(ans) = pi_4 + pi_4_l;
					else
						LD_RE(ans) = pi3_4 + pi3_4_l;
				} else
					/* INDENT OFF */
					/* cacos(inf + i NaN) = NaN  - i inf  */
					/* INDENT ON */
					LD_RE(ans) = y + y;
			} else {
				/* INDENT OFF */
				/* cacos(inf + iy ) = 0  - i inf */
				/* cacos(-inf+ iy  ) = pi - i inf */
				/* INDENT ON */
				if (hx >= 0)
					LD_RE(ans) = zero;
				else
					LD_RE(ans) = pi + pi_l;
			}
		} else {		/* x is NaN */
			/* INDENT OFF */
			/*
			 * cacos(NaN + i inf) = NaN  - i inf
			 * cacos(NaN + i y  ) = NaN  + i NaN
			 * cacos(NaN + i NaN) = NaN  + i NaN
			 */
			/* INDENT ON */
			LD_RE(ans) = x + y;
			if (iy >= 0x7fff0000) {
				LD_IM(ans) = -y;
			} else {
				LD_IM(ans) = x;
			}
		}
		if (hy < 0)
			LD_IM(ans) = -LD_IM(ans);
		return (ans);
	}

	if (y == zero) {	/* region 1: y=0 */
		if (ix < 0x3fff0000) {	/* |x| < 1 */
			LD_RE(ans) = acosl(x);
			LD_IM(ans) = zero;
		} else {
			LD_RE(ans) = zero;
			x = fabsl(x);
			if (ix >= ip1)	/* i386 ? 2**65 : 2**114 */
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
	} else if (y <= E * fabsl(fabsl(x) - one)) {
		/* region 2: y < tiny*||x|-1| */
		if (ix < 0x3fff0000) {	/* x < 1 */
			LD_RE(ans) = acosl(x);
			x = fabsl(x);
			LD_IM(ans) = y / sqrtl((one + x) * (one - x));
		} else if (ix >= ip1) {	/* i386 ? 2**65 : 2**114 */
			if (hx >= 0)
				LD_RE(ans) = y / x;
			else {
				if (ix >= ip1 + 0x00040000)
					LD_RE(ans) = pi + pi_l;
				else {
					t = pi_l + y / x;
					LD_RE(ans) = pi + t;
				}
			}
			LD_IM(ans) = ln2 + logl(fabsl(x));
		} else {
			x = fabsl(x);
			t = sqrtl((x - one) * (x + one));
			LD_RE(ans) = (hx >= 0)? y / t : pi - (y / t - pi_l);
			if (ix >= 0x3fff8000)	/* x > Acrossover */
				LD_IM(ans) = logl(x + t);
			else
				LD_IM(ans) = log1pl(t - (one - x));
		}
	} else if (y < Foursqrtu) {	/* region 3 */
		t = sqrtl(y);
		LD_RE(ans) = (hx >= 0)? t : pi + pi_l;
		LD_IM(ans) = t;
	} else if (E * y - one >= fabsl(x)) {	/* region 4 */
		LD_RE(ans) = pi_2 + pi_2_l;
		LD_IM(ans) = ln2 + logl(y);
	} else if (ix >= 0x5ffb0000 || iy >= 0x5ffb0000) {
		/* region 5: x+1 and y are both (>= sqrt(max)/8) i.e. 2**8188 */
		t = x / y;
		LD_RE(ans) = atan2l(y, x);
		LD_IM(ans) = ln2 + logl(y) + half * log1pl(t * t);
	} else if (fabsl(x) < Foursqrtu) {
		/* region 6: x is very small, < 4sqrt(min) */
		LD_RE(ans) = pi_2 + pi_2_l;
		A = sqrtl(one + y * y);
		if (iy >= 0x3fff8000)	/* if y > Acrossover */
			LD_IM(ans) = logl(y + A);
		else
			LD_IM(ans) = half * log1pl((y + y) * (y + A));
	} else {	/* safe region */
		t = fabsl(x);
		y2 = y * y;
		xp1 = t + one;
		xm1 = t - one;
		R = sqrtl(xp1 * xp1 + y2);
		S = sqrtl(xm1 * xm1 + y2);
		A = half * (R + S);
		B = t / A;

		if (B <= Bcrossover)
			LD_RE(ans) = (hx >= 0)? acosl(B) : acosl(-B);
		else {		/* use atan and an accurate approx to a-x */
			Apx = A + t;
			if (t <= one)
				LD_RE(ans) = atan2l(sqrtl(half * Apx * (y2 /
					(R + xp1) + (S - xm1))), x);
			else
				LD_RE(ans) = atan2l((y * sqrtl(half * (Apx /
					(R + xp1) + Apx / (S + xm1)))), x);
		}
		if (A <= Acrossover) {
			/* use log1p and an accurate approx to A-1 */
			if (ix < 0x3fff0000)
				Am1 = half * (y2 / (R + xp1) + y2 / (S - xm1));
			else
				Am1 = half * (y2 / (R + xp1) + (S + xm1));
			LD_IM(ans) = log1pl(Am1 + sqrtl(Am1 * (A + one)));
		} else {
			LD_IM(ans) = logl(A + sqrtl(A * A - one));
		}
	}

	if (hy >= 0)
		LD_IM(ans) = -LD_IM(ans);

	return (ans);
}