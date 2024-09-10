__m128i shift_left_sse11(__m128i vec, __m128i next_vec, int shift_num) {
	if (shift_num % 4 == 0)
		return left_alignr_helper(vec, next_vec, shift_num / 4);

	__m128i carryover;
	__m128i shiftee;
	__m128i mask;

	carryover = left_alignr_helper(vec, next_vec, shift_num / 4 + 1);
//	print128_bit(carryover);
	carryover = _mm_slli_epi64(carryover, (4 - (shift_num % 4)) * 2);
//	print128_bit(carryover);

	if (shift_num > 4)
		shiftee = left_alignr_helper(vec, next_vec, shift_num / 4);
	else
		shiftee = vec;

	shiftee = _mm_srli_epi64(shiftee, (shift_num % 4) * 2);

	return _mm_or_si128(shiftee, carryover);
}