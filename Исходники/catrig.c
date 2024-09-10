/*
 * All the hard work is contained in this function.
 * x and y are assumed positive or zero, and less than RECIP_EPSILON.
 * Upon return:
 * rx = Re(casinh(z)) = -Im(cacos(y + I*x)).
 * B_is_usable is set to 1 if the value of B is usable.
 * If B_is_usable is set to 0, sqrt_A2my2 = sqrt(A*A - y*y), and new_y = y.
 * If returning sqrt_A2my2 has potential to result in an underflow, it is
 * rescaled, and new_y is similarly rescaled.
 */
static inline void
do_hard_work(double x, double y, double *rx, int *B_is_usable, double *B,
    double *sqrt_A2my2, double *new_y)
{
	double R, S, A; /* A, B, R, and S are as in Hull et al. */
	double Am1, Amy; /* A-1, A-y. */

	R = hypot(x, y + 1);		/* |z+I| */
	S = hypot(x, y - 1);		/* |z-I| */

	/* A = (|z+I| + |z-I|) / 2 */
	A = (R + S) / 2;
	/*
	 * Mathematically A >= 1.  There is a small chance that this will not
	 * be so because of rounding errors.  So we will make certain it is
	 * so.
	 */
	if (A < 1)
		A = 1;

	if (A < A_crossover) {
		/*
		 * Am1 = fp + fm, where fp = f(x, 1+y), and fm = f(x, 1-y).
		 * rx = log1p(Am1 + sqrt(Am1*(A+1)))
		 */
		if (y == 1 && x < DBL_EPSILON * DBL_EPSILON / 128) {
			/*
			 * fp is of order x^2, and fm = x/2.
			 * A = 1 (inexactly).
			 */
			*rx = sqrt(x);
		} else if (x >= DBL_EPSILON * fabs(y - 1)) {
			/*
			 * Underflow will not occur because
			 * x >= DBL_EPSILON^2/128 >= FOUR_SQRT_MIN
			 */
			Am1 = f(x, 1 + y, R) + f(x, 1 - y, S);
			*rx = log1p(Am1 + sqrt(Am1 * (A + 1)));
		} else if (y < 1) {
			/*
			 * fp = x*x/(1+y)/4, fm = x*x/(1-y)/4, and
			 * A = 1 (inexactly).
			 */
			*rx = x / sqrt((1 - y) * (1 + y));
		} else {		/* if (y > 1) */
			/*
			 * A-1 = y-1 (inexactly).
			 */
			*rx = log1p((y - 1) + sqrt((y - 1) * (y + 1)));
		}
	} else {
		*rx = log(A + sqrt(A * A - 1));
	}

	*new_y = y;

	if (y < FOUR_SQRT_MIN) {
		/*
		 * Avoid a possible underflow caused by y/A.  For casinh this
		 * would be legitimate, but will be picked up by invoking atan2
		 * later on.  For cacos this would not be legitimate.
		 */
		*B_is_usable = 0;
		*sqrt_A2my2 = A * (2 / DBL_EPSILON);
		*new_y = y * (2 / DBL_EPSILON);
		return;
	}

	/* B = (|z+I| - |z-I|) / 2 = y/A */
	*B = y / A;
	*B_is_usable = 1;

	if (*B > B_crossover) {
		*B_is_usable = 0;
		/*
		 * Amy = fp + fm, where fp = f(x, y+1), and fm = f(x, y-1).
		 * sqrt_A2my2 = sqrt(Amy*(A+y))
		 */
		if (y == 1 && x < DBL_EPSILON / 128) {
			/*
			 * fp is of order x^2, and fm = x/2.
			 * A = 1 (inexactly).
			 */
			*sqrt_A2my2 = sqrt(x) * sqrt((A + y) / 2);
		} else if (x >= DBL_EPSILON * fabs(y - 1)) {
			/*
			 * Underflow will not occur because
			 * x >= DBL_EPSILON/128 >= FOUR_SQRT_MIN
			 * and
			 * x >= DBL_EPSILON^2 >= FOUR_SQRT_MIN
			 */
			Amy = f(x, y + 1, R) + f(x, y - 1, S);
			*sqrt_A2my2 = sqrt(Amy * (A + y));
		} else if (y > 1) {
			/*
			 * fp = x*x/(y+1)/4, fm = x*x/(y-1)/4, and
			 * A = y (inexactly).
			 *
			 * y < RECIP_EPSILON.  So the following
			 * scaling should avoid any underflow problems.
			 */
			*sqrt_A2my2 = x * (4 / DBL_EPSILON / DBL_EPSILON) * y /
			    sqrt((y + 1) * (y - 1));
			*new_y = y * (4 / DBL_EPSILON / DBL_EPSILON);
		} else {		/* if (y < 1) */
			/*
			 * fm = 1-y >= DBL_EPSILON, fp is of order x^2, and
			 * A = 1 (inexactly).
			 */
			*sqrt_A2my2 = sqrt((1 - y) * (1 + y));
		}
	}
}