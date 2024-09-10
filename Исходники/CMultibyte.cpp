ARCH_STRING::ARCH_STRING()
{
	s_mutex = ARCH->newMutex();

#if HAVE_LOCALE_H
	// see if we can convert a Latin-1 character
	char mb[MB_LEN_MAX];
	if (wctomb(mb, 0xe3) == -1) {
		// can't convert.  try another locale so we can convert latin-1.
		setlocale(LC_CTYPE, "en_US");
	}
#endif
}