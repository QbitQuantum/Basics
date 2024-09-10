// Returns false only if parsing should be aborted.
bool consume_value(value_t &val, const char** str)
{
	assert(str);

	const char *c = *str;

	// Double / float
	if(*c == '+' || *c == '-') {
		if(!lc_neutral) {
			lc_neutral = _create_locale(LC_NUMERIC, "C");
		}
		char *endptr;

		errno = 0;
		double result = _strtod_l(*str, &endptr, lc_neutral);
		if(errno == ERANGE && (result == HUGE_VAL || result == -HUGE_VAL)) {
			auto val_len = (endptr - *str);
			log_printf(
				"ERROR: Floating point constant \"%.*s\" out of range!\n",
				val_len, str
			);
			return false;
		} else if(endptr == *str) {
			// Not actually a floating-point number, keep going though
			*str += 1;
			return true;
		}
		if(*endptr == 'f') {
			val.type = VT_FLOAT;
			val.f = (float)result;
			endptr++;
		} else {
			val.type = VT_DOUBLE;
			val.d = result;
		}
		if(*endptr != ' ' && *endptr != '\0') {
			val.type = VT_NONE;
			*str += 1;
		} else {
			*str = endptr;
		}
	}
	// Byte
	else if(is_valid_hex(c[0]) && is_valid_hex(c[1])) {
		char conv[3];
		conv[2] = 0;
		memcpy(conv, *str, 2);
		val.type = VT_BYTE;
		val.b = (unsigned char)strtol(conv, nullptr, 16);
		*str += 2;
	}
	// Nothing, keep going
	else {
		*str += 1;
	}
	return true;
}