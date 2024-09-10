static pstatus_t sse2_set_8u(
    BYTE val,
    BYTE* pDst,
    UINT32 len)
{
	BYTE byte, *dptr;
	__m128i xmm0;
	size_t count;

	if (len < 16) return generic->set_8u(val, pDst, len);

	byte  = val;
	dptr = (BYTE*) pDst;

	/* Seek 16-byte alignment. */
	while ((ULONG_PTR) dptr & 0x0f)
	{
		*dptr++ = byte;

		if (--len == 0) return PRIMITIVES_SUCCESS;
	}

	xmm0 = _mm_set1_epi8(byte);
	/* Cover 256-byte chunks via SSE register stores. */
	count = len >> 8;
	len -= count << 8;

	/* Do 256-byte chunks using one XMM register. */
	while (count--)
	{
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
	}

	/* Cover 16-byte chunks via SSE register stores. */
	count = len >> 4;
	len -= count << 4;

	/* Do 16-byte chunks using one XMM register. */
	while (count--)
	{
		_mm_store_si128((__m128i*) dptr, xmm0);
		dptr += 16;
	}

	/* Do leftover bytes. */
	while (len--) *dptr++ = byte;

	return PRIMITIVES_SUCCESS;
}