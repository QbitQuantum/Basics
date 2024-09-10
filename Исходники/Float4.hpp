	inline float4 operator / (const float4 & a, const float b)
	{
		float4 res, scale;

		scale.m128 = _mm_set1_ps(b);
		scale.m128 = _mm_rcp_ps(scale.m128);
		res.m128 = _mm_mul_ps(a.m128, scale.m128);

		return res;
	}