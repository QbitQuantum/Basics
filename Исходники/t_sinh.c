ATF_TC_BODY(sinhf_inrange, tc)
{
	float eps;
	float x;
	float y;
	size_t i;

	for (i = 0; i < __arraycount(values); i++) {
		x = values[i].x;
		y = values[i].y;
		eps = 1e-6 * values[i].e;

		if (fabsf(sinhf(x) - y) > eps)
			atf_tc_fail_nonfatal("sinhf(%g) != %g\n", x, y);
	}
}