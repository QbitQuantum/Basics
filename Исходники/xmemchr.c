void* xmemchr(const void* src, int c, size_t n)
{

	if (n < 32) {
		return xmemchr_tiny(src, c, n);
	}


	__m256i ymm0 = _mm256_set1_epi8((char)c), ymm1;
	int mask;

	size_t rem = n % 32;
	n /= 32;

	for (size_t i = 0; i < n; i++) {
		ymm1 = _mm256_loadu_si256((const __m256i*)src + i);
		ymm1 = _mm256_cmpeq_epi8(ymm1, ymm0);
		mask = _mm256_movemask_epi8(ymm1);
		if (mask) {
			__asm__("bsfl %0, %0\n\t"
			        :"=r"(mask)
			        :"0"(mask)
			       );
			return (void*)((unsigned long)((const __m256i*)src + i) + mask);
		}
	}

	return xmemchr_tiny((const void*)((unsigned long)src + n), c, rem);
}