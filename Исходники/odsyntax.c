static void
odoffset(int argc, char ***argvp)
{
	char *p, *num, *end;
	int base;

	/*
	 * The offset syntax of od(1) was genuinely bizarre.  First, if
	 * it started with a plus it had to be an offset.  Otherwise, if
	 * there were at least two arguments, a number or lower-case 'x'
	 * followed by a number makes it an offset.  By default it was
	 * octal; if it started with 'x' or '0x' it was hex.  If it ended
	 * in a '.', it was decimal.  If a 'b' or 'B' was appended, it
	 * multiplied the number by 512 or 1024 byte units.  There was
	 * no way to assign a block count to a hex offset.
	 *
	 * We assume it's a file if the offset is bad.
	 */
	p = argc == 1 ? (*argvp)[0] : (*argvp)[1];

	if (*p != '+' && (argc < 2 ||
	    (!isdigit(p[0]) && (p[0] != 'x' || !isxdigit(p[1])))))
		return;

	base = 0;
	/*
	 * skip over leading '+', 'x[0-9a-fA-f]' or '0x', and
	 * set base.
	 */
	if (p[0] == '+')
		++p;
	if (p[0] == 'x' && isxdigit(p[1])) {
		++p;
		base = 16;
	} else if (p[0] == '0' && p[1] == 'x') {
		p += 2;
		base = 16;
	}

	/* skip over the number */
	if (base == 16)
		for (num = p; isxdigit(*p); ++p);
	else
		for (num = p; isdigit(*p); ++p);

	/* check for no number */
	if (num == p)
		return;

	/* if terminates with a '.', base is decimal */
	if (*p == '.') {
		if (base)
			return;
		base = 10;
	}

	skip = strtoll(num, &end, base ? base : 8);

	/* if end isn't the same as p, we got a non-octal digit */
	if (end != p) {
		skip = 0;
		return;
	}

	if (*p) {
		if (*p == 'B') {
			skip *= 1024;
			++p;
		} else if (*p == 'b') {
			skip *= 512;
			++p;
		}
	}

	if (*p) {
		skip = 0;
		return;
	}

	/*
	 * If the offset uses a non-octal base, the base of the offset
	 * is changed as well.  This isn't pretty, but it's easy.
	 */
	if (base == 16) {
		fshead->nextfu->fmt[TYPE_OFFSET] = 'x';
		fshead->nextfs->nextfu->fmt[TYPE_OFFSET] = 'x';
	} else if (base == 10) {
		fshead->nextfu->fmt[TYPE_OFFSET] = 'd';
		fshead->nextfs->nextfu->fmt[TYPE_OFFSET] = 'd';
	}

	/* Terminate file list. */
	(*argvp)[1] = NULL;
}