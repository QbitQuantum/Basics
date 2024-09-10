inline COLORREF MakeColor2(COLORREF a, COLORREF b, int alpha)
{
#ifdef USE_SSE2
	// (a * alpha + b * (256 - alpha)) / 256 -> ((a - b) * alpha) / 256 + b
	__m128i xmm0, xmm1, xmm2, xmm3;
	COLORREF color;
	xmm0 = _mm_setzero_si128();
	xmm1 = _mm_cvtsi32_si128( a );
	xmm2 = _mm_cvtsi32_si128( b );
	xmm3 = _mm_cvtsi32_si128( alpha );

	xmm1 = _mm_unpacklo_epi8( xmm1, xmm0 ); // a:a:a:a
	xmm2 = _mm_unpacklo_epi8( xmm2, xmm0 ); // b:b:b:b
	xmm3 = _mm_shufflelo_epi16( xmm3, 0 ); // alpha:alpha:alpha:alpha

	xmm1 = _mm_sub_epi16( xmm1, xmm2 ); // (a - b)
	xmm1 = _mm_mullo_epi16( xmm1, xmm3 ); // (a - b) * alpha
	xmm1 = _mm_srli_epi16( xmm1, 8 ); // ((a - b) * alpha) / 256
	xmm1 = _mm_add_epi8( xmm1, xmm2 ); // ((a - b) * alpha) / 256 + b

	xmm1 = _mm_packus_epi16( xmm1, xmm0 );
	color = _mm_cvtsi128_si32( xmm1 );

	return color;
#else
	const int ap = alpha;
	const int bp = 256 - ap;
	BYTE valR = (BYTE)((GetRValue(a) * ap + GetRValue(b) * bp) / 256);
	BYTE valG = (BYTE)((GetGValue(a) * ap + GetGValue(b) * bp) / 256);
	BYTE valB = (BYTE)((GetBValue(a) * ap + GetBValue(b) * bp) / 256);
	return RGB(valR, valG, valB);
#endif
}