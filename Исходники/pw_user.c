static int
pw_set_passwd(struct passwd *pwd, int fd, bool precrypted, bool update)
{
	int		 b, istty;
	struct termios	 t, n;
	login_cap_t	*lc;
	char		line[_PASSWORD_LEN+1];
	char		*p;

	if (fd == '-') {
		if (!pwd->pw_passwd || *pwd->pw_passwd != '*') {
			pwd->pw_passwd = "*";	/* No access */
			return (1);
		}
		return (0);
	}

	if ((istty = isatty(fd))) {
		if (tcgetattr(fd, &t) == -1)
			istty = 0;
		else {
			n = t;
			n.c_lflag &= ~(ECHO);
			tcsetattr(fd, TCSANOW, &n);
			printf("%s%spassword for user %s:",
			    update ? "new " : "",
			    precrypted ? "encrypted " : "",
			    pwd->pw_name);
			fflush(stdout);
		}
	}
	b = read(fd, line, sizeof(line) - 1);
	if (istty) {	/* Restore state */
		tcsetattr(fd, TCSANOW, &t);
		fputc('\n', stdout);
		fflush(stdout);
	}

	if (b < 0)
		err(EX_IOERR, "-%c file descriptor",
		    precrypted ? 'H' : 'h');
	line[b] = '\0';
	if ((p = strpbrk(line, "\r\n")) != NULL)
		*p = '\0';
	if (!*line)
		errx(EX_DATAERR, "empty password read on file descriptor %d",
		    fd);
	if (precrypted) {
		if (strchr(line, ':') != NULL)
			errx(EX_DATAERR, "bad encrypted password");
		pwd->pw_passwd = strdup(line);
	} else {
		lc = login_getpwclass(pwd);
		if (lc == NULL ||
				login_setcryptfmt(lc, "sha512", NULL) == NULL)
			warn("setting crypt(3) format");
		login_close(lc);
		pwd->pw_passwd = pw_pwcrypt(line);
	}
	return (1);
}