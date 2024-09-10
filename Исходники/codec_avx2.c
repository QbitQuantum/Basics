static inline __m256i
dec_reshuffle (__m256i in)
{
	// Shuffle bytes to 32-bit bigendian:
	in = _mm256_bswap_epi32(in);

	// Mask in a single byte per shift:
	__m256i mask = _mm256_set1_epi32(0x3F000000);

	// Pack bytes together:
	__m256i out = _mm256_slli_epi32(_mm256_and_si256(in, mask), 2);
	mask = _mm256_srli_epi32(mask, 8);

	out = _mm256_or_si256(out, _mm256_slli_epi32(_mm256_and_si256(in, mask), 4));
	mask = _mm256_srli_epi32(mask, 8);

	out = _mm256_or_si256(out, _mm256_slli_epi32(_mm256_and_si256(in, mask), 6));
	mask = _mm256_srli_epi32(mask, 8);

	out = _mm256_or_si256(out, _mm256_slli_epi32(_mm256_and_si256(in, mask), 8));

	// Pack bytes together within 32-bit words, discarding words 3 and 7:
	out = _mm256_shuffle_epi8(out, _mm256_setr_epi8(
		 3,  2,  1,
		 7,  6,  5,
		11, 10,  9,
		15, 14, 13,
		-1, -1, -1, -1,
		 3,  2,  1,
		 7,  6,  5,
		11, 10,  9,
		15, 14, 13,
		-1, -1, -1, -1));

	// Pack 32-bit words together, squashing empty words 3 and 7:
	return _mm256_permutevar8x32_epi32(out, _mm256_setr_epi32(
		0, 1, 2, 4, 5, 6, -1, -1));
}