const char *file_getbuffer(RMagic *ms) {
	char *pbuf, *op, *np;
	size_t psize, len;

	if (ms->haderr)
		return NULL;

	if (ms->flags & R_MAGIC_RAW)
		return ms->o.buf;

	if (ms->o.buf == NULL) {
		eprintf ("ms->o.buf = NULL\n");
		return NULL;
	}

	/* * 4 is for octal representation, + 1 is for NUL */
	len = strlen (ms->o.buf);
	if (len > (SIZE_MAX - 1) / 4) {
		file_oomem (ms, len);
		return NULL;
	}
	psize = len * 4 + 1;
	if ((pbuf = realloc (ms->o.pbuf, psize)) == NULL) {
		file_oomem (ms, psize);
		return NULL;
	}
	ms->o.pbuf = pbuf;

#if 1
//defined(HAVE_WCHAR_H) && defined(HAVE_MBRTOWC) && defined(HAVE_WCWIDTH)
	{
		mbstate_t state;
		wchar_t nextchar;
		int mb_conv = 1;
		size_t bytesconsumed;
		char *eop;
		(void)memset(&state, 0, sizeof(mbstate_t));

		np = ms->o.pbuf;
		op = ms->o.buf;
		eop = op + len;

		while (op < eop) {
			bytesconsumed = mbrtowc(&nextchar, op,
			    (size_t)(eop - op), &state);
			if (bytesconsumed == (size_t)(-1) ||
			    bytesconsumed == (size_t)(-2)) {
				mb_conv = 0;
				break;
			}

			if (iswprint(nextchar)) {
				(void)memcpy(np, op, bytesconsumed);
				op += bytesconsumed;
				np += bytesconsumed;
			} else {
				while (bytesconsumed-- > 0)
					OCTALIFY(np, op);
			}
		}
		*np = '\0';

		/* Parsing succeeded as a multi-byte sequence */
		if (mb_conv != 0)
			return ms->o.pbuf;
	}
#endif
	for (np = ms->o.pbuf, op = ms->o.buf; *op; op++) {
		if (isprint ((ut8)*op)) {
			*np++ = *op;	
		} else {
			OCTALIFY (np, op);
		}
	}
	*np = '\0';
	return ms->o.pbuf;
}