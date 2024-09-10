int
list(void)
{
	ARCHD *arcn;
	int res;
	time_t now;

	arcn = &archd;
	/*
	 * figure out archive type; pass any format specific options to the
	 * archive option processing routine; call the format init routine. We
	 * also save current time for ls_list() so we do not make a system
	 * call for each file we need to print. If verbose (vflag) start up
	 * the name and group caches.
	 */
	if ((get_arc() < 0) || ((*frmt->options)() < 0) ||
	    ((*frmt->st_rd)() < 0))
		return 1;

	now = time(NULL);

	/*
	 * step through the archive until the format says it is done
	 */
	while (next_head(arcn) == 0) {
		if (arcn->type == PAX_GLL || arcn->type == PAX_GLF) {
			/*
			 * we need to read, to get the real filename
			 */
			off_t cnt;
			if (!(*frmt->rd_data)(arcn, -arcn->type, &cnt))
				(void)rd_skip(cnt + arcn->pad);
			continue;
		}

		/*
		 * check for pattern, and user specified options match.
		 * When all patterns are matched we are done.
		 */
		if ((res = pat_match(arcn)) < 0)
			break;

		if ((res == 0) && (sel_chk(arcn) == 0)) {
			/*
			 * pattern resulted in a selected file
			 */
			if (pat_sel(arcn) < 0)
				break;

			/*
			 * modify the name as requested by the user if name
			 * survives modification, do a listing of the file
			 */
			if ((res = mod_name(arcn, RENM)) < 0)
				break;
			if (res == 0) {
				if (arcn->name[0] == '/' && !check_Aflag()) {
					memmove(arcn->name, arcn->name + 1, 
					    strlen(arcn->name));
				}
				ls_list(arcn, now, stdout);
			}
			/*
			 * if there's an error writing to stdout then we must
			 * stop now -- we're probably writing to a pipe that
			 * has been closed by the reader.
			 */
			if (ferror(stdout)) {
				syswarn(1, errno, "Listing incomplete.");
				break;
			}
		}
		/*
		 * skip to next archive format header using values calculated
		 * by the format header read routine
		 */
		if (rd_skip(arcn->skip + arcn->pad) == 1)
			break;
	}

	/*
	 * all done, let format have a chance to cleanup, and make sure that
	 * the patterns supplied by the user were all matched
	 */
	(void)(*frmt->end_rd)();
	(void)sigprocmask(SIG_BLOCK, &s_mask, NULL);
	ar_close();
	pat_chk();

	return 0;
}