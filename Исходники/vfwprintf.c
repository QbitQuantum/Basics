/*
 * Like __fputwc_unlock, but handles fake string (__SSTR) files properly.
 * File must already be locked.
 */
static wint_t
__xfputwc(wchar_t wc, FILE *fp, locale_t locale)
{
	mbstate_t mbs;
	char buf[MB_LEN_MAX];
	struct __suio uio;
	struct __siov iov;
	size_t len;

	if ((fp->_flags & __SSTR) == 0)
		return (__fputwc_unlock(wc, fp, locale));

	memset(&mbs, 0, sizeof(mbs));
	len = wcrtomb(buf, wc, &mbs);
	if (len == (size_t)-1) {
		fp->_flags |= __SERR;
		errno = EILSEQ;
		return (WEOF);
	}
	uio.uio_iov = &iov;
	uio.uio_resid = len;
	uio.uio_iovcnt = 1;
	iov.iov_base = buf;
	iov.iov_len = len;
	return (__sfvwrite(fp, &uio) != EOF ? (wint_t)wc : WEOF);
}