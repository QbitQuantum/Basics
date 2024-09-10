/* elements are given in 2 arrays (4 and 4),
   result will be returned in the same arrays with a straight order */
inline void bitonic_sort_kernel4(float *a, float *b)
{
	__m128	ma;
	__m128	mb;
	__m128	map;
	__m128	mbp;
	__m128	lo;
	__m128	hi;

	/* load 8 elements to sse registers */
	ma = _mm_load_ps(a);
	mb = _mm_load_ps(b);

	/* In-Register sort */
	map = _mm_shuffle_ps(ma, mb, _MM_SHUFFLE(2, 0, 2, 0)); /* 0x88: */
	mbp = _mm_shuffle_ps(ma, mb, _MM_SHUFFLE(3, 1, 3, 1)); /* 0xdd: */

	lo = _mm_castsi128_ps (_mm_min_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));
	hi = _mm_castsi128_ps (_mm_max_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));

	map = _mm_shuffle_ps(hi, lo, _MM_SHUFFLE(3, 1, 2, 0)); /* 0xd8: */
	mbp = _mm_shuffle_ps(hi, lo, _MM_SHUFFLE(2, 0, 3, 1)); /* 0x8d: */

	lo = _mm_castsi128_ps (_mm_min_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));
	hi = _mm_castsi128_ps (_mm_max_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));

	map = _mm_shuffle_ps(lo, lo, _MM_SHUFFLE(3, 1, 2, 0)); /* 0xd8: */
	mbp = _mm_shuffle_ps(hi, hi, _MM_SHUFFLE(1, 3, 0, 2)); /* 0x72: */

	lo = _mm_castsi128_ps (_mm_min_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));
	hi = _mm_castsi128_ps (_mm_max_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));

	map = _mm_shuffle_ps(lo, hi, _MM_SHUFFLE(1, 0, 0, 1)); /* 0x41: */
	mbp = _mm_shuffle_ps(hi, lo, _MM_SHUFFLE(3, 2, 2, 3)); /* 0xeb: */

	lo = _mm_castsi128_ps (_mm_min_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));
	hi = _mm_castsi128_ps (_mm_max_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));

	map = _mm_shuffle_ps(lo, hi, _MM_SHUFFLE(3, 2, 1, 0)); /* 0xe4: */
	mbp = _mm_shuffle_ps(lo, hi, _MM_SHUFFLE(1, 0, 3, 2)); /* 0x4e: */

	lo = _mm_castsi128_ps (_mm_min_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));
	hi = _mm_castsi128_ps (_mm_max_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));

	map = _mm_shuffle_ps(lo, hi, _MM_SHUFFLE(3, 1, 2, 0)); /* 0xd8: */
	mbp = _mm_shuffle_ps(lo, hi, _MM_SHUFFLE(2, 0, 3, 1)); /* 0x8d: */

	lo = _mm_castsi128_ps (_mm_min_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));
	hi = _mm_castsi128_ps (_mm_max_epu32(_mm_castps_si128(map), _mm_castps_si128(mbp)));

	map = _mm_shuffle_ps(hi, lo, _MM_SHUFFLE(2, 0, 2, 0)); /* 0x88: */
	mbp = _mm_shuffle_ps(hi, lo, _MM_SHUFFLE(3, 1, 3, 1)); /* 0xdd: */

	map = _mm_shuffle_ps(map, map, _MM_SHUFFLE(1, 3, 0, 2)); /* 0x72: */
	mbp = _mm_shuffle_ps(mbp, mbp, _MM_SHUFFLE(1, 3, 0, 2)); /* 0x72: */

	/* unload sorted elements to memory */
	_mm_store_ps(a, map);
	_mm_store_ps(b, mbp);

	CHECK_RAWS(a, b, 4);
}