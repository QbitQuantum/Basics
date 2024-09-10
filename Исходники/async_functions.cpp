int get_param(Lex& lex, Param *& p)
{
	const char *s, *e;
	int t, paren;
	p = 0;
	for(;;) {
		do {
			t = lex.GetToken();
		} while(isspace(t) || t == '\n');
		if(t == '\0') {
			return t;
		}
		if(t == ',' || t == ')') {
			if(p == 0) {
				if(t == ',') {
					fprintf(stderr, "%s:%ld: error: , not expected here\n", lex.Filename(), lex.Line());
					g_errcnt++;
				}
				return t;
			}
			break;
		}
		if(p == 0) {
			p = new Param;
		}

		if(t == '=') {
			break;
		}
		s = lex.GetStart();
		if(t == '(') {
			p->f_function = true;
			paren = 1;
			do {
				t = lex.GetToken();
				if(t == '(') {
					paren++;
				}
				else if(t == ')') {
					paren--;
				}
			} while(paren != 0 && t != '\0');
		}
		e = lex.GetEnd();

		p->AppendType(s, static_cast<int>(e - s));
	}

// if the type is just 'void' and t is ')' then we don't want it
	if(strcmp(p->f_type, "void") == 0) {
		if(t != ')') {
			fprintf(stderr, "%s:%ld: error: invalid usage of type void\n", lex.Filename(), lex.Line());
			g_errcnt++;
			return t;
		}
		delete p;
		p = 0;
		return t;
	}

// compute the name of the parameter
	p->DefineName();

// special case of default values
	if(t == '=') {
		do {
			t = lex.GetToken();
		} while(isspace(t) || t == '\n');
		if(t == '\0') {
			return t;
		}
		if(t == ',') {
			fprintf(stderr, "%s:%ld: error: default value missing for parameter %s\n", lex.Filename(), lex.Line(), p->f_type);
			g_errcnt++;
			return t;
		}
		s = lex.GetStart();
		do {
			e = lex.GetEnd();
			t = lex.GetToken();
		} while(t != ',' && t != ')' && t != '\0');
		if(t == '\0') {
			return t;
		}
		p->SetDefaultValue(s, static_cast<long>(e - s));
	}

	return t;
}