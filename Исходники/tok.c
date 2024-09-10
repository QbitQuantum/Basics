/*
	lexical analyzer for larn
 */
int
yylex(void)
{
	char cc;
	int ic;
	if (hit2flag) {
		hit2flag = 0;
		yrepcount = 0;
		return (' ');
	}
	if (yrepcount > 0) {
		--yrepcount;
		return (lastok);
	} else
		yrepcount = 0;
	if (yrepcount == 0) {
		bottomdo();
		showplayer();
	}			/* show where the player is */
	lflush();
	while (1) {
		c[BYTESIN]++;
		/* check for periodic checkpointing */
		if (ckpflag)
			if ((c[BYTESIN] % CHECKPOINT_INTERVAL) == 0) {
#ifndef DOCHECKPOINTS
				savegame(ckpfile);
#else
				wait(0);	/* wait for other forks to finish */
				if (fork() == 0) {
					savegame(ckpfile);
					exit(0);
				}
#endif
#ifdef TIMECHECK
				if (dayplay == 0)
					if (playable()) {
						cursor(1, 19);
						lprcat("\nSorry, but it is now time for work.  Your game has been saved.\n");
						beep();
						lflush();
						savegame(savefilename);
						wizard = nomove = 1;
						sleep(4);
						died(-257);
					}
#endif /* TIMECHECK */
			}

		do {		/* if keyboard input buffer is too big, flush some of it */
			ioctl(0, FIONREAD, &ic);
			if (ic > flushno)
				read(0, &cc, 1);
		} while (ic > flushno);

		if (read(0, &cc, 1) != 1)
			return (lastok = -1);

		if (cc == 'Y' - 64) {	/* control Y -- shell escape */
			resetscroll();
			clear();	/* scrolling region, home, clear, no attributes */
			if ((ic = fork()) == 0) {	/* child */
				/* revoke */
				setgid(getgid());
				execl("/bin/csh", "csh", NULL);
				exit(1);
			}
			wait(0);
			if (ic < 0) {	/* error */
				write(2, "Can't fork off a shell!\n", 25);
				sleep(2);
			}

			setscroll();
			return (lastok = 'L' - 64);	/* redisplay screen */
		}

		if ((cc <= '9') && (cc >= '0')) {
			yrepcount = yrepcount * 10 + cc - '0';
		} else {
			if (yrepcount > 0)
				--yrepcount;
			return (lastok = cc);
		}
	}
}