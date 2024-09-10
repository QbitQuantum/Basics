static inline bool equals_sse(const float3& f1, const float3& f2)
{
	// same as equals_new() just with SSE
	__m128 eq;
	__m128 m1 = _mm_set_ps(f1[0], f1[1], f1[2], 0.f);
	__m128 m2 = _mm_set_ps(f2[0], f2[1], f2[2], 0.f);
	eq = _mm_cmpeq_ps(m1, m2);
	if ((eq[0] != 0) && (eq[1] != 0) && (eq[2] != 0))
		return true;

	static const __m128 sign_mask = _mm_set1_ps(-0.f); // -0.f = 1 << 31
	static const __m128 eps = _mm_set1_ps(float3::cmp_eps());
	static const __m128 ones = _mm_set1_ps(1.f);
	__m128 am1 = _mm_andnot_ps(sign_mask, m1);
	__m128 am2 = _mm_andnot_ps(sign_mask, m2);
	__m128 right = _mm_add_ps(am1, am2);
	right = _mm_add_ps(right, ones);
	right = _mm_mul_ps(right, eps);
	__m128 left = _mm_sub_ps(m1, m2);
	left = _mm_andnot_ps(sign_mask, left);

	eq = _mm_cmple_ps(left, right);
	return ((eq[0] != 0) && (eq[1] != 0) && (eq[2] != 0));
}