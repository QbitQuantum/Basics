void
run_log2_tests(void)
{
	int i;

	/*
	 * We should insist that log2() return exactly the correct
	 * result and not raise an inexact exception for powers of 2.
	 */
	feclearexcept(FE_ALL_EXCEPT);
	for (i = FLT_MIN_EXP - FLT_MANT_DIG; i < FLT_MAX_EXP; i++) {
		assert(log2f(ldexpf(1.0, i)) == i);
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
	for (i = DBL_MIN_EXP - DBL_MANT_DIG; i < DBL_MAX_EXP; i++) {
		assert(log2(ldexp(1.0, i)) == i);
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
	for (i = LDBL_MIN_EXP - LDBL_MANT_DIG; i < LDBL_MAX_EXP; i++) {
		assert(log2l(ldexpl(1.0, i)) == i);
#if 0
		/* XXX This test does not pass yet. */
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
#endif
	}
}