LPARAM YUVCodecDriver::Default(DWORD dwDriverID, HDRVR hDriver, UINT uiMessage, LPARAM lParam1, LPARAM lParam2) {
	return DefDriverProc(dwDriverID, hDriver, uiMessage, lParam1, lParam2);
}