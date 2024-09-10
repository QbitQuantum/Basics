	if(Index < MaxSize)
	{
		const u32* pData = (const u32 *)(cached_arraybases[ARRAY_POSITION] + (Index * arraystrides[ARRAY_POSITION]));
		((u32*)VertexManager::s_pCurBufferPointer)[0] = Common::swap32(pData[0]);
		((u32*)VertexManager::s_pCurBufferPointer)[1] = Common::swap32(pData[1]);
		if (three)
			((u32*)VertexManager::s_pCurBufferPointer)[2] = Common::swap32(pData[2]);
		else
			((float*)VertexManager::s_pCurBufferPointer)[2] = 0.0f;
		LOG_VTX();
		VertexManager::s_pCurBufferPointer += 12;
	}
}

#if _M_SSE >= 0x301
static const __m128i kMaskSwap32_3 = _mm_set_epi32(0xFFFFFFFFL, 0x08090A0BL, 0x04050607L, 0x00010203L);
static const __m128i kMaskSwap32_2 = _mm_set_epi32(0xFFFFFFFFL, 0xFFFFFFFFL, 0x04050607L, 0x00010203L);

template<bool three,int MaxSize>
void Pos_ReadIndex_Float_SSSE3(int Index)
{
	if(Index < MaxSize)
	{
		const u32* pData = (const u32 *)(cached_arraybases[ARRAY_POSITION] + (Index * arraystrides[ARRAY_POSITION]));
		GC_ALIGNED128(const __m128i a = _mm_loadu_si128((__m128i*)pData));
		GC_ALIGNED128(__m128i b = _mm_shuffle_epi8(a, three ? kMaskSwap32_3 : kMaskSwap32_2));
		_mm_storeu_si128((__m128i*)VertexManager::s_pCurBufferPointer, b);
		LOG_VTX();
		VertexManager::s_pCurBufferPointer += 12;
	}
}