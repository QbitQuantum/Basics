void t_print__m128i (__m128i a) 
{
	printf("%d = %d\n", 0, _mm_extract_epi32(a, 0));
	printf("%d = %d\n", 1, _mm_extract_epi32(a, 1));
	printf("%d = %d\n", 2, _mm_extract_epi32(a, 2));
	printf("%d = %d\n", 3, _mm_extract_epi32(a, 3));
	printf("\n");
}