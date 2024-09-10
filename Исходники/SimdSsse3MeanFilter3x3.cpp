		template<bool align> SIMD_INLINE __m128i AverageRow16(const Buffer & buffer, size_t offset)
		{
			return _mm_mulhi_epu16(K16_DIVISION_BY_9_FACTOR, _mm_add_epi16(
				_mm_add_epi16(K16_0005, Load<align>((__m128i*)(buffer.src0 + offset))),
				_mm_add_epi16(Load<align>((__m128i*)(buffer.src1 + offset)), Load<align>((__m128i*)(buffer.src2 + offset)))));
		}