void
do_objs(FILE *fp, const char *msg, int ext)
{
	register struct file_list *tp;
	register int lpos, len;
	char *cp;
	char och;
	const char *sp;
#if	DO_SWAPFILE
	register struct file_list *fl;
	char swapname[32];
#endif	/* DO_SWAPFILE */

	fprintf(fp, "%s", msg);
	lpos = strlen(msg);
	for (tp = ftab; tp != 0; tp = tp->f_next) {
		if (tp->f_type == INVISIBLE)
			continue;

		/*
		 *	Check for '.o' file in list
		 */
		cp = tp->f_fn + (len = strlen(tp->f_fn)) - 1;
		if ((ext == -1 && tp->f_flags & ORDERED) ||		/* not in objs */
		    (ext != -1 && *cp != ext))
			continue;
		else if (*cp == 'o') {
			if (len + lpos > 72) {
				lpos = 8;
				fprintf(fp, "\\\n\t");
			}
			put_source_file_name(fp, tp);
			fprintf(fp, " ");
			lpos += len + 1;
			continue;
		}
		sp = tail(tp->f_fn);
#if	DO_SWAPFILE
		for (fl = conf_list; fl; fl = fl->f_next) {
			if (fl->f_type != SWAPSPEC)
				continue;
			(void) sprintf(swapname, "swap%s.c", fl->f_fn);
			if (eq(sp, swapname))
				goto cont;
		}
#endif	/* DO_SWAPFILE */
		cp = (char *)sp + (len = strlen(sp)) - 1;
		och = *cp;
		*cp = 'o';
		if (len + lpos > 72) {
			lpos = 8;
			fprintf(fp, "\\\n\t");
		}
		fprintf(fp, "%s ", sp);
		lpos += len + 1;
		*cp = och;
#if	DO_SWAPFILE
cont:
		;
#endif	/* DO_SWAPFILE */
	}
	if (lpos != 8)
		putc('\n', fp);
}