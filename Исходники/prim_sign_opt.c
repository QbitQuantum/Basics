/* ------------------------------------------------------------------------- */
pstatus_t ssse3_sign_16s(
	const INT16 *pSrc,
	INT16 *pDst,
	INT32 len)
{
	const INT16 *sptr = (const INT16 *) pSrc;
	INT16 *dptr = (INT16 *) pDst;
	size_t count;

	if (len < 16)
	{
		return general_sign_16s(pSrc, pDst, len);
	}

	/* Check for 16-byte alignment (eventually). */
	if ((ULONG_PTR) pDst & 0x01)
	{
		return general_sign_16s(pSrc, pDst, len);
	}

	/* Seek 16-byte alignment. */
	while ((ULONG_PTR) dptr & 0x0f)
	{
		INT16 src = *sptr++;
		*dptr++ = (src < 0) ? (-1) : ((src > 0) ? 1 : 0);
		if (--len == 0) return PRIMITIVES_SUCCESS;
	}

	/* Do 32-short chunks using 8 XMM registers. */
	count = len >> 5;	/* / 32  */
	len -= count << 5;	/* * 32 */
	if ((ULONG_PTR) sptr & 0x0f)
	{
		/* Unaligned */
		while (count--)
		{
			__m128i xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
			xmm0 = _mm_set1_epi16(0x0001U);
			xmm1 = _mm_set1_epi16(0x0001U);
			xmm2 = _mm_set1_epi16(0x0001U);
			xmm3 = _mm_set1_epi16(0x0001U);
			xmm4 = _mm_lddqu_si128((__m128i *) sptr); sptr += 8;
			xmm5 = _mm_lddqu_si128((__m128i *) sptr); sptr += 8;
			xmm6 = _mm_lddqu_si128((__m128i *) sptr); sptr += 8;
			xmm7 = _mm_lddqu_si128((__m128i *) sptr); sptr += 8;
			xmm0 = _mm_sign_epi16(xmm0, xmm4);
			xmm1 = _mm_sign_epi16(xmm1, xmm5);
			xmm2 = _mm_sign_epi16(xmm2, xmm6);
			xmm3 = _mm_sign_epi16(xmm3, xmm7);
			_mm_store_si128((__m128i *) dptr, xmm0);         dptr += 8;
			_mm_store_si128((__m128i *) dptr, xmm1);         dptr += 8;
			_mm_store_si128((__m128i *) dptr, xmm2);         dptr += 8;
			_mm_store_si128((__m128i *) dptr, xmm3);         dptr += 8;
		}
	}
	else
	{
		/* Aligned */
		while (count--)
		{
			__m128i xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
			xmm0 = _mm_set1_epi16(0x0001U);
			xmm1 = _mm_set1_epi16(0x0001U);
			xmm2 = _mm_set1_epi16(0x0001U);
			xmm3 = _mm_set1_epi16(0x0001U);
			xmm4 = _mm_load_si128((__m128i *) sptr); sptr += 8;
			xmm5 = _mm_load_si128((__m128i *) sptr); sptr += 8;
			xmm6 = _mm_load_si128((__m128i *) sptr); sptr += 8;
			xmm7 = _mm_load_si128((__m128i *) sptr); sptr += 8;
			xmm0 = _mm_sign_epi16(xmm0, xmm4);
			xmm1 = _mm_sign_epi16(xmm1, xmm5);
			xmm2 = _mm_sign_epi16(xmm2, xmm6);
			xmm3 = _mm_sign_epi16(xmm3, xmm7);
			_mm_store_si128((__m128i *) dptr, xmm0);         dptr += 8;
			_mm_store_si128((__m128i *) dptr, xmm1);         dptr += 8;
			_mm_store_si128((__m128i *) dptr, xmm2);         dptr += 8;
			_mm_store_si128((__m128i *) dptr, xmm3);         dptr += 8;
		}
	}

	/* Do 8-short chunks using two XMM registers. */
	count = len >> 3;
	len -= count << 3;
	while (count--)
	{
		__m128i xmm0 = _mm_set1_epi16(0x0001U);
		__m128i xmm1 = LOAD_SI128(sptr);					sptr += 8;
		xmm0 = _mm_sign_epi16(xmm0, xmm1);
		_mm_store_si128((__m128i *) dptr, xmm0);			dptr += 8;
	}

	/* Do leftovers. */
	while (len--)
	{
		INT16 src = *sptr++;
		*dptr++ = (src < 0) ? -1 : ((src > 0) ? 1 : 0);
	}

	return PRIMITIVES_SUCCESS;
}