void ie_FillLine(iePwBGRA pDst, DWORD nXW, iewBGRA clr)
{
#ifndef __X64__
	if (g_bSSE2 && (nXW >= 4) && (_mm_isAligned(pDst) || _mm_isAligned(pDst + 1))) {
#else
	if (nXW >= 4) {
#endif
		// Do fill using SSE2!

		if (!_mm_isAligned(pDst)) {												// Fill until destination is aligned
			*pDst++ = clr;
			nXW--;
		}

		__m128i r0 = _mm_loadl_epi64((const __m128i *)&clr);
		r0 = _mm_unpacklo_epi64(r0, r0);

		for (DWORD nXW_2 = nXW >> 1; nXW_2--;) {
			_mm_store_si128((__m128i *)pDst, r0);
			pDst += 2;
		}

		if (nXW & 1) {
			_mm_storel_epi64((__m128i *)pDst, r0);
		}

		return;
	}

	while (nXW--)
		*pDst++ = clr;
}