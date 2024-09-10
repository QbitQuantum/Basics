unsigned long ILAnsiGetByteCount(const unsigned short *chars,
								 unsigned long count)
{
#ifdef IL_CONFIG_LATIN1
	return count;
#else
#if HAVE_WCRTOMB
	/* Use the re-entrant function to perform the conversion */
	mbstate_t state;
	char buf[MB_LEN_MAX+1];
	size_t chlen;
	unsigned short ch;
	unsigned long len = 0;
	ILMemZero(&state, sizeof(state));
	wcrtomb(buf, 0, &state);
	while(count > 0)
	{
		ch = *chars++;
		if(ch != 0)
		{
			chlen = wcrtomb(buf, (wchar_t)ch, &state);
			if(chlen != (size_t)(-1))
			{
				len += (unsigned long)chlen;
			}
		}
		else
		{
			++len;
		}
		--count;
	}
	return len;
#else
	/* Use the non re-entrant function to perform the conversion
	   and just hope that the underlying libc takes care of the
	   thread-safety issues for us */
	char buf[MB_LEN_MAX+1];
	int chlen;
	unsigned long len = 0;
	wctomb((char *)0, 0);
	while(count > 0)
	{
		chlen = wctomb(buf, (wchar_t)(*chars));
		if(chlen > 0)
		{
			len += (unsigned long)chlen;
		}
		++chars;
		--count;
	}
	return len;
#endif
#endif
}