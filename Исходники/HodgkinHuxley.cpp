double HodgkinHuxley::dV(double *V, double I) {
	const double C = 1.0;
	const double gNa = 120.0;
	const double gK = 36.0;
	const double gL = 0.3;
	const double ENa = 50.0;
	const double EK = -77.0;
	const double EL = -54.4;
#ifdef __AVX__
/*
AVX is an instruction set from Intel which allows simultaneous operation
on 4 doubles. Seems to be slower than optimized FPU, though.
*/
	double Va[] __attribute__ ((aligned (32))) = {V[0], V[0], V[0], 1.0},
		   Ea[] __attribute__ ((aligned (32))) = {EL, ENa, EK, 0.0},
		   Ga[] __attribute__ ((aligned (32))) = {-gL, -gNa * pow(V[2], 3.0) * V[3], -gK * pow(V[1], 4.0), I};
	
	// load V
	__m256d Vr = _mm256_load_pd(Va);
	// load E
	__m256d Er = _mm256_load_pd(Ea);
	// load G
	__m256d Gr = _mm256_load_pd(Ga);
	// subtract
	Vr = _mm256_sub_pd(Vr, Er);
	// dot product (why does intel not have _mm256_dp_pd ?)
	Vr = _mm256_mul_pd(Vr, Gr);
	__m256d temp = _mm256_hadd_pd(Vr, Vr);
	__m128d lo128 = _mm256_extractf128_pd(temp, 0);
	__m128d hi128 = _mm256_extractf128_pd(temp, 1);
	__m128d dotproduct = _mm_add_pd(lo128, hi128);
	
	double sseVal;
	// store
	_mm_storel_pd(&sseVal, dotproduct);
	sseVal /= C;
		
	return sseVal;
#else
	return (-gL * (V[0] - EL) - gNa * pow(V[2], 3.0) * V[3] * (V[0] - ENa)
		- gK * pow(V[1], 4.0) * (V[0] - EK) + I) / C;
#endif
}