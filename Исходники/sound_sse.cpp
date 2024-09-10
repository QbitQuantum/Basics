void SoundSSE::unpack_16bit_mono(short *input, int size, float *output)
{
#ifndef CL_DISABLE_SSE2
	int sse_size = (size/8)*8;

	__m128i zero = _mm_setzero_si128();
	__m128 constant1 = _mm_set1_ps(1.0f/32767.0f);
	for (int i = 0; i < sse_size; i+=8)
	{
		__m128i isamples = _mm_loadu_si128((__m128i*)(input+i));
		__m128 samples0 = _mm_cvtepi32_ps(_mm_srai_epi32(_mm_unpacklo_epi16(zero, isamples), 16));
		__m128 samples1 = _mm_cvtepi32_ps(_mm_srai_epi32(_mm_unpackhi_epi16(zero, isamples), 16));
		samples0 = _mm_mul_ps(samples0, constant1);
		samples1 = _mm_mul_ps(samples1, constant1);
		_mm_storeu_ps(output+i+0, samples0);
		_mm_storeu_ps(output+i+4, samples1);
	}
#else
	const int sse_size = 0;
#endif

	// unpack remaining
	for (int i = sse_size; i < size; i++)
	{
		output[i] = ((float) input[i]) / 32767.0f;
	}
}