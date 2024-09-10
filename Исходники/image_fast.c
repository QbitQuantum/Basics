ppm_t* img_fast_bw(ppm_t* src, uint64_t* cycles)
{
	int i = 0, j = 0;
	
	uint8_t* r = src->r;
	uint8_t* g = src->g;
	uint8_t* b = src->b;
	int ni = 0;
	
	__m128i xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
	
	uint64_t t0 = readTSC();
	
	for (j = 0; j < src->w; j++)
	{
		for (i = 0; i < src->h; i += 16)
		{
			ni += 16;
			
			// Load 16 RGB pixels
			xmm0 = _mm_load_si128((__m128i*)(r + ni));
			xmm1 = _mm_load_si128((__m128i*)(g + ni));
			xmm2 = _mm_load_si128((__m128i*)(b + ni));
			
			// Average by pairs (RG, GB), then average pairs
			xmm3 = _mm_avg_epu8(xmm0, xmm1);
			xmm4 = _mm_avg_epu8(xmm1, xmm2);
			xmm5 = _mm_avg_epu8(xmm0, xmm1);
			
			// Store back
			_mm_store_si128((__m128i*)(r + ni), xmm5);
			_mm_store_si128((__m128i*)(g + ni), xmm5);
			_mm_store_si128((__m128i*)(b + ni), xmm5);
		}
	}
	
	if (cycles != NULL) *cycles = cyclesElapsed(readTSC(), t0);
	
	return src;
}