int ps_get_monitor_timing(int monitor_index, MonitorTiming *timing)
{
	LRESULT lresult;
	char in[256];
	
	if (!hPSWnd) return 0;
	
	lresult = SendMessage(hPSWnd, UM_GETTIMING, monitor_index, 0);
	
	if (lresult == -1)
	{
		mame_printf_verbose("PStrip: Could not get PowerStrip timing string\n");
		return 0;
	}
	
	if (!GlobalGetAtomNameA(lresult, in, sizeof(in)))
	{
		mame_printf_verbose("PStrip: GlobalGetAtomName failed\n");
		return 0;
	}
	
	mame_printf_verbose("PStrip: ps_get_monitor_timing(%d): %s\n", monitor_index, in);
	
	read_timing_string(in, timing);
	
	GlobalDeleteAtom(lresult); // delete atom created by PowerStrip

	return 1;
}