/* *********************************************************** */

mlib_status FUN_NAME(
	1ch) (
	mlib_affine_param *param)
{
	DECLAREVAR_BL();
	DTYPE *dstLineEnd;
	DTYPE *srcPixelPtr2;

#if MLIB_SHIFT == 15
	dX = (dX + 1) >> 1;
	dY = (dY + 1) >> 1;
#endif /* MLIB_SHIFT == 15 */

	__m128i zeros = _mm_setzero_si128();
	__m128i const_ffff = _mm_set1_epi16(0xffff);
	__m128i rounds = _mm_set1_epi16(MLIB_ROUND_SSE2);

	for (j = yStart; j <= yFinish; j++) {
		__m128i fdxs, fdys, deltax, deltay;
		__m128i fdx2s, fdy2s;
		__m128i a00_0s, a01_0s, a10_0s, a11_0s;
		__m128i pix0_0s, pix0_1s, pix1_0s, pix1_1s, res0s;

		mlib_s32 fdx, fdy;
		mlib_s32 a00_0, a01_0, a10_0, a11_0;
		mlib_s32 pix0_0, pix1_0, res0;

		mlib_u8 *srcPtr_0, *srcPtr_1, *srcPtr_2, *srcPtr_3;
		mlib_u8 *srcPtr_4, *srcPtr_5, *srcPtr_6, *srcPtr_7;