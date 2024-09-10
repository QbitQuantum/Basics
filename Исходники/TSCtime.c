void recalibrate(void) {
	int i;

	ULONGLONG basetscs[nreps];  // basetsc for each round
	ULONGLONG basests[nreps];   // basest for each round

        char buf[100] = "0";

	// read calibration
	HKEY key;
	DWORD cbData;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\NetSem\\TTHEE",0,KEY_READ,&key);
	cbData = sizeof(tscfreq);
	RegQueryValueEx(key,"tscfreq",NULL,NULL,(BYTE *)&tscfreq,&cbData);
	cbData = sizeof(tscsd);
	RegQueryValueEx(key,"tscsd",NULL,NULL,(BYTE *)&tscsd,&cbData);
	// double error = double(tscsd) / double(tscfreq);
        cbData = sizeof(buf)-1;
	RegQueryValueEx(key,"ugly_hack_offset",NULL,NULL,(BYTE *)buf,&cbData);
        buf[cbData] = '\0';
        ugly_hack_offset = _atoi64(buf);

	// get base times
	for (i=0; i<nreps; i++) {
		FILETIME baseft;
		Sleep(5);  // to be sure we're on a tick boundary
		basetscs[i] = gettsc();  // get this first because it changes very fast
		GetSystemTimeAsFileTime(&baseft);  // no rush; we have 1/64 sec to read this before it changes
		basests[i] = ((ULONGLONG)baseft.dwHighDateTime)<<32 | ((ULONGLONG)baseft.dwLowDateTime);
	}

	basetsc = basetscs[nreps-1];
	/* Now: we want to know the correct basest for the latest basetsc.  Each measurement can be
	   extrapolated to give us a basest for the latest basetsc.  But if there was a delay between the
	   tick and our process being scheduled in a particular round, this will show up as the basetsc
	   being high, a.k.a., the basest being low.  Thus, we take the highest computed basest. */
	basest = basests[nreps-1];
	for (i=0; i<nreps; i++) {
		ULONGLONG basestx = basests[i] + (10000000 * (basetscs[nreps-1] - basetscs[i])) / tscfreq;
			// don't worry about overflow; at 500MHz (glia) it won't overflow until just over an hour
		if (basestx > basest) {
			basest = basestx;
		}
	}

        basest -= ugly_hack_offset;   // apply the hack offset.

	lastrecal = basest;  // we just recalibrated.
}