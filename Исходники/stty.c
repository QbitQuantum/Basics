static void
sane(int not)
{
	speed_t	ispeed, ospeed;

	if (not)
		inval();
	ispeed = cfgetispeed(&ts);
	ospeed = cfgetospeed(&ts);
	ts.c_cc[VINTR] = '\3';
	ts.c_cc[VQUIT] = '\34';
	ts.c_cc[VERASE] = '\10';
	ts.c_cc[VKILL] = '\25';
	ts.c_cc[VEOF] = '\4';
	ts.c_cc[VEOL] = vdis;
	ts.c_cc[VEOL2] = vdis;
#ifdef	VSWTCH
	ts.c_cc[VSWTCH] = vdis;
#endif
	ts.c_cc[VSTART] = '\21';
	ts.c_cc[VSTOP] = '\23';
	ts.c_cc[VSUSP] = '\32';
#ifdef	VREPRINT
	ts.c_cc[VREPRINT] = '\22';
#endif
#ifdef	VDISCARD
	ts.c_cc[VDISCARD] = '\17';
#endif
#ifdef	VWERASE
	ts.c_cc[VWERASE] = '\27';
#endif
	ts.c_cc[VLNEXT] = '\26';
	ts.c_cflag = CS8|CREAD;
	ts.c_lflag = ISIG|ICANON|ECHO|ECHOE|ECHOK|ECHOKE|IEXTEN;
	ts.c_iflag = BRKINT|IGNPAR|ICRNL|IXON|IMAXBEL;
#ifdef	IUTF8
	if (MB_CUR_MAX > 1) {
		wchar_t	wc;
		if (mbtowc(&wc, "\303\266", 2) == 2 && wc == 0xF6 &&
				mbtowc(&wc, "\342\202\254", 3) == 3 &&
				wc == 0x20AC)
			ts.c_iflag |= IUTF8;
	}
#endif	/* IUTF8 */
	ts.c_oflag = OPOST|ONLCR;
	cfsetispeed(&ts, ispeed);
	cfsetospeed(&ts, ospeed);
}