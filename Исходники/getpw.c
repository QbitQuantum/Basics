int
getpw(uid_t uid, char buf[])
{
	int n, c;
	char *bp;
	FILE *fp;
	rmutex_t *lk;

	if (pwf == NULL) {
		fp = fopen(PASSWD, "rF");
		lmutex_lock(&_pwlock);
		if (pwf == NULL) {
			if ((pwf = fp) == NULL) {
				lmutex_unlock(&_pwlock);
				return (1);
			}
			fp = NULL;
		}
		lmutex_unlock(&_pwlock);
		if (fp != NULL)		/* someone beat us to it */
			(void) fclose(fp);
	}

	FLOCKFILE(lk, pwf);
	_rewind_unlocked(pwf);

	for (;;) {
		bp = buf;
		while ((c = GETC(pwf)) != '\n') {
			if (c == EOF) {
				FUNLOCKFILE(lk);
				return (1);
			}
			*bp++ = (char)c;
		}
		*bp = '\0';
		bp = buf;
		n = 3;
		while (--n)
			while ((c = *bp++) != ':')
				if (c == '\n') {
					FUNLOCKFILE(lk);
					return (1);
				}
		while ((c = *bp++) != ':')
			if (isdigit(c))
				n = n*10+c-'0';
			else
				continue;
		if (n == uid) {
			FUNLOCKFILE(lk);
			return (0);
		}
	}
}