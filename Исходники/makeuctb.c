int main(int argc, char **argv)
{
    static const char *first_ifdefs[] =
    {
	"/*",
	" * Compile-in this chunk of code unless we've turned it off specifically",
	" * or in general (id=%s).",
	" */",
	"",
	"#ifndef INCL_CHARSET%s",
	"#define INCL_CHARSET%s 1",
	"",
	"/*ifdef NO_CHARSET*/",
	"#ifdef  NO_CHARSET",
	"#undef  NO_CHARSET",
	"#endif",
	"#define NO_CHARSET 0 /* force default to always be active */",
	"",
	"/*ifndef NO_CHARSET%s*/",
	"#ifndef NO_CHARSET%s",
	"",
	"#if    ALL_CHARSETS",
	"#define NO_CHARSET%s 0",
	"#else",
	"#define NO_CHARSET%s 1",
	"#endif",
	"",
	"#endif /* ndef(NO_CHARSET%s) */",
	"",
	"#if NO_CHARSET%s",
	"#define UC_CHARSET_SETUP%s /*nothing*/",
	"#else"
    };
    static const char *last_ifdefs[] =
    {
	"",
	"#endif /* NO_CHARSET%s */",
	"",
	"#endif /* INCL_CHARSET%s */"
    };

    FILE *ctbl;
    char buffer[65536];
    char *outname = 0;
    unsigned n;
    int fontlen;
    int i, nuni, nent;
    int fp0 = 0, fp1 = 0, un0, un1;
    char *p, *p1;
    char *tbuf, ch;

    if (argc < 2 || argc > 5) {
	usage();
    }

    if (!strcmp(argv[1], "-")) {
	ctbl = stdin;
	tblname = "stdin";
    } else {
	ctbl = fopen(tblname = argv[1], "r");
	if (!ctbl) {
	    perror(tblname);
	    done(EX_NOINPUT);
	}
    }

    if (argc > 2) {
	if (!strcmp(argv[2], "-")) {
	    chdr = stdout;
	    hdrname = "stdout";
	} else {
	    hdrname = argv[2];
	}
    } else if (ctbl == stdin) {
	chdr = stdout;
	hdrname = "stdout";
    } else if ((outname = (char *) malloc(strlen(tblname) + 3)) != 0) {
	strcpy(outname, tblname);
	hdrname = outname;
	if ((p = strrchr(outname, '.')) == 0)
	    p = outname + strlen(outname);
	strcpy(p, ".h");
    } else {
	perror("malloc");
	done(EX_NOINPUT);
    }

    if (chdr == 0) {
	chdr = fopen(hdrname, "w");
	if (!chdr) {
	    perror(hdrname);
	    done(EX_NOINPUT);
	}
    }

    /*
     *  For now we assume the default font is always 256 characters.
     */
    fontlen = 256;

    /*
     *  Initialize table.
     */
    for (i = 0; i < fontlen; i++) {
	unicount[i] = 0;
    }

    /*
     *  Now we comes to the tricky part.  Parse the input table.
     */
    while (fgets(buffer, sizeof(buffer), ctbl) != NULL) {
	if ((p = strchr(buffer, '\n')) != NULL) {
	    *p = '\0';
	} else {
	    fprintf(stderr,
		    "%s: Warning: line too long or incomplete.\n",
		    tblname);
	}

	/*
	 *  Syntax accepted:
	 *      <fontpos>       <unicode> <unicode> ...
	 *      <fontpos>       <unicode range> <unicode range> ...
	 *      <fontpos>       idem
	 *      <range>         idem
	 *      <range>         <unicode range>
	 *      <unicode>       :<replace>
	 *      <unicode range> :<replace>
	 *      <unicode>       "<C replace>"
	 *      <unicode range> "<C replace>"
	 *
	 *  where <range> ::= <fontpos>-<fontpos>
	 *  and <unicode> ::= U+<h><h><h><h>
	 *  and <h> ::= <hexadecimal digit>
	 *  and <replace> any string not containing '\n' or '\0'
	 *  and <C replace> any string with C backslash escapes.
	 */
	p = buffer;
	while (*p == ' ' || *p == '\t') {
	    p++;
	}
	if (!(*p) || *p == '#') {
	    /*
	     *  Skip comment or blank line.
	     */
	    continue;
	}

	switch (*p) {
	    /*
	     *  Raw Unicode?  I.e. needs some special
	     *  processing.  One digit code.
	     */
	case 'R':
	    if (p[1] == 'a' || p[1] == 'A') {
		buffer[sizeof(buffer) - 1] = '\0';
		if (!strncasecomp(p, "RawOrEnc", 8)) {
		    p += 8;
		}
	    }
	    p++;
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    RawOrEnc = strtol(p, 0, 10);
	    Raw_found = 1;
	    continue;

	    /*
	     *  Is this the default table?
	     */
	case 'D':
	    if (p[1] == 'e' || p[1] == 'E') {
		buffer[sizeof(buffer) - 1] = '\0';
		if (!strncasecomp(p, "Default", 7)) {
		    p += 7;
		}
	    }
	    p++;
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    this_isDefaultMap = (*p == '1' || TOLOWER(*p) == 'y');
	    continue;

	    /*
	     *  Is this the default table?
	     */
	case 'F':
	    if (p[1] == 'a' || p[1] == 'A') {
		buffer[sizeof(buffer) - 1] = '\0';
		if (!strncasecomp(p, "FallBack", 8)) {
		    p += 8;
		}
	    }
	    p++;
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    useDefaultMap = (*p == '1' || TOLOWER(*p) == 'y');
	    continue;

	case 'M':
	    if (p[1] == 'i' || p[1] == 'I') {
		buffer[sizeof(buffer) - 1] = '\0';
		if (!strncasecomp(p, "MIMEName", 8)) {
		    p += 8;
		}
	    }
	    p++;
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    sscanf(p, "%40s", this_MIMEcharset);
	    continue;

	    /*
	     *  Display charset name for options screen.
	     */
	case 'O':
	    if (p[1] == 'p' || p[1] == 'P') {
		buffer[sizeof(buffer) - 1] = '\0';
		if (!strncasecomp(p, "OptionName", 10)) {
		    p += 10;
		}
	    }
	    p++;
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    for (i = 0; *p && i < UC_MAXLEN_LYNXCSNAME; p++, i++) {
		this_LYNXcharset[i] = *p;
	    }
	    this_LYNXcharset[i] = '\0';
	    continue;

	    /*
	     *  Codepage number.  Three or four digit code.
	     */
	case 'C':
	    if (p[1] == 'o' || p[1] == 'O') {
		buffer[sizeof(buffer) - 1] = '\0';
		if (!strncasecomp(p, "CodePage", 8)) {
		    p += 8;
		}
	    }
	    p++;
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    CodePage = strtol(p, 0, 10);
	    continue;
	}

	if (*p == 'U') {
	    un0 = getunicode(&p);
	    if (un0 < 0) {
		fprintf(stderr, "Bad input line: %s\n", buffer);
		done(EX_DATAERR);
		fprintf(stderr,
			"%s: Bad Unicode range corresponding to font position range 0x%x-0x%x\n",
			tblname, fp0, fp1);
		done(EX_DATAERR);
	    }
	    un1 = un0;
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    if (*p == '-') {
		p++;
		while (*p == ' ' || *p == '\t') {
		    p++;
		}
		un1 = getunicode(&p);
		if (un1 < 0 || un1 < un0) {
		    fprintf(stderr,
			    "%s: Bad Unicode range U+%x-U+%x\n",
			    tblname, un0, un1);
		    fprintf(stderr, "Bad input line: %s\n", buffer);
		    done(EX_DATAERR);
		}
		while (*p == ' ' || *p == '\t') {
		    p++;
		}
	    }

	    if (*p != ':' && *p != '"') {
		fprintf(stderr, "No ':' or '\"' where expected: %s\n",
			buffer);
		continue;
	    }

	    /*
	     * Allocate a string large enough for the worst-case use in the
	     * loop using sprintf.
	     */
	    tbuf = (char *) malloc(5 * strlen(p));

	    if (!(p1 = tbuf)) {
		fprintf(stderr, "%s: Out of memory\n", tblname);
		done(EX_DATAERR);
	    }
	    if (*p == '"') {
		/*
		 *  Handle "<C replace>".
		 *  Copy chars verbatim until first '"' not \-escaped or
		 *  end of buffer.
		 */
		int escaped = 0;

		for (ch = *(++p); (ch = *p) != '\0'; p++) {
		    if (escaped) {
			escaped = 0;
		    } else if (ch == '"') {
			break;
		    } else if (ch == '\\') {
			escaped = 1;
		    }
		    *p1++ = ch;
		}
		if (escaped || ch != '"') {
		    fprintf(stderr, "Warning: String not terminated: %s\n",
			    buffer);
		    if (escaped)
			*p1++ = '\n';
		}
	    } else {
		/*
		 *  We had ':'.
		 */
		for (ch = *(++p); (ch = *p) != '\0'; p++, p1++) {
		    if (UCH(ch) < 32 || ch == '\\' || ch == '\"' ||
			UCH(ch) >= 127) {
			sprintf(p1, "\\%.3o", UCH(ch));
			p1 += 3;
		    } else {
			*p1 = ch;
		    }
		}
	    }
	    *p1 = '\0';
	    for (i = un0; i <= un1; i++) {
		addpair_str(tbuf, i);
	    }
	    continue;
	}

	/*
	 *  Input line (after skipping spaces) doesn't start with one
	 *  of the specially recognized characters, so try to interpret
	 *  it as starting with a fontpos.
	 */
	fp0 = strtol(p, &p1, 0);
	if (p1 == p) {
	    fprintf(stderr, "Bad input line: %s\n", buffer);
	    done(EX_DATAERR);
	}
	p = p1;

	while (*p == ' ' || *p == '\t') {
	    p++;
	}
	if (*p == '-') {
	    p++;
	    fp1 = strtol(p, &p1, 0);
	    if (p1 == p) {
		fprintf(stderr, "Bad input line: %s\n", buffer);
		done(EX_DATAERR);
	    }
	    p = p1;
	} else {
	    fp1 = 0;
	}

	if (fp0 < 0 || fp0 >= fontlen) {
	    fprintf(stderr,
		    "%s: Glyph number (0x%x) larger than font length\n",
		    tblname, fp0);
	    done(EX_DATAERR);
	}
	if (fp1 && (fp1 < fp0 || fp1 >= fontlen)) {
	    fprintf(stderr,
		    "%s: Bad end of range (0x%x)\n",
		    tblname, fp1);
	    done(EX_DATAERR);
	}

	if (fp1) {
	    /*
	     *  We have a range; expect the word "idem"
	     *  or a Unicode range of the same length.
	     */
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    if (!strncmp(p, "idem", 4)) {
		for (i = fp0; i <= fp1; i++) {
		    addpair(i, i);
		}
		p += 4;
	    } else {
		un0 = getunicode(&p);
		while (*p == ' ' || *p == '\t') {
		    p++;
		}
		if (*p != '-') {
		    fprintf(stderr,
			    "%s: Corresponding to a range of font positions,",
			    tblname);
		    fprintf(stderr,
			    " there should be a Unicode range.\n");
		    done(EX_DATAERR);
		}
		p++;
		un1 = getunicode(&p);
		if (un0 < 0 || un1 < 0) {
		    fprintf(stderr,
			    "%s: Bad Unicode range corresponding to font position range 0x%x-0x%x\n",
			    tblname, fp0, fp1);
		    done(EX_DATAERR);
		}
		if (un1 - un0 != fp1 - fp0) {
		    fprintf(stderr,
			    "%s: Unicode range U+%x-U+%x not of the same length",
			    tblname, un0, un1);
		    fprintf(stderr,
			    " as font position range 0x%x-0x%x\n",
			    fp0, fp1);
		    done(EX_DATAERR);
		}
		for (i = fp0; i <= fp1; i++) {
		    addpair(i, un0 - fp0 + i);
		}
	    }
	} else {
	    /*
	     *  No range; expect a list of unicode values
	     *  or unicode ranges for a single font position,
	     *  or the word "idem"
	     */
	    while (*p == ' ' || *p == '\t') {
		p++;
	    }
	    if (!strncmp(p, "idem", 4)) {
		addpair(fp0, fp0);
		p += 4;
	    }
	    while ((un0 = getunicode(&p)) >= 0) {
		addpair(fp0, un0);
		while (*p == ' ' || *p == '\t') {
		    p++;
		}
		if (*p == '-') {
		    p++;
		    un1 = getunicode(&p);
		    if (un1 < un0) {
			fprintf(stderr,
				"%s: Bad Unicode range 0x%x-0x%x\n",
				tblname, un0, un1);
			done(EX_DATAERR);
		    }
		    for (un0++; un0 <= un1; un0++) {
			addpair(fp0, un0);
		    }
		}
	    }
	}
	while (*p == ' ' || *p == '\t') {
	    p++;
	}
	if (*p && *p != '#') {
	    fprintf(stderr, "%s: trailing junk (%s) ignored\n", tblname, p);
	}
    }

    /*
     *  Okay, we hit EOF, now output tables.
     */
    fclose(ctbl);

    /*
     *  Compute total size of Unicode list.
     */
    nuni = 0;
    for (i = 0; i < fontlen; i++) {
	nuni += unicount[i];
    }

    if (argc > 3) {
	strncpy(this_MIMEcharset, argv[3], UC_MAXLEN_MIMECSNAME);
    } else if (this_MIMEcharset[0] == '\0') {
	strncpy(this_MIMEcharset, tblname, UC_MAXLEN_MIMECSNAME);
	if ((p = strchr(this_MIMEcharset, '.')) != 0) {
	    *p = '\0';
	}
    }
    for (p = this_MIMEcharset; *p; p++) {
	*p = TOLOWER(*p);
    }
    if (argc > 4) {
	strncpy(this_LYNXcharset, argv[4], UC_MAXLEN_LYNXCSNAME);
    } else if (this_LYNXcharset[0] == '\0') {
	strncpy(this_LYNXcharset, this_MIMEcharset, UC_MAXLEN_LYNXCSNAME);
    }

    if (this_isDefaultMap == -1) {
	this_isDefaultMap = !strncmp(this_MIMEcharset, "iso-8859-1", 10);
    }
    fprintf(stderr,
	    "makeuctb: %s: %stranslation map",
	    this_MIMEcharset, (this_isDefaultMap ? "default " : ""));
    if (this_isDefaultMap == 1) {
	*id_append = '\0';
    } else {
	for (i = 0, p = this_MIMEcharset;
	     *p && (i < UC_MAXLEN_ID_APPEND - 1);
	     p++, i++) {
	    id_append[i + 1] = isalnum(UCH(*p)) ? *p : '_';
	}
	id_append[i + 1] = '\0';
    }
    fprintf(stderr, " (%s).\n", id_append);

    for (n = 0; n < TABLESIZE(first_ifdefs); n++) {
	fprintf(chdr, first_ifdefs[n], id_append);
	fprintf(chdr, "\n");
    }

    fprintf(chdr, "\n\
/*\n\
 *  uni_hash.tbl\n\
 *\n\
 *  Do not edit this file; it was automatically generated by\n\
 *\n\
 *  %s %s\n\
 *\n\
 */\n\
\n\
static const u8 dfont_unicount%s[%d] = \n\
{\n\t", argv[0], argv[1], id_append, fontlen);

    for (i = 0; i < fontlen; i++) {
	if (i >= 128 && unicount[i] > 0 && i < lowest_eight) {
	    lowest_eight = i;
	}
	fprintf(chdr, "%3d", unicount[i]);
	if (i == (fontlen - 1)) {
	    fprintf(chdr, "\n};\n");
	} else if ((i % 8) == 7) {
	    fprintf(chdr, ",\n\t");
	} else {
	    fprintf(chdr, ", ");
	}
    }

    /*
     *  If lowest_eightbit is anything else but 999,
     *  this can't be 7-bit only.
     */
    if (lowest_eight != 999 && !RawOrEnc) {
	RawOrEnc = UCT_ENC_8BIT;
    }

    if (nuni) {
	fprintf(chdr, "\nstatic const u16 dfont_unitable%s[%d] = \n{\n\t",
		id_append, nuni);
    } else {
	fprintf(chdr,
		"\nstatic const u16 dfont_unitable%s[1] = {0}; /* dummy */\n", id_append);
    }

    fp0 = 0;
    nent = 0;
    for (i = 0; i < nuni; i++) {
	while (nent >= unicount[fp0]) {
	    fp0++;
	    nent = 0;
	}
	fprintf(chdr, "0x%04x", unitable[fp0][nent++]);
	if (i == (nuni - 1)) {
	    fprintf(chdr, "\n};\n");
	} else if ((i % 8) == 7) {
	    fprintf(chdr, ",\n\t");
	} else {
	    fprintf(chdr, ", ");
	}
    }

    if (themap_str.entry_ct) {
	fprintf(chdr, "\n\
static struct unipair_str repl_map%s[%d] = \n\
{\n\t", id_append, themap_str.entry_ct);
    } else {
	fprintf(chdr, "\n\
/* static struct unipair_str repl_map%s[]; */\n", id_append);
    }

    for (i = 0; i < themap_str.entry_ct; i++) {
	fprintf(chdr, "{0x%x,\"%s\"}",
		themap_str.entries[i].unicode,
		themap_str.entries[i].replace_str);
	if (i == (themap_str.entry_ct - 1)) {
	    fprintf(chdr, "\n};\n");
	} else if ((i % 4) == 3) {
	    fprintf(chdr, ",\n\t");
	} else {
	    fprintf(chdr, ", ");
	}
    }
    if (themap_str.entry_ct) {
	fprintf(chdr, "\n\
static const struct unimapdesc_str dfont_replacedesc%s = {%d,repl_map%s,",
		id_append, themap_str.entry_ct, id_append);
    } else {