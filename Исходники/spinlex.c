Symbol *
prep_inline(Symbol *s, Lextok *nms)
{	int c, nest = 1, dln, firstchar, cnr;
	char *p;
	Lextok *t;
	static char Buf1[SOMETHINGBIG], Buf2[RATHERSMALL];
	static int c_code = 1;

	for (t = nms; t; t = t->rgt)
		if (t->lft)
		{	if (t->lft->ntyp != NAME)
			fatal("bad param to inline %s", s?s->name:"--");
			t->lft->sym->hidden |= 32;
		}

	if (!s)	/* C_Code fragment */
	{	s = (Symbol *) emalloc(sizeof(Symbol));
		s->name = (char *) emalloc(strlen("c_code")+26);
		sprintf(s->name, "c_code%d", c_code++);
		s->context = context;
		s->type = CODE_FRAG;
	} else
		s->type = PREDEF;

	p = &Buf1[0];
	Buf2[0] = '\0';
	for (;;)
	{	c = Getchar();
		switch (c) {
		case '[':
			if (s->type != CODE_FRAG)
				goto bad;
			precondition(&Buf2[0]);	/* e.g., c_code [p] { r = p-r; } */
			continue;
		case '{':
			break;
		case '\n':
			lineno++;
			/* fall through */
		case ' ': case '\t': case '\f': case '\r':
			continue;
		default :
			 printf("spin: saw char '%c'\n", c);
bad:			 fatal("bad inline: %s", s->name);
		}
		break;
	}
	dln = lineno;
	if (s->type == CODE_FRAG)
	{	if (verbose&32)
			sprintf(Buf1, "\t/* line %d %s */\n\t\t",
				lineno, Fname->name);
		else
			strcpy(Buf1, "");
	} else
		sprintf(Buf1, "\n#line %d \"%s\"\n{", lineno, Fname->name);
	p += strlen(Buf1);
	firstchar = 1;

	cnr = 1; /* not zero */
more:
	c = Getchar();
	*p++ = (char) c;
	if (p - Buf1 >= SOMETHINGBIG)
		fatal("inline text too long", 0);
	switch (c) {
	case '\n':
		lineno++;
		cnr = 0;
#if 0
		if (nest <= 0)
		{	*--p = '\0';
		}
#endif
		break;
	case '{':
		cnr++;
		nest++;
		break;
	case '}':
		cnr++;
		if (--nest <= 0)
		{	*p = '\0';
			if (s->type == CODE_FRAG)
				*--p = '\0';	/* remove trailing '}' */	
			def_inline(s, dln, &Buf1[0], &Buf2[0], nms);
			if (firstchar)
				printf("%3d: %s, warning: empty inline definition (%s)\n",
					dln, Fname->name, s->name);
			return s;	/* normal return */
		}
		break;
	case '#':
		if (cnr == 0)
		{	p--;
			do_directive(c); /* reads to newline */
		} else
		{	firstchar = 0;
			cnr++;
		}
		break;
	case '\t':
	case ' ':
	case '\f':
		cnr++;
		break;
	default:
		firstchar = 0;
		cnr++;
		break;
	}
	goto more;
}