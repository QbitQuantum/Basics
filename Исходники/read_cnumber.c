static void read_floating(struct tok_floating *out, const struct scan_number *sn,
			tok_message_queue *mq) {
	/*
	Assertions about a float's struct scan_number:
		prefix is empty or [0B 0b 0X 0x] (note: no octal prefix 0)
		sn->digits not empty, ever
		exponent may or may not exist
		If exponent exists, it is valid and formatted as:
			( [E P e p] ['+' '-']*0..1 [0-9]* )
		An exponent starts with E if this is decimal, P if it is hex/binary
		suffix is [0-9 A-Z a-z '.']*
		dots_found can be anything
	*/
	const char *tokstart = sn->prefix;
	const char *s = sn->prefix, *e = sn->suffix;
	char borrow = *sn->end;
	//long double strtold(const char *nptr, char **endptr);
	
	out->v = 0.0;
	out->suffix = TOK_NOSUFFIX;
	
	if (sn->prefix < sn->digits) {
		if (sn->prefix[1]=='B' || sn->prefix[1]=='b') {
			tok_msg_error(binary_float, tokstart,
				"Binary floating point constants not allowed");
			return;
		}
		if (sn->exponent >= sn->suffix) {
			tok_msg_error(hex_float_no_exponent, tokstart,
				"Hex floating point constant missing exponent");
			return;
		}
	}
	
	
	/* Stick a null terminator at the end of the input so strtold
	 * won't read beyond the given input.
	 *
	 * This is thread-safe because the input is from
	 * token_list.txt, which was generated in the
	 * tokenize function which is still running.
	 */
	*(char*)sn->end = 0;
	errno = 0;
	out->v = strtold(s, (char**)&s);
	//don't forget to set it back
	*(char*)sn->end = borrow;
	
	if (errno) {
		//for some reason, strtold may errno to EDOM to indicate underrun
		//open test/run.c and search "floating_out_of_range" for more details
		if (errno == ERANGE || errno == EDOM) {
			tok_msg_error(floating_out_of_range, tokstart,
				"Floating point constant out of range");
		} else {
			tok_msg_bug(strtold_unknown, tokstart,
				"Unknown error returned by strtold");
		}
	}
	
	if (s != e) {
		tok_msg_error(floating_invalid_digits, tokstart,
			"Floating point constant contains invalid digits");
	}
	
	out->suffix =
		read_number_suffix(sn->suffix, sn->end, TOK_FLOATING, mq);
}