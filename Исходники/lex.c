int
yylex(void)
{
	int c, r;
	char c1;
	Sym *s;

genblock:
	if(block != nblock){
		if(block > nblock){
			if(debug)
				fprint(2, "%s %d -> %d\n", ty(Tend), block, nblock);
			block--;
			return Tend;
		}else{
			if(debug)
				fprint(2, "%s %d -> %d\n", ty(Tbegin), block, nblock);
			block++;
			return Tbegin;
		}
	}

	c = GETC();
	if(c == Beof){
		nblock = 0;
		if(block != nblock)
			goto genblock;
		return 0;
	}
	UNGETC(c);

	switch(state){
	case Head0:			/* [%type] string */
		c = GETC();
		if(c != '%'){
			UNGETC(c);
			setstate(Body0);
			goto genblock;
		}
		r = readname(" \t");
		if(r == Terror)
			return fail(Head2);

		s = lookup(s_to_c(sbuf));
		yylval.sym = s;
		if(debug)
			fprint(2, "Sym[%s] %s\n", ty(s->type), s->name);
		setstate(Head1);
		return s->type;

	case Head1:			/* %type [string] */
		r = readstr("\n", " \t", 0);
		if(r == Terror)
			return fail(Head2);
		yylval.s = estrdup(s_to_c(sbuf));
		if(debug)
			fprint(2, "%s %q\n", ty(Tstring), yylval.s);
		setstate(Head2);
		return Tstring;

	case Head2:
		skip(" \t");
		c = GETC();
		assert(c == '\n' || c == Beof);
		setstate(Head0);
		return ';';

	case Body0:			/* [indent] cmd inline */
		c = GETC();
		if(c == '%'){
			UNGETC(c);
			setstate(Head0);
			goto genblock;
		}
		UNGETC(c);

		r = skip(" \t");
		c = GETC();
		if(c == '\n'){
			if(debug)
				fprint(2, "%s\n", ty(Tbreak));
			return Tbreak;
		}
		UNGETC(c);

		nblock = r;
		setstate(Body1);
		goto genblock;

	case Body1:			/* indent [cmd] inline */
		switch(c = GETC()){
		case Beof:
			yyerror("eof in body");
			if(debug)
				fprint(2, "%s\n", ty(Terror));
			return fail(Body3);
		case '=':
		case '\\':
		case '+':
		case '*':
		case ':':
		case '-':
		case '>':
			if(debug)
				fprint(2, "%c\n", c);
			setstate(Body2);
			return c;
		case '!':
			if(debug)
				fprint(2, "%c\n", c);
			setstate(Code);
			return c;
		case '{':
		case '}':
			if(debug)
				fprint(2, "%c\n", c);
			setstate(Body3);
			return c;
		case '#':
			if(debug)
				fprint(2, "%c\n", c);
			setstate(ID);
			return c;
		case '.':
			if(debug)
				fprint(2, "%c\n", c);
			setstate(Class);
			return c;
		case '|':
			if(debug)
				fprint(2, "%c\n", c);
			setstate(Table);
			return c;
		default:
			UNGETC(c);
			if(debug)
				fprint(2, "\\\n");
			setstate(Body2);
			return '\\';
		}

	case Body2:			/* indent cmd [inline] */
	case Table:
		r = skip(" \t");
		if(state == Table && r > 0)
			return ',';

		switch(c = getcc(&c1, "*[]|<>")){
		case Beof:
			yyerror("eof in body");
			if(debug)
				fprint(2, "%s\n", ty(Terror));
			return fail(Body3);
		case '\n':
			UNGETC(c);
			setstate(Body3);
			break;
		case '*':
		case '[':
		case ']':
		case '|':
		case '<':
		case '>':
			if(c == '[' || c == '|' || c == '<')
				skip(" \t\n");
			if(debug)
				fprint(2, "%c\n", c);
			return c;
		default:
			s_reset(sbuf);
			s_putc(sbuf, c1);
			while((c=getcc(&c1, "*[]|<>")) == 0){
				if(state == Table && c1 == '\t'){
					UNGETC(c);
					break;
				}
				s_putc(sbuf, c1);
			}
			s_terminate(sbuf);
			if(c > 0)
				UNGETC(c);
			yylval.s = estrdup(s_to_c(sbuf));
			if(debug)
				fprint(2, "%s %q\n", ty(Tstring), yylval.s);
			return Tstring;
		}

	case Body3:
		skip(" \t");
		c = GETC();
		if(c != '\n')
			return fail(Body3);
		setstate(Body0);
		return ';';

	case Code:
		r = readstr("\n", "", 1);
		if(r == Terror){
			if(debug)
				fprint(2, "%s\n", ty(Terror));
			return fail(Body3);
		}
		setstate(Body3);
		yylval.s = estrdup(s_to_c(sbuf));
		if(debug)
			fprint(2, "%s %q\n", ty(Tstring), yylval.s);
		return Tstring;

	case ID:
	case Class:
		r = readname(" \t");
		if(r == Terror){
			if(debug)
				fprint(2, "%s\n", ty(Terror));
			return fail(Body3);
		}
		setstate(Body3);
		yylval.s = estrdup(s_to_c(sbuf));
		if(debug)
			fprint(2, "%s %q\n", ty(Tstring), yylval.s);
		return Tstring;

	default:
		assert(0);
		return Terror;
	}
}