HOOKFUNC LONG WINAPI MySetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong)
{
	debuglog(LCF_WINDOW|LCF_FREQUENT, __FUNCTION__ "(%d, 0x%X) called on 0x%X.\n", nIndex, dwNewLong, hWnd);
	if(nIndex == GWL_WNDPROC)
	{
		// the game is trying to change this window's procedure.
		// since we need it to stay replaced with our own winproc,
		// update our pointer to the original winproc instead.
		LONG rv = MyGetWindowLongA(hWnd, nIndex);
		debuglog(LCF_WINDOW|LCF_FREQUENT, __FUNCTION__ "hwndToOrigHandler[0x%X] = 0x%X.\n", hWnd, dwNewLong);
		debuglog(LCF_WINDOW|LCF_FREQUENT, __FUNCTION__ "rv = 0x%X.\n", rv);
		hwndToOrigHandler[hWnd] = (WNDPROC)dwNewLong;
		SetWindowLongA(hWnd, GWL_WNDPROC, (LONG)MyWndProcA);
		return rv;
	}
	if(nIndex == GWL_STYLE)
	{
		// some SDL apps create a window, attach d3d,
		// then modify the window style for fullscreen.
		// disallow that last step if the window has been fake-fullscreen locked.
		if(IsWindowFakeFullscreen(hWnd))
		{
			return MyGetWindowLongA(hWnd, nIndex);
		}
	}
	LONG rv = SetWindowLongA(hWnd, nIndex, dwNewLong);
	debuglog(LCF_WINDOW|LCF_FREQUENT, __FUNCTION__ "RV = 0x%X.\n", rv);
	return rv;
}