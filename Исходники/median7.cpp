inline  __m256 _mm256_broadcast_3_ss(__m256 a) {
	__m256 b = _mm256_permute_ps(a, _MM_SHUFFLE(3, 3, 3, 3));
	return _mm256_blend_ps(b, _mm256_permute2f128_ps(b, b, 1), 0xF0);
}