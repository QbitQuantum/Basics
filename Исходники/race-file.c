/*
 * Modified	: 01.20.2002 Author	: Dark0n3
 *
 * Description	: Parses file entries from sfv file and store them in a file.
 *
 * Todo		: Add dupefile remover.
 *
 * Totally rewritten by js on 08.02.2005
 */
int
copysfv(const char *source, const char *target, struct VARS *raceI)
{
	int		infd, outfd, i, retval = 0;
	short int	music, rars, video, others, type;

	char		*ptr, fbuf[2048];
	FILE		*insfv;

	DIR		*dir;

	SFVDATA		sd;

//#if ( sfv_dupecheck == TRUE )
	int		skip = 0;
	SFVDATA		tempsd;
//#endif

#if ( sfv_cleanup == TRUE )
	int		tmpfd;
	char		crctmp[16];

	if ((tmpfd = open(".tmpsfv", O_CREAT | O_TRUNC | O_RDWR, 0644)) == -1)
		d_log("copysfv: open(.tmpsfv): %s\n", strerror(errno));
#endif

	if ((infd = open(source, O_RDONLY)) == -1) {
		d_log("copysfv: open(%s): %s\n", source, strerror(errno));
		remove_lock(raceI);
		exit(EXIT_FAILURE);
	}

	if ((outfd = open(target, O_CREAT | O_TRUNC | O_RDWR, 0666)) == -1) {
		d_log("copysfv: open(%s): %s\n", target, strerror(errno));
		remove_lock(raceI);
		exit(EXIT_FAILURE);
	}

	video = music = rars = others = type = 0;

	dir = opendir(".");

	if (!update_lock(raceI, 1, 0)) {
		d_log("copysfv: Lock is suggested removed. Will comply and exit\n");
		remove_lock(raceI);
		exit(EXIT_FAILURE);
	}

	if ((insfv = fdopen(infd, "r")) == NULL) {
		d_log("copysfv: Unable to fdopen %s: %s\n", source, strerror(errno));
		remove_lock(raceI);
		exit(EXIT_FAILURE);
	}

	while ((fgets(fbuf, sizeof(fbuf), insfv))) {

		/* remove comment */
		if ((ptr = find_first_of(fbuf, ";")))
			*ptr = '\0';

		tailstrip_chars(fbuf, WHITESPACE_STR);
		ptr = prestrip_chars(fbuf, WHITESPACE_STR);
		if (ptr != fbuf)
			d_log("copysfv: prestripped whitespaces (%d chars)\n", ptr - fbuf);

		if (strlen(ptr) == 0)
			continue;

#if (sfv_cleanup_lowercase == TRUE)
		for (; *ptr; ptr++)
			*ptr = tolower(*ptr);
#endif
		sd.crc32 = 0;
		bzero(sd.fname, sizeof(sd.fname));
		if ((ptr = find_last_of(fbuf, " \t"))) {

			/* pass the " \t" */
			ptr++;

			/* what we have now is hopefully a crc */
			for (i = 0; isxdigit(*ptr) != 0; i++)
				ptr++;

			ptr -= i;
			if (i > 8 || i < 6) {
				/* we didn't get an 8 digit crc number */
#if (sfv_cleanup == TRUE)
				/* do stuff  */
				d_log("copysfv: We did not get a 8 digit crc number for %s - trying to continue anyway\n", sd.fname);
#else
				retval = 1;
				goto END;
#endif
			} else {
				sd.crc32 = hexstrtodec(ptr);

				/* cut off crc string */
				*ptr = '\0';

				/* nobody should be stupid enough to have spaces
				 * at the end of the file name */
				tailstrip_chars(fbuf, WHITESPACE_STR);
			}

		} else {
			/* we have a filename only. */
#if (sfv_cleanup == TRUE)
			/* do stuff  */
			d_log("copysfv: We did not find a crc number for %s - trying to continue anyway\n", sd.fname);
#else
			retval = 1;
			goto END;
#endif
		}

		/* we assume what's left is a filename */
		ptr = prestrip_chars(fbuf, WHITESPACE_STR);
		if (ptr != fbuf)
			d_log("copysfv: prestripped whitespaces (%d chars)\n", ptr - fbuf);

#if (allow_slash_in_sfv == TRUE)
		if (ptr != find_last_of(ptr, "/")) {
			ptr = find_last_of(ptr, "/") + 1;
			d_log("copysfv: found '/' in filename - adjusting.\n");
		}
		if (ptr != find_last_of(ptr, "\\")) {
			ptr = find_last_of(ptr, "\\") + 1;
			d_log("copysfv: found '\\' in filename - adjusting.\n");
		}
#endif
		if (strlen(ptr) > 0 && strlen(ptr) < NAME_MAX-9 ) {
			strlcpy(sd.fname, ptr, NAME_MAX-9);

			if (sd.fname != find_last_of(sd.fname, "\t") || sd.fname != find_last_of(sd.fname, "\\") || sd.fname != find_last_of(sd.fname, "/")) {
				d_log("copysfv: found '/', '\\' or <TAB> as part of filename in sfv - logging file as bad.\n");
				retval = 1;
				break;
			}

			if (sd.crc32 == 0) {
#if (sfv_calc_single_fname == TRUE || create_missing_sfv == TRUE)
				sd.crc32 = match_lenient(dir, sd.fname);
				d_log("copysfv: Got filename (%s) without crc, calculated to %X.\n", sd.fname, sd.crc32);
#else
				d_log("copysfv: Got filename (%s) without crc - ignoring file.\n", sd.fname);
				continue;
#endif
			}


			/* get file extension */
			ptr = find_last_of(fbuf, ".");
			if (*ptr == '.')
				ptr++;

			if (!strcomp(ignored_types, ptr) && !(strcomp(allowed_types, ptr) && !matchpath(allowed_types_exemption_dirs, raceI->misc.current_path)) && !strcomp("sfv", ptr) && !strcomp("nfo", ptr)) {

				skip = 0;
//#if ( sfv_dupecheck == TRUE )
				/* read from sfvdata - no parsing */
				lseek(outfd, 0L, SEEK_SET);
				while (read(outfd, &tempsd, sizeof(SFVDATA)))
//					if (!strcmp(sd.fname, tempsd.fname) || (sd.crc32 == tempsd.crc32 && sd.crc32))
					if (!strcmp(sd.fname, tempsd.fname))
						skip = 1;

				lseek(outfd, 0L, SEEK_END);

#if ( sfv_dupecheck == TRUE )
				if (skip)
					continue;
#endif

				d_log("copysfv:  File in sfv: '%s' (%x)\n", sd.fname, sd.crc32);

#if ( sfv_cleanup == TRUE )
				/* write good stuff to .tmpsfv */
				if (tmpfd != -1) {
					sprintf(crctmp, "%.8x", sd.crc32);
					if (write(tmpfd, sd.fname, strlen(sd.fname)) != (int)strlen(sd.fname))
						d_log("copysfv: write failed: %s\n", strerror(errno));
					if (write(tmpfd, " ", 1) != 1)
						d_log("copysfv: write failed: %s\n", strerror(errno));
					if (write(tmpfd, crctmp, 8) != 8)
						d_log("copysfv: write failed: %s\n", strerror(errno));
#if (sfv_cleanup_crlf == TRUE )
					if (write(tmpfd, "\r", 1) != 1)
						d_log("copysfv: write failed: %s\n", strerror(errno));
#endif
					if (write(tmpfd, "\n", 1) != 1)
						d_log("copysfv: write failed: %s\n", strerror(errno));
				}
#endif

				if (strcomp(audio_types, ptr))
					music++;
				else if (israr(ptr))
					rars++;
				else if (strcomp(video_types, ptr))
					video++;
				else
					others++;

#if ( create_missing_files == TRUE )
				if (!findfile(dir, sd.fname) && !(matchpath(allowed_types_exemption_dirs, raceI->misc.current_path) && strcomp(allowed_types, ptr)))
					create_missing(sd.fname, raceI);
#endif

				if (write(outfd, &sd, sizeof(SFVDATA)) != sizeof(SFVDATA))
					d_log("copysfv: write failed: %s\n", strerror(errno));
			}
		}
	}

	if (music > rars) {
		if (video > music)
			type = (video >= others ? 4 : 2);
		else
			type = (music >= others ? 3 : 2);
	} else {
		if (video > rars)
			type = (video >= others ? 4 : 2);
		else
			type = (rars >= others ? 1 : 2);
	}

#if ( sfv_cleanup == FALSE )
END:
#endif
	close(infd);
#if ( sfv_cleanup == TRUE )
	if (tmpfd != -1) {
		close(tmpfd);
		unlink(source);
		rename(".tmpsfv", source);
#ifdef USING_EBFTPD
                if (ebftpd_chown(source, raceI->user.uid, raceI->user.gid) < 0)
                        d_log("copysfv: ebftpd_chown(%s,%i,%i): %s\n", source, raceI->user.uid, raceI->user.gid, strerror(errno));

#endif
	}
#endif

	closedir(dir);
	close(outfd);
	if (!update_lock(raceI, 1, type)) {
		d_log("copysfv: Lock is suggested removed. Will comply and exit\n");
		remove_lock(raceI);
		exit(EXIT_FAILURE);
	}
	raceI->data_type = type;
	return retval;
}