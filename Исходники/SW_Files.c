void SW_F_read(const char *s) {
	/* =================================================== */
	/* enter with the name of the first file to read for
	 * the filenames, or NULL.  If null, then read files.in
	 * or whichever filename was set previously. see init().
	 *
	 * 1/24/02 - replaced [re]alloc with StrDup()
	 *         - added facility for log-to-file. logfp depends
	 *             on having executed SW_F_read().
	 */

	FILE *f;
	int lineno = 0, fileno = 0;
	char buf[FILENAME_MAX];

	if (!isnull(s))
		init(s); /* init should be run by SW_F_Construct() */

	MyFileName = SW_F_name(eFirst);
	f = OpenFile(MyFileName, "r");

	while (GetALine(f, inbuf)) {

		switch (lineno) {
		case 5:
			strcpy(weather_prefix, inbuf);
			break;
		case 12:
			strcpy(output_prefix, inbuf);
			break;

		default:
			if (++fileno == SW_NFILES)
				break;

			if (!isnull(InFiles[fileno]))
				Mem_Free(InFiles[fileno]);
			strcpy(buf, _ProjDir);
			strcat(buf, inbuf);
			InFiles[fileno] = Str_Dup(buf);
		}

		lineno++;
	}

	if (fileno < eEndFile - 1) {
		CloseFile(&f);
		LogError(stdout, LOGFATAL, "Too few files (%d) in %s", fileno, MyFileName);
	}

	CloseFile(&f);

#if !defined(STEPWAT) && !defined(RSOILWAT)
	if (0 == strcmp(InFiles[eLog], "stdout")) {
		logfp = stdout;
	} else if (0 == strcmp(InFiles[eLog], "stderr")) {
		logfp = stderr;
	} else {
		logfp = OpenFile(SW_F_name(eLog), "w");
	}
#endif

}