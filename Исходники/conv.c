void
conv_c(PR *pr, u_char *p, size_t bufsize)
{
	char buf[10];
	char const *str;
	wchar_t wc;
	size_t clen, oclen;
	int converr, pad, width;
	u_char peekbuf[MB_LEN_MAX];

	if (pr->mbleft > 0) {
		str = "**";
		pr->mbleft--;
		goto strpr;
	}

	switch(*p) {
	case '\0':
		str = "\\0";
		goto strpr;
	/* case '\a': */
	case '\007':
		str = "\\a";
		goto strpr;
	case '\b':
		str = "\\b";
		goto strpr;
	case '\f':
		str = "\\f";
		goto strpr;
	case '\n':
		str = "\\n";
		goto strpr;
	case '\r':
		str = "\\r";
		goto strpr;
	case '\t':
		str = "\\t";
		goto strpr;
	case '\v':
		str = "\\v";
		goto strpr;
	default:
		break;
	}
	/*
	 * Multibyte characters are disabled for hexdump(1) for backwards
	 * compatibility and consistency (none of its other output formats
	 * recognize them correctly).
	 */
	converr = 0;
	if (odmode && MB_CUR_MAX > 1) {
		oclen = 0;
retry:
		clen = mbrtowc(&wc, (const char *)p, bufsize, &pr->mbstate);
		if (clen == 0)
			clen = 1;
		else if (clen == (size_t)-1 || (clen == (size_t)-2 &&
		    p == peekbuf)) {
			memset(&pr->mbstate, 0, sizeof(pr->mbstate));
			wc = *p;
			clen = 1;
			converr = 1;
		} else if (clen == (size_t)-2) {
			/*
			 * Incomplete character; peek ahead and see if we
			 * can complete it.
			 */
			oclen = bufsize;
			bufsize = peek(p = peekbuf, MB_CUR_MAX);
			goto retry;
		}
		clen += oclen;
	} else {
		wc = *p;
		clen = 1;
	}
	if (!converr && iswprint(wc)) {
		if (!odmode) {
			*pr->cchar = 'c';
			(void)printf(pr->fmt, (int)wc);
		} else {	
			*pr->cchar = 'C';
			assert(strcmp(pr->fmt, "%3C") == 0);
			width = wcwidth(wc);
			assert(width >= 0);
			pad = 3 - width;
			if (pad < 0)
				pad = 0;
			(void)printf("%*s%C", pad, "", wc);
			pr->mbleft = clen - 1;
		}
	} else {
		(void)sprintf(buf, "%03o", (int)*p);
		str = buf;
strpr:		*pr->cchar = 's';
		(void)printf(pr->fmt, str);
	}
}