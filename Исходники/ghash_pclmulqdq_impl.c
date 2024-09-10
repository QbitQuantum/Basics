/** Performs a carryless multiplication of two 128bit integers modulo \f$ x^{128} + x^7 + x^2 + x + 1 \f$ */
static __m128i gmul(__m128i v, __m128i h) {
	/* multiply */
	__m128i z0, z1, z2, tmp;
	z0 = _mm_clmulepi64_si128(v, h, 0x11);
	z2 = _mm_clmulepi64_si128(v, h, 0x00);

	__m128i tmpv = _mm_srli_si128(v, 8);
	tmpv = _mm_xor_si128(tmpv, v);

	__m128i tmph = _mm_srli_si128(h, 8);
	tmph = _mm_xor_si128(tmph, h);

	z1 = _mm_clmulepi64_si128(tmpv, tmph, 0x00);
	z1 = _mm_xor_si128(z1, z0);
	z1 = _mm_xor_si128(z1, z2);

	tmp = _mm_srli_si128(z1, 8);
	__m128i pl = _mm_xor_si128(z0, tmp);

	tmp = _mm_slli_si128(z1, 8);
	__m128i ph = _mm_xor_si128(z2, tmp);

	tmp = _mm_srli_epi64(ph, 63);
	tmp = _mm_srli_si128(tmp, 8);

	pl = shl(pl, 1);
	pl = _mm_xor_si128(pl, tmp);

	ph = shl(ph, 1);

	/* reduce */
	__m128i b, c;
	b = c = _mm_slli_si128(ph, 8);

	b = _mm_slli_epi64(b, 62);
	c = _mm_slli_epi64(c, 57);

	tmp = _mm_xor_si128(b, c);
	__m128i d = _mm_xor_si128(ph, tmp);

	__m128i e = shr(d, 1);
	__m128i f = shr(d, 2);
	__m128i g = shr(d, 7);

	pl = _mm_xor_si128(pl, d);
	pl = _mm_xor_si128(pl, e);
	pl = _mm_xor_si128(pl, f);
	pl = _mm_xor_si128(pl, g);

	return pl;
}