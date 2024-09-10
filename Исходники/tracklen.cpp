/*--------------------------------------------------------------------------
 Restore the autoplay setting saved by AutoPlay_Disable().
--------------------------------------------------------------------------*/
void tracklen_AutoPlay_Restore()
{	
	int res;
	HKEY hkey = NULL;

	// If AutoPlay_Disable() was never called, just return.
	if (s_oldAutoRunValue == AUTORUN_UNKNOWN) {
		return;
	}

	// Restore AutoPlay setting
	res = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 0, KEY_ALL_ACCESS, &hkey);
	if (res == ERROR_SUCCESS) {	
		RegSetValueEx(hkey, "NoDriveTypeAutoRun", 0, REG_BINARY, (const unsigned char*)&s_oldAutoRunValue, 4);
		RegFlushKey(hkey);
		RegCloseKey(hkey);
	 }
}