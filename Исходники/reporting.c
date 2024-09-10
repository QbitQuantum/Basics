void reportu(string msg, int etype, ...)
{
	letter          mbuffer[4096];
	va_list         vlist;
	COPYDATASTRUCT  cd;

	if(!reporting_initialized) return;
	if(!reporting_window) return;
	if(!IsWindow(reporting_window))
	{
		reporting_window = 0;
		return;
	}

	va_start(vlist, etype);

	vswprintf(mbuffer, sizeof(mbuffer) / sizeof(letter), msg, vlist);

	cd.cbData = sizeof(mbuffer);
	cd.dwData = etype;
	cd.lpData = mbuffer;

	SendMessage(reporting_window, WM_COPYDATA, sizeof(letter) /* Unicode */, (LPARAM)&cd);

	va_end(vlist);
}