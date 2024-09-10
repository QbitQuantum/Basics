int
main(void) {
	char *status;
	char *tmchicago;
	char *alsavolume;
	char *mpdinfo;
	char *mailinfo;
	char *networkinfo;
	char *layoutinfo;
	static unsigned long long int rec, sent;
	time_t count5min = time(NULL);

	/*
	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}
	*/

	xkblayoutSetup();

	parse_netdev(&rec,&sent);
	mailinfo = getMailCount();
	for (;;sleep(1)) {
		/* Put together the pieces of our status */
		tmchicago = mktimes("%a, %b %d %I:%M", tzchicago);
		alsavolume = get_volume();
		mpdinfo = getmpdstat();
		networkinfo = get_netusage(&rec,&sent);
		layoutinfo = getKeyboardLayout();

		if(runevery(&count5min, 300)) {
			free(mailinfo);
			mailinfo = getMailCount();
		}

		/* Build the status string from our pieces */
		status = smprintf("%s %s %s %s %s[%s%s%%%s] %s[%s%s%s]", mpdinfo, networkinfo, mailinfo, layoutinfo, colcyan, colgreen, alsavolume, colcyan, colcyan, colyellow, tmchicago, colcyan);

		/* Send it to the wm for display */
		setstatus(status);

		/* Clean up our pieces */
		free(layoutinfo);
		free(tmchicago);
		free(alsavolume);
		free(mpdinfo);
		free(networkinfo);
		free(status);
	}

	free(mailinfo);

	xkblayoutCleanup();

	XCloseDisplay(dpy);

	return 0;
}