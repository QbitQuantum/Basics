void mpeg2_idct_add_sse2(const int last, int16_t* block, uint8_t* dest, const int stride)
{
	idct_M128ASM(block);

	/*
	for(int i = 0; i < 8; i++)
	{
		dest[0] = CLIP(block[0] + dest[0]);
		dest[1] = CLIP(block[1] + dest[1]);
		dest[2] = CLIP(block[2] + dest[2]);
		dest[3] = CLIP(block[3] + dest[3]);
		dest[4] = CLIP(block[4] + dest[4]);
		dest[5] = CLIP(block[5] + dest[5]);
		dest[6] = CLIP(block[6] + dest[6]);
		dest[7] = CLIP(block[7] + dest[7]);

		memset(block, 0, sizeof(short)*8);

		dest += stride;
		block += 8;
	}
	*/

	__m128i* src = (__m128i*)block;
	__m128i zero = _mm_setzero_si128();

	__m128i r0 = _mm_load_si128(&src[0]);
	__m128i r1 = _mm_load_si128(&src[1]);
	__m128i r2 = _mm_load_si128(&src[2]);
	__m128i r3 = _mm_load_si128(&src[3]);
	__m128i r4 = _mm_load_si128(&src[4]);
	__m128i r5 = _mm_load_si128(&src[5]);
	__m128i r6 = _mm_load_si128(&src[6]);
	__m128i r7 = _mm_load_si128(&src[7]);

	__m128 q0 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[0*stride]);
	__m128 q1 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[1*stride]);
	__m128 q2 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[2*stride]);
	__m128 q3 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[3*stride]);
	__m128 q4 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[4*stride]);
	__m128 q5 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[5*stride]);
	__m128 q6 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[6*stride]);
	__m128 q7 = _mm_loadl_pi(*(__m128*)&zero, (__m64*)&dest[7*stride]);

	r0 = _mm_adds_epi16(r0, _mm_unpacklo_epi8(*(__m128i*)&q0, zero));
	r1 = _mm_adds_epi16(r1, _mm_unpacklo_epi8(*(__m128i*)&q1, zero));
	r2 = _mm_adds_epi16(r2, _mm_unpacklo_epi8(*(__m128i*)&q2, zero));
	r3 = _mm_adds_epi16(r3, _mm_unpacklo_epi8(*(__m128i*)&q3, zero));
	r4 = _mm_adds_epi16(r4, _mm_unpacklo_epi8(*(__m128i*)&q4, zero));
	r5 = _mm_adds_epi16(r5, _mm_unpacklo_epi8(*(__m128i*)&q5, zero));
	r6 = _mm_adds_epi16(r6, _mm_unpacklo_epi8(*(__m128i*)&q6, zero));
	r7 = _mm_adds_epi16(r7, _mm_unpacklo_epi8(*(__m128i*)&q7, zero));

	r0 = _mm_packus_epi16(r0, r1);
	r1 = _mm_packus_epi16(r2, r3);
	r2 = _mm_packus_epi16(r4, r5);
	r3 = _mm_packus_epi16(r6, r7);

	_mm_storel_pi((__m64*)&dest[0*stride], *(__m128*)&r0);
	_mm_storeh_pi((__m64*)&dest[1*stride], *(__m128*)&r0);
	_mm_storel_pi((__m64*)&dest[2*stride], *(__m128*)&r1);
	_mm_storeh_pi((__m64*)&dest[3*stride], *(__m128*)&r1);
	_mm_storel_pi((__m64*)&dest[4*stride], *(__m128*)&r2);
	_mm_storeh_pi((__m64*)&dest[5*stride], *(__m128*)&r2);
	_mm_storel_pi((__m64*)&dest[6*stride], *(__m128*)&r3);
	_mm_storeh_pi((__m64*)&dest[7*stride], *(__m128*)&r3);

	_mm_store_si128(&src[0], zero);
	_mm_store_si128(&src[1], zero);
	_mm_store_si128(&src[2], zero);
	_mm_store_si128(&src[3], zero);
	_mm_store_si128(&src[4], zero);
	_mm_store_si128(&src[5], zero);
	_mm_store_si128(&src[6], zero);
	_mm_store_si128(&src[7], zero);
}