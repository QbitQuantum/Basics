void AlignedAvxNonTemporalMult(float* d, float const* a, float const* b)
{
	for(int i = 0; i < gNumFloats; i += 8)
	{
		__m256 v1 = _mm256_load_ps(&a[i]);
		__m256 v2 = _mm256_load_ps(&b[i]);
		__m256 r = _mm256_mul_ps(v1, v2);
		_mm256_stream_ps(&d[i], r);
	}
}