//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
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
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	if (message == WM_TASKBARCREATED && !IsWindowVisible(g_hwnd))
	{
		Minimize();
		return 0;
	}
	switch (message)
	{
		case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_PRINT://create raport.txt file and print

			PRINTDLG pd;
			
			memset(&pd, 0, sizeof(PRINTDLG));
			pd.lStructSize = sizeof(PRINTDLG);
			pd.hwndOwner = hWnd;
			pd.Flags = PD_RETURNDC;
			pd.hDevMode = NULL;//hInst.hDevMode;
			pd.hDevNames = NULL;//psd.hDevNames;

			if (PrintDlg(&pd))
			{
				WORD     wCopies;
				
				RECT     rect;
				DOCINFO  docInfo;
				FILE *file;
				errno_t err;
								
				LPDEVMODE lpDevMode = (LPDEVMODE)GlobalLock(pd.hDevMode);
				LPCWSTR lpszString = (LPCWSTR)L"This is a test";

				memset(&docInfo	, 0, sizeof(DOCINFO));
				GetClientRect(hWnd, &rect);
				docInfo.cbSize = sizeof(DOCINFO);
				
				docInfo.lpszDocName = (LPCWSTR)L"report.txt";
				
				err = fopen_s(&file, "report.txt", "w+");

				if (StartDoc(pd.hDC, &docInfo) > 0)
				{
					for (wCopies = 0; wCopies < pd.nCopies; wCopies++)
					{
						StartPage(pd.hDC);
						TextOut(pd.hDC, 100, 100, LPCWSTR(lpszString), lstrlen(lpszString));
						EndPage(pd.hDC);
						fclose(file);
					}
					EndDoc(pd.hDC);
				}
				GlobalUnlock(pd.hDevMode);
				DeleteDC(pd.hDC);
			}
			else
			if (CommDlgExtendedError() == 0x1008)
				MessageBox(hWnd, (LPCWSTR)L"No default printer selected.", (LPCWSTR)L"Print", MB_OK | MB_ICONSTOP);

			break;//IDM_PRINT
		
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//create menu - if push left button
	case WM_CREATE:// create the menu once.
		HBITMAP hbmpPie1, hbmpPie2;
		hbmpPie1 = (HBITMAP)LoadImage(NULL, TEXT("gnome_session_logout.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		hbmpPie2 = (HBITMAP)LoadImage(NULL, TEXT("green_print.bmp"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_menu = CreatePopupMenu();
		AppendMenu(g_menu, MF_STRING | MF_BYPOSITION | MF_POPUP, ID_TRAY_PRINT_CONTEXT_MENU_ITEM, TEXT("  Print Report"));
		SetMenuItemBitmaps(g_menu, ID_TRAY_PRINT_CONTEXT_MENU_ITEM, MF_BYCOMMAND, hbmpPie2, hbmpPie2);
		AppendMenu(g_menu, MF_SEPARATOR, NULL, NULL);
		InsertMenu(g_menu, -1, MF_STRING | MF_BYPOSITION | MF_POPUP, ID_TRAY_EXIT_CONTEXT_MENU_ITEM, _T("  Exit"));
		SetMenuItemBitmaps(g_menu, ID_TRAY_EXIT_CONTEXT_MENU_ITEM, MF_BITMAP | MF_BYCOMMAND, hbmpPie1, hbmpPie1);
		break;

	case WM_SYSCOMMAND:
		switch (wParam & 0xfff0)
		{
			case SC_MINIMIZE:
			case SC_CLOSE:  // redundant to WM_CLOSE, it appears
				Minimize();
				return 0;
			break;
		}

	case WM_TRAYICON:
	{
		if (lParam == WM_RBUTTONDOWN) // I'm using WM_RBUTTONDOWN here because
		{
			printf("Mmm.  Let's get contextual.  I'm showing you my context menu.\n");
			POINT curPoint;
			GetCursorPos(&curPoint);
			SetForegroundWindow(hWnd);
			printf("calling track\n");
			UINT clicked = TrackPopupMenu(

				g_menu,
				TPM_RETURNCMD | TPM_NONOTIFY, // don't send me WM_COMMAND messages about this window, instead return the identifier of the clicked menu item
				curPoint.x,
				curPoint.y,
				0,
				hWnd,
				NULL
				);

			if (clicked == ID_TRAY_EXIT_CONTEXT_MENU_ITEM)
			{
				// quit the application.
				printf("I have posted the quit message, biatch\n");
				PostQuitMessage(0);
			}
			if (clicked == ID_TRAY_PRINT_CONTEXT_MENU_ITEM)
			{
				
				DialogBox(hInst, MAKEINTRESOURCE(IDD_REPORTBOX), hWnd, About);
				SendMessage(g_hwnd, WM_COMMAND, IDM_PRINT, lParam);
				return 0;
			}
		}
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}