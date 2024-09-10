static void SSE2_StereoMixToFloat(const int32 *pSrc, float *pOut1, float *pOut2, uint32 nCount, const float _i2fc)
//----------------------------------------------------------------------------------------------------------------
{
	__m128 i2fc = _mm_load_ps1(&_i2fc);
	const __m128i *in = reinterpret_cast<const __m128i *>(pSrc);

	// We may read beyond the wanted length... this works because we know that we will always work on our buffers of size MIXBUFFERSIZE
	nCount = (nCount + 3) / 4;
	do
	{
		__m128i i1 = _mm_loadu_si128(in);		// Load four integer values, LRLR
		__m128i i2 = _mm_loadu_si128(in + 1);	// Load four integer values, LRLR
		in += 2;
		__m128 f1 = _mm_cvtepi32_ps(i1);		// Convert to four floats, LRLR
		__m128 f2 = _mm_cvtepi32_ps(i2);		// Convert to four floats, LRLR
		f1 = _mm_mul_ps(f1, i2fc);				// Apply int->float factor
		f2 = _mm_mul_ps(f2, i2fc);				// Apply int->float factor
		__m128 fl = _mm_shuffle_ps(f1, f2, _MM_SHUFFLE(2, 0, 2, 0));	// LRLR+LRLR => LLLL
		__m128 fr = _mm_shuffle_ps(f1, f2, _MM_SHUFFLE(3, 1, 3, 1));	// LRLR+LRLR => RRRR
		_mm_storeu_ps(pOut1, fl);				// Store four float values, LLLL
		_mm_storeu_ps(pOut2, fr);				// Store four float values, RRRR
		pOut1 += 4;
		pOut2 += 4;
	} while(--nCount);
}