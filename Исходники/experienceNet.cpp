void experienceNet::normalPDF_sse(float* result, const float* _partitions, float _mean, float _stdDev)
{
	/* 
	CODE ADAPTED FROM boost/math/normal.hpp 

	RealType exponent = x - mean;
	exponent *= -exponent;
	exponent /= 2 * sd * sd;

	result = exp(exponent);
	result /= sd * sqrt(2 * constants::pi<RealType>());

	return result;
	*/
	const __m128& partitions = *(__m128*)_partitions;
	__m128 exponent, tmp, mean, sd;

	/* CODE ADAPTED FROM http://fastcpp.blogspot.com/2011/03/changing-sign-of-float-values-using-sse.html */
	static const __m128 signmask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));

	static const __m128 twos = _mm_set_ps1(2.0f);
	static const __m128 sqrt_pi_2_s = _mm_set_ps1(sqrt(2.0 * M_PI));

	// store mean and sd:
	mean = _mm_load_ps1(&_mean);
	sd = _mm_load_ps1(&_stdDev);

	// exponent = x - mean
	exponent = _mm_sub_ps(partitions, mean);
	// exponent *= -exponent;
	tmp = _mm_xor_ps(exponent, signmask);
	exponent = _mm_mul_ps(exponent, tmp);
	// exponent /= 2 * sd * sd;
	tmp = _mm_mul_ps(sd, sd);
	tmp = _mm_mul_ps(tmp, twos);
	exponent = _mm_div_ps(exponent, tmp);
	// exponent = exp(exponent);
	exponent = _mm_exp_ps(exponent);
	// exponent /= sd * sqrt(2 * pi)
	tmp = _mm_mul_ps(sd, sqrt_pi_2_s);
	tmp = _mm_div_ps(exponent, tmp);


#ifndef NDEBUG
	const float* _result = (float*)&tmp;
	boost::math::normal_distribution<float> cNormal(_mean, _stdDev);
	assert(fastabs(_result[0] - boost::math::pdf(cNormal, _partitions[0])) < 0.001f);
	assert(fastabs(_result[1] - boost::math::pdf(cNormal, _partitions[1])) < 0.001f);
	assert(fastabs(_result[2] - boost::math::pdf(cNormal, _partitions[2])) < 0.001f);
	assert(fastabs(_result[3] - boost::math::pdf(cNormal, _partitions[3])) < 0.001f);
#endif

	// return result:
	_mm_store_ps(result, tmp);
};