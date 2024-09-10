ATF_TC_BODY(ldexpf_exp2f, tc)
{
	const float n[] = { 1, 2, 3, 10, 50, 100 };
	const float eps = 1.0e-9;
	const float x = 12.0;
	float y;
	size_t i;

	for (i = 0; i < __arraycount(n); i++) {

		y = ldexpf(x, n[i]);

		if (fabsf(y - (x * exp2f(n[i]))) > eps) {
			atf_tc_fail_nonfatal("ldexpf(%0.01f, %0.01f) "
			    "!= %0.01f * exp2f(%0.01f)", x, n[i], x, n[i]);
		}
	}
}