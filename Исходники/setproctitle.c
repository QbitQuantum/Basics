void
setproctitle(const char *fmt, ...)
{
	static struct ps_strings *ps_strings;
	static char *buf = NULL;
	static char *obuf = NULL;
	static char **oargv, *kbuf;
	static int oargc = -1;
	static char *nargv[2] = { NULL, NULL };
	char **nargvp;
	int nargc;
	int i;
	va_list ap;
	size_t len;
	unsigned long ul_ps_strings;
	int oid[4];

	if (buf == NULL) {
		buf = malloc(SPT_BUFSIZE);
		if (buf == NULL) 
			return;
		nargv[0] = buf;
	}

	if (obuf == NULL ) {
		obuf = malloc(SPT_BUFSIZE);
		if (obuf == NULL)
			return;
		*obuf = '\0';
	}

	va_start(ap, fmt);

	if (fmt) {
		buf[SPT_BUFSIZE - 1] = '\0';

		if (fmt[0] == '-') {
			/* skip program name prefix */
			fmt++;
			len = 0;
		} else {
			/* print program name heading for grep */
			(void)snprintf(buf, SPT_BUFSIZE, "%s: ", _getprogname());
			len = strlen(buf);
		}

		/* print the argument string */
		(void) vsnprintf(buf + len, SPT_BUFSIZE - len, fmt, ap);

		nargvp = nargv;
		nargc = 1;
		kbuf = buf;
	} else if (*obuf != '\0') {
  		/* Idea from NetBSD - reset the title on fmt == NULL */
		nargvp = oargv;
		nargc = oargc;
		kbuf = obuf;
	} else
		/* Nothing to restore */
		return;

	va_end(ap);

	/* Set the title into the kernel cached command line */
	oid[0] = CTL_KERN;
	oid[1] = KERN_PROC;
	oid[2] = KERN_PROC_ARGS;
	oid[3] = getpid();
	sysctl(oid, 4, 0, 0, kbuf, strlen(kbuf) + 1);

	if (ps_strings == NULL) {
		len = sizeof(ul_ps_strings);
		if (sysctlbyname("kern.ps_strings", &ul_ps_strings, &len, NULL,
		    0) == -1)
			ul_ps_strings = PS_STRINGS;
		ps_strings = (struct ps_strings *)ul_ps_strings;
	}

	/* PS_STRINGS points to zeroed memory on a style #2 kernel */
	if (ps_strings->ps_argvstr) {
		/* style #3 */
		if (oargc == -1) {
			/* Record our original args */
			oargc = ps_strings->ps_nargvstr;
			oargv = ps_strings->ps_argvstr;
			for (i = len = 0; i < oargc; i++) {
				/*
				 * The program may have scribbled into its
				 * argv array, e.g., to remove some arguments.
				 * If that has happened, break out before
				 * trying to call strlen on a NULL pointer.
				 */
				if (oargv[i] == NULL) {
					oargc = i;
					break;
				}
				snprintf(obuf + len, SPT_BUFSIZE - len, "%s%s",
				    len ? " " : "", oargv[i]);
				if (len)
					len++;
				len += strlen(oargv[i]);
				if (len >= SPT_BUFSIZE)
					break;
			}
		}
		ps_strings->ps_nargvstr = nargc;
		ps_strings->ps_argvstr = nargvp;
	} else {
		/* style #2 - we can only restore our first arg :-( */
		if (*obuf == '\0')
			strncpy(obuf, OLD_PS_STRINGS->old_ps_argvstr,
			    SPT_BUFSIZE - 1);
		OLD_PS_STRINGS->old_ps_nargvstr = 1;
		OLD_PS_STRINGS->old_ps_argvstr = nargvp[0];
	}
}