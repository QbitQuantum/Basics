wint_t
fgetwc(Sfio_t* f)
{
	wchar_t	c;

	STDIO_INT(f, "fgetwc", wint_t, (Sfio_t*), (f))

	FWIDE(f, WEOF);
	return (sfread(f, &c, sizeof(c)) == sizeof(c)) ? c : WEOF;
}