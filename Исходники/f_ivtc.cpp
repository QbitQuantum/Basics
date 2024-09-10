	IVTCScore ComputeScanImprovement_X8R8G8B8_SSE2(const void *src1, const void *src2, ptrdiff_t srcpitch, uint32 w, uint32 h) {
		IVTCScore score = {0};

		__m128i zero = _mm_setzero_si128();

		uint32 w2 = w >> 1;

		static const __m128i mask = { -1, -1, -1, -1, -1, -1, 0, 0, -1, -1, -1, -1, -1, -1, 0, 0 };

		bool firstfield = true;
		do {
			__m128i var = zero;
			__m128i varshift = zero;

			const uint8 *src1r0 = (const uint8 *)src1;
			const uint8 *src1r1 = src1r0 + srcpitch;
			const uint8 *src1r2 = src1r1 + srcpitch;
			const uint8 *src2r = (const uint8 *)src2 + srcpitch;
			for(uint32 x=0; x<w2; ++x) {
				__m128i rA = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)src1r0), zero);
				__m128i rB = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)src1r1), zero);
				__m128i rC = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)src1r2), zero);
				__m128i rE = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)src2r), zero);
				__m128i rAC = _mm_add_epi16(rA, rC);
				__m128i d1 = _mm_sub_epi16(rAC, _mm_add_epi16(rB, rB));		// combing in current frame
				__m128i d3 = _mm_sub_epi16(rAC, _mm_add_epi16(rE, rE));		// combing in merged frame

				d1 = _mm_and_si128(d1, mask);
				d3 = _mm_and_si128(d3, mask);

				var = _mm_add_epi32(var, _mm_madd_epi16(d1, d1));
				varshift = _mm_add_epi32(varshift, _mm_madd_epi16(d3, d3));

				src1r0 += 8;
				src1r1 += 8;
				src1r2 += 8;
				src2r += 8;
			}

			if (w & 1) {
				__m128i rA = _mm_unpacklo_epi8(_mm_cvtsi32_si128(*(const int *)src1r0), zero);
				__m128i rB = _mm_unpacklo_epi8(_mm_cvtsi32_si128(*(const int *)src1r1), zero);
				__m128i rC = _mm_unpacklo_epi8(_mm_cvtsi32_si128(*(const int *)src1r2), zero);
				__m128i rE = _mm_unpacklo_epi8(_mm_cvtsi32_si128(*(const int *)src2r), zero);
				__m128i rAC = _mm_add_epi16(rA, rC);
				__m128i d1 = _mm_sub_epi16(rAC, _mm_add_epi16(rB, rB));		// combing in current frame
				__m128i d3 = _mm_sub_epi16(rAC, _mm_add_epi16(rE, rE));		// combing in merged frame

				d1 = _mm_and_si128(d1, mask);
				d3 = _mm_and_si128(d3, mask);

				var = _mm_add_epi32(var, _mm_madd_epi16(d1, d1));
				varshift = _mm_add_epi32(varshift, _mm_madd_epi16(d3, d3));
			}

			src1 = (const uint8 *)src1 + srcpitch;
			src2 = (const uint8 *)src2 + srcpitch;

			var = _mm_add_epi32(var, _mm_shuffle_epi32(var, 0xee));
			varshift = _mm_add_epi32(varshift, _mm_shuffle_epi32(varshift, 0xee));
			var = _mm_add_epi32(var, _mm_shuffle_epi32(var, 0x55));
			varshift = _mm_add_epi32(varshift, _mm_shuffle_epi32(varshift, 0x55));

			uint32 ivar = _mm_cvtsi128_si32(var);
			uint32 ivarshift = _mm_cvtsi128_si32(varshift);

			if (firstfield) {
				score.mVar[0] += ivar;
				score.mVarShift[0] += ivarshift;
			} else {
				score.mVar[1] += ivar;
				score.mVarShift[1] += ivarshift;
			}

			firstfield = !firstfield;
		} while(--h);

		return score;
	}