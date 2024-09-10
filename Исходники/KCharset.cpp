int KCharset::to_uchar(const char* src, int len, unsigned int* uchar) const
{
	*uchar = 0;
#if defined(WIN32)
	int bytes = IsDBCSLeadByteEx(m_codepage,src[0]) ? 2:1;
	if(len < bytes) return -1;
	int n = MultiByteToWideChar(m_codepage, 0, src, bytes, (wchar_16*)uchar, 1);
	if(!n) return -1;
	return bytes;
#else
	char* src2 = (char*)src; size_t srclen = len;
	char* dst2 = (char*)uchar; size_t dstlen = sizeof(int);
	size_t n = iconv(m_iconv_utf32, &src2, &srclen, &dst2, &dstlen);
	if(n == -1 && errno != E2BIG) return -1;
	return (int)(src2 - src);
#endif
}