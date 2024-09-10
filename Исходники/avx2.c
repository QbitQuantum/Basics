	mask = _mm256_srli_epi32(mask, 8);

	/* Shift bits by 6, mask in only the third byte: */
	res = _mm256_or_si256(res, _mm256_and_si256(_mm256_srli_epi32(str, 6) , mask));
	mask = _mm256_srli_epi32(mask, 8);

	/* No shift necessary for the fourth byte because we duplicated
	 * the third byte to this position; just mask: */
	res = _mm256_or_si256(res, _mm256_and_si256(str, mask));

	/* Reorder to 32-bit little-endian: */
	res = _mm256_shuffle_epi8(res,
	      _mm256_setr_epi8(
			 3,  2,  1,  0,
			 7,  6,  5,  4,
			11, 10,  9,  8,
			15, 14, 13, 12,
			 3,  2,  1,  0,
			 7,  6,  5,  4,
			11, 10,  9,  8,
			15, 14, 13, 12));

	/* The bits have now been shifted to the right locations;
	 * translate their values 0..63 to the Base64 alphabet.
	 * Because AVX2 can only compare 'greater than', start from end of alphabet: */

	/* set 5: 63, "/" */
	s5mask = _mm256_cmpeq_epi8(res, _mm256_set1_epi8(63));
	blockmask = s5mask;

	/* set 4: 62, "+" */
	s4mask = _mm256_cmpeq_epi8(res, _mm256_set1_epi8(62));