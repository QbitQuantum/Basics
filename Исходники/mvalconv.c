/* This function does the bulk of the conversion for i82mval and ui82mval. The primary routines set the sgn flag and pass the
 * absolute value to xi82mval(). In the case of a >18 digit number, xi82mval() examines the sgn flag to determine whether to
 * switch back to a signed value before string conversion.
 */
void xi82mval(mval *v, gtm_uint64_t i)
{
	int	exp;
	uint4	low;
	uint4	high;
	char    buf[21];	/* [possible] sign, [up to] 19L/20UL digits, and terminator. */
	int	len;

	if (i < INT_HI)
	{
		v->mvtype |= MV_INT;
		v->m[1] = MV_BIAS * (v->sgn ? -(int4)i : (uint4)i);
	} else
	{
		if (i < MANT_HI)
		{
			low = 0;
			high = i;
			exp = EXP_IDX_BIAL;
			while (high < MANT_LO)
			{
				high *= 10;
				exp--;
			}
			v->e = exp;
			v->m[0] = low;
			v->m[1] = high;
		} else if (i < (gtm_uint64_t)MANT_HI * MANT_HI)
		{
			low = i % MANT_HI;
			high = i / MANT_HI;
			exp = EXP_IDX_BIAL + 9;
			while (high < MANT_LO)
			{
				high = (high * 10) + (low / MANT_LO);
				low = (low % MANT_LO) * 10;
				exp--;
			}
			v->e = exp;
			v->m[0] = low;
			v->m[1] = high;
		} else
		{	/* The value won't fit in 18 digits, so return a string. */
			if (v->sgn)
				len = SPRINTF(buf, "%lld", -(gtm_int64_t)i);
			else
				len = SPRINTF(buf, "%llu", i);
			assert(18 < len);
			ENSURE_STP_FREE_SPACE(len);
			memcpy(stringpool.free, buf, len);
			v->mvtype = MV_STR;
			v->str.len = len;
			v->str.addr = (char *)stringpool.free;
			stringpool.free += len;
		}
		assert((v->mvtype != MV_NM) || (v->m[1] < MANT_HI));
		assert((v->mvtype != MV_NM) || (v->m[1] >= MANT_LO));
	}
}