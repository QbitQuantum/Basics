U_CAPI void U_EXPORT2
uiter_setUTF16BE(UCharIterator * iter, const char * s, int32_t length)
{
	if (iter != NULL)
	{
		/* allow only even-length strings (the input length counts bytes) */
		if (s != NULL && (length == -1 || (length >= 0 && IS_EVEN(length))))
		{
			/* length/=2, except that >>=1 also works for -1 (-1/2==0, -1>>1==-1) */
			length >>= 1;

			if (U_IS_BIG_ENDIAN && IS_POINTER_EVEN(s))
			{
				/* big-endian machine and 2-aligned UTF-16BE string: use normal UChar iterator */
				uiter_setString(iter, (const UChar *)s, length);
				return;
			}

			*iter = utf16BEIterator;
			iter->context = s;
			if (length >= 0)
			{
				iter->length = length;
			}
			else
			{
				iter->length = utf16BE_strlen(s);
			}
			iter->limit = iter->length;
		}
		else
		{