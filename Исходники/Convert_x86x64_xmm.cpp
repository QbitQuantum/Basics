void tuned_ConvertRGBToULY4(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride)
{
	const int shift = 14;

	__m128i rb2y, xg2y, rb2u, xg2u, rb2v, xg2v;

	if (std::is_same<T, CBGRAColorOrder>::value || std::is_same<T, CBGRColorOrder>::value)
	{
		rb2y = _mm_set2_epi16_shift(C::R2Y, C::B2Y, shift);
		xg2y = _mm_set2_epi16_shift(16.5 / 0xff, C::G2Y, shift);
		rb2u = _mm_set2_epi16_shift(C::R2U, C::B2U, shift);
		xg2u = _mm_set2_epi16_shift(128.5 / 0xff, C::G2U, shift);
		rb2v = _mm_set2_epi16_shift(C::R2V, C::B2V, shift);
		xg2v = _mm_set2_epi16_shift(128.5 / 0xff, C::G2V, shift);
	}
	else
	{
		rb2y = _mm_set2_epi16_shift(C::B2Y, C::R2Y, shift);
		xg2y = _mm_set2_epi16_shift(C::G2Y, 16.5 / 0xff, shift);
		rb2u = _mm_set2_epi16_shift(C::B2U, C::R2U, shift);
		xg2u = _mm_set2_epi16_shift(C::G2U, 128.5 / 0xff, shift);
		rb2v = _mm_set2_epi16_shift(C::B2V, C::R2V, shift);
		xg2v = _mm_set2_epi16_shift(C::G2V, 128.5 / 0xff, shift);
	}

	auto y = pYBegin;
	auto u = pUBegin;
	auto v = pVBegin;

	for (auto p = pSrcBegin; p != pSrcEnd; p += scbStride)
	{
		auto pp = p;

		for (; pp <= p + cbWidth - 16; pp += T::BYPP*4)
		{
			__m128i m = _mm_loadu_si128((const __m128i *)pp);
			__m128i rb, xg;
			if (std::is_same<T, CBGRAColorOrder>::value)
			{
				// m = XX R3 G3 B3 XX R2 G2 B2 XX R1 G1 B1 XX R0 G0 B0
				rb = _mm_and_si128(m, _mm_set1_epi16(0x00ff)); // 00 R3 00 B3 00 R2 00 B2 00 R1 00 B1 00 R0 00 B0
				xg = _mm_or_si128(_mm_srli_epi16(m, 8), _mm_set1_epi32(0x00ff0000)); // 00 ff 00 G3 00 ff 00 G2 00 ff 00 G1 00 ff 00 G0
			}
#ifdef __SSSE3__
			else if (std::is_same<T, CBGRColorOrder>::value)
			{
				// m = XX XX XX XX R3 G3 B3 R2 G2 B2 R1 G1 B1 R0 G0 B0
				rb = _mm_shuffle_epi8(m, _mm_set_epi8(-1, 11, -1, 9, -1, 8, -1, 6, -1, 5, -1, 3, -1, 2, -1, 0)); // 00 R3 00 B3 00 R2 00 B2 00 R1 00 B1 00 R0 00 B0
				xg = _mm_or_si128(_mm_shuffle_epi8(m, _mm_set_epi8(-1, -1, -1, 10, -1, -1, -1, 7, -1, -1, -1, 4, -1, -1, -1, 1)), _mm_set1_epi32(0x00ff0000)); // 00 ff 00 G3 00 ff 00 G2 00 ff 00 G1 00 ff 00 G0
			}
#endif
			else if (std::is_same<T, CARGBColorOrder>::value)
			{
				// m = B3 G3 R3 XX B2 G2 R2 XX B1 G1 R1 XX B0 G0 R0 XX
				rb = _mm_srli_epi16(m, 8); // 00 B3 00 R3 00 B2 00 R2 00 B1 00 R1 00 B0 00 R0
				xg = _mm_or_si128(_mm_and_si128(m, _mm_set1_epi32(0x00ff0000)), _mm_set1_epi32(0x000000ff)); // 00 G3 00 ff 00 G2 00 ff 00 G1 00 ff 00 G0 00 ff
			}
#ifdef __SSSE3__
			else if (std::is_same<T, CRGBColorOrder>::value)
			{
				// m = XX XX XX XX B3 G3 R3 B2 G2 R2 B1 G1 R1 B0 G0 R0
				rb = _mm_shuffle_epi8(m, _mm_set_epi8(-1, 11, -1, 9, -1, 8, -1, 6, -1, 5, -1, 3, -1, 2, -1, 0)); // 00 B3 00 R3 00 B2 00 R2 00 B1 00 R1 00 B0 00 R0
				xg = _mm_or_si128(_mm_shuffle_epi8(m, _mm_set_epi8(-1, 10, -1, -1, -1, 7, -1, -1, -1, 4, -1, -1, -1, 1, -1, -1)), _mm_set1_epi32(0x000000ff)); // 00 G3 00 ff 00 G2 00 ff 00 G1 00 ff 00 G0 00 ff
			}
#endif

			auto xrgb2yuv = [rb, xg, shift](__m128i rb2yuv, __m128i xg2yuv) -> uint32_t {
				__m128i yuv = _mm_add_epi32(_mm_madd_epi16(rb, rb2yuv), _mm_madd_epi16(xg, xg2yuv));
				yuv = _mm_srli_epi32(yuv, shift);
#ifdef __SSSE3__
				if (F >= CODEFEATURE_SSSE3)
				{
					yuv = _mm_shuffle_epi8(yuv, _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, 8, 4, 0));
				}
				else
#endif
				{
					yuv = _mm_packs_epi32(yuv, yuv);
					yuv = _mm_packus_epi16(yuv, yuv);
				}
				return _mm_cvtsi128_si32(yuv);
			};
			*(uint32_t *)y = xrgb2yuv(rb2y, xg2y);
			*(uint32_t *)u = xrgb2yuv(rb2u, xg2u);
			*(uint32_t *)v = xrgb2yuv(rb2v, xg2v);

			y += 4;
			u += 4;
			v += 4;
		}
		for (; pp < p + cbWidth; pp += T::BYPP)
		{
			__m128i m;
			__m128i rb, xg;
			if (std::is_same<T, CBGRAColorOrder>::value || std::is_same<T, CBGRColorOrder>::value)
			{
				if (std::is_same<T, CBGRAColorOrder>::value)
				{
					m = _mm_cvtsi32_si128(*(const uint32_t *)pp); // m = XX XX XX XX XX XX XX XX XX XX XX XX XX R0 G0 B0
				}
				else
				{
					m = _mm_cvtsi32_si128(*(const uint32_t *)(pp - 1)); // m = XX XX XX XX XX XX XX XX XX XX XX XX R0 G0 B0 XX
					m = _mm_srli_epi32(m, 8);
				}
				rb = _mm_and_si128(m, _mm_set1_epi16(0x00ff)); // 00 XX 00 XX 00 XX 00 XX 00 XX 00 XX 00 R0 00 B0
				xg = _mm_or_si128(_mm_srli_epi16(m, 8), _mm_set1_epi32(0x00ff0000)); // 00 ff 00 XX 00 ff 00 XX 00 ff 00 XX 00 ff 00 G0
			}
			else if (std::is_same<T, CARGBColorOrder>::value || std::is_same<T, CRGBColorOrder>::value)
			{
				if (std::is_same<T, CARGBColorOrder>::value)
				{
					m = _mm_cvtsi32_si128(*(const uint32_t *)pp); // m = XX XX XX XX XX XX XX XX XX XX XX XX B0 G0 R0 XX
				}
				else
				{
					m = _mm_cvtsi32_si128(*(const uint32_t *)(pp - 1)); // m = XX XX XX XX XX XX XX XX XX XX XX XX B0 G0 R0 XX
				}
				rb = _mm_srli_epi16(m, 8); // 00 XX 00 XX 00 XX 00 XX 00 XX 00 XX 00 B0 00 R0
				xg = _mm_or_si128(_mm_and_si128(m, _mm_set1_epi32(0x00ff0000)), _mm_set1_epi32(0x000000ff)); // 00 XX 00 ff 00 XX 00 ff 00 XX 00 ff 00 G0 00 ff
			}

			auto xrgb2yuv = [rb, xg, shift](__m128i rb2yuv, __m128i xg2yuv) -> uint8_t {
				__m128i yuv = _mm_add_epi32(_mm_madd_epi16(rb, rb2yuv), _mm_madd_epi16(xg, xg2yuv));
				yuv = _mm_srli_epi32(yuv, shift);
				return (uint8_t)_mm_cvtsi128_si32(yuv);
			};
			*y = xrgb2yuv(rb2y, xg2y);
			*u = xrgb2yuv(rb2u, xg2u);
			*v = xrgb2yuv(rb2v, xg2v);

			y++;
			u++;
			v++;
		}
	}
}