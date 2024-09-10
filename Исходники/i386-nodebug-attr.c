__m128  COMPUTE ()
{
	__m128 v0 = _mm_setzero_ps();
	__m128 v1 = _mm_set1_ps(1.0);
	__m128 v2 = _mm_set1_ps(1.0);;
	__m128 v3 = _mm_sub_ss (v1, v2);
	return _mm_add_ss (v3, v0);
}