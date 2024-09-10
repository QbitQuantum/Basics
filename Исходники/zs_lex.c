static z_token lex_scan(z_lexstate *ls)
{
	if(ls->cur.eof) {
		lex_save(ls);
		return lex_newToken(ls, T_EOF, 0);
	}

	if(isWhite(nc)) {
		while(isWhite(nc)) {
			if(isNewLine(nc)) {
				lex_scanNewLine(ls);
				return lex_newToken(ls, T_NL, tk_generic);
			}
			else
				lex_nextchar(ls);
		}
		return lex_scan(ls);
	}

	/* line comment */
	if(nc == '/') {
		if(nnc == '/') {
			while(!isNewLine(nc))
				lex_nextchar(ls);
			return lex_scan(ls);
		}
	}

	/* multi line comment */
	if(nc == '/') {
		if(nnc == '*') {
			lex_nextchar(ls);
			lex_nextchar(ls);
			for(;;) {
				if(ls->cur.eof) {
					syntaxError(ls, "unterminated comment reached end of file");
					break;
				}
				else if(nc == '*') {
					lex_nextchar(ls);
					if(nc == '/') {
						lex_nextchar(ls);
						return lex_scan(ls);
					}
				}
				else if(isNewLine(nc)) {
					lex_scanNewLine(ls);
				}
				else
					lex_nextchar(ls);
			}
		}
	}

	lex_save(ls);

	/* numerical constants */
	if(isDigit(nc)) {
parse_number:
		while(isDigit(nc))
			lex_nextchar(ls);
		if(nc == '.') {
			lex_nextchar(ls);
			while(isDigit(nc))
				lex_nextchar(ls);
			if(nc == '.')
				syntaxError(ls, "invalid numerical constant");
		}
		return lex_newToken(ls, T_NUMBER, tk_numeric);
	}

	/* identifiers */
	else if(isAlpha(nc)) {
parse_ident:
		while(isAlNum(nc) || nc == '_')
			lex_nextchar(ls);
		
		/* check if it matches a keyword token */
		z_token tk = lex_newToken(ls, T_IDENT, tk_identifier);
		lex_matchKeyword(ls, &tk);

		return tk;
	}

	/* string literals */
	else if(nc == '"' || nc == '\''){
//parse_string:
		char q = nc;
		lex_nextchar(ls);
		while(nc != q) {
			if(ls->cur.eof) {
				syntaxError(ls, "unterminated string literal reached end of file");
				break;
			}
			/* skip escaped chars */
			if(nc == '\\') {
				lex_nextchar(ls);
				continue;
			}
			if(isNewLine(nc)) {
				lex_scanNewLine(ls);
			}
			lex_nextchar(ls);
		}
		lex_nextchar(ls);	// skip the closing cc
		return lex_newToken(ls, T_STRING, tk_string);
	}

	/* other multi char tokens */
	switch(nc)
	{
		case '.':	// may be numeric?
			lex_nextchar(ls);
			if(isDigit(nc))
				goto parse_number;
			return lex_newToken(ls, '.', 0);
		case '_':	// may be ident?
			lex_nextchar(ls);
			if(isAlNum(nc))
				goto parse_ident;
			return lex_newToken(ls, '_', 0);
		case '+':
			lex_nextchar(ls);
			if(nc == '+') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_INC, tk_op);
			}
			else if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_AA, tk_op);
			}
			return lex_newToken(ls, '+', tk_op);
		case '-':
			lex_nextchar(ls);
			if(nc == '-') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_DEC, tk_op);
			}
			else if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_SA, tk_op);
			}
			return lex_newToken(ls, '-', tk_op);
		case '*':
			lex_nextchar(ls);
			if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_MA, tk_op);
			}
			return lex_newToken(ls, '*', tk_op);
		case '/':
			lex_nextchar(ls);
			if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_DA, tk_op);
			}
			return lex_newToken(ls, '/', tk_op);
		case '>':
			lex_nextchar(ls);
			if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_GTE, tk_op);
			}
			return lex_newToken(ls, '>', tk_op);
		case '<':
			lex_nextchar(ls);
			if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_LTE, tk_op);
			}
			else if(nc == '>') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_NE, tk_op);
			}
			return lex_newToken(ls, '<', tk_op);
		case '=':
			lex_nextchar(ls);
			if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_EQ, tk_op);
			}
			return lex_newToken(ls, '=', tk_op);
		case '&':
			lex_nextchar(ls);
			if(nc == '&') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_AND, tk_op);
			}
			return lex_newToken(ls, '&', tk_op);
		case '|':
			lex_nextchar(ls);
			if(nc == '|') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_OR, tk_op);
			}
			return lex_newToken(ls, '|', tk_op);
		case '^':
			lex_nextchar(ls);
			if(nc == '^') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_XOR, tk_op);
			}
			return lex_newToken(ls, '^', tk_op);
		case '!':
			lex_nextchar(ls);
			return lex_newToken(ls, T_NOT, tk_op);
		case ':':
			lex_nextchar(ls);
			if(nc == '=') {
				lex_nextchar(ls);
				return lex_newToken(ls, T_DE, tk_op);
			}
			return lex_newToken(ls, ':', 0);
	}

	char c = nc;
	lex_nextchar(ls);

	return lex_newToken(ls, c, 0);
}