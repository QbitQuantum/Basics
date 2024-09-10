	static void	/* file processing function */
process(FILE *fid) {
	char line[MAXLINE+3], *s;

	for (;;) {
		++emess_dat.File_line;
		if (!(s = fgets(line, MAXLINE, fid)))
			break;
		if (!strchr(s, '\n')) { /* overlong line */
			int c;
			strcat(s, "\n");
			/* gobble up to newline */
			while ((c = fgetc(fid)) != EOF && c != '\n') ;
		}
		if (*s == tag) {
			fputs(line, stdout);
			continue;
		}
		phi1 = dmstor(s, &s);
		lam1 = dmstor(s, &s);
		if (inverse) {
			phi2 = dmstor(s, &s);
			lam2 = dmstor(s, &s);
			geod_inv();
		} else {
			al12 = dmstor(s, &s);
			geod_S = strtod(s, &s) * to_meter;
			geod_pre();
			geod_for();
		}
		if (!*s && (s > line)) --s; /* assumed we gobbled \n */
		if (pos_azi) {
			if (al12 < 0.) al12 += M_TWOPI;
			if (al21 < 0.) al21 += M_TWOPI;
		}
		if (fullout) {
			printLL(phi1, lam1); TAB;
			printLL(phi2, lam2); TAB;
			if (oform) {
				(void)printf(oform, al12 * RAD_TO_DEG); TAB;
				(void)printf(oform, al21 * RAD_TO_DEG); TAB;
				(void)printf(osform, geod_S * fr_meter);
			}  else {
				(void)fputs(rtodms(pline, al12, 0, 0), stdout); TAB;
				(void)fputs(rtodms(pline, al21, 0, 0), stdout); TAB;
				(void)printf(osform, geod_S * fr_meter);
			}
		} else if (inverse)
			if (oform) {
				(void)printf(oform, al12 * RAD_TO_DEG); TAB;
				(void)printf(oform, al21 * RAD_TO_DEG); TAB;
				(void)printf(osform, geod_S * fr_meter);
			} else {
				(void)fputs(rtodms(pline, al12, 0, 0), stdout); TAB;
				(void)fputs(rtodms(pline, al21, 0, 0), stdout); TAB;
				(void)printf(osform, geod_S * fr_meter);
			}
		else {
			printLL(phi2, lam2); TAB;
			if (oform)
				(void)printf(oform, al21 * RAD_TO_DEG);
			else
				(void)fputs(rtodms(pline, al21, 0, 0), stdout);
		}
		(void)fputs(s, stdout);
	}
}