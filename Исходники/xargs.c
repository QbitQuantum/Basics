static void
parse_input(int argc, char *argv[])
{
	int hasblank = 0;
	static int hadblank = 0;
	int ch, foundeof = 0;
	char **avj;

	ch = getchar();
	if (isblank(ch)) {
		/* Quotes escape tabs and spaces. */
		if (insingle || indouble)
			goto addch;
		hasblank = 1;
		if (zflag)
			goto addch;
		goto arg2;
	}

	switch (ch) {
	case EOF:
		/* No arguments since last exec. */
		if (p == bbp) {
			if (runeof)
				prerun(0, av);
			waitchildren(*argv, 1);
			exit(rval);
		}
		goto arg1;
	case '\0':
		if (zflag)
			goto arg2;
		goto addch;
	case '\n':
		hasblank = 1;
		if (hadblank == 0)
			count++;
		if (zflag)
			goto addch;

		/* Quotes do not escape newlines. */
arg1:		if (insingle || indouble)
			errx(1, "unterminated quote");
arg2:
		foundeof = *eofstr != '\0' &&
		    strcmp(argp, eofstr) == 0;

		/* Do not make empty args unless they are quoted */
		if ((argp != p || wasquoted) && !foundeof) {
			*p++ = '\0';
			*xp++ = argp;
			if (Iflag) {
				size_t curlen;

				if (inpline == NULL)
					curlen = 0;
				else {
					/*
					 * If this string is not zero
					 * length, append a space for
					 * separation before the next
					 * argument.
					 */
					if ((curlen = strlen(inpline)))
						strlcat(inpline, " ", inpsize);
				}
				curlen++;
				/*
				 * Allocate enough to hold what we will
				 * be holding in a second, and to append
				 * a space next time through, if we have
				 * to.
				 */
				inpsize = curlen + 2 + strlen(argp);
				inpline = realloc(inpline, inpsize);
				if (inpline == NULL)
					errx(1, "realloc failed");
				if (curlen == 1)
					strlcpy(inpline, argp, inpsize);
				else
					strlcat(inpline, argp, inpsize);
			}
		}

		/*
		 * If max'd out on args or buffer, or reached EOF,
		 * run the command.  If xflag and max'd out on buffer
		 * but not on args, object.  Having reached the limit
		 * of input lines, as specified by -L is the same as
		 * maxing out on arguments.
		 */
		if (xp == endxp || p > ebp || ch == EOF ||
		    (Lflag <= count && xflag) || foundeof) {
			if (xflag && xp != endxp && p > ebp)
				errx(1, "insufficient space for arguments");
			if (jfound) {
				for (avj = argv; *avj; avj++)
					*xp++ = *avj;
			}
			prerun(argc, av);
			if (ch == EOF || foundeof) {
				waitchildren(*argv, 1);
				exit(rval);
			}
			p = bbp;
			xp = bxp;
			count = 0;
		}
		argp = p;
		wasquoted = 0;
		break;
	case '\'':
		if (indouble || zflag)
			goto addch;
		insingle = !insingle;
		wasquoted = 1;
		break;
	case '"':
		if (insingle || zflag)
			goto addch;
		indouble = !indouble;
		wasquoted = 1;
		break;
	case '\\':
		if (zflag)
			goto addch;
		/* Backslash escapes anything, is escaped by quotes. */
		if (!insingle && !indouble && (ch = getchar()) == EOF)
			errx(1, "backslash at EOF");
		/* FALLTHROUGH */
	default:
addch:		if (p < ebp) {
			*p++ = ch;
			break;
		}

		/* If only one argument, not enough buffer space. */
		if (bxp == xp)
			errx(1, "insufficient space for argument");
		/* Didn't hit argument limit, so if xflag object. */
		if (xflag)
			errx(1, "insufficient space for arguments");

		if (jfound) {
			for (avj = argv; *avj; avj++)
				*xp++ = *avj;
		}
		prerun(argc, av);
		xp = bxp;
		cnt = ebp - argp;
		memcpy(bbp, argp, (size_t)cnt);
		p = (argp = bbp) + cnt;
		*p++ = ch;
		break;
	}
	hadblank = hasblank;
}