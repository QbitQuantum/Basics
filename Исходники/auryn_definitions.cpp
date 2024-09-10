inline __m128 sse_load( float * i ) 
{
#ifdef CODE_ALIGNED_SIMD_INSTRUCTIONS
	return _mm_load_ps( i );
#else
	return _mm_loadu_ps( i );
#endif
}