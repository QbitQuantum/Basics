mlib_status
__mlib_VideoP64Loop_S16_U8(
	mlib_s16 mc_block[64],
	const mlib_u8 *ref_block,
	mlib_s32 stride)
{
	const mlib_u8 *sl;
	mlib_s16 *sd;

	__m128i txmm0, txmm1, txmm2, txmm3, txmm4, txmm5, txmm6, txmm7;
	__m128i t0, t1, t2, t3, t4, t5, t6, t7;
	__m128i Czero, CF, C2, C4, C8;

	Czero = _mm_setzero_si128();
	C2 = _mm_set1_epi16(2);
	C4 = _mm_set1_epi16(4);
	C8 = _mm_set1_epi16(8);
	CF = _mm_set_epi32(0xff0000, 0, 0, 0xff);

	sd = mc_block;
	sl = ref_block;

	LOADL(0);
	sl += stride;
	FILTERX(0);

	LOADL(1);
	sl += stride;
	FILTERX(1);

	STORB(0);
	sd += 8;
	ADDL(0, 1);

	LOADL(2);
	sl += stride;
	FILTERX(2);

	ADDLRND(1, 2);
	STORSUM(0, 1);
	sd += 8;

	LOADL(3);
	sl += stride;
	FILTERX(3);

	ADDL(2, 3);
	STORSUM(1, 2);
	sd += 8;

	LOADL(4);
	sl += stride;
	FILTERX(4);

	ADDLRND(3, 4);
	STORSUM(2, 3);
	sd += 8;

	LOADL(5);
	sl += stride;
	FILTERX(5);

	ADDL(4, 5);
	STORSUM(3, 4);
	sd += 8;

	LOADL(6);
	sl += stride;
	FILTERX(6);

	ADDLRND(5, 6);
	STORSUM(4, 5);
	sd += 8;

	LOADL(7);
	FILTERX(7);

	ADDL(6, 7);
	STORSUM(5, 6);
	sd += 8;

	STORB(7);

	return (MLIB_SUCCESS);
}