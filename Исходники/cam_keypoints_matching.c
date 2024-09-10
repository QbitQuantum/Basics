int camCompareDescriptors(const int *desc1, const int *desc2, const int s)
{
    int i, j, distance = 0;
    __m128i sum, d1, d2, md, d, cmp;
    __m128i *p1 = (__m128i*)desc1, *p2 = (__m128i*)desc2;
    ALIGN(int out_sse[4], 16);

    /* Looks like a good idea... But this deteriorates performance...
    // Software prefetch
    d1 = _mm_load_si128(p1);
    d2 = _mm_load_si128(p2);
    for (i = 0; i != s; i += 32) {
	_mm_prefetch(&desc1[i], _MM_HINT_NTA);
	_mm_prefetch(&desc2[i], _MM_HINT_NTA);
    }
    */

    sum = _mm_setzero_si128();
    for (i = 0; i != s >> 4; i++) {
	// 32-bits SAD for 4 integers in parallel
	d1 = _mm_loadu_si128(p1++);
	d2 = _mm_loadu_si128(p2++);
	d = _mm_sub_epi32(d1, d2);
	md = _mm_sub_epi32(d2, d1);
	cmp = _mm_cmplt_epi32(d, _mm_setzero_si128());
	md = _mm_and_si128(cmp, md);
	d = _mm_andnot_si128(cmp, d);
	sum = _mm_add_epi32(sum, md);
	sum = _mm_add_epi32(sum, d);

	// 32-bits SAD for 4 integers in parallel
	d1 = _mm_loadu_si128(p1++);
	d2 = _mm_loadu_si128(p2++);
	d = _mm_sub_epi32(d1, d2);
	md = _mm_sub_epi32(d2, d1);
	cmp = _mm_cmplt_epi32(d, _mm_setzero_si128());
	md = _mm_and_si128(cmp, md);
	d = _mm_andnot_si128(cmp, d);
	sum = _mm_add_epi32(sum, md);
	sum = _mm_add_epi32(sum, d);

	// 32-bits SAD for 4 integers in parallel
	d1 = _mm_loadu_si128(p1++);
	d2 = _mm_loadu_si128(p2++);
	d = _mm_sub_epi32(d1, d2);
	md = _mm_sub_epi32(d2, d1);
	cmp = _mm_cmplt_epi32(d, _mm_setzero_si128());
	md = _mm_and_si128(cmp, md);
	d = _mm_andnot_si128(cmp, d);
	sum = _mm_add_epi32(sum, md);
	sum = _mm_add_epi32(sum, d);

	// 32-bits SAD for 4 integers in parallel
	d1 = _mm_loadu_si128(p1++);
	d2 = _mm_loadu_si128(p2++);
	d = _mm_sub_epi32(d1, d2);
	md = _mm_sub_epi32(d2, d1);
	cmp = _mm_cmplt_epi32(d, _mm_setzero_si128());
	md = _mm_and_si128(cmp, md);
	d = _mm_andnot_si128(cmp, d);
	sum = _mm_add_epi32(sum, md);
	sum = _mm_add_epi32(sum, d);
    }
    _mm_store_si128((__m128i*)out_sse, sum);
    return out_sse[0] + out_sse[1] + out_sse[2] + out_sse[3];
}