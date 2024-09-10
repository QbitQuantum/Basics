int VDScriptInterpreter::Token() {
	static char hexdig[]="0123456789ABCDEF";
	char *s,c;

	if (tokhold) {
		int t = tokhold;
		tokhold = 0;
		return t;
	}

	do {
		c=*tokstr++;
	} while(c && isspace((unsigned char)c));

	if (!c) {
		--tokstr;

		return 0;
	}

	// C++ style comment?

	if (c=='/')
		if (tokstr[0]=='/') {
			while(*tokstr) ++tokstr;

			return 0;		// C++ comment
		} else
			return '/';

	// string?

	if (c=='"') {
		const char *s = tokstr;
		char *t;
		long len_adjust=0;

		while((c=*tokstr++) && c!='"') {
			if (c=='\\') {
				c = *tokstr++;
				if (!c) SCRIPT_ERROR(PARSE_ERROR);
				else {
					if (c=='x') {
						if (!isxdigit((unsigned char)tokstr[0]) || !isxdigit((unsigned char)tokstr[1]))
							SCRIPT_ERROR(PARSE_ERROR);
						tokstr+=2;
						len_adjust += 2;
					}
					++len_adjust;
				}
			}
		}

		tokslit = strheap.Allocate(tokstr - s - 1 - len_adjust);
		t = *tokslit;
		while(s<tokstr-1) {
			int val;

			c = *s++;

			if (c=='\\')
				switch(c=*s++) {
				case 'a': *t++='\a'; break;
				case 'b': *t++='\b'; break;
				case 'f': *t++='\f'; break;
				case 'n': *t++='\n'; break;
				case 'r': *t++='\r'; break;
				case 't': *t++='\t'; break;
				case 'v': *t++='\v'; break;
				case 'x':
					val = strchr(hexdig,toupper(s[0]))-hexdig;
					val = (val<<4) | (strchr(hexdig,toupper(s[1]))-hexdig);
					*t++ = val;
					s += 2;
					break;
				default:
					*t++ = c;
				}
			else
				*t++ = c;
		}
		*t=0;

		if (!c) --tokstr;

		return TOK_STRING;
	}

	// unescaped string?
	if ((c=='u' || c=='U') && *tokstr == '"') {
		const char *s = ++tokstr;

		while((c=*tokstr++) && c != '"')
			;

		if (!c) {
			--tokstr;
			SCRIPT_ERROR(PARSE_ERROR);
		}

		size_t len = tokstr - s - 1;

		const VDStringA strA(VDTextWToU8(VDTextAToW(s, len)));

		len = strA.size();

		tokslit = strheap.Allocate(len);
		memcpy(*tokslit, strA.data(), len);
		(*tokslit)[len] = 0;

		return TOK_STRING;
	}

	// look for variable/keyword

	if (isIdentFirstChar(c)) {
		s = szIdent;

		*s++ = c;
		while(isIdentNextChar(c = *tokstr++)) {
			if (s>=szIdent + MAX_IDENT_CHARS)
				SCRIPT_ERROR(IDENT_TOO_LONG);

			*s++ = c;
		}

		--tokstr;
		*s=0;

		if (!strcmp(szIdent, "declare"))
			return TOK_DECLARE;
		else if (!strcmp(szIdent, "true"))
			return TOK_TRUE;
		else if (!strcmp(szIdent, "false"))
			return TOK_FALSE;
		else if (!strcmp(szIdent, "int"))
			return TOK_INT;
		else if (!strcmp(szIdent, "long"))
			return TOK_LONG;
		else if (!strcmp(szIdent, "double"))
			return TOK_DOUBLE;

		return TOK_IDENT;
	}

	// test for number: decimal (123), octal (0123), or hexadecimal (0x123)

	if (isdigit((unsigned char)c)) {
		sint64 v = 0;

		if (c=='0' && tokstr[0] == 'x') {

			// hex (base 16)
			++tokstr;

			while(isxdigit((unsigned char)(c = *tokstr++))) {
				v = v*16 + (strchr(hexdig, toupper(c))-hexdig);
			}

		} else if (c=='0' && isdigit((unsigned char)tokstr[0])) {
			// octal (base 8)
			while((c=*tokstr++)>='0' && c<='7')
				v = v*8 + (c-'0');
		} else {
			// check for float
			const char *s = tokstr;
			while(*s) {
				if (*s == '.' || *s == 'e' || *s == 'E') {
					// It's a float -- parse and return.

					--tokstr;
					tokdval = strtod(tokstr, (char **)&tokstr);
					return TOK_DBLVAL;
				}

				if (!isdigit((unsigned char)*s))
					break;
				++s;
			}

			// decimal
			v = (c-'0');
			while(isdigit((unsigned char)(c=*tokstr++)))
				v = v*10 + (c-'0');
		}
		--tokstr;

		if (v > 0x7FFFFFFF) {
			toklval = v;
			return TOK_LONGVAL;
		} else {
			tokival = (int)v;
			return TOK_INTVAL;
		}
	}

	// test for symbols:
	//
	//	charset:	+-*/<>=!&|^[]~;%(),
	//	solitary:	+-*/<>=!&|^[]~;%(),
	//	extra:		!= <= >= == && ||
	//
	//	the '/' is handled above for comment handling

	if (c=='!')
		if (tokstr[0] == '=') { ++tokstr; return TOK_NOTEQ;  } else return '!';

	if (c=='<')
		if (tokstr[0] == '=') { ++tokstr; return TOK_LESSEQ; } else return '<';

	if (c=='>')
		if (tokstr[0] == '=') { ++tokstr; return TOK_GRTREQ; } else return '>';

	if (c=='=')
		if (tokstr[0] == '=') { ++tokstr; return TOK_EQUALS; } else return '=';

	if (c=='&')
		if (tokstr[0] == '&') { ++tokstr; return TOK_AND;    } else return '&';

	if (c=='|')
		if (tokstr[0] == '|') { ++tokstr; return TOK_OR;     } else return '|';

	if (strchr("+-*^[]~;%(),.",c))
		return c;

	SCRIPT_ERROR(PARSE_ERROR);
}