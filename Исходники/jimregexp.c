/* 0 failure, 1 success */
static int regmatch(regex_t *preg, int prog)
{
	int scan;	/* Current node. */
	int next;		/* Next node. */

	scan = prog;

#ifdef DEBUG
	if (scan != 0 && regnarrate)
		fprintf(stderr, "%s(\n", regprop(scan));
#endif
	while (scan != 0) {
		int n;
		int c;
#ifdef DEBUG
		if (regnarrate) {
			fprintf(stderr, "%3d: %s...\n", scan, regprop(OP(preg, scan)));	/* Where, what. */
		}
#endif
		next = regnext(preg, scan);
		n = reg_utf8_tounicode_case(preg->reginput, &c, (preg->cflags & REG_ICASE));

		switch (OP(preg, scan)) {
		case BOL:
			if (preg->reginput != preg->regbol)
				return(0);
			break;
		case EOL:
			if (!reg_iseol(preg, c)) {
				return(0);
			}
			break;
		case WORDA:
			/* Must be looking at a letter, digit, or _ */
			if ((!isalnum(UCHAR(c))) && c != '_')
				return(0);
			/* Prev must be BOL or nonword */
			if (preg->reginput > preg->regbol &&
				(isalnum(UCHAR(preg->reginput[-1])) || preg->reginput[-1] == '_'))
				return(0);
			break;
		case WORDZ:
			/* Can't match at BOL */
			if (preg->reginput > preg->regbol) {
				/* Current must be EOL or nonword */
				if (reg_iseol(preg, c) || !isalnum(UCHAR(c)) || c != '_') {
					c = preg->reginput[-1];
					/* Previous must be word */
					if (isalnum(UCHAR(c)) || c == '_') {
						break;
					}
				}
			}
			/* No */
			return(0);

		case ANY:
			if (reg_iseol(preg, c))
				return 0;
			preg->reginput += n;
			break;
		case EXACTLY: {
				int opnd;
				int len;
				int slen;

				opnd = OPERAND(scan);
				len = str_int_len(preg->program + opnd);

				slen = prefix_cmp(preg->program + opnd, len, preg->reginput, preg->cflags & REG_ICASE);
				if (slen < 0) {
					return(0);
				}
				preg->reginput += slen;
			}
			break;
		case ANYOF:
			if (reg_iseol(preg, c) || reg_range_find(preg->program + OPERAND(scan), c) == 0) {
				return(0);
			}
			preg->reginput += n;
			break;
		case ANYBUT:
			if (reg_iseol(preg, c) || reg_range_find(preg->program + OPERAND(scan), c) != 0) {
				return(0);
			}
			preg->reginput += n;
			break;
		case NOTHING:
			break;
		case BACK:
			break;
		case BRANCH: {
				const char *save;

				if (OP(preg, next) != BRANCH)		/* No choice. */
					next = OPERAND(scan);	/* Avoid recursion. */
				else {
					do {
						save = preg->reginput;
						if (regmatch(preg, OPERAND(scan))) {
							return(1);
						}
						preg->reginput = save;
						scan = regnext(preg, scan);
					} while (scan != 0 && OP(preg, scan) == BRANCH);
					return(0);
					/* NOTREACHED */
				}
			}
			break;
		case REP:
		case REPMIN:
			return regmatchsimplerepeat(preg, scan, OP(preg, scan) == REPMIN);

		case REPX:
		case REPXMIN:
			return regmatchrepeat(preg, scan, OP(preg, scan) == REPXMIN);

		case END:
			return(1);	/* Success! */
			break;

		case OPENNC:
		case CLOSENC:
			if (regmatch(preg, next)) {
				return 1;
			}
			return 0;

		default:
			if (OP(preg, scan) >= OPEN+1 && OP(preg, scan) < CLOSE_END) {
				const char *save;

				save = preg->reginput;

				if (regmatch(preg, next)) {
					int no;
					/*
					 * Don't set startp if some later
					 * invocation of the same parentheses
					 * already has.
					 */
					if (OP(preg, scan) < CLOSE) {
						no = OP(preg, scan) - OPEN;
						if (no < preg->nmatch && preg->pmatch[no].rm_so == -1) {
							preg->pmatch[no].rm_so = save - preg->start;
						}
					}
					else {
						no = OP(preg, scan) - CLOSE;
						if (no < preg->nmatch && preg->pmatch[no].rm_eo == -1) {
							preg->pmatch[no].rm_eo = save - preg->start;
						}
					}
					return(1);
				} else
					return(0);
			}
			return REG_ERR_INTERNAL;
		}

		scan = next;
	}

	/*
	 * We get here only if there's trouble -- normally "case END" is
	 * the terminating point.
	 */
	return REG_ERR_INTERNAL;
}