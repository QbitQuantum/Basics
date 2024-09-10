void
makemsg(char *fname)
{
	int cnt;
	wchar_t ch;
	struct tm *lt;
	struct passwd *pw;
	struct stat sbuf;
	time_t now;
	FILE *fp;
	int fd;
	char hostname[MAXHOSTNAMELEN], tmpname[64];
	wchar_t *p, *tmp, lbuf[256], codebuf[13];
	const char *tty;
	const char *whom;
	gid_t egid;

	(void)snprintf(tmpname, sizeof(tmpname), "%s/wall.XXXXXX", _PATH_TMP);
	if ((fd = mkstemp(tmpname)) == -1 || !(fp = fdopen(fd, "r+")))
		err(1, "can't open temporary file");
	(void)unlink(tmpname);

	if (!nobanner) {
		tty = ttyname(STDERR_FILENO);
		if (tty == NULL)
			tty = "no tty";

		if (!(whom = getlogin()))
			whom = (pw = getpwuid(getuid())) ? pw->pw_name : "???";
		(void)gethostname(hostname, sizeof(hostname));
		(void)time(&now);
		lt = localtime(&now);

		/*
		 * all this stuff is to blank out a square for the message;
		 * we wrap message lines at column 79, not 80, because some
		 * terminals wrap after 79, some do not, and we can't tell.
		 * Which means that we may leave a non-blank character
		 * in column 80, but that can't be helped.
		 */
		(void)fwprintf(fp, L"\r%79s\r\n", " ");
		(void)swprintf(lbuf, sizeof(lbuf)/sizeof(wchar_t),
		    L"Broadcast Message from %s@%s",
		    whom, hostname);
		(void)fwprintf(fp, L"%-79.79S\007\007\r\n", lbuf);
		(void)swprintf(lbuf, sizeof(lbuf)/sizeof(wchar_t),
		    L"        (%s) at %d:%02d %s...", tty,
		    lt->tm_hour, lt->tm_min, lt->tm_zone);
		(void)fwprintf(fp, L"%-79.79S\r\n", lbuf);
	}
	(void)fwprintf(fp, L"%79s\r\n", " ");

	if (fname) {
		egid = getegid();
		setegid(getgid());
		if (freopen(fname, "r", stdin) == NULL)
			err(1, "can't read %s", fname);
		if (setegid(egid) != 0)
			err(1, "setegid failed");
	}
	cnt = 0;
	while (fgetws(lbuf, sizeof(lbuf)/sizeof(wchar_t), stdin)) {
		for (p = lbuf; (ch = *p) != L'\0'; ++p, ++cnt) {
			if (ch == L'\r') {
				putwc(L'\r', fp);
				cnt = 0;
				continue;
			} else if (ch == L'\n') {
				for (; cnt < 79; ++cnt)
					putwc(L' ', fp);
				putwc(L'\r', fp);
				putwc(L'\n', fp);
				break;
			}
			if (cnt == 79) {
				putwc(L'\r', fp);
				putwc(L'\n', fp);
				cnt = 0;
			}
			if (iswprint(ch) || iswspace(ch) || ch == L'\a' || ch == L'\b') {
				putwc(ch, fp);
			} else {
				(void)swprintf(codebuf, sizeof(codebuf)/sizeof(wchar_t), L"<0x%X>", ch);
				for (tmp = codebuf; *tmp != L'\0'; ++tmp) {
					putwc(*tmp, fp);
					if (++cnt == 79) {
						putwc(L'\r', fp);
						putwc(L'\n', fp);
						cnt = 0;
					}
				}
				--cnt;
			}
		}
	}
	(void)fwprintf(fp, L"%79s\r\n", " ");
	rewind(fp);

	if (fstat(fd, &sbuf))
		err(1, "can't stat temporary file");
	mbufsize = sbuf.st_size;
	if (!(mbuf = malloc((u_int)mbufsize)))
		err(1, "out of memory");
	if ((int)fread(mbuf, sizeof(*mbuf), mbufsize, fp) != mbufsize)
		err(1, "can't read temporary file");
	(void)close(fd);
}