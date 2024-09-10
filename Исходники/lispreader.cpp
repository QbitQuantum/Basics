LISPTR lisp_read(FILE* in)
{
	LISPTR s = NIL;
	wchar_t ch = fgetwc(in);
	while (iswspace(ch)) {
		ch = fgetwc(in);
	}
	if (ch == '(') {
		// start of cons
		LISPTR last = s = cons(lisp_read(in), NIL);
		while (true) {
			ch = fgetwc(in); while (iswspace(ch)) { ch = fgetwc(in); }
			if (ch==WEOF || ch==')') { break; }
			ungetwc(ch, in);
			LISPTR e = lisp_read(in);
			rplacd(last, cons(e, NIL));
			last = cdr(last);
		}
	} else if (ch == '\'') {
		// '<expr>, sugar for (QUOTE <expr>)
		s = cons(QUOTE, cons(lisp_read(in), NIL));
	} else if (ch == '#') {
		// so-called sharpsign or 'dispatching macro character'
		// http://www.lispworks.com/documentation/HyperSpec/Body/02_dh.htm
		ch = fgetwc(in);
		switch (ch) {
		case '\'':				// function-quote
			s = cons(FUNCTION, cons(lisp_read(in), NIL));
			break;
		default:
			lisp_error(L"invalid char after #");
			break;
		} // switch
	} else if (ch == WEOF) {
		// end of file, return NIL.
	} else {
		// must be an atom - number, symbol or string
		wchar_t name[MAX_ATOM_CHARS];
		int n = 0;
		while (true) {
			if (n < MAX_ATOM_CHARS) {
				name[n++] = towupper(ch);
			}
			ch = fgetwc(in);
			if (ch==WEOF) break;				// better not be inside a string, eh?
			if (name[0] != '"') {
				// not a string
				if (iswspace(ch)) break;
				if (ch==')' || ch=='(') {
					ungetwc(ch, in);
					break;
				}
			} else {
				// collecting a string
				if (ch=='\\') {
					ch = fgetwc(in);
					if (ch==WEOF) break;		// bad luck er bad string syntax
				} else if (ch=='"') {
					break;				// end of string
				}
			}
		} // while (true)
		name[n] = 0;
		if (name[0] == '"') {
			s = intern_string(name+1);
		} else if (isnumber(name)) {
			s = intern_number(name);
		} else {
			s = intern(name);
		}
	}
	return s;
}