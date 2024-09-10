	void convert_le_d24x8_to_le_f32(void *dst, void *src, u32 row_length_in_texels, u32 num_rows)
	{
		const u32 num_pixels = row_length_in_texels * num_rows;
		verify(HERE), (num_pixels & 3) == 0;

		const auto num_iterations = (num_pixels >> 2);

		__m128i* dst_ptr = (__m128i*)dst;
		__m128i* src_ptr = (__m128i*)src;

		const __m128 scale_vector = _mm_set1_ps(1.f / 16777214.f);
		const __m128i mask = _mm_set1_epi32(0x00FFFFFF);
		for (u32 n = 0; n < num_iterations; ++n)
		{
			const __m128 src_vector = _mm_cvtepi32_ps(_mm_and_si128(mask, _mm_loadu_si128(src_ptr)));
			const __m128 normalized_vector = _mm_mul_ps(src_vector, scale_vector);
			_mm_stream_si128(dst_ptr, (__m128i&)normalized_vector);
			++dst_ptr;
			++src_ptr;
		}
	}