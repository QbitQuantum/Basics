void
mlib_v_ImageSqrShift_S32(
    mlib_s32 *src,
    mlib_s32 slb,
    mlib_s32 *dst,
    mlib_s32 dlb,
    mlib_s32 xsize,
    mlib_s32 ysize,
    mlib_s32 shift)
{
	mlib_d64 dscale;
	mlib_s32 i, j;

/* dscale = 2 ** (-shift) */
	SCALBN(dscale, -shift);

/* if src and dst - 1-D vector */
	if (xsize == slb && slb == dlb) {
		xsize *= ysize;
		ysize = 1;
	}

	for (j = 0; j < ysize; j++) {
#pragma pipeloop(0)
		for (i = 0; i < xsize - 3; i += 4) {
			FLOAT2INT_CLAMP(dst[i + 0],
			    src[i + 0] * (mlib_d64)src[i + 0] * dscale);
			FLOAT2INT_CLAMP(dst[i + 1],
			    src[i + 1] * (mlib_d64)src[i + 1] * dscale);
			FLOAT2INT_CLAMP(dst[i + 2],
			    src[i + 2] * (mlib_d64)src[i + 2] * dscale);
			FLOAT2INT_CLAMP(dst[i + 3],
			    src[i + 3] * (mlib_d64)src[i + 3] * dscale);
		}

#pragma pipeloop(0)
		for (; i < xsize; i++) {
			FLOAT2INT_CLAMP(dst[i],
			    src[i] * (mlib_d64)src[i] * dscale);
		}

		src += slb;
		dst += dlb;
	}
}