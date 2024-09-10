LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_60:
		case IDM_70:
		case IDM_85:
		case IDM_100:
		case IDM_120:
		case IDM_150:
			if(wmId==RROdefault)
			{
				RROenable^=8;
				CheckMenuItem(hmenu, wmId, RROenable);
			}
			else
			{
				CheckMenuItem(hmenu, RROdefault, 0);
				RROdefault=wmId;
				RROenable=8;
				CheckMenuItem(hmenu, wmId, 8);
			}
			break;
		case IDM_UPDATEREGISTRY:
			updateregistry^=1;
			CheckMenuItem(hmenu, IDM_UPDATEREGISTRY, (updateregistry<<3));
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_DISPLAYCHANGE:
		if(!RROenable || Skip_WM_DISPLAYCHANGE) break;

		HDC hDefaultDisplay;
		hDefaultDisplay = GetDC(0);
		if(!hDefaultDisplay) break;

		refreshrate = GetDeviceCaps(hDefaultDisplay, VREFRESH);
		ReleaseDC(0, hDefaultDisplay);
		if (refreshrate==RROdefault) break;

		devmode.dmSize = sizeof(devmode);
		devmode.dmPelsWidth = (lParam<<16>>16);
		devmode.dmPelsHeight = (lParam>>16);
		devmode.dmFields = (DM_DISPLAYFREQUENCY|DM_PELSWIDTH|DM_PELSHEIGHT);
		devmode.dmDisplayFrequency = RROdefault;

		/*
		TCHAR temp[256];
		wsprintf((LPWSTR)&temp,L"%ldx%ld",devmode.dmPelsWidth,devmode.dmPelsHeight);
		MessageBox(0,(LPWSTR)&temp,(LPWSTR)&temp,0);
		break;
		//*/

		// TEST will not help if there is no restriction on frequency (user turned it off, etc)!
		if((ChangeDisplaySettingsW(&devmode, CDS_TEST))==DISP_CHANGE_SUCCESSFUL)
		{
			Skip_WM_DISPLAYCHANGE=1; // I hope this works as I think...
			ChangeDisplaySettingsW(&devmode, updateregistry); // CDS_UPDATEREGISTRY = 1
			Skip_WM_DISPLAYCHANGE=0;
		}
		break;

	case WM_CREATE:
		hmenu=GetMenu(hWnd);
		if(hmenu)return 1;
		else return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}