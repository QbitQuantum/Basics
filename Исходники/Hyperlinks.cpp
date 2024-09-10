LRESULT CALLBACK _HyperlinkProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WNDPROC pfnOrigProc = (WNDPROC) GetProp(hwnd, PROP_ORIGINAL_PROC);

	switch (message)
	{
	case WM_DESTROY:
		{
			SetWindowLong(hwnd, GWL_WNDPROC, (LONG) pfnOrigProc);
			RemoveProp(hwnd, PROP_ORIGINAL_PROC);

			HFONT hOrigFont = (HFONT) GetProp(hwnd, PROP_ORIGINAL_FONT);
			SendMessage(hwnd, WM_SETFONT, (WPARAM) hOrigFont, 0);
			RemoveProp(hwnd, PROP_ORIGINAL_FONT);

			HFONT hFont = (HFONT) GetProp(hwnd, PROP_UNDERLINE_FONT);
			DeleteObject(hFont);
			RemoveProp(hwnd, PROP_UNDERLINE_FONT);

			RemoveProp(hwnd, PROP_STATIC_HYPERLINK);

			break;
		}
	case WM_MOUSEMOVE:
		{
			if (GetCapture() != hwnd)
			{
				HFONT hFont = (HFONT) GetProp(hwnd, PROP_UNDERLINE_FONT);
				SendMessage(hwnd, WM_SETFONT, (WPARAM) hFont, FALSE);
				InvalidateRect(hwnd, NULL, FALSE);
				SetCapture(hwnd);
			}
			else
			{
				RECT rect;
				GetWindowRect(hwnd, &rect);

				POINT pt = { LOWORD(lParam), HIWORD(lParam) };
				ClientToScreen(hwnd, &pt);

				if (!PtInRect(&rect, pt))
				{
					HFONT hFont = (HFONT) GetProp(hwnd, PROP_ORIGINAL_FONT);
					SendMessage(hwnd, WM_SETFONT, (WPARAM) hFont, FALSE);
					InvalidateRect(hwnd, NULL, FALSE);
					ReleaseCapture();
				}
			}
			break;
		}
	case WM_SETCURSOR:
		{
			// Since IDC_HAND is not available on all operating systems,
			// we will load the arrow cursor if IDC_HAND is not present.
			HCURSOR hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
			if (NULL == hCursor)
			{
				hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
			}
			SetCursor(hCursor);
			return TRUE;
		}
    case WM_LBUTTONUP:
        {
		  //	Shell to the website
		  TCHAR lpOpen[MAX_PATH] = L"open";
		  TCHAR lpFile[MAX_PATH] = L"https://sites.google.com/site/wifilapper/";
		  int nShowCmd = SW_RESTORE;	//	Restore the Help document, if it is minimized or whatever.
		  HINSTANCE Check = ShellExecuteW(hwnd, lpOpen, lpFile, NULL, NULL, nShowCmd);
		  if ((int)Check <= 32)
			MessageBox(NULL, L"There was an error trying to open the website, check your connection and try again", L"ERROR", MB_OK);
		  return true;
		}
	}

	return CallWindowProc(pfnOrigProc, hwnd, message, wParam, lParam);
}