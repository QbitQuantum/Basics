EXPORT_C double
fma(double x, double y, double z)
{
	#ifndef __SYMBIAN32__
	static const double split = 0x1p27 + 1.0;
	#else
	static const double split = 134217729;
	#endif //__SYMBIAN32__
	double xs, ys, zs;
	double c, cc, hx, hy, p, q, tx, ty;
	double r, rr, s;
	int oround;
	int ex, ey, ez;
	int spread;

	if (z == 0.0)
		return (x * y);
	if (x == 0.0 || y == 0.0)
		return (x * y + z);

	/* Results of frexp() are undefined for these cases. */
	if (!isfinite(x) || !isfinite(y) || !isfinite(z))
		return (x * y + z);

	xs = frexp(x, &ex);
	ys = frexp(y, &ey);
	zs = frexp(z, &ez);
	oround = fegetround();
	spread = ex + ey - ez;

	/*
	 * If x * y and z are many orders of magnitude apart, the scaling
	 * will overflow, so we handle these cases specially.  Rounding
	 * modes other than FE_TONEAREST are painful.
	 */
	if (spread > DBL_MANT_DIG * 2) {
		fenv_t env;
		feraiseexcept(FE_INEXACT);
		switch(oround) {
		case FE_TONEAREST:
			return (x * y);
		case FE_TOWARDZERO:
			if (x > 0.0 ^ y < 0.0 ^ z < 0.0)
				return (x * y);
			feholdexcept(&env);
			r = x * y;
			if (!fetestexcept(FE_INEXACT))
				r = nextafter(r, 0);
			feupdateenv(&env);
			return (r);
		case FE_DOWNWARD:
			if (z > 0.0)
				return (x * y);
			feholdexcept(&env);
			r = x * y;
			if (!fetestexcept(FE_INEXACT))
				r = nextafter(r, -INFINITY);
			feupdateenv(&env);
			return (r);
		default:	/* FE_UPWARD */
			if (z < 0.0)
				return (x * y);
			feholdexcept(&env);
			r = x * y;
			if (!fetestexcept(FE_INEXACT))
				r = nextafter(r, INFINITY);
			feupdateenv(&env);
			return (r);
		}
	}
	if (spread < -DBL_MANT_DIG) {
		feraiseexcept(FE_INEXACT);
		if (!isnormal(z))
			feraiseexcept(FE_UNDERFLOW);
		switch (oround) {
		case FE_TONEAREST:
			return (z);
		case FE_TOWARDZERO:
			if (x > 0.0 ^ y < 0.0 ^ z < 0.0)
				return (z);
			else
				return (nextafter(z, 0));
		case FE_DOWNWARD:
			if (x > 0.0 ^ y < 0.0)
				return (z);
			else
				return (nextafter(z, -INFINITY));
		default:	/* FE_UPWARD */
			if (x > 0.0 ^ y < 0.0)
				return (nextafter(z, INFINITY));
			else
				return (z);
		}
	}

	/*
	 * Use Dekker's algorithm to perform the multiplication and
	 * subsequent addition in twice the machine precision.
	 * Arrange so that x * y = c + cc, and x * y + z = r + rr.
	 */
	fesetround(FE_TONEAREST);

	p = xs * split;
	hx = xs - p;
	hx += p;
	tx = xs - hx;

	p = ys * split;
	hy = ys - p;
	hy += p;
	ty = ys - hy;

	p = hx * hy;
	q = hx * ty + tx * hy;
	c = p + q;
	cc = p - c + q + tx * ty;

	zs = ldexp(zs, -spread);
	r = c + zs;
	s = r - c;
	rr = (c - (r - s)) + (zs - s) + cc;

	spread = ex + ey;
	if (spread + ilogb(r) > -1023) {
		fesetround(oround);
		r = r + rr;
	} else {
		/*
		 * The result is subnormal, so we round before scaling to
		 * avoid double rounding.
		 */
		#ifndef __SYMBIAN32__
		p = ldexp(copysign(0x1p-1022, r), -spread);
		#else

		p = ldexp(copysign(0, r), -spread);


		#endif //__SYMBIAN32__
		c = r + p;
		s = c - r;
		cc = (r - (c - s)) + (p - s) + rr;
		fesetround(oround);
		r = (c + cc) - p;
	}
	return (ldexp(r, spread));
}