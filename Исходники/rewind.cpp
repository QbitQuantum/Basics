// There's no equivalent in libc, you'd think so ... std::mismatch exists, but it's not optimized at all. :(
static inline size_t find_change(const uint16_t * a, const uint16_t * b)
{
	const __m128i * a128=(const __m128i*)a;
	const __m128i * b128=(const __m128i*)b;
	
	while (true)
	{
		__m128i v0 = _mm_loadu_si128(a128);
		__m128i v1 = _mm_loadu_si128(b128);
		__m128i c = _mm_cmpeq_epi32(v0, v1);
		uint32_t mask = _mm_movemask_epi8(c);
		a128++;
		b128++;
		__m128i v0b = _mm_loadu_si128(a128);
		__m128i v1b = _mm_loadu_si128(b128);
		__m128i cb = _mm_cmpeq_epi32(v0b, v1b);
		uint32_t maskb = _mm_movemask_epi8(cb);
		if (mask != 0xffff || maskb != 0xffff) // Something has changed, figure out where.
		{
			if (mask == 0xffff) mask=maskb;
			else a128--;//ignore b128 since we'll return anyways
			size_t ret=(((char*)a128-(char*)a) | (compat_ctz(~mask))) >> 1;
			return (ret | (a[ret]==b[ret]));
		}
		a128++;
		b128++;
	}
}