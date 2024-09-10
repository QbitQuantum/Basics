ATF_TC_BODY(powf_zero_x, tc)
{
#ifndef __vax__
	float z;

	/*
	 * If x is +0.0 or -0.0, y > 0, and y
	 * is an odd integer, x is returned.
	 */
	z = powf(+0.0, 3.0);

	if (fabsf(z) > 0.0 || signbit(z) != 0)
		atf_tc_fail_nonfatal("powf(+0.0, 3.0) != +0.0");

	z = powf(-0.0, 3.0);

	if (fabsf(z) > 0.0 || signbit(z) == 0)
		atf_tc_fail_nonfatal("powf(-0.0, 3.0) != -0.0");

	/*
	 * If y > 0 and not an odd integer,
	 * if x is +0.0 or -0.0, +0.0 is returned.
	 */
	z = powf(+0.0, 4.0);

	if (fabsf(z) > 0.0 || signbit(z) != 0)
		atf_tc_fail_nonfatal("powf(+0.0, 4.0) != +0.0");

	z = powf(-0.0, 4.0);

	if (fabsf(z) > 0.0 || signbit(z) != 0)
		atf_tc_fail_nonfatal("powf(-0.0, 4.0) != +0.0");

	/*
	 * If y < 0 and x is +0.0 or -0.0, either +-HUGE_VAL,
	 * +-HUGE_VALF, or +-HUGE_VALL shall be returned.
	 */
	z = powf(+0.0, -4.0);

	if (z != HUGE_VALF) {
		atf_tc_expect_fail("PR port-amd64/45391");
		atf_tc_fail_nonfatal("powf(+0.0, -4.0) != HUGE_VALF");
	}

	z = powf(-0.0, -4.0);

	if (z != HUGE_VALF) {
		atf_tc_expect_fail("PR port-amd64/45391");
		atf_tc_fail_nonfatal("powf(-0.0, -4.0) != HUGE_VALF");
	}

	z = powf(+0.0, -5.0);

	if (z != HUGE_VALF) {
		atf_tc_expect_fail("PR port-amd64/45391");
		atf_tc_fail_nonfatal("powf(+0.0, -5.0) != HUGE_VALF");
	}

	z = powf(-0.0, -5.0);

	if (z != -HUGE_VALF)
		atf_tc_fail_nonfatal("powf(-0.0, -5.0) != -HUGE_VALF");
#endif
}