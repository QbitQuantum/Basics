static __m128i
test_mm_max_epu16 (struct testcase *tc)
{
	tc->expect = (tc->i > tc->j) ? tc->i : tc->j;
	return _mm_max_epu16(
		_mm_set1_epi16(tc->i),
		_mm_set1_epi16(tc->j));
}