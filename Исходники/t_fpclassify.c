ATF_TC_BODY(fpclassify_long_double, tc)
{
	long double d0, d1, d2, f, ip;
	int e, i;

	d0 = LDBL_MIN;
	ATF_REQUIRE_EQ(fpclassify(d0), FP_NORMAL);
	f = frexpl(d0, &e);
	ATF_REQUIRE_EQ(e, LDBL_MIN_EXP);
	ATF_REQUIRE_EQ(f, 0.5);
	d1 = d0;

	/* shift a "1" bit through the mantissa (skip the implicit bit) */
	for (i = 1; i < LDBL_MANT_DIG; i++) {
		d1 /= 2;
		ATF_REQUIRE_EQ(fpclassify(d1), FP_SUBNORMAL);
		ATF_REQUIRE(d1 > 0 && d1 < d0);

		d2 = ldexpl(d0, -i);
		ATF_REQUIRE_EQ(d2, d1);

		d2 = modfl(d1, &ip);
		ATF_REQUIRE_EQ(d2, d1);
		ATF_REQUIRE_EQ(ip, 0);

		f = frexpl(d1, &e);
		ATF_REQUIRE_EQ(e, LDBL_MIN_EXP - i);
		ATF_REQUIRE_EQ(f, 0.5);
	}

	d1 /= 2;
	ATF_REQUIRE_EQ(fpclassify(d1), FP_ZERO);
	f = frexpl(d1, &e);
	ATF_REQUIRE_EQ(e, 0);
	ATF_REQUIRE_EQ(f, 0);
}