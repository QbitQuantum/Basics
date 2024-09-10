/*
 * Test whether csqrt(a + bi) works for inputs that are large enough to
 * cause overflow in hypot(a, b) + a. In this case we are using
 *	csqrt(115 + 252*I) == 14 + 9*I
 * scaled up to near MAX_EXP.
 */
static void
test_overflow(int maxexp)
{
	long double a, b;
	long double complex result;

	a = ldexpl(115 * 0x1p-8, maxexp);
	b = ldexpl(252 * 0x1p-8, maxexp);
	result = t_csqrt(CMPLXL(a, b));
	assert(creall(result) == ldexpl(14 * 0x1p-4, maxexp / 2));
	assert(cimagl(result) == ldexpl(9 * 0x1p-4, maxexp / 2));
}