void LOADERDECL TexCoord_ReadIndex_Short2_SSE4()
{
	static_assert(!std::numeric_limits<I>::is_signed, "Only unsigned I is sane!");

	// Heavy in ZWW
	auto const index = DataRead<I>();
	const s32 *pData = (const s32*)(cached_arraybases[ARRAY_TEXCOORD0+tcIndex] + (index * g_main_cp_state.array_strides[ARRAY_TEXCOORD0+tcIndex]));
	const __m128i a = _mm_cvtsi32_si128(*pData);
	const __m128i b = _mm_shuffle_epi8(a, kMaskSwap16_2);
	const __m128i c = _mm_cvtepi16_epi32(b);
	const __m128 d = _mm_cvtepi32_ps(c);
	const __m128 e = _mm_load1_ps(&tcScale[tcIndex]);
	const __m128 f = _mm_mul_ps(d, e);
	_mm_storeu_ps((float*)VertexManager::s_pCurBufferPointer, f);
	VertexManager::s_pCurBufferPointer += sizeof(float) * 2;
	LOG_TEX<2>();
	tcIndex++;
}