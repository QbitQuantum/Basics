/* The encodec YCbCr coeffectients are represented as 11.5 fixed-point
 * numbers. See the general code above.
 */
PRIM_STATIC pstatus_t sse2_RGBToYCbCr_16s16s_P3P3(
	const INT16 *pSrc[3],
	int srcStep,
	INT16 *pDst[3],
	int dstStep,
	const prim_size_t *roi)	/* region of interest */
{
	__m128i min, max, y_r, y_g, y_b, cb_r, cb_g, cb_b, cr_r, cr_g, cr_b;
	__m128i *r_buf, *g_buf, *b_buf, *y_buf, *cb_buf, *cr_buf;
	int srcbump, dstbump, yp, imax;

	if (((ULONG_PTR) (pSrc[0]) & 0x0f)
			|| ((ULONG_PTR) (pSrc[1]) & 0x0f)
			|| ((ULONG_PTR) (pSrc[2]) & 0x0f)
			|| ((ULONG_PTR) (pDst[0]) & 0x0f)
			|| ((ULONG_PTR) (pDst[1]) & 0x0f)
			|| ((ULONG_PTR) (pDst[2]) & 0x0f)
			|| (roi->width & 0x07)
			|| (srcStep & 127)
			|| (dstStep & 127))
	{
		/* We can't maintain 16-byte alignment. */
		return general_RGBToYCbCr_16s16s_P3P3(pSrc, srcStep,
			pDst, dstStep, roi);
	}

	min = _mm_set1_epi16(-128 << 5);
	max = _mm_set1_epi16(127 << 5);

	r_buf  = (__m128i*) (pSrc[0]);
	g_buf  = (__m128i*) (pSrc[1]);
	b_buf  = (__m128i*) (pSrc[2]);
	y_buf  = (__m128i*) (pDst[0]);
	cb_buf = (__m128i*) (pDst[1]);
	cr_buf = (__m128i*) (pDst[2]);

	y_r  = _mm_set1_epi16(9798);   /*  0.299000 << 15 */
	y_g  = _mm_set1_epi16(19235);  /*  0.587000 << 15 */
	y_b  = _mm_set1_epi16(3735);   /*  0.114000 << 15 */
	cb_r = _mm_set1_epi16(-5535);  /* -0.168935 << 15 */
	cb_g = _mm_set1_epi16(-10868); /* -0.331665 << 15 */
	cb_b = _mm_set1_epi16(16403);  /*  0.500590 << 15 */
	cr_r = _mm_set1_epi16(16377);  /*  0.499813 << 15 */
	cr_g = _mm_set1_epi16(-13714); /* -0.418531 << 15 */
	cr_b = _mm_set1_epi16(-2663);  /* -0.081282 << 15 */

	srcbump = srcStep / sizeof(__m128i);
	dstbump = dstStep / sizeof(__m128i);

#ifdef DO_PREFETCH
	/* Prefetch RGB's. */
	for (yp=0; yp<roi->height; yp++)
	{
		int i;
		for (i=0; i<roi->width * sizeof(INT16) / sizeof(__m128i);
			i += (CACHE_LINE_BYTES / sizeof(__m128i)))
		{
			_mm_prefetch((char*)(&r_buf[i]), _MM_HINT_NTA);
			_mm_prefetch((char*)(&g_buf[i]), _MM_HINT_NTA);
			_mm_prefetch((char*)(&b_buf[i]), _MM_HINT_NTA);
		}
		r_buf += srcbump;
		g_buf += srcbump;
		b_buf += srcbump;
	}
	r_buf = (__m128i*) (pSrc[0]);
	g_buf = (__m128i*) (pSrc[1]);
	b_buf = (__m128i*) (pSrc[2]);
#endif /* DO_PREFETCH */

	imax = roi->width * sizeof(INT16) / sizeof(__m128i);
	for (yp=0; yp<roi->height; ++yp)
	{
		int i;
		for (i=0; i<imax; i++)
		{
			/* In order to use SSE2 signed 16-bit integer multiplication we
			 * need to convert the floating point factors to signed int
			 * without loosing information.  The result of this multiplication
			 * is 32 bit and using SSE2 we get either the product's hi or lo
			 * word.  Thus we will multiply the factors by the highest
			 * possible 2^n and take the upper 16 bits of the signed 32-bit
			 * result (_mm_mulhi_epi16).  Since the final result needs to
			 * be scaled by << 5 and also in in order to keep the precision
			 * within the upper 16 bits we will also have to scale the RGB
			 * values used in the multiplication by << 5+(16-n).
			 */
			__m128i r, g, b, y, cb, cr;
			r = _mm_load_si128(y_buf+i);
			g = _mm_load_si128(g_buf+i);
			b = _mm_load_si128(b_buf+i);

			/* r<<6; g<<6; b<<6 */
			r = _mm_slli_epi16(r, 6);
			g = _mm_slli_epi16(g, 6);
			b = _mm_slli_epi16(b, 6);

			/* y = HIWORD(r*y_r) + HIWORD(g*y_g) + HIWORD(b*y_b) + min */
			y = _mm_mulhi_epi16(r, y_r);
			y = _mm_add_epi16(y, _mm_mulhi_epi16(g, y_g));
			y = _mm_add_epi16(y, _mm_mulhi_epi16(b, y_b));
			y = _mm_add_epi16(y, min);
			/* y_r_buf[i] = MINMAX(y, 0, (255 << 5)) - (128 << 5); */
			_mm_between_epi16(y, min, max);
			_mm_store_si128(y_buf+i, y);

			/* cb = HIWORD(r*cb_r) + HIWORD(g*cb_g) + HIWORD(b*cb_b) */
			cb = _mm_mulhi_epi16(r, cb_r);
			cb = _mm_add_epi16(cb, _mm_mulhi_epi16(g, cb_g));
			cb = _mm_add_epi16(cb, _mm_mulhi_epi16(b, cb_b));
			/* cb_g_buf[i] = MINMAX(cb, (-128 << 5), (127 << 5)); */
			_mm_between_epi16(cb, min, max);
			_mm_store_si128(cb_buf+i, cb);

			/* cr = HIWORD(r*cr_r) + HIWORD(g*cr_g) + HIWORD(b*cr_b) */
			cr = _mm_mulhi_epi16(r, cr_r);
			cr = _mm_add_epi16(cr, _mm_mulhi_epi16(g, cr_g));
			cr = _mm_add_epi16(cr, _mm_mulhi_epi16(b, cr_b));
			/* cr_b_buf[i] = MINMAX(cr, (-128 << 5), (127 << 5)); */
			_mm_between_epi16(cr, min, max);
			_mm_store_si128(cr_buf+i, cr);
		}
		y_buf  += srcbump;
		cb_buf += srcbump;
		cr_buf += srcbump;
		r_buf += dstbump;
		g_buf += dstbump;
		b_buf += dstbump;
	}

	return PRIMITIVES_SUCCESS;
}