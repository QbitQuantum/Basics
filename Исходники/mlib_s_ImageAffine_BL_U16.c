	a01_##ind = srcPixelPtr[ind2];                          \
	a10_##ind = srcPixelPtr2[ind1];                         \
	a11_##ind = srcPixelPtr2[ind2]

/* *********************************************************** */

mlib_status FUN_NAME(
	1ch) (
	mlib_affine_param *param)
{
	DECLAREVAR_BL();
	DTYPE *dstLineEnd;
	DTYPE *srcPixelPtr2;
	__m128i deltax, deltay;

	__m128i const_7fff = _mm_set1_epi16(0x7fff);
	__m128i const_7ffe = _mm_set1_epi16(0x7ffe);
	__m128i mask_8000 = _mm_set1_epi16(0x8000);

	for (j = yStart; j <= yFinish; j++) {
		__m128i a00_0s, a01_0s, a10_0s, a11_0s;
		__m128i pix0_0s, pix0_1s, pix1_0s, pix1_1s, res0s;
		__m128i pix0s, pix1s;
		__m128i fdxs, fdys;
		__m128i fdx2s, fdy2s;

		mlib_s32 fdx, fdy;
		mlib_s32 a00_0, a01_0, a10_0, a11_0;
		mlib_s32 a00_1, a01_1, a10_1, a11_1;
		mlib_s32 pix0_0, pix1_0, res0;
		mlib_s32 pix0_1, pix1_1, res1;