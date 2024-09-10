static boolean winregdeletekey (HKEY hkey, Handle h) {

	/*
	7.0.2b1 Radio PBS: delete a key.
	*/

	long lentext;
	boolean fl = true;

	lentext = gethandlesize (h);

	sethandlesize (h, lentext + 1);

	(*h) [lentext] = '\0'; /*null terminate*/

	lockhandle (h);

	if (RegOpenKeyEx (hkey, *h, 0, KEY_SET_VALUE, &hkey) == ERROR_SUCCESS) {

		if (RegDeleteKey (hkey, *h) == ERROR_SUCCESS) {

			fl = true;

			RegFlushKey (hkey);
			} /*if*/

		RegCloseKey (hkey);
		} /*if*/

	unlockhandle (h);

	return (fl);
	} /*winregdeletekey*/