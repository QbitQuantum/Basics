long double
atan2l(long double y, long double x) {
	long double t, z;
	int k, m, signy, signx;

	if (x != x || y != y)
		return (x + y);	/* return NaN if x or y is NAN */
	signy = signbitl(y);
	signx = signbitl(x);
	if (x == one)
		return (atanl(y));
	m = signy + signx + signx;

	/* when y = 0 */
	if (y == zero)
		switch (m) {
		case 0:
			return (y);	/* atan(+0,+anything) */
		case 1:
			return (y);	/* atan(-0,+anything) */
		case 2:
			return (PI + tiny);	/* atan(+0,-anything) */
		case 3:
			return (-PI - tiny);	/* atan(-0,-anything) */
		}

	/* when x = 0 */
	if (x == zero)
		return (signy == 1 ? -PIo2 - tiny : PIo2 + tiny);

	/* when x is INF */
	if (!finitel(x))
		if (!finitel(y)) {
			switch (m) {
			case 0:
				return (PIo4 + tiny);	/* atan(+INF,+INF) */
			case 1:
				return (-PIo4 - tiny);	/* atan(-INF,+INF) */
			case 2:
				return (PI3o4 + tiny);	/* atan(+INF,-INF) */
			case 3:
				return (-PI3o4 - tiny);	/* atan(-INF,-INF) */
			}
		} else {
			switch (m) {
			case 0:
				return (zero);	/* atan(+...,+INF) */
			case 1:
				return (-zero);	/* atan(-...,+INF) */
			case 2:
				return (PI + tiny);	/* atan(+...,-INF) */
			case 3:
				return (-PI - tiny);	/* atan(-...,-INF) */
			}
		}

	/* when y is INF */
	if (!finitel(y))
		return (signy == 1 ? -PIo2 - tiny : PIo2 + tiny);

	/* compute y/x */
	x = fabsl(x);
	y = fabsl(y);
	t = PI_lo;
	k = (ilogbl(y) - ilogbl(x));

	if (k > 120)
		z = PIo2 + half * t;
	else if (m > 1 && k < -120)
		z = zero;
	else
		z = atanl(y / x);

	switch (m) {
	case 0:
		return (z);	/* atan(+,+) */
	case 1:
		return (-z);	/* atan(-,+) */
	case 2:
		return (PI - (z - t));	/* atan(+,-) */
	case 3:
		return ((z - t) - PI);	/* atan(-,-) */
	}
	/* NOTREACHED */
}