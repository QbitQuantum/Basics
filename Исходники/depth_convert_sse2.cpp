void left_shift_w2b_sse2(const void *src, void *dst, unsigned shift, unsigned left, unsigned right)
{
	const uint16_t *src_p = static_cast<const uint16_t *>(src);
	uint8_t *dst_p = static_cast<uint8_t *>(dst);

	unsigned vec_left = ceil_n(left, 16);
	unsigned vec_right = floor_n(right, 16);

	__m128i count = _mm_set1_epi64x(shift);

	if (left != vec_left) {
		__m128i lo = _mm_load_si128((const __m128i *)(src_p + vec_left - 16));
		__m128i hi = _mm_load_si128((const __m128i *)(src_p + vec_left - 8));
		lo = _mm_sll_epi16(lo, count);
		hi = _mm_sll_epi16(hi, count);
		lo = _mm_packus_epi16(lo, hi);
		mm_store_left_epi8(dst_p + vec_left - 16, lo, vec_left - left);
	}

	for (unsigned j = vec_left; j < vec_right; j += 16) {
		__m128i lo = _mm_load_si128((const __m128i *)(src_p + j + 0));
		__m128i hi = _mm_load_si128((const __m128i *)(src_p + j + 8));
		lo = _mm_sll_epi16(lo, count);
		hi = _mm_sll_epi16(hi, count);
		lo = _mm_packus_epi16(lo, hi);
		_mm_store_si128((__m128i *)(dst_p + j), lo);
	}

	if (right != vec_right) {
		__m128i lo = _mm_load_si128((const __m128i *)(src_p + vec_right + 0));
		__m128i hi = _mm_load_si128((const __m128i *)(src_p + vec_right + 8));
		lo = _mm_sll_epi16(lo, count);
		hi = _mm_sll_epi16(hi, count);
		lo = _mm_packus_epi16(lo, hi);
		mm_store_right_epi8(dst_p + vec_right, lo, right - vec_right);
	}
}