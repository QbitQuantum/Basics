static void
filegen_open(
	FILEGEN *	gen,
	uint32_t		stamp,
	const time_t *	pivot
	)
{
	char *savename;	/* temp store for name collision handling */
	char *fullname;	/* name with any designation extension */
	char *filename;	/* name without designation extension */
	char *suffix;	/* where to print suffix extension */
	u_int len, suflen;
	FILE *fp;
	struct calendar cal;
	struct isodate	iso;

	/* get basic filename in buffer, leave room for extensions */
	len = strlen(gen->dir) + strlen(gen->fname) + 65;
	filename = emalloc(len);
	fullname = emalloc(len);
	savename = NULL;
	snprintf(filename, len, "%s%s", gen->dir, gen->fname);

	/* where to place suffix */
	suflen = strlcpy(fullname, filename, len);
	suffix = fullname + suflen;
	suflen = len - suflen;

	/* last octet of fullname set to '\0' for truncation check */
	fullname[len - 1] = '\0';

	switch (gen->type) {

	default:
		msyslog(LOG_ERR, 
			"unsupported file generations type %d for "
			"\"%s\" - reverting to FILEGEN_NONE",
			gen->type, filename);
		gen->type = FILEGEN_NONE;
		break;

	case FILEGEN_NONE:
		/* no suffix, all set */
		break;

	case FILEGEN_PID:
		gen->id_lo = getpid();
		gen->id_hi = 0;
		snprintf(suffix, suflen, "%c#%ld",
			 SUFFIX_SEP, gen->id_lo);
		break;

	case FILEGEN_DAY:
		/*
		 * You can argue here in favor of using MJD, but I
		 * would assume it to be easier for humans to interpret
		 * dates in a format they are used to in everyday life.
		 */
		ntpcal_ntp_to_date(&cal, stamp, pivot);
		snprintf(suffix, suflen, "%c%04d%02d%02d",
			 SUFFIX_SEP, cal.year, cal.month, cal.monthday);
		cal.hour = cal.minute = cal.second = 0;
		gen->id_lo = ntpcal_date_to_ntp(&cal); 
		gen->id_hi = (uint32_t)(gen->id_lo + SECSPERDAY);
		break;

	case FILEGEN_WEEK:
		isocal_ntp_to_date(&iso, stamp, pivot);
		snprintf(suffix, suflen, "%c%04dw%02d",
			 SUFFIX_SEP, iso.year, iso.week);
		iso.hour = iso.minute = iso.second = 0;
		iso.weekday = 1;
		gen->id_lo = isocal_date_to_ntp(&iso);
		gen->id_hi = (uint32_t)(gen->id_lo + 7 * SECSPERDAY);
		break;

	case FILEGEN_MONTH:
		ntpcal_ntp_to_date(&cal, stamp, pivot);
		snprintf(suffix, suflen, "%c%04d%02d",
			 SUFFIX_SEP, cal.year, cal.month);
		cal.hour = cal.minute = cal.second = 0;
		cal.monthday = 1;
		gen->id_lo = ntpcal_date_to_ntp(&cal); 
		cal.month++;
		gen->id_hi = ntpcal_date_to_ntp(&cal); 
		break;

	case FILEGEN_YEAR:
		ntpcal_ntp_to_date(&cal, stamp, pivot);
		snprintf(suffix, suflen, "%c%04d",
			 SUFFIX_SEP, cal.year);
		cal.hour = cal.minute = cal.second = 0;
		cal.month = cal.monthday = 1;
		gen->id_lo = ntpcal_date_to_ntp(&cal); 
		cal.year++;
		gen->id_hi = ntpcal_date_to_ntp(&cal); 
		break;

	case FILEGEN_AGE:
		gen->id_lo = current_time - (current_time % SECSPERDAY);
		gen->id_hi = gen->id_lo + SECSPERDAY;
		snprintf(suffix, suflen, "%ca%08ld",
			 SUFFIX_SEP, gen->id_lo);
	}
  
	/* check possible truncation */
	if ('\0' != fullname[len - 1]) {
		fullname[len - 1] = '\0';
		msyslog(LOG_ERR, "logfile name truncated: \"%s\"",
			fullname);
	}

	if (FILEGEN_NONE != gen->type) {
		/*
		 * check for existence of a file with name 'basename'
		 * as we disallow such a file
		 * if FGEN_FLAG_LINK is set create a link
		 */
		struct stat stats;
		/*
		 * try to resolve name collisions
		 */
		static u_long conflicts = 0;

#ifndef	S_ISREG
#define	S_ISREG(mode)	(((mode) & S_IFREG) == S_IFREG)
#endif
		if (stat(filename, &stats) == 0) {
			/* Hm, file exists... */
			if (S_ISREG(stats.st_mode)) {
				if (stats.st_nlink <= 1)	{
					/*
					 * Oh, it is not linked - try to save it
					 */
					savename = emalloc(len);
					snprintf(savename, len,
						"%s%c%dC%lu",
						filename, SUFFIX_SEP,
						(int)getpid(), conflicts++);

					if (rename(filename, savename) != 0)
						msyslog(LOG_ERR,
							"couldn't save %s: %m",
							filename);
					free(savename);
				} else {
					/*
					 * there is at least a second link to
					 * this file.
					 * just remove the conflicting one
					 */
					/* coverity[toctou] */
					if (unlink(filename) != 0)
						msyslog(LOG_ERR, 
							"couldn't unlink %s: %m",
							filename);
				}
			} else {
				/*
				 * Ehh? Not a regular file ?? strange !!!!
				 */
				msyslog(LOG_ERR, 
					"expected regular file for %s "
					"(found mode 0%lo)",
					filename,
					(unsigned long)stats.st_mode);
			}
		} else {
			/*
			 * stat(..) failed, but it is absolutely correct for
			 * 'basename' not to exist
			 */
			if (ENOENT != errno)
				msyslog(LOG_ERR, "stat(%s) failed: %m",
						 filename);
		}
	}

	/*
	 * now, try to open new file generation...
	 */
	DPRINTF(4, ("opening filegen (type=%d/stamp=%u) \"%s\"\n",
		    gen->type, stamp, fullname));

	fp = fopen(fullname, "a");
  
	if (NULL == fp)	{
		/* open failed -- keep previous state
		 *
		 * If the file was open before keep the previous generation.
		 * This will cause output to end up in the 'wrong' file,
		 * but I think this is still better than losing output
		 *
		 * ignore errors due to missing directories
		 */

		if (ENOENT != errno)
			msyslog(LOG_ERR, "can't open %s: %m", fullname);
	} else {
		if (NULL != gen->fp) {
			fclose(gen->fp);
			gen->fp = NULL;
		}
		gen->fp = fp;

		if (gen->flag & FGEN_FLAG_LINK) {
			/*
			 * need to link file to basename
			 * have to use hardlink for now as I want to allow
			 * gen->basename spanning directory levels
			 * this would make it more complex to get the correct
			 * fullname for symlink
			 *
			 * Ok, it would just mean taking the part following
			 * the last '/' in the name.... Should add it later....
			 */

			/* Windows NT does not support file links -Greg Schueman 1/18/97 */

#if defined(SYS_WINNT)
			SetLastError(0); /* On WinNT, don't support FGEN_FLAG_LINK */
#else  /* not WINNT ; DO THE LINK) */
			if (link(fullname, filename) != 0)
				if (EEXIST != errno)
					msyslog(LOG_ERR, 
						"can't link(%s, %s): %m",
						fullname, filename);
#endif /* SYS_WINNT */
		}		/* flags & FGEN_FLAG_LINK */
	}			/* else fp == NULL */
	
	free(filename);
	free(fullname);
	return;
}