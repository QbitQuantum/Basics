static int
cnt(const char *file)
{
	struct stat sb;
	uintmax_t linect, wordct, charct, llct, tmpll;
	int fd, len, warned;
	size_t clen;
	short gotsp;
	u_char *p;
	u_char buf[MAXBSIZE];
	wchar_t wch;
	mbstate_t mbs;

	linect = wordct = charct = llct = tmpll = 0;
	if (file == NULL)
		fd = STDIN_FILENO;
	else {
		if ((fd = open(file, O_RDONLY, 0)) < 0) {
			warn("%s: open", file);
			return (1);
		}
		if (doword || (domulti && MB_CUR_MAX != 1))
			goto word;
		/*
		 * Line counting is split out because it's a lot faster to get
		 * lines than to get words, since the word count requires some
		 * logic.
		 */
		if (doline) {
			while ((len = read(fd, buf, MAXBSIZE))) {
				if (len == -1) {
					warn("%s: read", file);
					(void)close(fd);
					return (1);
				}
				if (siginfo) {
					show_cnt(file, linect, wordct, charct,
					    llct);
				}
				charct += len;
				for (p = buf; len--; ++p)
					if (*p == '\n') {
						if (tmpll > llct)
							llct = tmpll;
						tmpll = 0;
						++linect;
					} else
						tmpll++;
			}
			reset_siginfo();
			tlinect += linect;
			if (dochar)
				tcharct += charct;
			if (dolongline) {
				if (llct > tlongline)
					tlongline = llct;
			}
			show_cnt(file, linect, wordct, charct, llct);
			(void)close(fd);
			return (0);
		}
		/*
		 * If all we need is the number of characters and it's a
		 * regular file, just stat the puppy.
		 */
		if (dochar || domulti) {
			if (fstat(fd, &sb)) {
				warn("%s: fstat", file);
				(void)close(fd);
				return (1);
			}
			if (S_ISREG(sb.st_mode)) {
				reset_siginfo();
				charct = sb.st_size;
				show_cnt(file, linect, wordct, charct, llct);
				tcharct += charct;
				(void)close(fd);
				return (0);
			}
		}
	}

	/* Do it the hard way... */
word:	gotsp = 1;
	warned = 0;
	memset(&mbs, 0, sizeof(mbs));
	while ((len = read(fd, buf, MAXBSIZE)) != 0) {
		if (len == -1) {
			warn("%s: read", file != NULL ? file : "stdin");
			(void)close(fd);
			return (1);
		}
		p = buf;
		while (len > 0) {
			if (siginfo)
				show_cnt(file, linect, wordct, charct, llct);
			if (!domulti || MB_CUR_MAX == 1) {
				clen = 1;
				wch = (unsigned char)*p;
			} else if ((clen = mbrtowc(&wch, p, len, &mbs)) ==
			    (size_t)-1) {
				if (!warned) {
					errno = EILSEQ;
					warn("%s",
					    file != NULL ? file : "stdin");
					warned = 1;
				}
				memset(&mbs, 0, sizeof(mbs));
				clen = 1;
				wch = (unsigned char)*p;
			} else if (clen == (size_t)-2)
				break;
			else if (clen == 0)
				clen = 1;
			charct++;
			if (wch != L'\n')
				tmpll++;
			len -= clen;
			p += clen;
			if (wch == L'\n') {
				if (tmpll > llct)
					llct = tmpll;
				tmpll = 0;
				++linect;
			}
			if (iswspace(wch))
				gotsp = 1;
			else if (gotsp) {
				gotsp = 0;
				++wordct;
			}
		}
	}
	reset_siginfo();
	if (domulti && MB_CUR_MAX > 1)
		if (mbrtowc(NULL, NULL, 0, &mbs) == (size_t)-1 && !warned)
			warn("%s", file != NULL ? file : "stdin");
	if (doline)
		tlinect += linect;
	if (doword)
		twordct += wordct;
	if (dochar || domulti)
		tcharct += charct;
	if (dolongline) {
		if (llct > tlongline)
			tlongline = llct;
	}
	show_cnt(file, linect, wordct, charct, llct);
	(void)close(fd);
	return (0);
}