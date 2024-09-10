inline void modify2x264StyleDepth(uint16_t *lp,const int lshift)
{
	
	
	if(SIMDWIDTH==8)
	{
		auto xmm0 = _mm_loadu_si128((__m128i*)lp);
		auto xmm1 = _mm_slli_epi16(xmm0,lshift);
		_mm_stream_si128((__m128i*)lp,xmm1);
	}
	else
	{
		for(int i=0;i<SIMDWIDTH;i++)
		{
			lp[i] = lp[i] << lshift;
		}
	}
}