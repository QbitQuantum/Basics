int
dosave()
{
#ifdef KEEP_SAVE
	/*WAC for reloading*/
	register int fd;
#endif

	clear_nhwindow(WIN_MESSAGE);
	if(yn("Really save?") == 'n') {
		clear_nhwindow(WIN_MESSAGE);
		if(multi > 0) nomul(0);
	} else {
		clear_nhwindow(WIN_MESSAGE);
		pline("Saving...");
#if defined(UNIX) || defined(VMS) || defined(__EMX__)
		program_state.done_hup = 0;
#endif
#ifdef KEEP_SAVE
                saverestore = FALSE;
                if (flags.keep_savefile)
                        if(yn("Really quit?") == 'n') saverestore = TRUE;
                if(dosave0() && !saverestore) {
#else
		if(dosave0()) {
#endif
			program_state.something_worth_saving = 0;
			u.uhp = -1;		/* universal game's over indicator */
			/* make sure they see the Saving message */
			display_nhwindow(WIN_MESSAGE, TRUE);
			exit_nhwindows("Be seeing you...");
			terminate(EXIT_SUCCESS);
	}
/*WAC redraw later
		else (void)doredraw();*/
	}
#ifdef KEEP_SAVE
	if (saverestore) {
/*WAC pulled this from pcmain.c - restore game from the file just saved*/
		fd = create_levelfile(0);
		if (fd < 0) {
			raw_print("Cannot create lock file");
		} else {
			hackpid = 1;
			write(fd, (genericptr_t) &hackpid, sizeof(hackpid));
			close(fd);
		}
#ifdef MFLOPPY
		level_info[0].where = ACTIVE;
#endif

		fd = restore_saved_game();
		if (fd >= 0) dorecover(fd);
		check_special_room(FALSE);
		flags.move = 0;
/*WAC correct these after restore*/
		if(flags.moonphase == FULL_MOON)
			change_luck(1);         
		if(flags.friday13)
			change_luck(-1);
		if(iflags.window_inited)
			clear_nhwindow(WIN_MESSAGE);
	}
	saverestore = FALSE;
#endif
	(void)doredraw();
	return 0;
}


#if defined(UNIX) || defined(VMS) || defined (__EMX__) || defined(WIN32)
/*ARGSUSED*/
void
hangup(sig_unused)  /* called as signal() handler, so sent at least one arg */
int sig_unused;
{
# ifdef NOSAVEONHANGUP
	(void) signal(SIGINT, SIG_IGN);
	clearlocks();
#  ifndef VMS
	terminate(EXIT_FAILURE);
#  endif
# else	/* SAVEONHANGUP */
	if (!program_state.done_hup++) {
	    if (program_state.something_worth_saving)
		(void) dosave0();
#  ifdef VMS
	    /* don't call exit when already within an exit handler;
	       that would cancel any other pending user-mode handlers */
	    if (!program_state.exiting)
#  endif
	    {
		clearlocks();
		terminate(EXIT_FAILURE);
	    }
	}
# endif
	return;
}
#endif

/* returns 1 if save successful */
int
dosave0()
{
	const char *fq_save;
	register int fd, ofd;
	xchar ltmp;
	d_level uz_save;
	char whynot[BUFSZ];

	if (!SAVEF[0])
		return 0;
	fq_save = fqname(SAVEF, SAVEPREFIX, 1);	/* level files take 0 */

#if defined(UNIX) || defined(VMS)
	(void) signal(SIGHUP, SIG_IGN);
#endif
#ifndef NO_SIGNAL
	(void) signal(SIGINT, SIG_IGN);
#endif

#if defined(MICRO) && defined(MFLOPPY)
	if (!saveDiskPrompt(0)) return 0;
#endif

	HUP if (iflags.window_inited) {
	    uncompress_area(fq_save, SAVEF);
	    fd = open_savefile();
	    if (fd > 0) {
		(void) close(fd);
		clear_nhwindow(WIN_MESSAGE);
		There("seems to be an old save file.");
		if (yn("Overwrite the old file?") == 'n') {
		    compress_area(fq_save, SAVEF);
#ifdef KEEP_SAVE
/*WAC don't restore if you didn't save*/
			saverestore = FALSE;
#endif
		    return 0;
		}
	    }
	}

	HUP mark_synch();	/* flush any buffered screen output */

	fd = create_savefile();
	if(fd < 0) {
		HUP pline("Cannot open save file.");
		(void) delete_savefile();	/* ab@unido */
		return(0);
	}

	vision_recalc(2);	/* shut down vision to prevent problems
				   in the event of an impossible() call */
	
	/* undo date-dependent luck adjustments made at startup time */
	if(flags.moonphase == FULL_MOON)	/* ut-sally!fletcher */
		change_luck(-1);		/* and unido!ab */
	if(flags.friday13)
		change_luck(1);
	if(iflags.window_inited)
	    HUP clear_nhwindow(WIN_MESSAGE);

#if defined(MICRO) && defined(TTY_GRAPHICS)
	if (!strncmpi("tty", windowprocs.name, 3)) {
	dotcnt = 0;
	dotrow = 2;
	curs(WIN_MAP, 1, 1);
	  putstr(WIN_MAP, 0, "Saving:");
	}
#endif
#ifdef MFLOPPY
	/* make sure there is enough disk space */
	if (iflags.checkspace) {
	    long fds, needed;

	    savelev(fd, ledger_no(&u.uz), COUNT_SAVE);
	    savegamestate(fd, COUNT_SAVE);
	    needed = bytes_counted;

	    for (ltmp = 1; ltmp <= maxledgerno(); ltmp++)
		if (ltmp != ledger_no(&u.uz) && level_info[ltmp].where)
		    needed += level_info[ltmp].size + (sizeof ltmp);
	    fds = freediskspace(fq_save);
	    if (needed > fds) {
		HUP {
		    There("is insufficient space on SAVE disk.");
		    pline("Require %ld bytes but only have %ld.", needed, fds);
		}
		flushout();
		(void) close(fd);
		(void) delete_savefile();
		return 0;
	    }

	    co_false();
	}