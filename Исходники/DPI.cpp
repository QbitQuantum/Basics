	int CDPI::GetDPIOfMonitor(HMONITOR hMonitor)
	{
		UINT dpix = 96, dpiy = 96;
		if (IsWindows8Point1OrGreater()) {
			HRESULT  hr = E_FAIL;
			HMODULE hModule =::LoadLibrary(_T("Shcore.dll"));
			if(hModule != NULL) {
				LPGetDpiForMonitor GetDpiForMonitor = (LPGetDpiForMonitor)GetProcAddress(hModule, "GetDpiForMonitor");
				if (GetDpiForMonitor != NULL && GetDpiForMonitor(hMonitor,MDT_EFFECTIVE_DPI, &dpix, &dpiy) != S_OK) {
					MessageBox(NULL, _T("GetDpiForMonitor failed"), _T("Notification"), MB_OK);
					return 96;
				}
			}
		}
		else {
			HDC screen = GetDC(0);
			dpix = GetDeviceCaps(screen, LOGPIXELSX);
			ReleaseDC(0, screen);
		}
		return dpix;
	}