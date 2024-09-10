static int print_f(void (*printchar_handler)(struct printchar_handler_data *d, int c),
		struct printchar_handler_data *printchar_data, long double r, int width,
		int precision, unsigned int ops, int base, int with_exp, int is_shortened) {
	char buff[PRINT_F_BUFF_SZ], *str, *end, *prefix, *postfix;
	DOUBLE ip, fp, ep;
	int pc, i, ch, len, prefix_len, postfix_len, pad_count, sign_count, zero_left, letter_base;

	assert(printchar_handler != NULL);
	assert(width >= 0);
	assert(precision >= 0);

	postfix = end = str = &buff[0] + sizeof buff / sizeof buff[0] - 1;
	*end = '\0';
	prefix = signbit(r) ? (r = -r, base == 16)
				? ops & OPS_SPEC_UPPER_CASE ? "-0X" : "-0x"
				: "-"
			: ops & OPS_FLAG_WITH_SIGN ? base == 16
				? ops & OPS_SPEC_UPPER_CASE ? "+0X" : "+0x"
				: "+"
			: ops & OPS_FLAG_EXTRA_SPACE ? base == 16
				? ops & OPS_SPEC_UPPER_CASE ? " 0X" : " 0x"
				: " "
			: base == 16 ? ops & OPS_SPEC_UPPER_CASE ? "0X" : "0x"
			: "";
	sign_count = i = pc = 0;
	prefix_len = strlen(prefix);
	letter_base = ops & OPS_SPEC_UPPER_CASE ? 'A' : 'a';
	precision = ops & OPS_PREC_IS_GIVEN ? is_shortened ?
				max(precision, 1) : precision
			: base == 16 ? 12 : PRINT_F_PREC_DEFAULT;

	fp = MODF(r, &ip);
	if (with_exp || is_shortened) {
		ep = 0.0L;
		while (ip >= base) fp = MODF((ip + fp) / base, &ip), ep += 1.0L;
		if (fp != 0.0L) while (ip == 0.0L) fp = MODF((ip + fp) * base, &ip), ep -= 1.0L;
		if ((ep < -4) || (ep >= precision)) with_exp = 1;
	}
	fp = with_exp ? fp : MODF(r, &ip);
	precision -= is_shortened ? ceill(LOG10(ip)) + (ip != 0.0L) : 0;
	assert(precision >= 0);
	for (; (sign_count < precision) && (FMOD(fp, 1.0L) != 0.0L); ++sign_count) fp *= base;
	fp = roundl(fp);
	ip = precision ? fp != POW(base, sign_count)
			? ip : ip + 1.0L : roundl(ip + fp);
	fp = fp != POW(base, sign_count) ? fp : 0.0L;
	if (with_exp && (ip >= base)) fp = MODF((ip + fp) / base, &ip), ep += 1.0L;

	if (with_exp) {
		do {
			ch = FMOD(FABS(ep), base);
			assert((ch >= 0) && (ch < base));
			if (ch >= 10) ch += letter_base - 10 - '0';
			*--postfix = ch + '0';
			MODF(ep / base, &ep);
		} while (ep != 0.0L);
		if ((strlen(postfix) == 1) && (base != 16)) *--postfix = '0';
		*--postfix = signbit(ep) ? '-' : '+';
		*--postfix = base == 16 ? ops & OPS_SPEC_UPPER_CASE ?
					'P' : 'p'
				: ops & OPS_SPEC_UPPER_CASE ? 'E' : 'e';
		str = end = postfix - 1;
		*end = '\0';
	}

	for (; i < sign_count; ++i) {
		ch = FMOD(fp, base);
		assert((ch >= 0) && (ch < base));
		if (ch >= 10) ch += letter_base - 10 - '0';
		*--str = ch + '0';
		MODF(fp / base, &fp);
	}

	if ((precision && !is_shortened) || sign_count
			|| (ops & OPS_FLAG_WITH_SPEC)) {
		*--str = '.';
	}

	do {
		ch = (int)FMOD(ip, (long double)base);
		assert((ch >= 0) && (ch < base));
		if (ch >= 10) ch += letter_base - 10 - '0';
		*--str = ch + '0';
		MODF(ip / base, &ip);
	} while (ip != 0.0L);

	len = end - str;
	postfix_len = strlen(postfix);
	zero_left = is_shortened ? 0 : precision - sign_count;
	pad_count = max(width - prefix_len - len - zero_left - postfix_len, 0);

	if (!(ops & (OPS_FLAG_ZERO_PAD | OPS_FLAG_LEFT_ALIGN))) {
		pc += pad_count;
		while (pad_count--) printchar_handler(printchar_data, ' ');
	}

	pc += prefix_len;
	while (prefix_len--) printchar_handler(printchar_data, *prefix++);

	if (ops & OPS_FLAG_ZERO_PAD) {
		pc += pad_count;
		while (pad_count--) printchar_handler(printchar_data, '0');
	}

	pc += len;
	while (len--) printchar_handler(printchar_data, *str++);

	pc += zero_left;
	while (zero_left--) printchar_handler(printchar_data, '0');

	pc += postfix_len;
	while (postfix_len--) printchar_handler(printchar_data, *postfix++);

	if (ops & OPS_FLAG_LEFT_ALIGN) {
		pc += pad_count;
		while (pad_count--) printchar_handler(printchar_data, ' ');
	}

	return pc;
}