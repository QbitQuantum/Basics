void FragmentAttributesBuffer::SetAll(const FragmentAttributes &attr)
{
	size_t i = 0;
	
#ifdef ENABLE_SSE2
	const __m128i attrDepth_vec128				= _mm_set1_epi32(attr.depth);
	const __m128i attrOpaquePolyID_vec128		= _mm_set1_epi8(attr.opaquePolyID);
	const __m128i attrTranslucentPolyID_vec128	= _mm_set1_epi8(attr.translucentPolyID);
	const __m128i attrStencil_vec128			= _mm_set1_epi8(attr.stencil);
	const __m128i attrIsFogged_vec128			= _mm_set1_epi8(attr.isFogged);
	const __m128i attrIsTranslucentPoly_vec128	= _mm_set1_epi8(attr.isTranslucentPoly);
	
	const size_t sseCount = count - (count % 16);
	for (; i < sseCount; i += 16)
	{
		_mm_stream_si128((__m128i *)(this->depth +  0), attrDepth_vec128);
		_mm_stream_si128((__m128i *)(this->depth +  4), attrDepth_vec128);
		_mm_stream_si128((__m128i *)(this->depth +  8), attrDepth_vec128);
		_mm_stream_si128((__m128i *)(this->depth + 12), attrDepth_vec128);
		
		_mm_stream_si128((__m128i *)this->opaquePolyID, attrOpaquePolyID_vec128);
		_mm_stream_si128((__m128i *)this->translucentPolyID, attrTranslucentPolyID_vec128);
		_mm_stream_si128((__m128i *)this->stencil, attrStencil_vec128);
		_mm_stream_si128((__m128i *)this->isFogged, attrIsFogged_vec128);
		_mm_stream_si128((__m128i *)this->isTranslucentPoly, attrIsTranslucentPoly_vec128);
	}
#endif
	
	for (; i < count; i++)
	{
		this->SetAtIndex(i, attr);
	}
}