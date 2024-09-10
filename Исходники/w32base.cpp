vduisize VDUIBaseWindowW32::MapUnitsToPixels(vduisize s) {
	RECT rwin = {0,0,s.w,s.h};

	MapDialogRect(mhwnd, &rwin);

	return vduisize(rwin.right, rwin.bottom);
}