void* memccpy(void *dst, void *src, int c, size_t len) {
	uint8_t* a = dst;
	uint8_t* b = src;
	uint8_t endchar = c & 0xff;

	if(!len)
		return NULL;

	int aligned_a = 0, aligned_b = 0;
	int i = 0;

	aligned_a = ((uintptr_t)a & (sizeof(__m128i) - 1));
	aligned_b = ((uintptr_t)b & (sizeof(__m128i) - 1));

	/* Not aligned */
	if(aligned_a != aligned_b) {
		while(len) {
			if(b[i] == endchar) {
				a[i] = b[i];
				return a + i;
			}

			a[i] = b[i];

			i++;
			len--;
		}

		return NULL;
	}

	/* aligned */
	if(aligned_a) {
		while(len && ((uintptr_t) &a[i] & ( sizeof(__m128i)-1))) {
			if(b[i] == endchar) {
				a[i] = b[i];
				return a + i;
			}

			a[i] = b[i];

			i++;
			len--;
		}
	}

	if(len >= 16) {
		uint32_t buf_32 = endchar;
		buf_32 |= (buf_32 << 8);
		buf_32 |= (buf_32 << 16);

		__m128i r1 = _mm_set_epi32(buf_32, buf_32, buf_32, buf_32);

		while(len >= 16) {
			__m128i y = _mm_loadu_si128((__m128i*)&(b[i])); //16byte

			__m128i cmp = _mm_cmpeq_epi8(y, r1);

			uint16_t result = (uint16_t)_mm_movemask_epi8(cmp);

			if(result != 0x0) {
				//result = ~result;

				while(1) {
					if(result & 0x1) {
						a[i] = b[i];
						return a + i;
					}

					a[i] = b[i];
					result = result >> 1;
					i++;
				}
			}

			_mm_store_si128((__m128i*)&a[i], y);

			i += 16;
			len -= 16;
		}
	}