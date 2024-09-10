int
disrsl_(int stream, int *negate, unsigned long *value, unsigned long count, int recursv)
{
	int		c;
	unsigned long	locval;
	unsigned long	ndigs;
	char		*cp;

	assert(negate != NULL);
	assert(value != NULL);
	assert(count);
	assert(stream >= 0);
	assert(dis_getc != NULL);
	assert(dis_gets != NULL);

	if (++recursv > DIS_RECURSIVE_LIMIT)
		return (DIS_PROTO);

	switch (c = (*dis_getc)(stream)) {
		case '-':
		case '+':
			if (count > ulmaxdigs)
				goto overflow;
			*negate = c == '-';
			if ((*dis_gets)(stream, dis_buffer, count) != count)
				return (DIS_EOD);
			if (count == ulmaxdigs) {
				if (memcmp(dis_buffer, ulmax, ulmaxdigs) > 0)
					goto overflow;
			}
			cp = dis_buffer;
			locval = 0;
			do {
				if ((c = *cp++) < '0' || c > '9')
					return (DIS_NONDIGIT);
				locval = 10 * locval + c - '0';
			} while (--count);
			*value = locval;
			return (DIS_SUCCESS);
		case '0':
			return (DIS_LEADZRO);
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			ndigs = c - '0';
			if (count > 1) {
				if (count > ulmaxdigs)
					break;
				if ((*dis_gets)(stream, dis_buffer + 1, count - 1) !=
					count - 1)
					return (DIS_EOD);
				cp = dis_buffer;
				if (count == ulmaxdigs) {
					*cp = c;
					if (memcmp(dis_buffer, ulmax, ulmaxdigs) > 0)
						break;
				}
				while (--count) {
					if ((c = *++cp) < '0' || c > '9')
						return (DIS_NONDIGIT);
					ndigs = 10 * ndigs + c - '0';
				}
			}
			return (disrsl_(stream, negate, value, ndigs, recursv));
		case -1:
			return (DIS_EOD);
		case -2:
			return (DIS_EOF);
		default:
			return (DIS_NONDIGIT);
	}
	*negate = FALSE;
overflow:
	*value = ULONG_MAX;
	return (DIS_OVERFLOW);
}