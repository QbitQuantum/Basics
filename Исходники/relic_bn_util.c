void bn_read_str(bn_t a, const char *str, int len, int radix) {
	int sign, i, j;
	char c;

	bn_zero(a);

	if (radix < 2 || radix > 64) {
		THROW(ERR_NO_VALID)
	}

	j = 0;
	if (str[0] == '-') {
		j++;
		sign = BN_NEG;
	} else {
		sign = BN_POS;
	}

	while (str[j] && j < len) {
		c = (char)((radix < 36) ? TOUPPER(str[j]) : str[j]);
		for (i = 0; i < 64; i++) {
			if (c == util_conv_char(i)) {
				break;
			}
		}

		if (i < radix) {
			bn_mul_dig(a, a, (dig_t)radix);
			bn_add_dig(a, a, (dig_t)i);
		} else {
			break;
		}
		j++;
	}

	a->sign = sign;
}