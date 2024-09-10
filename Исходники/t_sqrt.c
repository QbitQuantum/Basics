ATF_TC_BODY(sqrtl_powl, tc)
{
#ifndef __vax__
	const long double x[] = { 0.0, 0.005, 1.0, 99.0, 123.123, 9999.9999 };
	const long double eps = 5.0*DBL_EPSILON; /* XXX powl == pow for now */
	volatile long double y, z;
	size_t i;

	for (i = 0; i < __arraycount(x); i++) {

		y = sqrtl(x[i]);
		z = powl(x[i], 1.0 / 2.0);

		if (fabsl(y - z) > eps)
			atf_tc_fail_nonfatal("sqrtl(%0.03Lf) != "
			    "powl(%0.03Lf, 1/2)\n", x[i], x[i]);
	}
#endif
}