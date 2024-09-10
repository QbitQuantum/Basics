void
_testfmt(const char *result, int line, const char *argstr, const char *fmt,...)
{
#define	BUF	100
	wchar_t ws[BUF], wfmt[BUF], wresult[BUF];
	char s[BUF];
	va_list ap, ap2;

	va_start(ap, fmt);
	va_copy(ap2, ap);
	smash_stack();
	vsnprintf(s, sizeof(s), fmt, ap);
	if (strcmp(result, s) != 0) {
		fprintf(stderr,
		    "%d: printf(\"%s\", %s) ==> [%s], expected [%s]\n",
		    line, fmt, argstr, s, result);
		abort();
	}

	smash_stack();
	mbstowcs(ws, s, BUF - 1);
	mbstowcs(wfmt, fmt, BUF - 1);
	mbstowcs(wresult, result, BUF - 1);
	vswprintf(ws, sizeof(ws) / sizeof(ws[0]), wfmt, ap2);
	if (wcscmp(wresult, ws) != 0) {
		fprintf(stderr,
		    "%d: wprintf(\"%ls\", %s) ==> [%ls], expected [%ls]\n",
		    line, wfmt, argstr, ws, wresult);
		abort();
	}	
}