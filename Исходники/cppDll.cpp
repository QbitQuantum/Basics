__inline __m128d Length(__m128d vec1,__m128d vec2)
{
	__m128d result1 = _mm_mul_pd(vec1, vec1);
	__m128d result2 = _mm_mul_sd(vec2, vec2);
	__m128d result3 = _mm_shuffle_pd(result1, result1, 1);
	__m128d result4 = _mm_add_sd(result1, result2);
	__m128d result5 = _mm_add_sd(result4, result3);
	__m128d result6 = _mm_sqrt_sd(vec1, result5);
	return result6;
}