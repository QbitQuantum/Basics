int x_rsne(cilist *a)
{
	int ch, got1, k, n, nd, quote, readall;
	Namelist *nl;
	static char where[] = "namelist read";
	char buf[64];
	hashtab *ht;
	Vardesc *v;
	dimen *dn, *dn0, *dn1;
	ftnlen *dims, *dims1;
	ftnlen b, b0, b1, ex, no, nomax, size, span;
	ftnint no1, no2, type;
	char *vaddr;
	long iva, ivae;
	dimen dimens[MAXDIM], substr;

	if (!Alpha['a'])
		nl_init();
	f__reading=1;
	f__formatted=1;
	got1 = 0;
 top:
	for(;;) switch(GETC(ch)) {
		case EOF:
 eof:
			err(a->ciend,(EOF),where0);
		case '&':
		case '$':
			goto have_amp;
#ifndef No_Namelist_Questions
		case '?':
			print_ne(a);
			continue;
#endif
		default:
			if (ch <= ' ' && ch >= 0)
				continue;
#ifndef No_Namelist_Comments
			while(GETC(ch) != '\n')
				if (ch == EOF)
					goto eof;
#else
			errfl(a->cierr, 115, where0);
#endif
		}
 have_amp:
	if (ch = getname(buf,sizeof(buf)))
		return ch;
	nl = (Namelist *)a->cifmt;
	if (strcmp(buf, nl->name))
#ifdef No_Bad_Namelist_Skip
		errfl(a->cierr, 118, where0);
#else
	{
		fprintf(stderr,
			"Skipping namelist \"%s\": seeking namelist \"%s\".\n",
			buf, nl->name);
		fflush(stderr);
		for(;;) switch(GETC(ch)) {
			case EOF:
				err(a->ciend, EOF, where0);
			case '/':
			case '&':
			case '$':
				if (f__external)
					e_rsle();
				else
					z_rnew();
				goto top;
			case '"':
			case '\'':
				quote = ch;
 more_quoted:
				while(GETC(ch) != quote)
					if (ch == EOF)
						err(a->ciend, EOF, where0);
				if (GETC(ch) == quote)
					goto more_quoted;
				Ungetc(ch,f__cf);
			default:
				continue;
			}
		}
#endif
	ht = mk_hashtab(nl);
	if (!ht)
		errfl(f__elist->cierr, 113, where0);
	for(;;) {
		for(;;) switch(GETC(ch)) {
			case EOF:
				if (got1)
					return 0;
				err(a->ciend, EOF, where0);
			case '/':
			case '$':
			case '&':
				return 0;
			default:
				if (ch <= ' ' && ch >= 0 || ch == ',')
					continue;
				Ungetc(ch,f__cf);
				if (ch = getname(buf,sizeof(buf)))
					return ch;
				goto havename;
			}
 havename:
		v = hash(ht,buf);
		if (!v)
			errfl(a->cierr, 119, where);
		while(GETC(ch) <= ' ' && ch >= 0);
		vaddr = v->addr;
		type = v->type;
		if (type < 0) {
			size = -type;
			type = TYCHAR;
			}
		else
			size = f__typesize[type];
		ivae = size;
		iva = readall = 0;
		if (ch == '(' /*)*/ ) {
			dn = dimens;
			if (!(dims = v->dims)) {
				if (type != TYCHAR)
					errfl(a->cierr, 122, where);
				if (k = getdimen(&ch, dn, (ftnlen)size,
						(ftnlen)size, &b))
					errfl(a->cierr, k, where);
				if (ch != ')')
					errfl(a->cierr, 115, where);
				b1 = dn->extent;
				if (--b < 0 || b + b1 > size)
					return 124;
				iva += b;
				size = b1;
				while(GETC(ch) <= ' ' && ch >= 0);
				goto scalar;
				}
			nd = (int)dims[0];
			nomax = span = dims[1];
			ivae = iva + size*nomax;
			colonseen = 0;
			if (k = getdimen(&ch, dn, size, nomax, &b))
				errfl(a->cierr, k, where);
			no = dn->extent;
			b0 = dims[2];
			dims1 = dims += 3;
			ex = 1;
			for(n = 1; n++ < nd; dims++) {
				if (ch != ',')
					errfl(a->cierr, 115, where);
				dn1 = dn + 1;
				span /= *dims;
				if (k = getdimen(&ch, dn1, dn->delta**dims,
						span, &b1))
					errfl(a->cierr, k, where);
				ex *= *dims;
				b += b1*ex;
				no *= dn1->extent;
				dn = dn1;
				}
			if (ch != ')')
				errfl(a->cierr, 115, where);
			readall = 1 - colonseen;
			b -= b0;
			if (b < 0 || b >= nomax)
				errfl(a->cierr, 125, where);
			iva += size * b;
			dims = dims1;
			while(GETC(ch) <= ' ' && ch >= 0);
			no1 = 1;
			dn0 = dimens;
			if (type == TYCHAR && ch == '(' /*)*/) {
				if (k = getdimen(&ch, &substr, size, size, &b))
					errfl(a->cierr, k, where);
				if (ch != ')')
					errfl(a->cierr, 115, where);
				b1 = substr.extent;
				if (--b < 0 || b + b1 > size)
					return 124;
				iva += b;
				b0 = size;
				size = b1;
				while(GETC(ch) <= ' ' && ch >= 0);
				if (b1 < b0)
					goto delta_adj;
				}
			if (readall)
				goto delta_adj;
			for(; dn0 < dn; dn0++) {
				if (dn0->extent != *dims++ || dn0->stride != 1)
					break;
				no1 *= dn0->extent;
				}
			if (dn0 == dimens && dimens[0].stride == 1) {
				no1 = dimens[0].extent;
				dn0++;
				}
 delta_adj:
			ex = 0;
			for(dn1 = dn0; dn1 <= dn; dn1++)
				ex += (dn1->extent-1)
					* (dn1->delta *= dn1->stride);
			for(dn1 = dn; dn1 > dn0; dn1--) {
				ex -= (dn1->extent - 1) * dn1->delta;
				dn1->delta -= ex;
				}
			}
		else if (dims = v->dims) {
			no = no1 = dims[1];
			ivae = iva + no*size;
			}
		else
 scalar:
			no = no1 = 1;
		if (ch != '=')
			errfl(a->cierr, 115, where);
		got1 = nml_read = 1;
		f__lcount = 0;
	 readloop:
		for(;;) {
			if (iva >= ivae || iva < 0) {
				f__lquit = 1;
				goto mustend;
				}
			else if (iva + no1*size > ivae)
				no1 = (ivae - iva)/size;
			f__lquit = 0;
			if (k = l_read(&no1, vaddr + iva, size, type))
				return k;
			if (f__lquit == 1)
				return 0;
			if (readall) {
				iva += dn0->delta;
				if (f__lcount > 0) {
					no2 = (ivae - iva)/size;
					if (no2 > f__lcount)
						no2 = f__lcount;
					if (k = l_read(&no2, vaddr + iva,
							size, type))
						return k;
					iva += no2 * dn0->delta;
					}
				}
 mustend:
			GETC(ch);
			if (readall)
				if (iva >= ivae)
					readall = 0;
				else for(;;) {
					switch(ch) {
						case ' ':
						case '\t':
						case '\n':
							GETC(ch);
							continue;
						}
					break;
					}
			if (ch == '/' || ch == '$' || ch == '&') {
				f__lquit = 1;
				return 0;
				}
			else if (f__lquit) {
				while(ch <= ' ' && ch >= 0)
					GETC(ch);
				Ungetc(ch,f__cf);
				if (!Alpha[ch & 0xff] && ch >= 0)
					errfl(a->cierr, 125, where);
				break;
				}
			Ungetc(ch,f__cf);
			if (readall && !Alpha[ch & 0xff])
				goto readloop;
			if ((no -= no1) <= 0)
				break;
			for(dn1 = dn0; dn1 <= dn; dn1++) {
				if (++dn1->curval < dn1->extent) {
					iva += dn1->delta;
					goto readloop;
					}
				dn1->curval = 0;
				}
			break;
			}
		}
}