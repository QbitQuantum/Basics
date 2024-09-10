float inline REDUCE(__m512 val)
{
	float retval;
	__m512 reduce_1 = _mm512_castsi512_ps(_mm512_permute4f128_epi32(_mm512_castps_si512(val), _MM_PERM_CDAB));
	reduce_1 = _mm512_add_ps(reduce_1, val);
	__m512 reduce_2 = _mm512_castsi512_ps(_mm512_permute4f128_epi32(_mm512_castps_si512(reduce_1), _MM_PERM_AACC));
	reduce_1 = _mm512_add_ps(reduce_1, reduce_2);
	reduce_1 = _mm512_add_ps(reduce_1, _mm512_swizzle_ps(reduce_1, _MM_SWIZ_REG_CDAB));
	reduce_1 = _mm512_add_ps(reduce_1, _mm512_swizzle_ps(reduce_1, _MM_SWIZ_REG_BADC));
	_MM_STORE_SS(&retval, reduce_1);
	return retval;
}