int main()
{
	double (*f)(double) = sin;
	printf("f=%p\n", f);
	double x = 1.0;
	CYBOZU_BENCH("before vinsertf128", x = f, x);
	printf("x=%f\n", x);

#if 1
	call_vinsertf128();
#else
	{
		puts("a");
		__m128d x;// = _mm_setzero_si128();
		__m256d y;// = _mm256_setzero_si256();
		y = _mm256_insertf128_pd(y, x, 1);
		printf("%d\n", *(int*)&y);
	}
#endif
	CYBOZU_BENCH("after vinsertf128", x = f, x);
	printf("x=%f\n", x);
}