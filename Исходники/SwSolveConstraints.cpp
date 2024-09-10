	template <> __m256 fnmadd_ps<2>(__m256 a, __m256 b, __m256 c)
	{
		return _mm256_fnmadd_ps(a, b, c);
	}