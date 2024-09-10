//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent,i;
	PAINTSTRUCT ps;
	HDC hdc;
	char* str[100];
	RECT rt;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			ILibStopChain(TheChain);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:

		// Paint the complete screen here. Quite workout to get the UI looking
		// event half decent using Win32 directly.
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWndMainWindow, &rt);

		// Paint the top portion of the screen
		RECT r;
		r.left = 1;
		r.right = rt.right-1;
		r.top = 0;
		r.bottom = 40;
		FillRect(hdc,&r,GetSysColorBrush(COLOR_SCROLLBAR));
		DrawEdge(hdc,&r,EDGE_RAISED,BF_RECT);
		DrawIcon(hdc,8,5,HICON_MEDIASERVER2);
		SetBkColor(hdc,GetSysColor(COLOR_SCROLLBAR));

		// Paint the title
		r.left = 50;
		r.right = rt.right-1;
		r.top = 4;
		r.bottom = 50;
		DrawText(hdc,TEXT("Intel Micro Media Server"),-1,&r,0);

		// Paint the transfer count stat label & value
		r.left = 50;
		r.right = rt.right-1;
		r.top = 20;
		r.bottom = 50;
		if (MmsCurrentTransfersCount == 0)
		{
			DrawText(hdc,TEXT("No File Transfers          "),-1,&r,0);
		}
		if (MmsCurrentTransfersCount == 1)
		{
			DrawText(hdc,TEXT("1 File Transfer          "),-1,&r,0);
		}
		if (MmsCurrentTransfersCount > 1)
		{
			sprintf((char*)str,"%d File Transfers        ",MmsCurrentTransfersCount);
			DrawText(hdc,(LPCSTR)str,-1,&r,0);
		}

		// Paint the main portion of the screen
		r.left = 1;
		r.right = rt.right-1;
		r.top = 42;
		r.bottom = 267;
		FillRect(hdc,&r,GetSysColorBrush(COLOR_SCROLLBAR));

		// Paint global media server stats labels
		r.left = 8;
		r.right = 150;
		r.top = 50;
		r.bottom = 70;
		DrawText(hdc,TEXT("Browse Requests"),-1,&r,0);
		r.left = 8;
		r.right = 150;
		r.top = 70;
		r.bottom = 90;
		DrawText(hdc,TEXT("HTTP Requests"),-1,&r,0);

		// Paint global media server stats values
		sprintf((char*)str,"%d",MmsBrowseCount);
		r.left = 180;
		r.right = rt.right-5;
		r.top = 50;
		r.bottom = 70;
		DrawText(hdc,(LPCSTR)str,-1,&r,DT_RIGHT);
		sprintf((char*)str,"%d",MmsHttpRequestCount);
		r.left = 180;
		r.right = rt.right-5;
		r.top = 70;
		r.bottom = 90;
		DrawText(hdc,(LPCSTR)str,-1,&r,DT_RIGHT);

		// Paint the transfer window edge
		r.left = 2;
		r.right = rt.right-1;
		r.top = 94;
		r.bottom = 264;
		DrawEdge(hdc,&r,EDGE_SUNKEN,BF_RECT);

		// Paint the white transfer window
		r.left = 4;
		r.right = rt.right-5;
		r.top = 96;
		r.bottom = 262;
		FillRect(hdc,&r,GetSysColorBrush(COLOR_MENU));

		// Draw all of the active transfers on the screen (up to 5)
		for (i=0;i<5;i++)
		{
			DrawTransferInfo(hdc,i,g_DownloadStatsMapping[i]);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		// Clear up all of the active transfers.
		for (i=0;i<DOWNLOAD_STATS_ARRAY_SIZE;i++) {g_DownloadStatsMapping[i] = -1;}

		// Load all of the icon resources we will need to draw the UI.
		HICON_MEDIASERVER  = LoadIcon(g_hInst, (LPCTSTR)IDI_MEDIASERVER);
		HICON_MEDIASERVER2 = LoadIcon(g_hInst, (LPCTSTR)IDI_MEDIASERVER2);
		HICON_RIGHTARROW   = LoadIcon(g_hInst, (LPCTSTR)IDI_RIGHTARROW);
		HICON_LEFTARROW    = LoadIcon(g_hInst, (LPCTSTR)IDI_LEFTARROW);

		CreateThread(NULL, 0, &UPnPMain, hWnd, 0, NULL ); 
		break;
	case WM_CLOSE:
		ILibStopChain(TheChain);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}