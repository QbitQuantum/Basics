static uint32_t maxasint(const __m128i accumulator) {
	const __m128i _tmp1 = _mm_max_epu32(_mm_srli_si128(accumulator, 8), accumulator); /* (A,B,C,D) xor (0,0,A,B) = (A,B,C xor A,D xor B)*/
	const __m128i _tmp2 = _mm_max_epu32(_mm_srli_si128(_tmp1, 4), _tmp1); /*  (A,B,C xor A,D xor B) xor  (0,0,0,C xor A)*/
	return  _mm_cvtsi128_si32(_tmp2);
}