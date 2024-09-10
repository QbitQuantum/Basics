void MakeFullscreen()
{
	HWND hWnd = NULL;
	
	// find the PowerDVD window
	hWnd = FindWindow(NULL, L"PowerDVD");

	if (hWnd != NULL)
	{
		WINDOWPLACEMENT placement;
		placement.length = sizeof(placement);

		// get the window's position and size
		GetWindowPlacement(hWnd, &placement);

		// enumerate all child windows of the PowerDVD window
		EnumChildWindows(hWnd, EnumChildProc, (LPARAM)&placement.rcNormalPosition);
	}
}