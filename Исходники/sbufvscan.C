int streambuf::vscan(char const *fmt0,
		     _G_va_list ap,
		     ios *stream /* = NULL */)
{
	register const u_char *fmt = (const u_char *)fmt0;
	register int c;		/* character from format, or conversion */
	register size_t width;	/* field width, or 0 */
	register char *p;	/* points into all kinds of strings */
	register int n;		/* handy integer */
	register int flags;	/* flags as defined above */
	register char *p0;	/* saves original value of p when necessary */
	int nassigned;		/* number of fields assigned */
	int nread;		/* number of characters consumed from fp */
	// Assignments to base and ccfn are just to suppress warnings from gcc.
	int base = 0;		/* base argument to strtol/strtoul */
	typedef u_long (*strtoulfn)(const char*, char**, int);
	strtoulfn ccfn = 0;
	// conversion function (strtol/strtoul)
	char ccltab[256];	/* character class table for %[...] */
	char buf[BUF];		/* buffer for numeric conversions */
	int seen_eof = 0;

	/* `basefix' is used to avoid `if' tests in the integer scanner */
	static short basefix[17] =
		{ 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	nassigned = 0;
	nread = 0;
	for (;;) {
		c = *fmt++;
		if (c == 0)
			goto done;
		if (isspace(c)) {
			for (;;) {
			        c = sbumpc();
				if (c == EOF)
				    goto eof_failure;
				if (!isspace(c)) {
				    sputbackc(c);
				    break;
				}
				nread++;
			}
			continue;
		}
		if (c != '%')
			goto literal;
		width = 0;
		flags = 0;
		/*
		 * switch on the format.  continue if done;
		 * break once format type is derived.
		 */
again:		c = *fmt++;
		switch (c) {
		case '%':
literal:
		        n = sbumpc();
			if (n == EOF)
			    goto eof_failure;
			if (n != c) {
			    sputbackc(n);
			    goto match_failure;
			}
			nread++;
			continue;

		case '*':
			flags |= SUPPRESS;
			goto again;
		case 'l':
			flags |= LONG;
			goto again;
		case 'L':
			flags |= LONGDBL;
			goto again;
		case 'h':
			flags |= SHORT;
			goto again;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			width = width * 10 + c - '0';
			goto again;

		/*
		 * Conversions.
		 * Those marked `compat' are for 4.[123]BSD compatibility.
		 *
		 * (According to ANSI, E and X formats are supposed
		 * to the same as e and x.  Sorry about that.)
		 */
		case 'D':	/* compat */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'd':
			c = CT_INT;
			ccfn = (strtoulfn)strtol;
			base = 10;
			break;

		case 'i':
			c = CT_INT;
			ccfn = (strtoulfn)strtol;
			base = 0;
			break;

		case 'O':	/* compat */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'o':
			c = CT_INT;
			ccfn = strtoul;
			base = 8;
			break;

		case 'u':
			c = CT_INT;
			ccfn = strtoul;
			base = 10;
			break;

		case 'X':
		case 'x':
			flags |= PFXOK;	/* enable 0x prefixing */
			c = CT_INT;
			ccfn = strtoul;
			base = 16;
			break;

#ifdef FLOATING_POINT
		case 'E': case 'F':
		case 'e': case 'f': case 'g':
			c = CT_FLOAT;
			break;
#endif

		case 's':
			c = CT_STRING;
			break;

		case '[':
			fmt = __sccl(ccltab, fmt);
			flags |= NOSKIP;
			c = CT_CCL;
			break;

		case 'c':
			flags |= NOSKIP;
			c = CT_CHAR;
			break;

		case 'p':	/* pointer format is like hex */
			flags |= POINTER | PFXOK;
			c = CT_INT;
			ccfn = strtoul;
			base = 16;
			break;

		case 'n':
			if (flags & SUPPRESS)	/* ??? */
				continue;
			if (flags & SHORT)
				*va_arg(ap, short *) = nread;
			else if (flags & LONG)
				*va_arg(ap, long *) = nread;
			else
				*va_arg(ap, int *) = nread;
			continue;

		/*
		 * Disgusting backwards compatibility hacks.	XXX
		 */
		case '\0':	/* compat */
		        nassigned = EOF;
			goto done;

		default:	/* compat */
			if (isupper(c))
				flags |= LONG;
			c = CT_INT;
			ccfn = (strtoulfn)strtol;
			base = 10;
			break;
		}

		/*
		 * We have a conversion that requires input.
		 */
		if (sgetc() == EOF)
			goto eof_failure;

		/*
		 * Consume leading white space, except for formats
		 * that suppress this.
		 */
		if ((flags & NOSKIP) == 0) {
		    n = (unsigned char)*_gptr;
		    while (isspace(n)) {
			_gptr++;
			nread++;
			n = sgetc();
			if (n == EOF)
			    goto eof_failure;
		    }
		    // Note that there is at least one character in
		    // the buffer, so conversions that do not set NOSKIP
		    // can no longer result in an input failure.
		}

		/*
		 * Do the conversion.
		 */
		switch (c) {

		case CT_CHAR:
			/* scan arbitrary characters (sets NOSKIP) */
			if (width == 0) // FIXME!
				width = 1;
			if (flags & SUPPRESS) {
			    size_t sum = 0;
			    for (;;) {
				if ((n = _egptr - _gptr) < (int)width) {
				    sum += n;
				    width -= n;
				    _gptr += n;
				    if (underflow() == EOF)
					if (sum == 0)
					    goto eof_failure;
					else {
					    seen_eof++;
					    break;
					}
				} else {
				    sum += width;
				    _gptr += width;
				    break;
				}
			    }
			    nread += sum;
			} else {
			    size_t r = sgetn((char*)va_arg(ap, char*),
						 width);
			    if (r != width)
				goto eof_failure;
			    nread += r;
			    nassigned++;
			}
			break;

		case CT_CCL:
			/* scan a (nonempty) character class (sets NOSKIP) */
			if (width == 0)
				width = ~0;	/* `infinity' */
			/* take only those things in the class */
			if (flags & SUPPRESS) {
				n = 0;
				while (ccltab[(unsigned char)*_gptr]) {
				    n++, _gptr++;
				    if (--width == 0)
					break;
				    if (sgetc() == EOF) {
					if (n == 0)
					    goto eof_failure;
					seen_eof++;
					break;
				    }
				}
				if (n == 0)
					goto match_failure;
			} else {
			    p0 = p = va_arg(ap, char *);
			    while (ccltab[(unsigned char)*_gptr]) {
				*p++ = *_gptr++;
				if (--width == 0)
				    break;
				if (sgetc() == EOF) {
				    if (p == p0)
					goto eof_failure;
				    seen_eof++;
				    break;
				}
			    }
			    n = p - p0;
			    if (n == 0)
				goto match_failure;
			    *p = 0;
			    nassigned++;
			}
			nread += n;
			break;

		case CT_STRING:
			/* like CCL, but zero-length string OK, & no NOSKIP */
			if (width == 0)
				width = ~0;
			if (flags & SUPPRESS) {
				n = 0;
				while (!isspace((unsigned char)*_gptr)) {
					n++, _gptr++;
					if (--width == 0)
						break;
					if (sgetc() == EOF) {
					    seen_eof++;
					    break;
					}
				}
				nread += n;
			} else {
				p0 = p = va_arg(ap, char *);
				while (!isspace((unsigned char)*_gptr)) {
					*p++ = *_gptr++;
					if (--width == 0)
						break;
					if (sgetc() == EOF) {
					    seen_eof++;
					    break;
					}
				}
				*p = 0;
				nread += p - p0;
				nassigned++;
			}
			continue;

		case CT_INT:
			/* scan an integer as if by strtol/strtoul */
			if (width == 0 || width > sizeof(buf) - 1)
				width = sizeof(buf) - 1;
			flags |= SIGNOK | NDIGITS | NZDIGITS;
			for (p = buf; width; width--) {
				c = (unsigned char)*_gptr;
				/*
				 * Switch on the character; `goto ok'
				 * if we accept it as a part of number.
				 */
				switch (c) {

				/*
				 * The digit 0 is always legal, but is
				 * special.  For %i conversions, if no
				 * digits (zero or nonzero) have been
				 * scanned (only signs), we will have
				 * base==0.  In that case, we should set
				 * it to 8 and enable 0x prefixing.
				 * Also, if we have not scanned zero digits
				 * before this, do not turn off prefixing
				 * (someone else will turn it off if we
				 * have scanned any nonzero digits).
				 */
				case '0':
					if (base == 0) {
						base = 8;
						flags |= PFXOK;
					}
					if (flags & NZDIGITS)
					    flags &= ~(SIGNOK|NZDIGITS|NDIGITS);
					else
					    flags &= ~(SIGNOK|PFXOK|NDIGITS);
					goto ok;

				/* 1 through 7 always legal */
				case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
					base = basefix[base];
					flags &= ~(SIGNOK | PFXOK | NDIGITS);
					goto ok;

				/* digits 8 and 9 ok iff decimal or hex */
				case '8': case '9':
					base = basefix[base];
					if (base <= 8)
						break;	/* not legal here */
					flags &= ~(SIGNOK | PFXOK | NDIGITS);
					goto ok;

				/* letters ok iff hex */
				case 'A': case 'B': case 'C':
				case 'D': case 'E': case 'F':
				case 'a': case 'b': case 'c':
				case 'd': case 'e': case 'f':
					/* no need to fix base here */
					if (base <= 10)
						break;	/* not legal here */
					flags &= ~(SIGNOK | PFXOK | NDIGITS);
					goto ok;

				/* sign ok only as first character */
				case '+': case '-':
					if (flags & SIGNOK) {
						flags &= ~SIGNOK;
						goto ok;
					}
					break;

				/* x ok iff flag still set & 2nd char */
				case 'x': case 'X':
					if (flags & PFXOK && p == buf + 1) {
						base = 16;	/* if %i */
						flags &= ~PFXOK;
						goto ok;
					}
					break;
				}

				/*
				 * If we got here, c is not a legal character
				 * for a number.  Stop accumulating digits.
				 */
				break;
		ok:
				/*
				 * c is legal: store it and look at the next.
				 */
				*p++ = c;
				_gptr++;
				if (sgetc() == EOF) {
				    seen_eof++;
				    break;		/* EOF */
				}
		        }
			/*
			 * If we had only a sign, it is no good; push
			 * back the sign.  If the number ends in `x',
			 * it was [sign] '0' 'x', so push back the x
			 * and treat it as [sign] '0'.
			 */
			if (flags & NDIGITS) {
				if (p > buf)
					(void) sputbackc(*(u_char *)--p);
				goto match_failure;
			}
			c = ((u_char *)p)[-1];
			if (c == 'x' || c == 'X') {
				--p;
				(void) sputbackc(c);
			}
			if ((flags & SUPPRESS) == 0) {
				u_long res;

				*p = 0;
				res = (*ccfn)(buf, (char **)NULL, base);
				if (flags & POINTER)
					*va_arg(ap, void **) = (void *)res;
				else if (flags & SHORT)
					*va_arg(ap, short *) = res;
				else if (flags & LONG)
					*va_arg(ap, long *) = res;
				else
					*va_arg(ap, int *) = res;
				nassigned++;
			}
			nread += p - buf;
			break;

#ifdef FLOATING_POINT
		case CT_FLOAT:
			/* scan a floating point number as if by strtod */
			if (width == 0 || width > sizeof(buf) - 1)
				width = sizeof(buf) - 1;
			flags |= SIGNOK | NDIGITS | DPTOK | EXPOK;
			for (p = buf; width; width--) {
				c = (unsigned char)*_gptr;
				/*
				 * This code mimicks the integer conversion
				 * code, but is much simpler.
				 */
				switch (c) {

				case '0': case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
				case '8': case '9':
					flags &= ~(SIGNOK | NDIGITS);
					goto fok;

				case '+': case '-':
					if (flags & SIGNOK) {
						flags &= ~SIGNOK;
						goto fok;
					}
					break;
				case '.':
					if (flags & DPTOK) {
						flags &= ~(SIGNOK | DPTOK);
						goto fok;
					}
					break;
				case 'e': case 'E':
					/* no exponent without some digits */
					if ((flags&(NDIGITS|EXPOK)) == EXPOK) {
						flags =
						    (flags & ~(EXPOK|DPTOK)) |
						    SIGNOK | NDIGITS;
						goto fok;
					}
					break;
				}
				break;
		fok:
				*p++ = c;
				_gptr++;
				if (sgetc() == EOF) {
				    seen_eof++;
				    break;	/* EOF */
				}
			}
			/*
			 * If no digits, might be missing exponent digits
			 * (just give back the exponent) or might be missing
			 * regular digits, but had sign and/or decimal point.
			 */
			if (flags & NDIGITS) {
				if (flags & EXPOK) {
					/* no digits at all */
					while (p > buf)
					    sputbackc(*(u_char *)--p);
					goto match_failure;
				}
				/* just a bad exponent (e and maybe sign) */
				c = *(u_char *)--p;
				if (c != 'e' && c != 'E') {
					(void)sputbackc(c);/* sign */
					c = *(u_char *)--p;
				}
				(void) sputbackc(c);
			}
			if ((flags & SUPPRESS) == 0) {
				double res;
				*p = 0;
#ifdef USE_DTOA
				res = strtod(buf, NULL);
#else
				res = atof(buf);
#endif
				if (flags & LONG)
					*va_arg(ap, double *) = res;
				else
					*va_arg(ap, float *) = res;
				nassigned++;
			}
			nread += p - buf;
			break;
#endif /* FLOATING_POINT */
		}
	}
eof_failure:
	seen_eof++;
input_failure:
	if (nassigned == 0)
	    nassigned = -1;
match_failure:
	if (stream)
	    stream->set(ios::failbit);
done:
	if (stream && seen_eof)
		stream->set(ios::eofbit);
	return (nassigned);
}