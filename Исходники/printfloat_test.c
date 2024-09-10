static void
_testfmt(const char *result, const char *argstr, const char *fmt,...)
{
#define	BUF	100
	wchar_t ws[BUF], wfmt[BUF], wresult[BUF];
	char s[BUF];
	va_list ap, ap2;

	va_start(ap, fmt);
	va_copy(ap2, ap);
	smash_stack();
	vsnprintf(s, sizeof(s), fmt, ap);
	ATF_CHECK_MSG(strcmp(result, s) == 0,
	    "printf(\"%s\", %s) ==> [%s], expected [%s]",
	    fmt, argstr, s, result);

	smash_stack();
	mbstowcs(ws, s, BUF - 1);
	mbstowcs(wfmt, fmt, BUF - 1);
	mbstowcs(wresult, result, BUF - 1);
	vswprintf(ws, sizeof(ws) / sizeof(ws[0]), wfmt, ap2);
	ATF_CHECK_MSG(wcscmp(wresult, ws) == 0,
	    "wprintf(\"%ls\", %s) ==> [%ls], expected [%ls]",
	    wfmt, argstr, ws, wresult);

	va_end(ap);
	va_end(ap2);
}