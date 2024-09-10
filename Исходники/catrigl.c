long double complex
catanhl(long double complex z)
{
	long double x, y, ax, ay, rx, ry;

	x = creall(z);
	y = cimagl(z);
	ax = fabsl(x);
	ay = fabsl(y);

	if (y == 0 && ax <= 1)
		return (CMPLXL(atanhl(x), y));

	if (x == 0)
		return (CMPLXL(x, atanl(y)));

	if (isnan(x) || isnan(y)) {
		if (isinf(x))
			return (CMPLXL(copysignl(0, x), y + y));
		if (isinf(y))
			return (CMPLXL(copysignl(0, x),
			    copysignl(pio2_hi + pio2_lo, y)));
		return (CMPLXL(nan_mix(x, y), nan_mix(x, y)));
	}

	if (ax > RECIP_EPSILON || ay > RECIP_EPSILON)
		return (CMPLXL(real_part_reciprocal(x, y),
		    copysignl(pio2_hi + pio2_lo, y)));

	if (ax < SQRT_3_EPSILON / 2 && ay < SQRT_3_EPSILON / 2) {
		raise_inexact();
		return (z);
	}

	if (ax == 1 && ay < LDBL_EPSILON)
		rx = (m_ln2 - logl(ay)) / 2;
	else
		rx = log1pl(4 * ax / sum_squares(ax - 1, ay)) / 4;

	if (ax == 1)
		ry = atan2l(2, -ay) / 2;
	else if (ay < LDBL_EPSILON)
		ry = atan2l(2 * ay, (1 - ax) * (1 + ax)) / 2;
	else
		ry = atan2l(2 * ay, (1 - ax) * (1 + ax) - ay * ay) / 2;

	return (CMPLXL(copysignl(rx, x), copysignl(ry, y)));
}