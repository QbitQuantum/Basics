/*
 * Tests to ensure argument reduction for large arguments is accurate.
 */
static void
run_reduction_tests(void)
{
	/* floats very close to odd multiples of pi */
	static const float f_pi_odd[] = {
		85563208.0f,
		43998769152.0f,
		9.2763667655669323e+25f,
		1.5458357838905804e+29f,
	};
	/* doubles very close to odd multiples of pi */
	static const double d_pi_odd[] = {
		3.1415926535897931,
		91.106186954104004,
		642615.9188844458,
		3397346.5699258847,
		6134899525417045.0,
		3.0213551960457761e+43,
		1.2646209897993783e+295,
		6.2083625380677099e+307,
	};
	/* long doubles very close to odd multiples of pi */
#if LDBL_MANT_DIG == 64
	static const long double ld_pi_odd[] = {
		1.1891886960373841596e+101L,
		1.07999475322710967206e+2087L,
		6.522151627890431836e+2147L,
		8.9368974898260328229e+2484L,
		9.2961044110572205863e+2555L,
		4.90208421886578286e+3189L,
		1.5275546401232615884e+3317L,
		1.7227465626338900093e+3565L,
		2.4160090594000745334e+3808L,
		9.8477555741888350649e+4314L,
		1.6061597222105160737e+4326L,
	};
#elif LDBL_MANT_DIG == 113
	static const long double ld_pi_odd[] = {
		/* XXX */
	};
#endif

	int i;

	for (i = 0; i < nitems(f_pi_odd); i++) {
		assert(fabs(sinf(f_pi_odd[i])) < FLT_EPSILON);
		assert(cosf(f_pi_odd[i]) == -1.0);
		assert(fabs(tan(f_pi_odd[i])) < FLT_EPSILON);

		assert(fabs(sinf(-f_pi_odd[i])) < FLT_EPSILON);
		assert(cosf(-f_pi_odd[i]) == -1.0);
		assert(fabs(tanf(-f_pi_odd[i])) < FLT_EPSILON);

		assert(fabs(sinf(f_pi_odd[i] * 2)) < FLT_EPSILON);
		assert(cosf(f_pi_odd[i] * 2) == 1.0);
		assert(fabs(tanf(f_pi_odd[i] * 2)) < FLT_EPSILON);

		assert(fabs(sinf(-f_pi_odd[i] * 2)) < FLT_EPSILON);
		assert(cosf(-f_pi_odd[i] * 2) == 1.0);
		assert(fabs(tanf(-f_pi_odd[i] * 2)) < FLT_EPSILON);
	}

	for (i = 0; i < nitems(d_pi_odd); i++) {
		assert(fabs(sin(d_pi_odd[i])) < 2 * DBL_EPSILON);
		assert(cos(d_pi_odd[i]) == -1.0);
		assert(fabs(tan(d_pi_odd[i])) < 2 * DBL_EPSILON);

		assert(fabs(sin(-d_pi_odd[i])) < 2 * DBL_EPSILON);
		assert(cos(-d_pi_odd[i]) == -1.0);
		assert(fabs(tan(-d_pi_odd[i])) < 2 * DBL_EPSILON);

		assert(fabs(sin(d_pi_odd[i] * 2)) < 2 * DBL_EPSILON);
		assert(cos(d_pi_odd[i] * 2) == 1.0);
		assert(fabs(tan(d_pi_odd[i] * 2)) < 2 * DBL_EPSILON);

		assert(fabs(sin(-d_pi_odd[i] * 2)) < 2 * DBL_EPSILON);
		assert(cos(-d_pi_odd[i] * 2) == 1.0);
		assert(fabs(tan(-d_pi_odd[i] * 2)) < 2 * DBL_EPSILON);
	}

#if LDBL_MANT_DIG > 53
	for (i = 0; i < nitems(ld_pi_odd); i++) {
		assert(fabsl(sinl(ld_pi_odd[i])) < LDBL_EPSILON);
		assert(cosl(ld_pi_odd[i]) == -1.0);
		assert(fabsl(tanl(ld_pi_odd[i])) < LDBL_EPSILON);

		assert(fabsl(sinl(-ld_pi_odd[i])) < LDBL_EPSILON);
		assert(cosl(-ld_pi_odd[i]) == -1.0);
		assert(fabsl(tanl(-ld_pi_odd[i])) < LDBL_EPSILON);

		assert(fabsl(sinl(ld_pi_odd[i] * 2)) < LDBL_EPSILON);
		assert(cosl(ld_pi_odd[i] * 2) == 1.0);
		assert(fabsl(tanl(ld_pi_odd[i] * 2)) < LDBL_EPSILON);

		assert(fabsl(sinl(-ld_pi_odd[i] * 2)) < LDBL_EPSILON);
		assert(cosl(-ld_pi_odd[i] * 2) == 1.0);
		assert(fabsl(tanl(-ld_pi_odd[i] * 2)) < LDBL_EPSILON);
	}
#endif
}