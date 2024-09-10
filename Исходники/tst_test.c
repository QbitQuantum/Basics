static void print_result(const char *file, const int lineno, int ttype,
                         const char *fmt, va_list va)
{
	char buf[1024];
	char *str = buf;
	int ret, size = sizeof(buf), ssize;
	const char *str_errno = NULL;
	const char *res;

	switch (TTYPE_RESULT(ttype)) {
	case TPASS:
		res = "PASS";
	break;
	case TFAIL:
		res = "FAIL";
	break;
	case TBROK:
		res = "BROK";
	break;
	case TCONF:
		res = "CONF";
	break;
	case TWARN:
		res = "WARN";
	break;
	case TINFO:
		res = "INFO";
	break;
	default:
		tst_brk(TBROK, "Invalid ttype value %i", ttype);
		abort();
	}

	if (ttype & TERRNO)
		str_errno = tst_strerrno(errno);

	if (ttype & TTERRNO)
		str_errno = tst_strerrno(TEST_ERRNO);

	ret = snprintf(str, size, "%s:%i: ", file, lineno);
	str += ret;
	size -= ret;

	if (tst_color_enabled(STDERR_FILENO))
		ret = snprintf(str, size, "%s%s: %s", tst_ttype2color(ttype),
			       res, ANSI_COLOR_RESET);
	else
		ret = snprintf(str, size, "%s: ", res);
	str += ret;
	size -= ret;

	ssize = size - 2;
	ret = vsnprintf(str, size, fmt, va);
	str += MIN(ret, ssize);
	size -= MIN(ret, ssize);
	if (ret >= ssize) {
		tst_res_(file, lineno, TWARN,
				"Next message is too long and truncated:");
	} else if (str_errno) {
		ssize = size - 2;
		ret = snprintf(str, size, ": %s", str_errno);
		str += MIN(ret, ssize);
		size -= MIN(ret, ssize);
		if (ret >= ssize)
			tst_res_(file, lineno, TWARN,
				"Next message is too long and truncated:");
	}

	snprintf(str, size, "\n");

	fputs(buf, stderr);
}