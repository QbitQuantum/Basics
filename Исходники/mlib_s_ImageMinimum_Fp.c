void
mlib_ImageMinimum_D64_124(
    const mlib_image *img,
    mlib_d64 *min)
{
/* src address */
	mlib_d64 *sp, *sl;
/* src data */
	__m128d sd0, sd1;
/* min values */
	__m128d min0, min1;

/* loop variables */
	mlib_s32 n1, i;

/* height of image */
	mlib_s32 height = mlib_ImageGetHeight(img);

/* elements to next row */
	mlib_s32 src_stride = mlib_ImageGetStride(img);

/* number of image channels */
	mlib_s32 channels = mlib_ImageGetChannels(img);
	mlib_s32 size_row = mlib_ImageGetWidth(img) * channels;

	sp = sl = mlib_ImageGetData(img);

	if (src_stride == size_row) {
		size_row *= height;
		height = 1;
	}

/* min values */
	min0 = _mm_set1_pd(MLIB_D64_MAX);
	min1 = _mm_set1_pd(MLIB_D64_MAX);

	mlib_d64 rez[4] = {
		MLIB_D64_MAX, MLIB_D64_MAX,
		MLIB_D64_MAX, MLIB_D64_MAX};

	for (; height > 0; height--) {
		n1 = size_row;
		for (; n1 > 3; n1 -= 4) {
		    sd0 = _mm_loadu_pd(sp);
		    sp += 2;
		    sd1 = _mm_loadu_pd(sp);
		    sp += 2;
		    MLIB_S_IMAGE_MINIMUM_D64(min0, min0, sd0);
		    MLIB_S_IMAGE_MINIMUM_D64(min1, min1, sd1);
		}

		if (n1 > 0) {
		    mlib_d64 sd2[4] = {
			MLIB_D64_MAX, MLIB_D64_MAX,
			MLIB_D64_MAX, MLIB_D64_MAX};
		    for (int i = 0; i < n1; i++) {
				sd2[i] = *sp++;
		    }
		    sd0 = _mm_set_pd(sd2[3], sd2[2]);
		    sd1 = _mm_set_pd(sd2[1], sd2[0]);

		    MLIB_S_IMAGE_MINIMUM_D64(min0, min0, sd0);
		    MLIB_S_IMAGE_MINIMUM_D64(min1, min1, sd1);
		}
		sp = sl = (mlib_d64 *) ((mlib_u8 *)sl + src_stride);
	}

	switch (channels) {
	case 1: {
		mlib_d64 tmpRes0[2];
		mlib_d64 tmpRes1[2];
		_mm_storeu_pd(tmpRes0, min0);
		_mm_storeu_pd(tmpRes1, min1);
		tmpRes0[0] =
		    (tmpRes0[0] < tmpRes0[1]) ? tmpRes0[0] : tmpRes0[1];
		tmpRes1[0] =
		    (tmpRes1[0] < tmpRes1[1]) ? tmpRes1[0] : tmpRes1[1];
		min[0] = (tmpRes0[0] < tmpRes1[0]) ? tmpRes0[0] : tmpRes1[0];
		break;
	}
	case 2: {
		mlib_d64 tmpRes0[2];
		mlib_d64 tmpRes1[2];
		_mm_storeu_pd(tmpRes0, min0);
		_mm_storeu_pd(tmpRes1, min1);
		min[0] = (tmpRes0[0] < tmpRes1[0]) ? tmpRes0[0] : tmpRes1[0];
		min[1] = (tmpRes0[1] < tmpRes1[1]) ? tmpRes0[1] : tmpRes1[1];
		break;
	}
	case 4: {
		_mm_storeu_pd(min, min0);
		_mm_storeu_pd((min + 2), min1);
		break;
	}
	}
}