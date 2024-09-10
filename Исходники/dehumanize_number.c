/*
 * Converts the number given in 'str', which may be given in a humanized
 * form (as described in humanize_number(3), but with some limitations),
 * to an int64_t without units.
 * In case of success, 0 is returned and *size holds the value.
 * Otherwise, -1 is returned and *size is untouched.
 *
 * TODO: Internationalization, SI units.
 */
int
dehumanize_number(const char *str, int64_t *size)
{
	char *ep, unit;
	const char *delimit;
	long multiplier;
	long long tmp, tmp2;
	size_t len;

	len = strlen(str);
	if (len == 0) {
		errno = EINVAL;
		return -1;
	}

	multiplier = 1;

	unit = str[len - 1];
	if (isalpha((unsigned char)unit)) {
		switch (tolower((unsigned char)unit)) {
		case 'b':
			multiplier = 1;
			break;

		case 'k':
			multiplier = 1024;
			break;

		case 'm':
			multiplier = 1024 * 1024;
			break;

		case 'g':
			multiplier = 1024 * 1024 * 1024;
			break;

		default:
			errno = EINVAL;
			return -1; /* Invalid suffix. */
		}

		delimit = &str[len - 1];
	} else
		delimit = NULL;

	errno = 0;
	tmp = strtoll(str, &ep, 10);
	if (str[0] == '\0' || (ep != delimit && *ep != '\0'))
		return -1; /* Not a number. */
	else if (errno == ERANGE && (tmp == LLONG_MAX || tmp == LLONG_MIN))
		return -1; /* Out of range. */

	tmp2 = tmp * multiplier;
	tmp2 = tmp2 / multiplier;
	if (tmp != tmp2) {
		errno = ERANGE;
		return -1; /* Out of range. */
	}
	tmp *= multiplier;
#ifdef _DIAGASSERT
	_DIAGASSERT(__type_fit(int64_t, tmp));
#endif
	*size = (int64_t)tmp;

	return 0;
}