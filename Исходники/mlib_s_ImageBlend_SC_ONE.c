mlib_status
__mlib_ImageBlend_SC_ONE(
    mlib_image *dst,
    const mlib_image *src1,
    const mlib_image *src2,
    mlib_s32 cmask)
{
	BLEND_VALIDATE;

	dst_width *= channels;


	int k;
	__m128i *px, *py, *pz;
	__m128i dx, dy;
/* upper - 1 lower - 0 */
	__m128i dx_1, dx_0, dy_1, dy_0, dz_1, dz_0;
	__m128i dall_zero;

	dall_zero = _mm_setzero_si128();

	if (0 == (((((mlib_addr) psrc1 | (mlib_addr)psrc2 |
				(mlib_addr)pdst)) & 0xf)) &&
				(0 == (((src1_stride | src2_stride |
				dst_stride) & 0xf) || (1 == dst_height)))) {
		for (j = 0; j < dst_height; j++) {
			px = (__m128i *)psrc1;
			py = (__m128i *)psrc2;
			pz = (__m128i *)pdst;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
			for (i = 0; i <= dst_width - 16; i += 16) {
				dx = _mm_load_si128(px);
				dy = _mm_load_si128(py);

				UNPACK_UNSIGN_BYTE;

				PROCESS_DATA(dx_1, dy_1, dz_1);
				PROCESS_DATA(dx_0, dy_0, dz_0);
				dz_0 = _mm_packus_epi16(dz_0, dz_1);
				_mm_store_si128(pz, dz_0);
				px++;
				py++;
				pz++;
			}

#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
			DO_REST;
			psrc1 += src1_stride;
			psrc2 += src2_stride;
			pdst += dst_stride;
		}
	} else {
		for (j = 0; j < dst_height; j++) {
			px = (__m128i *)psrc1;
			py = (__m128i *)psrc2;
			pz = (__m128i *)pdst;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
			for (i = 0; i <= dst_width - 16; i += 16) {
				dx = _mm_loadu_si128(px);
				dy = _mm_loadu_si128(py);

				UNPACK_UNSIGN_BYTE;

				PROCESS_DATA(dx_1, dy_1, dz_1);
				PROCESS_DATA(dx_0, dy_0, dz_0);
				dz_0 = _mm_packus_epi16(dz_0, dz_1);
				_mm_storeu_si128(pz, dz_0);
				px++;
				py++;
				pz++;
			}
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
			DO_REST;
			psrc1 += src1_stride;
			psrc2 += src2_stride;
			pdst += dst_stride;
		}
	}

	return (MLIB_SUCCESS);
}