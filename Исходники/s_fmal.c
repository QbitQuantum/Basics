/*
 * Fused multiply-add: Compute x * y + z with a single rounding error.
 *
 * We use scaling to avoid overflow/underflow, along with the
 * canonical precision-doubling technique adapted from:
 *
 *	Dekker, T.  A Floating-Point Technique for Extending the
 *	Available Precision.  Numer. Math. 18, 224-242 (1971).
 */
long double
fmal(long double x, long double y, long double z)
{
	long double xs, ys, zs, adj;
	struct dd xy, r;
	int oround;
	int ex, ey, ez;
	int spread;

	/*
	 * Handle special cases. The order of operations and the particular
	 * return values here are crucial in handling special cases involving
	 * infinities, NaNs, overflows, and signed zeroes correctly.
	 */
	if (x == 0.0 || y == 0.0)
		return (x * y + z);
	if (z == 0.0)
		return (x * y);
	if (!isfinite(x) || !isfinite(y))
		return (x * y + z);
	if (!isfinite(z))
		return (z);

	xs = frexpl(x, &ex);
	ys = frexpl(y, &ey);
	zs = frexpl(z, &ez);
	oround = fegetround();
	spread = ex + ey - ez;

	/*
	 * If x * y and z are many orders of magnitude apart, the scaling
	 * will overflow, so we handle these cases specially.  Rounding
	 * modes other than FE_TONEAREST are painful.
	 */
	if (spread < -LDBL_MANT_DIG) {
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
				return (nextafterl(z, 0));
		case FE_DOWNWARD:
			if (x > 0.0 ^ y < 0.0)
				return (z);
			else
				return (nextafterl(z, -INFINITY));
		default:	/* FE_UPWARD */
			if (x > 0.0 ^ y < 0.0)
				return (nextafterl(z, INFINITY));
			else
				return (z);
		}
	}
	if (spread <= LDBL_MANT_DIG * 2)
		zs = ldexpl(zs, -spread);
	else
		zs = copysignl(LDBL_MIN, zs);

	fesetround(FE_TONEAREST);
	/* work around clang bug 8100 */
	volatile long double vxs = xs;

	/*
	 * Basic approach for round-to-nearest:
	 *
	 *     (xy.hi, xy.lo) = x * y		(exact)
	 *     (r.hi, r.lo)   = xy.hi + z	(exact)
	 *     adj = xy.lo + r.lo		(inexact; low bit is sticky)
	 *     result = r.hi + adj		(correctly rounded)
	 */
	xy = dd_mul(vxs, ys);
	r = dd_add(xy.hi, zs);

	spread = ex + ey;

	if (r.hi == 0.0) {
		/*
		 * When the addends cancel to 0, ensure that the result has
		 * the correct sign.
		 */
		fesetround(oround);
		volatile long double vzs = zs; /* XXX gcc CSE bug workaround */
		return (xy.hi + vzs + ldexpl(xy.lo, spread));
	}

	if (oround != FE_TONEAREST) {
		/*
		 * There is no need to worry about double rounding in directed
		 * rounding modes.
		 */
		fesetround(oround);
		/* work around clang bug 8100 */
		volatile long double vrlo = r.lo;
		adj = vrlo + xy.lo;
		return (ldexpl(r.hi + adj, spread));
	}

	adj = add_adjusted(r.lo, xy.lo);
	if (spread + ilogbl(r.hi) > -16383)
		return (ldexpl(r.hi + adj, spread));
	else
		return (add_and_denormalize(r.hi, adj, spread));
}