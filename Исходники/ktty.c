int termIoctl(Inode *inode, File *fp, uint64_t cmd, void *argp)
{
	Thread *target = NULL;
	Thread *scan;
	int pgid;
	struct termios *tc = (struct termios*) argp;
	TermWinSize *winsz = (TermWinSize*) argp;
	
	switch (cmd)
	{
	case IOCTL_TTY_GETATTR:
		memcpy(tc, &termState, sizeof(struct termios));
		return 0;
	case IOCTL_TTY_SETATTR:
		termState.c_iflag = tc->c_iflag;
		termState.c_oflag = tc->c_oflag;
		termState.c_cflag = tc->c_cflag;
		termState.c_lflag = tc->c_lflag;
		return 0;
	case IOCTL_TTY_GETPGID:
		*((int*)argp) = termGroup;
		return 0;
	case IOCTL_TTY_SETPGID:
		if (getCurrentThread()->creds->sid != 1)
		{
			ERRNO = ENOTTY;
			return -1;
		};
		pgid = *((int*)argp);
		cli();
		lockSched();
		scan = getCurrentThread();
		do
		{
			if (scan->creds != NULL)
			{
				if (scan->creds->pgid == pgid)
				{
					target = scan;
					break;
				};
			};
			
			scan = scan->next;
		} while (scan != getCurrentThread());
		if (target == NULL)
		{
			unlockSched();
			sti();
			ERRNO = EPERM;
			return -1;
		};
		if (target->creds->sid != 1)
		{
			unlockSched();
			sti();
			ERRNO = EPERM;
			return -1;
		};
		unlockSched();
		sti();
		termGroup = pgid;
		return 0;
	case IOCTL_TTY_ISATTY:
		return 0;
	case IOCTL_TTY_GETSIZE:
		getConsoleSize(&winsz->ws_col, &winsz->ws_row);
		winsz->ws_xpixel = 0;
		winsz->ws_ypixel = 0;
		return 0;
	default:
		ERRNO = ENODEV;
		return -1;
	};
};