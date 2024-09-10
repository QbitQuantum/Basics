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
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

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
				case IDM_VIEW_25:
				case IDM_VIEW_33:
				case IDM_VIEW_50:
				case IDM_VIEW_100:
				case IDM_VIEW_200:
				case IDM_VIEW_300:
				case IDM_VIEW_400:
                    iViewScale = wmId - IDM_VIEW_100;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateMenu(hWnd);
                    break;
                case ID_VIEW_ANIMATE:
                    bAnimate = !bAnimate;
                    UpdateMenu(hWnd);
                    break;
                case ID_VIEW_FRAME:
                    bAnimate = FALSE;
                    if (hFrameEvent)
                        SetEvent(hFrameEvent);
                    UpdateMenu(hWnd);
                    break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_DROPFILES:
		{
			HDROP hDrop = (HDROP) wParam;

			// Don't accept more dropped files
			::DragAcceptFiles(hWnd, FALSE);

			// Get number of files dropped
			const int iFiles = ::DragQueryFile(hDrop, ~0U, NULL, 0);

			// Free previous file list (if allocated)
			if (pszFileList)
			{
				GlobalFreePtr(pszFileList);
			}

			// Allocate buffer to hold list of files
			pszFileList = (LPTSTR) GlobalAllocPtr(GMEM_ZEROINIT, iFiles * MAX_PATH);
			if (pszFileList)
			{
				LPTSTR pFile = pszFileList;
				for (int iIndex = 0; iIndex < iFiles; ++iIndex)
				{
					if (::DragQueryFile(hDrop, iIndex, pFile, MAX_PATH))
					{
						TRACE("WM_DROPFILES (%d of %d) szPathName=%s\n", iIndex, iFiles, pFile);
						// Add terminating '\n' between files
						int iLength = lstrlen(pFile);
						pFile += (iLength + 1);
					}
				}
				*pFile++ = '\0';
				pszCurrentFile = pszFileList;
			}
			DragFinish(hDrop);
			break;
		}
		case WM_CREATE:
		{
			HDC hDC = ::GetDC(hWnd);
#ifdef PALETTE_SUPPORT
			hPalette = ::CreateHalftonePalette(hDC);
#endif // PALETTE_SUPPORT
			::ReleaseDC(hWnd, hDC);
			ghwndGIF = hWnd;
			_beginthread(DrawGifThread, 0, hWnd);
            UpdateMenu(hWnd);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		case WM_PAINT:
		{	
			RECT rect;
			GetClientRect(hWnd, &rect);

			HDC hDC = BeginPaint(hWnd, &ps);
#ifdef PALETTE_SUPPORT
			// Select and realize palette (for 8-bit displays)
			HPALETTE hOldPal = ::SelectPalette(hDC, hPalette, TRUE);
			::RealizePalette(hDC);
			gif.Draw(hDC, &rect, iViewScale);
			if (hOldPal)
				::SelectPalette(hDC, hOldPal, TRUE);
#else
			gif.Draw(hDC, &rect, iViewScale);
#endif // PALETTE_SUPPORT
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			ghwndGIF = NULL;
			Sleep(1000);			// Wait for thread to self destruct

			// Free previous file list (if allocated)
			if (pszFileList)
			{
				TRACE("Free pszFileList!\n");
				GlobalFreePtr(pszFileList);
				pszFileList = NULL;
			}
#ifdef PALETTE_SUPPORT
			if (hPalette)
			{
				TRACE("Delete palette!\n");
				::DeleteObject(hPalette);
				hPalette = NULL;
			}
#endif // PALETTE_SUPPORT
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}