void
mulrc4_shuffle_ssse3(uint8_t *region, uint8_t constant, size_t length)
{
	uint8_t *end;
	register __m128i in, out, t1, t2, m1, m2, l, h;

	if (constant == 0) {
		memset(region, 0, length);
		return;
	}

	if (constant == 1)
		return;

	t1 = _mm_loadu_si128((void *)tl[constant]);
	t2 = _mm_slli_epi64(t1, 4);
	m1 = _mm_set1_epi8(0x0f);
	m2 = _mm_set1_epi8(0xf0);

	for (end=region+length; region<end; region+=16) {
		in = _mm_load_si128((void *)region);
		l = _mm_and_si128(in, m1);
		l = _mm_shuffle_epi8(t1, l);
		h = _mm_and_si128(in, m2);
		h = _mm_srli_epi64(h, 4);
		h = _mm_shuffle_epi8(t2, h);
		out = _mm_xor_si128(h, l);
		_mm_store_si128((void *)region, out);
	}
}