TARGET_SSE4_1 static inline __m128i extract(__m128i xmm0, __m128i xmm1, __m128i xmm2, __m128i xmm3)
{
	__m64 mm0, mm1;

	mm0 = _mm_cvtsi64_m64(Ax[0][static_cast<quint8>(_mm_extract_epi8(xmm0, row + 0))]);
	mm0 = _mm_xor_64(mm0, Ax[1][static_cast<quint8>(_mm_extract_epi8(xmm0, row + 8))]);
	mm0 = _mm_xor_64(mm0, Ax[2][static_cast<quint8>(_mm_extract_epi8(xmm1, row + 0))]);
	mm0 = _mm_xor_64(mm0, Ax[3][static_cast<quint8>(_mm_extract_epi8(xmm1, row + 8))]);
	mm0 = _mm_xor_64(mm0, Ax[4][static_cast<quint8>(_mm_extract_epi8(xmm2, row + 0))]);
	mm0 = _mm_xor_64(mm0, Ax[5][static_cast<quint8>(_mm_extract_epi8(xmm2, row + 8))]);
	mm0 = _mm_xor_64(mm0, Ax[6][static_cast<quint8>(_mm_extract_epi8(xmm3, row + 0))]);
	mm0 = _mm_xor_64(mm0, Ax[7][static_cast<quint8>(_mm_extract_epi8(xmm3, row + 8))]);

	mm1 = _mm_cvtsi64_m64(Ax[0][static_cast<quint8>(_mm_extract_epi8(xmm0, row + 1))]);
	mm1 = _mm_xor_64(mm1, Ax[1][static_cast<quint8>(_mm_extract_epi8(xmm0, row + 9))]);
	mm1 = _mm_xor_64(mm1, Ax[2][static_cast<quint8>(_mm_extract_epi8(xmm1, row + 1))]);
	mm1 = _mm_xor_64(mm1, Ax[3][static_cast<quint8>(_mm_extract_epi8(xmm1, row + 9))]);
	mm1 = _mm_xor_64(mm1, Ax[4][static_cast<quint8>(_mm_extract_epi8(xmm2, row + 1))]);
	mm1 = _mm_xor_64(mm1, Ax[5][static_cast<quint8>(_mm_extract_epi8(xmm2, row + 9))]);
	mm1 = _mm_xor_64(mm1, Ax[6][static_cast<quint8>(_mm_extract_epi8(xmm3, row + 1))]);
	mm1 = _mm_xor_64(mm1, Ax[7][static_cast<quint8>(_mm_extract_epi8(xmm3, row + 9))]);

	return _mm_set_epi64(mm1, mm0);
}