void
multiply(int *a, int *b, int *c, int n)
{
	int i;
	__m128i *pa, *pb, pc;
	for(i = 0; i < n; i += 4) {
		pa = (__m128i *)&a[i];
		pb = (__m128i *)&b[i];
		pc = _mm_mullo_epi32(*pa, *pb);
		memcpy(&c[i], &pc, 4*sizeof(int));
	}
}