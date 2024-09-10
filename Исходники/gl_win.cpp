// Called from GLimp_Shutdown() and AppActivate()
static void RestoreGamma()
{
	if (!gammaStored) return;
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetDC(hwnd);
#if 0
	DebugPrintf("restore gamma\n");
	if (!SetDeviceGammaRamp(hdc, gammaRamp))
		DebugPrintf("Cannot restore gamma!\n");
#else
	SetDeviceGammaRamp(hdc, gammaRamp);
#endif
	ReleaseDC(hwnd, hdc);
}