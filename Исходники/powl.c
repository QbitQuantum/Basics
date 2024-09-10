long double powl(long double x, long double y)
{
	/* double F, Fa, Fb, G, Ga, Gb, H, Ha, Hb */
	int i, nflg, iyflg, yoddint;
	long e;
	volatile long double z=0;
	long double w=0, W=0, Wa=0, Wb=0, ya=0, yb=0, u=0;

	/* make sure no invalid exception is raised by nan comparision */
	if (isnan(x)) {
		if (!isnan(y) && y == 0.0)
			return 1.0;
		return x;
	}
	if (isnan(y)) {
		if (x == 1.0)
			return 1.0;
		return y;
	}
	if (x == 1.0)
		return 1.0; /* 1**y = 1, even if y is nan */
	if (x == -1.0 && !isfinite(y))
		return 1.0; /* -1**inf = 1 */
	if (y == 0.0)
		return 1.0; /* x**0 = 1, even if x is nan */
	if (y == 1.0)
		return x;
	if (y >= LDBL_MAX) {
		if (x > 1.0 || x < -1.0)
			return INFINITY;
		if (x != 0.0)
			return 0.0;
	}
	if (y <= -LDBL_MAX) {
		if (x > 1.0 || x < -1.0)
			return 0.0;
		if (x != 0.0 || y == -INFINITY)
			return INFINITY;
	}
	if (x >= LDBL_MAX) {
		if (y > 0.0)
			return INFINITY;
		return 0.0;
	}

	w = floorl(y);

	/* Set iyflg to 1 if y is an integer. */
	iyflg = 0;
	if (w == y)
		iyflg = 1;

	/* Test for odd integer y. */
	yoddint = 0;
	if (iyflg) {
		ya = fabsl(y);
		ya = floorl(0.5 * ya);
		yb = 0.5 * fabsl(w);
		if( ya != yb )
			yoddint = 1;
	}

	if (x <= -LDBL_MAX) {
		if (y > 0.0) {
			if (yoddint)
				return -INFINITY;
			return INFINITY;
		}
		if (y < 0.0) {
			if (yoddint)
				return -0.0;
			return 0.0;
		}
	}
	nflg = 0; /* (x<0)**(odd int) */
	if (x <= 0.0) {
		if (x == 0.0) {
			if (y < 0.0) {
				if (signbit(x) && yoddint)
					/* (-0.0)**(-odd int) = -inf, divbyzero */
					return -1.0/0.0;
				/* (+-0.0)**(negative) = inf, divbyzero */
				return 1.0/0.0;
			}
			if (signbit(x) && yoddint)
				return -0.0;
			return 0.0;
		}
		if (iyflg == 0)
			return (x - x) / (x - x); /* (x<0)**(non-int) is NaN */
		/* (x<0)**(integer) */
		if (yoddint)
			nflg = 1; /* negate result */
		x = -x;
	}
	/* (+integer)**(integer)  */
	if (iyflg && floorl(x) == x && fabsl(y) < 32768.0) {
		w = powil(x, (int)y);
		return nflg ? -w : w;
	}

	/* separate significand from exponent */
	x = frexpl(x, &i);
	e = i;

	/* find significand in antilog table A[] */
	i = 1;
	if (x <= A[17])
		i = 17;
	if (x <= A[i+8])
		i += 8;
	if (x <= A[i+4])
		i += 4;
	if (x <= A[i+2])
		i += 2;
	if (x >= A[1])
		i = -1;
	i += 1;

	/* Find (x - A[i])/A[i]
	 * in order to compute log(x/A[i]):
	 *
	 * log(x) = log( a x/a ) = log(a) + log(x/a)
	 *
	 * log(x/a) = log(1+v),  v = x/a - 1 = (x-a)/a
	 */
	x -= A[i];
	x -= B[i/2];
	x /= A[i];

	/* rational approximation for log(1+v):
	 *
	 * log(1+v)  =  v  -  v**2/2  +  v**3 P(v) / Q(v)
	 */
	z = x*x;
	w = x * (z * __polevll(x, P, 3) / __p1evll(x, Q, 3));
	w = w - 0.5*z;

	/* Convert to base 2 logarithm:
	 * multiply by log2(e) = 1 + LOG2EA
	 */
	z = LOG2EA * w;
	z += w;
	z += LOG2EA * x;
	z += x;

	/* Compute exponent term of the base 2 logarithm. */
	w = -i;
	w /= NXT;
	w += e;
	/* Now base 2 log of x is w + z. */

	/* Multiply base 2 log by y, in extended precision. */

	/* separate y into large part ya
	 * and small part yb less than 1/NXT
	 */
	ya = reducl(y);
	yb = y - ya;

	/* (w+z)(ya+yb)
	 * = w*ya + w*yb + z*y
	 */
	F = z * y  +  w * yb;
	Fa = reducl(F);
	Fb = F - Fa;

	G = Fa + w * ya;
	Ga = reducl(G);
	Gb = G - Ga;

	H = Fb + Gb;
	Ha = reducl(H);
	w = (Ga + Ha) * NXT;

	/* Test the power of 2 for overflow */
	if (w > MEXP)
		return huge * huge;  /* overflow */
	if (w < MNEXP)
		return twom10000 * twom10000;  /* underflow */

	e = w;
	Hb = H - Ha;

	if (Hb > 0.0) {
		e += 1;
		Hb -= 1.0/NXT;  /*0.0625L;*/
	}

	/* Now the product y * log2(x)  =  Hb + e/NXT.
	 *
	 * Compute base 2 exponential of Hb,
	 * where -0.0625 <= Hb <= 0.
	 */
	z = Hb * __polevll(Hb, R, 6);  /*  z = 2**Hb - 1  */

	/* Express e/NXT as an integer plus a negative number of (1/NXT)ths.
	 * Find lookup table entry for the fractional power of 2.
	 */
	if (e < 0)
		i = 0;
	else
		i = 1;
	i = e/NXT + i;
	e = NXT*i - e;
	w = A[e];
	z = w * z;  /*  2**-e * ( 1 + (2**Hb-1) )  */
	z = z + w;
	z = scalbnl(z, i);  /* multiply by integer power of 2 */

	if (nflg)
		z = -z;
	return z;
}