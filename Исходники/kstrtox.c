static int _kstrtoull(const char *s, unsigned int base, unsigned long long *res)
{
	unsigned long long acc;
	int ok;

	if (base == 0) {
		if (s[0] == '0') {
			if (_tolower(s[1]) == 'x' && isxdigit(s[2]))
				base = 16;
			else
				base = 8;
		} else
			base = 10;
	}
	if (base == 16 && s[0] == '0' && _tolower(s[1]) == 'x')
		s += 2;

	acc = 0;
	ok = 0;
	while (*s) {
		unsigned int val;

		if ('0' <= *s && *s <= '9')
			val = *s - '0';
		else if ('a' <= _tolower(*s) && _tolower(*s) <= 'f')
			val = _tolower(*s) - 'a' + 10;
		else if (*s == '\n') {
			if (*(s + 1) == '\0')
				break;
			else
				return -EINVAL;
		} else
			return -EINVAL;

		if (val >= base)
			return -EINVAL;
		if (acc > div_u64(ULLONG_MAX - val, base))
			return -ERANGE;
		acc = acc * base + val;
		ok = 1;

		s++;
	}
	if (!ok)
		return -EINVAL;
	*res = acc;
	return 0;
}