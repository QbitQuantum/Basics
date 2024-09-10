void
dedtype(RING * gbl,
	char *name,
	int inlist,
	int binary,
	int stripped,
	int isdir)
{
    int had_eof;
    int c;
    int count,			/* ...and repeat-count */
      y,			/* current line-in-screen */
      shift = COLS / 4,		/* amount of left/right shift */
      done = FALSE, shown = FALSE, infile = -1;		/* # of lines processed */
    OFF_T skip = 0;

    tabstop = 8;
    Shift = 0;
    UsePattern = FALSE;
    OptBinary = binary;
    OptStripped = stripped;

    if (isdir && !OptBinary) {
	DIR *dp;
	DirentT *de;
	char bfr[MAXPATHLEN];
# define INO_FMT "%5lu"
	if ((InFile = tmpfile()) == 0) {
	    warn(gbl, "tmp-file");
	    return;
	}
	if ((dp = opendir(name)) != 0) {
	    while ((de = readdir(dp)) != NULL) {
		(void) ded2string(gbl, bfr,
				  (int) NAMLEN(de),
				  de->d_name,
				  FALSE);
		FPRINTF(InFile, INO_FMT, (unsigned long) de->d_ino);
		FPRINTF(InFile, " %s\n", bfr);
	    }
	    (void) closedir(dp);
	    rewind(InFile);
	} else {
	    warn(gbl, "opendir");
	    FCLOSE(InFile);
	    return;
	}
    } else
	InFile = fopen(name, "r");

    in_dedtype = TRUE;		/* disable clearing of workspace via A/a cmd */

    if (InFile) {
	int jump = 0;

	dlog_comment("type \"%s\" (%s %s)\n",
		     name,
		     OptBinary ? "binary" : "text",
		     isdir ? "directory" : "file");
	to_work(gbl, FALSE);

	dyn_init(&my_text, BUFSIZ);
	dyn_init(&my_over, BUFSIZ);

	max_lines = -1;
	MarkLine(&infile);

	while (!done) {

	    if (jump) {
#if defined(HAVE_WSCRL) && defined(HAVE_WSETSCRREG)
		/*
		 * If we're doing single-line scrolling past
		 * the point we've read in the file, try to
		 * cache pointers so that the scrolling logic
		 * will go more smoothly.
		 */
		if (jump > 0
		    && jump < NumP(1)
		    && infile + NumP(1) >= max_lines) {
		    int line = infile;
		    (void) StartPage(&line, TRUE, &had_eof);
		}
#endif
		(void) JumpBackwards(&infile, jump);
		jump = 0;
	    }

	    markC(gbl, TRUE);
	    y = StartPage(&infile, (int) skip, &had_eof);
	    if (skip && !was_interrupted) {
		if (feof(InFile)) {
		    skip = 0;
		    jump = NumP(1);
		} else {
		    IgnorePage(infile);
		    skip--;
		}
		continue;
	    }
	    if (had_eof) {
		int blank;
		infile = TopOfPage(infile, &blank);
		(void) JumpToLine(infile);
		y = StartPage(&infile, 0, &had_eof);
	    }
	    shown |= FinishPage(gbl, inlist, infile, y);
	    jump = NumP(1);

	    reset_catcher();
	    switch (c = dlog_char(gbl, &count, 1)) {
	    case CTL('K'):
		deddump(gbl);
		break;
	    case 'w':
		retouch(gbl, 0);
		break;
	    case '\t':
		if (OptBinary) {
		    beep();
		} else {
		    tabstop = (count <= 1)
			? (tabstop == 8 ? 4 : 8)
			: count;
		}
		break;

	    case 'q':
		done = TRUE;
		break;

	    case KEY_HOME:
	    case '^':
		jump = infile;
		break;

	    case KEY_END:
	    case '$':
		infile = max_lines;
		skip = MaxP();
		break;

	    case KEY_PPAGE:
	    case '\b':
	    case 'b':
		if (AtTop(infile)) {
		    beep();
		} else {
		    jump += NumP(count);
		}
		break;
	    case KEY_NPAGE:
	    case '\n':
	    case ' ':
	    case 'f':
		jump = 0;
		skip = count - 1;
		break;

	    case '<':
	    case CTL('L'):
		LeftOrRight(-shift * count);
		break;
	    case '>':
	    case CTL('R'):
		LeftOrRight(shift * count);
		break;

	    case KEY_LEFT:
	    case 'h':
		LeftOrRight(-count);
		break;
	    case KEY_DOWN:
	    case 'j':
		jump = NumP(1) - count;
		if ((infile - jump) > max_lines) {
		    skip = (-jump + NumP(1) - 1) / NumP(1);
		    jump = 0;
		}
		break;
	    case KEY_UP:
	    case 'k':
		if (AtTop(infile)) {
		    beep();
		} else {
		    jump += count;
		}
		break;
	    case KEY_RIGHT:
	    case 'l':
		LeftOrRight(count);
		break;

		/* move work-area marker */
	    case 'A':
		count = -count;
		jump -= count;
		/*FALLTHRU */
	    case 'a':
		markset(gbl, (unsigned) (mark_W + count));
		break;

	    case '/':
	    case '?':
	    case 'n':
	    case 'N':
		FindPattern(gbl, &infile, c);
		break;
	    default:
		beep();
	    }
	}
	FCLOSE(InFile);
	if (shown)
	    (void) reshow(gbl, (unsigned) inlist);
	showMARK(gbl->Xbase);

	showC(gbl);
    } else
	warn(gbl, name);
    in_dedtype = FALSE;
}