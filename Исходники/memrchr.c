void* memrchr(void *dst, int c, size_t len) {
	/* Backwards */
	uint8_t* a = dst;

	if(!len)
		return NULL;

	int i = len;
	int aligned_a = 0;

	aligned_a = ((uintptr_t)a & (sizeof(__m128i) - 1));
	/* aligned */
	if(aligned_a) {
		while(i && ((uintptr_t) &a[i] & ( sizeof(__m128i)-1))) {
			i--;
			if(a[i] == (char)c) {
				return a + i;
			}
		}
	}

	if(i >= 16) {
		uint32_t buf_32 = c;
		buf_32 |= (buf_32 << 8);
		buf_32 |= (buf_32 << 16);

		__m128i r1 = _mm_set_epi32(buf_32, buf_32, buf_32, buf_32);
		
		while(i >= 16) {
			i -= 16;
			__m128i x = _mm_loadu_si128((__m128i*)&(a[i])); //16byte
			__m128i cmp = _mm_cmpeq_epi8(x, r1);

			uint16_t result = (uint16_t)_mm_movemask_epi8(cmp);

			if(result != 0x0000U) {
				i += 15;
				while(!(result & 0x8000)) {
					result = result << 1;
					i--;
				}

				return a + i;
			}
		}
	}

	while(i) {
		i--;
		if(a[i] == (char)c) {
			return a + i;
		}
	}

	return NULL;
}