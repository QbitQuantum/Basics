bool	Interlocked::Data128::operator != (const Data128 & other) const
{
	__m128i var1 = _mm_load_si128((__m128i*)_data);
	__m128i var2 = _mm_load_si128((__m128i*)other._data);
	__m128i result = _mm_cmpeq_epi64(var1, var2);
	result = _mm_and_si128(result, _mm_srli_si128(result, 8));
	return !_mm_cvtsi128_si32(result);
}