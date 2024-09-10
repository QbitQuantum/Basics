int32_t gtm_strToTitle(UChar *dst, int32_t dstlen, const UChar *src, int32_t srclen,
		const char *locale, UErrorCode *status)
{
	return u_strToTitle(dst, dstlen, src, srclen, NULL, locale, status);
}