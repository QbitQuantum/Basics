bool CResizeEngine::verticalFilter(CDIBSection *src, CDIBSection *dst, ILongTimeRunCallback *pCallback) {
	assert(src->getBitCounts() == dst->getBitCounts());
	int bitcount = src->getBitCounts();
	uint src_width = src->getWidth();
	uint src_height = src->getHeight();
	uint dst_width = dst->getWidth();
	uint dst_height = dst->getHeight();
	assert(src_width == dst_width);
	src_width = src_width;
	if (src_height == dst_height) {

		unsigned char *src_bits = (unsigned char *)src->getData();
		unsigned char *dst_bits = (unsigned char *)dst->getData();
		assert(src_bits && dst_bits);

		memcpy(dst_bits, src_bits, dst_height * dst->getStride());

	} else if (!m_pFilter) { // fast (COLOR ON COLOR)

		double ratio_h = (double)src_height / (double)dst_height;

		uint bytespp = bitcount / 8;
		for (uint y = 0; y < dst_height; ++ y) {
			uint sy = (uint)(y * ratio_h + 0.5);
			if (sy >= src_height) {
				sy = src_height - 1;
			}
			uint8 *dst_data = (uint8 *)dst->getLine(y);
			uint8 *src_line = (uint8 *)src->getLine(sy);

			for (uint x = 0; x < dst_width; ++ x) {
				uint8 *src_data = src_line + x * bytespp;
				for (uint i = 0; i < bytespp; ++ i) {
					*dst_data ++ = *src_data ++;
				}
			}
		}

	} else {
#ifdef USE_SSE
		__m128i value, t;
		__m128 a, b, c, v05 = _mm_set_ps1(0.5);
#elif (defined(USE_SSE2))
		__m128i value, t;
		__m128d a, b, c, v05 = _mm_set1_pd(0.5);
#endif
		uint index; // pixel index
		CWeightsTable weightsTable(m_pFilter, dst_height, src_height);

		uint bytespp = src->getBitCounts() / 8;
		assert(bytespp == 3 || bytespp == 4);

		unsigned src_pitch = src->getStride();
		unsigned dst_pitch = dst->getStride();

		for(uint x = 0; x < dst_width; ++ x) {
			// test for stop
			if (x % 16 == 0) {
				if (pCallback && pCallback->shouldStop()) {
					return false;
				}
			}
			index = x * bytespp;

			unsigned char *dst_bits = (unsigned char *)dst->getData();
			dst_bits += index;

			for(uint y = 0; y < dst_height; ++ y) {
#ifdef USE_SSE
				__m128 v = _mm_set_ps1(0.0);
#elif defined (USE_SSE2)
				__m128d v1 = _mm_set1_pd(0.0);
				__m128d v2 = _mm_set1_pd(0.0);
#elif defined (USE_FLOAT)
				float value[4] = {0, 0, 0, 0};
#else
				double value[4] = {0, 0, 0, 0}; // 4 = 32bpp max
#endif
				int iLeft = weightsTable.getLeftBoundary(y);
				int iRight = weightsTable.getRightBoundary(y);

				uint8 *src_bits = src->getLine(iLeft);
				src_bits += index;

				for(int i = iLeft; i <= iRight; ++ i) {
#ifdef USE_SSE
					float weight = (float)weightsTable.getWeight(y, i - iLeft);
					a = _mm_set_ps1(weight);
					if (bytespp == 3) {
						t = _mm_set_epi32(0, src_bits[2], src_bits[1], src_bits[0]);
					} else {
						t = _mm_set_epi32(src_bits[3], src_bits[2], src_bits[1], src_bits[0]);
					}

					b = _mm_cvtepi32_ps(t);
					c = _mm_mul_ps(a, b);
					v = _mm_add_ps(v, c);
#elif defined(USE_SSE2)
					double weight = weightsTable.getWeight(y, i - iLeft);

					a = _mm_set1_pd(weight);
					t = _mm_set_epi32(0, 0, src_bits[1], src_bits[0]);
					b = _mm_cvtepi32_pd(t);
					c = _mm_mul_pd(a, b);
					v1 = _mm_add_pd(v1, c);

					t = _mm_set_epi32(0, 0, bytespp == 3 ? 0 : src_bits[3], src_bits[2]);
					b = _mm_cvtepi32_pd(t);
					c = _mm_mul_pd(a, b);
					v2 = _mm_add_pd(v2, c);
#elif defined (USE_FLOAT)
					float weight = (float)weightsTable.getWeight(y, i - iLeft);							
					for (uint j = 0; j < bytespp; ++ j) {
						value[j] += (weight * (float)src_bits[j]);
					}
#else
					double weight = weightsTable.getWeight(y, i - iLeft);							
					for (uint j = 0; j < bytespp; ++ j) {
						value[j] += (weight * (double)src_bits[j]);
					}
#endif

					src_bits += src_pitch;
				}

				// clamp and place result in destination pixel
#ifdef USE_SSE
				v = _mm_add_ps(v, v05);
				value = _mm_cvtps_epi32(v);
// 				__m128i flag = _mm_cmpgt_epi32(value, _mm_set1_epi32(0));
// 				value = _mm_and_si128(value, flag);
// 				dst_bits[0] = (unsigned char)MIN(255, value.m128i_i32[0]);
// 				dst_bits[1] = (unsigned char)MIN(255, value.m128i_i32[1]);
// 				dst_bits[2] = (unsigned char)MIN(255, value.m128i_i32[2]);
// 				if (bytespp == 4) {
// 					dst_bits[3] = (unsigned char)MIN(255, value.m128i_i32[3]);
// 				}
				dst_bits[0] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[0]), (int)255);
				dst_bits[1] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[1]), (int)255);
				dst_bits[2] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[2]), (int)255);
				if (bytespp == 4) {
					dst_bits[3] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[3]), (int)255);
				}
#elif defined (USE_SSE2)
				v1 = _mm_add_pd(v1, v05);
				v2 = _mm_add_pd(v2, v05);
				value = _mm_cvtpd_epi32(v1);
 				dst_bits[0] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[0]), (int)255);
				dst_bits[1] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[1]), (int)255);
				value = _mm_cvtpd_epi32(v2);
				dst_bits[2] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[0]), (int)255);
				if (bytespp == 4) {
					dst_bits[3] = (unsigned char)MIN(MAX((int)0, value.m128i_i32[1]), (int)255);
				}
#else
				for (unsigned j = 0; j < bytespp; ++ j) {
					dst_bits[j] = (unsigned char)MIN(MAX((int)0, (int)(value[j] + 0.5)), (int)255);
				}
#endif

				dst_bits += dst_pitch;
			}
		}
	}
	return true;
}