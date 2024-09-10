const char *
VNUM_2bytes(const char *p, uintmax_t *r, uintmax_t rel)
{
	double fval;
	const char *end;

	if (p == NULL || *p == '\0')
		return (err_miss_num);

	fval = VNUMpfx(p, &end);
	if (isnan(fval))
		return (err_invalid_num);

	if (end == NULL) {
		*r = (uintmax_t)fval;
		return (NULL);
	}

	if (end[0] == '%' && end[1] == '\0') {
		if (rel == 0)
			return (err_abs_req);
		fval *= rel / 100.0;
	} else {
		/* accept a space before the multiplier */
		if (end[0] == ' ' && end[1] != '\0')
			++end;

		switch (end[0]) {
		case 'k': case 'K':
			fval *= (uintmax_t)1 << 10;
			++end;
			break;
		case 'm': case 'M':
			fval *= (uintmax_t)1 << 20;
			++end;
			break;
		case 'g': case 'G':
			fval *= (uintmax_t)1 << 30;
			++end;
			break;
		case 't': case 'T':
			fval *= (uintmax_t)1 << 40;
			++end;
			break;
		case 'p': case 'P':
			fval *= (uintmax_t)1 << 50;
			++end;
			break;
		default:
			break;
		}

		/* [bB] is a generic suffix of no effect */
		if (end[0] == 'b' || end[0] == 'B')
			end++;

		if (end[0] != '\0')
			return (err_invalid_suff);
	}

	*r = (uintmax_t)round(fval);
	return (NULL);
}