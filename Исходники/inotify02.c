int main(int ac, char **av)
{
	int lc;			/* loop counter */
	char *msg;		/* message returned from parse_opts */

	/*
	 * parse standard options
	 */
	if ((msg = parse_opts(ac, av, NULL, NULL)) != NULL)
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);

	/*
	 * perform global setup for test
	 */
	setup();

	/*
	 * check looping state if -c option given
	 */
	for (lc = 0; TEST_LOOPING(lc); lc++) {

		Tst_count = 0;

		/*
		 * generate sequence of events
		 */
		if (chmod(".", 0755) < 0) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "chmod(\".\", 0755) failed");
		}
		event_set[Tst_count].mask = IN_ISDIR | IN_ATTRIB;
		strcpy(event_set[Tst_count].name, "");
		Tst_count++;

		if ((fd = creat(FILE_NAME1, 0755)) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "creat(\"%s\", 755) failed",
				 FILE_NAME1);
		}

		event_set[Tst_count].mask = IN_CREATE;
		strcpy(event_set[Tst_count].name, FILE_NAME1);
		Tst_count++;
		event_set[Tst_count].mask = IN_OPEN;
		strcpy(event_set[Tst_count].name, FILE_NAME1);
		Tst_count++;

		if (close(fd) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "close(%s) failed", FILE_NAME1);
		}
		event_set[Tst_count].mask = IN_CLOSE_WRITE;
		strcpy(event_set[Tst_count].name, FILE_NAME1);
		Tst_count++;

		if (rename(FILE_NAME1, FILE_NAME2) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "rename(%s, %s) failed",
				 FILE_NAME1, FILE_NAME2);
		}
		event_set[Tst_count].mask = IN_MOVED_FROM;
		strcpy(event_set[Tst_count].name, FILE_NAME1);
		Tst_count++;
		event_set[Tst_count].mask = IN_MOVED_TO;
		strcpy(event_set[Tst_count].name, FILE_NAME2);
		Tst_count++;

		if (getcwd(fname1, BUF_SIZE) == NULL) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "getcwd(%p, %d) failed", fname1,
				 BUF_SIZE);
		}

		snprintf(fname2, BUF_SIZE, "%s.rename1", fname1);
		if (rename(fname1, fname2) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "rename(%s, %s) failed", fname1, fname2);
		}
		event_set[Tst_count].mask = IN_MOVE_SELF;
		strcpy(event_set[Tst_count].name, "");
		Tst_count++;

		if (unlink(FILE_NAME2) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "unlink(%s) failed", FILE_NAME2);
		}
		event_set[Tst_count].mask = IN_DELETE;
		strcpy(event_set[Tst_count].name, FILE_NAME2);
		Tst_count++;

		/*
		 * test that duplicate events will be coalesced into
		 * a single event. This test case should be last, that
		 * we can correct determine kernel bug which exist before
		 * 2.6.25. See comment below.
		 */
		snprintf(fname3, BUF_SIZE, "%s.rename2", fname1);
		if (rename(fname2, fname3) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "rename(%s, %s) failed", fname2, fname3);
		}

		if (rename(fname3, fname1) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "rename(%s, %s) failed", fname3, fname1);
		}
		event_set[Tst_count].mask = IN_MOVE_SELF;
		strcpy(event_set[Tst_count].name, "");
		Tst_count++;

		if (Tst_count != TST_TOTAL) {
			tst_brkm(TBROK, cleanup,
				 "Tst_count and TST_TOTAL are not equal");
		}

		Tst_count = 0;

		int len, i = 0, test_num = 0;
		if ((len = read(fd_notify, event_buf, EVENT_BUF_LEN)) == -1) {
			tst_brkm(TBROK|TERRNO, cleanup,
				 "read(%d, buf, %zu) failed",
				 fd_notify, EVENT_BUF_LEN);

		}

		while (i < len) {
			struct inotify_event *event;
			event = (struct inotify_event *)&event_buf[i];
			if (test_num >= TST_TOTAL) {
				if (tst_kvercmp(2, 6, 25) < 0
				    && event_set[TST_TOTAL - 1].mask ==
				    event->mask)
					tst_resm(TWARN,
						 "This may be kernel bug. "
						 "Before kernel 2.6.25, a kernel bug "
						 "meant that the kernel code that was "
						 "intended to coalesce successive identical "
						 "events (i.e., the two most recent "
						 "events could potentially be coalesced "
						 "if the older had not yet been read) "
						 "instead checked if the most recent event "
						 "could be coalesced with the oldest "
						 "unread event. This has been fixed by commit"
						 "1c17d18e3775485bf1e0ce79575eb637a94494a2.");
				tst_resm(TFAIL,
					 "get unnecessary event: "
					 "wd=%d mask=%x cookie=%u len=%u"
					 "name=\"%s\"", event->wd, event->mask,
					 event->cookie, event->len,
					 event->name);

			} else if ((event_set[test_num].mask == event->mask)
				   &&
				   (!strncmp
				    (event_set[test_num].name, event->name,
				     event->len))) {
				tst_resm(TPASS,
					 "get event: wd=%d mask=%x"
					 " cookie=%u len=%u name=\"%s\"",
					 event->wd, event->mask, event->cookie,
					 event->len, event->name);

			} else {
				tst_resm(TFAIL, "get event: wd=%d mask=%x "
					 "(expected %x) cookie=%u len=%u "
					 "name=\"%s\" (expected \"%s\") %d",
					 event->wd, event->mask,
					 event_set[test_num].mask,
					 event->cookie, event->len, event->name,
					 event_set[test_num].name,
					 strcmp(event_set[test_num].name,
						event->name));
			}
			test_num++;
			i += EVENT_SIZE + event->len;
		}

		for (; test_num < TST_TOTAL; test_num++) {
			tst_resm(TFAIL, "didn't get event: mask=%x ",
				 event_set[test_num].mask);
		}
	}

	/* cleanup and exit */
	cleanup();
	tst_exit();
}