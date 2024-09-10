static char *
readtty(const char *pr, char *src)
{
	char canonb[LINESIZE];
	char *cp, *cp2;
	int c;
#ifdef TIOCSTI
	char ch;
#endif

	(void)fputs(pr, stdout);
	(void)fflush(stdout);
	if (src != NULL && strlen(src) > sizeof(canonb) - 2) {
		(void)printf("too long to edit\n");
		return src;
	}
#ifndef TIOCSTI
	if (src != NULL)
		cp = copy(src, canonb);
	else
		cp = copy(__UNCONST(""), canonb);
	c = *cp;
	(void)fputs(canonb, stdout);
	(void)fflush(stdout);
#else
	cp = src == NULL ? __UNCONST("") : src;
	while ((c = *cp++) != '\0') {
		if ((c_erase != _POSIX_VDISABLE && c == c_erase) ||
		    (c_kill != _POSIX_VDISABLE && c == c_kill)) {
			ch = '\\';
			(void)ioctl(0, TIOCSTI, &ch);
		}
		ch = c;
		(void)ioctl(0, TIOCSTI, &ch);
	}
	cp = canonb;
	*cp = '\0';
#endif
	clearerr(stdin);
	cp2 = cp;
	while (cp2 < canonb + sizeof(canonb) - 1) {
		c = getc(stdin);
		sig_check();
		if (c == EOF) {
			if (feof(stdin))
				(void)putc('\n', stdout);
			break;
		}
		if (c == '\n')
			break;
		*cp2++ = c;
	}
	*cp2 = '\0';

	if (c == EOF && ferror(stdin)) {
		cp = strlen(canonb) > 0 ? canonb : NULL;
		clearerr(stdin);
		return readtty(pr, cp);
	}
#ifndef TIOCSTI
	if (cp == NULL || *cp == '\0')
		return src;
	if (ttyset == 0)
		return strlen(canonb) > 0 ? savestr(canonb) : NULL;

	/*
	 * Do erase and kill.
	 */
	cp2 = cp;
	while (*cp != '\0') {
		c = *cp++;
		if (c_erase != _POSIX_VDISABLE && c == c_erase) {
			if (cp2 == canonb)
				continue;
			if (cp2[-1] == '\\') {
				cp2[-1] = c;
				continue;
			}
			cp2--;
			continue;
		}
		if (c_kill != _POSIX_VDISABLE && c == c_kill) {
			if (cp2 == canonb)
				continue;
			if (cp2[-1] == '\\') {
				cp2[-1] = c;
				continue;
			}
			cp2 = canonb;
			continue;
		}
		*cp2++ = c;
	}
	*cp2 = '\0';
#endif
	if (canonb[0] == '\0')
		return __UNCONST("");
	return savestr(canonb);
}