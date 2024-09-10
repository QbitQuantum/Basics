ATF_TC_BODY(coshf_inrange, tc)
{
	float eps;
	float x;
	float y;
	size_t i;

	for (i = 0; i < __arraycount(values); i++) {
		x = values[i].x;
		y = values[i].y;
		eps = 1e-6 * values[i].e;

		if (fabsf(coshf(x) - y) > eps)
			atf_tc_fail_nonfatal("coshf(%g) != %g\n", x, y);
	}
}