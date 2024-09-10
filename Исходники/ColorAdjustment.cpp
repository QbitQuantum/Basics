void CColorAdjustment::ProcessY(int Width, int Height, uint8_t *pData, int Pitch)
{
	if (m_Brightness != 0 || m_Contrast != 0) {
		if (m_fUpdateYTable) {
			MakeYTable(m_YTable, m_Brightness, m_Contrast);
			m_fUpdateYTable = false;
		}

#ifdef TVTVIDEODEC_SSE2_SUPPORT
		const bool fSSE2 = IsSSE2Enabled();
#endif

		for (int y = 0; y < Height; y++) {
			uint8_t *p = pData;
			int x = 0;

#ifdef TVTVIDEODEC_SSE2_SUPPORT
			if (fSSE2 && !((uintptr_t)p & 15)) {
				const short c = (short)(min((m_Contrast * 512 / 100) + 512, (1 << 16) - 1));
				const short b = (short)((m_Brightness * 255 / 100) + 16);
				const __m128i bc = _mm_set_epi16(b, c, b, c, b, c, b, c);
				const __m128i zero = _mm_setzero_si128();
				const __m128i w16 = _mm_set1_epi16(16);
				const __m128i w512 = _mm_set1_epi16(512);

				for (; x + 16 <= Width; x += 16) {
					__m128i r = _mm_load_si128((const __m128i*)p);

					__m128i rl = _mm_unpacklo_epi8(r, zero);
					__m128i rh = _mm_unpackhi_epi8(r, zero);

					rl = _mm_subs_epi16(rl, w16);
					rh = _mm_subs_epi16(rh, w16);

					__m128i rll = _mm_unpacklo_epi16(rl, w512);
					__m128i rlh = _mm_unpackhi_epi16(rl, w512);
					__m128i rhl = _mm_unpacklo_epi16(rh, w512);
					__m128i rhh = _mm_unpackhi_epi16(rh, w512);

					rll = _mm_madd_epi16(rll, bc);
					rlh = _mm_madd_epi16(rlh, bc);
					rhl = _mm_madd_epi16(rhl, bc);
					rhh = _mm_madd_epi16(rhh, bc);

					rll = _mm_srai_epi32(rll, 9);
					rlh = _mm_srai_epi32(rlh, 9);
					rhl = _mm_srai_epi32(rhl, 9);
					rhh = _mm_srai_epi32(rhh, 9);

					rl = _mm_packs_epi32(rll, rlh);
					rh = _mm_packs_epi32(rhl, rhh);

					r = _mm_packus_epi16(rl, rh);

					_mm_store_si128((__m128i*)p, r);

					p += 16;
				}
			}
#endif

			for (; x < Width; x++) {
				*p = m_YTable[*p];
				p++;
			}

			pData += Pitch;
		}
	}
}