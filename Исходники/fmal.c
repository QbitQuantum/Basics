/*
 * Compute ldexp(a+b, scale) with a single rounding error. It is assumed
 * that the result will be subnormal, and care is taken to ensure that
 * double rounding does not occur.
 */
static inline long double add_and_denormalize(long double a, long double b, int scale)
{
	struct dd sum;
	int bits_lost;
	union ldshape u;

	sum = dd_add(a, b);

	/*
	 * If we are losing at least two bits of accuracy to denormalization,
	 * then the first lost bit becomes a round bit, and we adjust the
	 * lowest bit of sum.hi to make it a sticky bit summarizing all the
	 * bits in sum.lo. With the sticky bit adjusted, the hardware will
	 * break any ties in the correct direction.
	 *
	 * If we are losing only one bit to denormalization, however, we must
	 * break the ties manually.
	 */
	if (sum.lo != 0) {
		u.f = sum.hi;
		bits_lost = -u.i.se - scale + 1;
		if ((bits_lost != 1) ^ LASTBIT(u))
			sum.hi = nextafterl(sum.hi, INFINITY * sum.lo);
	}
	return scalbnl(sum.hi, scale);
}