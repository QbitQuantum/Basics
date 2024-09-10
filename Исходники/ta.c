void
t_page(int n)	/* do whatever new page functions */
{
	int m, i;
	char buf[1024], *bp;

	pgnum[np++] = n;
	pgadr[np] = ftell(fp);
	if (np > npmax)
		npmax = np;
	if (output == 0) {
		output = in_olist(n);
		t_init(1);
		return;
	}
	/* have just printed something, and seen p<n> for next one */
	putpage();
	fflush(stdout);
	if (nowait)
		return;

  next:
	for (bp = buf; (*bp = readch()); )
		if (*bp++ == '\n' || bp >= &buf[sizeof buf - 1])
			break;
	*bp = 0;
	switch (buf[0]) {
	case 0:
		done();
		break;
	case '\n':
		output = in_olist(n);
		t_init(1);
		return;
	case '!':
		callunix(&buf[1]);
		fputs("!\n", stderr);
		break;
	case 'e':
		erase = 1 - erase;
		break;
	case 'w':
		wflag = 1 - wflag;
		break;
	case 'a':
		aspect = atof(&buf[1]);
		break;
	case '-':
	case 'p':
		m = atoi(&buf[1]) + 1;
		if (fp == stdin) {
			fputs("you can't; it's not a file\n", stderr);
			break;
		}
		if (np - m <= 0) {
			fputs("too far back\n", stderr);
			break;
		}
		np -= m;
		fseek(fp, pgadr[np], 0);
		output = 1;
		t_init(1);
		return;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		m = atoi(&buf[0]);
		for (i = 0; i < npmax; i++)
			if (m == pgnum[i])
				break;
		if (i >= npmax || fp == stdin) {
			fputs("you can't\n", stderr);
			break;
		}
		np = i + 1;
		fseek(fp, pgadr[np], 0);
		output = 1;
		t_init(1);
		return;
	case 'o':
		outlist(&buf[1]);
		output = 0;
		t_init(1);
		return;
	case '?':
		fputs("!cmd	unix cmd\n", stderr);
		fputs("p	print this page again\n", stderr);
		fputs("-n	go back n pages\n", stderr);
		fputs("n	print page n (previously printed)\n", stderr);
		fputs("o...	set the -o output list to ...\n", stderr);
		fputs("en	n=0 -> don't erase; n=1 -> erase\n", stderr);
		fputs("an	sets aspect ratio to n\n", stderr);
		break;
	default:
		fputs("?\n", stderr);
		break;
	}
	goto next;
}