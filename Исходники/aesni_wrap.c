/*
 * mixed endian increment, low 64bits stored in hi word to be compatible
 * with _icm's BSWAP.
 */
static inline __m128i
nextc(__m128i x)
{
	const __m128i ONE = _mm_setr_epi32(0, 0, 1, 0);
	const __m128i ZERO = _mm_setzero_si128();

	x = _mm_add_epi64(x, ONE);
	__m128i t = _mm_cmpeq_epi64(x, ZERO);
	t = _mm_unpackhi_epi64(t, ZERO);
	x = _mm_sub_epi64(x, t);

	return x;
}