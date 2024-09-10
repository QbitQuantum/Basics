LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case TRAY_CALLBACK:
	{
		switch(lParam)
		{
		case WM_LBUTTONDBLCLK:
			if (IsWindowVisible(hWnd))
				ShowWindow(hWnd, SW_HIDE);
			else
				ShowWindow(hWnd, SW_RESTORE);
			break;
		case WM_MOUSEMOVE:
			{
				CString sInfoTip;
				NOTIFYICONDATA SystemTray;
				sInfoTip.Format(_T("Cached Directories : %ld\nWatched paths : %ld"), 
					CGitStatusCache::Instance().GetCacheSize(),
					CGitStatusCache::Instance().GetNumberOfWatchedPaths());

				SystemTray.cbSize = sizeof(NOTIFYICONDATA);
				SystemTray.hWnd   = hTrayWnd;
				SystemTray.uID    = TRAY_ID;
				SystemTray.uFlags = NIF_TIP;
				_tcscpy_s(SystemTray.szTip, sInfoTip);
				Shell_NotifyIcon(NIM_MODIFY, &SystemTray);
			}
			break;
		case WM_RBUTTONUP:
		case WM_CONTEXTMENU:
			{
				POINT pt;
				DWORD ptW = GetMessagePos();
				pt.x = GET_X_LPARAM(ptW);
				pt.y = GET_Y_LPARAM(ptW);
				HMENU hMenu = CreatePopupMenu();
				if(hMenu)
				{
					InsertMenu(hMenu, (UINT)-1, MF_BYPOSITION, TRAYPOP_EXIT, _T("Exit"));
					SetForegroundWindow(hWnd);
					TrackPopupMenu(hMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);
					DestroyMenu(hMenu);
				}
			}
			break;
		}
	}
	break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			RECT rect;
			GetClientRect(hWnd, &rect);
			// clear the background
			HBRUSH background = CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
			HGDIOBJ oldbrush = SelectObject(hdc, background);
			FillRect(hdc, &rect, background);

			int line = 0;
			SIZE fontsize = {0};
			AutoLocker print(critSec);
			GetTextExtentPoint32( hdc, szCurrentCrawledPath[0], (int)_tcslen(szCurrentCrawledPath[0]), &fontsize );
			for (int i=nCurrentCrawledpathIndex; i<MAX_CRAWLEDPATHS; ++i)
			{
				TextOut(hdc, 0, line*fontsize.cy, szCurrentCrawledPath[i], (int)_tcslen(szCurrentCrawledPath[i]));
				line++;
			}
			for (int i=0; i<nCurrentCrawledpathIndex; ++i)
			{
				TextOut(hdc, 0, line*fontsize.cy, szCurrentCrawledPath[i], (int)_tcslen(szCurrentCrawledPath[i]));
				line++;
			}
			
			
			SelectObject(hdc,oldbrush);
			EndPaint(hWnd, &ps); 
			DeleteObject(background);
			return 0L; 
		}
		break;
	case WM_COMMAND:
		{
			WORD wmId    = LOWORD(wParam);

			switch (wmId)
			{
			case TRAYPOP_EXIT:
				DestroyWindow(hWnd);
				break;
			}
			return 1;
		}
	case WM_QUERYENDSESSION:
		{
			ATLTRACE("WM_QUERYENDSESSION\n");
			if (CGitStatusCache::Instance().WaitToWrite(200))
			{
				CGitStatusCache::Instance().Stop();
				CGitStatusCache::Instance().Done();
			}
			return TRUE;
		}
		break;
	case WM_CLOSE:
	case WM_ENDSESSION:
	case WM_DESTROY:
	case WM_QUIT:
		{
			ATLTRACE("WM_CLOSE/DESTROY/ENDSESSION/QUIT\n");
			CGitStatusCache::Instance().WaitToWrite();
			CGitStatusCache::Instance().Stop();
			CGitStatusCache::Instance().SaveCache();
			if (message != WM_QUIT)
				PostQuitMessage(0);
			bRun = false;
			return 1;
		}
		break;
	case WM_DEVICECHANGE:
		{
			DEV_BROADCAST_HDR * phdr = (DEV_BROADCAST_HDR*)lParam;
			switch (wParam)
			{
			case DBT_CUSTOMEVENT:
				{
					ATLTRACE("WM_DEVICECHANGE with DBT_CUSTOMEVENT\n");
					if (phdr->dbch_devicetype == DBT_DEVTYP_HANDLE)
					{
						DEV_BROADCAST_HANDLE * phandle = (DEV_BROADCAST_HANDLE*)lParam;
						if (IsEqualGUID(phandle->dbch_eventguid, GUID_IO_VOLUME_DISMOUNT))
						{
							ATLTRACE("Device to be dismounted\n");
							CGitStatusCache::Instance().WaitToWrite();
							CGitStatusCache::Instance().CloseWatcherHandles(phandle->dbch_hdevnotify);
							CGitStatusCache::Instance().Done();
						}
						if (IsEqualGUID(phandle->dbch_eventguid, GUID_IO_VOLUME_LOCK))
						{
							ATLTRACE("Device lock event\n");
							CGitStatusCache::Instance().WaitToWrite();
							CGitStatusCache::Instance().CloseWatcherHandles(phandle->dbch_hdevnotify);
							CGitStatusCache::Instance().Done();
						}
					}
				}
				break;
			case DBT_DEVICEREMOVEPENDING:
				ATLTRACE("WM_DEVICECHANGE with DBT_DEVICEREMOVEPENDING\n");
				if (phdr->dbch_devicetype == DBT_DEVTYP_HANDLE)
				{
					DEV_BROADCAST_HANDLE * phandle = (DEV_BROADCAST_HANDLE*)lParam;
					CGitStatusCache::Instance().WaitToWrite();
					CGitStatusCache::Instance().CloseWatcherHandles(phandle->dbch_hdevnotify);
					CGitStatusCache::Instance().Done();
				}
				else
				{
					CGitStatusCache::Instance().WaitToWrite();
					CGitStatusCache::Instance().CloseWatcherHandles(INVALID_HANDLE_VALUE);
					CGitStatusCache::Instance().Done();
				}
				break;
			case DBT_DEVICEQUERYREMOVE:
				ATLTRACE("WM_DEVICECHANGE with DBT_DEVICEQUERYREMOVE\n");
				if (phdr->dbch_devicetype == DBT_DEVTYP_HANDLE)
				{
					DEV_BROADCAST_HANDLE * phandle = (DEV_BROADCAST_HANDLE*)lParam;
					CGitStatusCache::Instance().WaitToWrite();
					CGitStatusCache::Instance().CloseWatcherHandles(phandle->dbch_hdevnotify);
					CGitStatusCache::Instance().Done();
				}
				else
				{
					CGitStatusCache::Instance().WaitToWrite();
					CGitStatusCache::Instance().CloseWatcherHandles(INVALID_HANDLE_VALUE);
					CGitStatusCache::Instance().Done();
				}
				break;
			case DBT_DEVICEREMOVECOMPLETE:
				ATLTRACE("WM_DEVICECHANGE with DBT_DEVICEREMOVECOMPLETE\n");
				if (phdr->dbch_devicetype == DBT_DEVTYP_HANDLE)
				{
					DEV_BROADCAST_HANDLE * phandle = (DEV_BROADCAST_HANDLE*)lParam;
					CGitStatusCache::Instance().WaitToWrite();
					CGitStatusCache::Instance().CloseWatcherHandles(phandle->dbch_hdevnotify);
					CGitStatusCache::Instance().Done();
				}
				else
				{
					CGitStatusCache::Instance().WaitToWrite();
					CGitStatusCache::Instance().CloseWatcherHandles(INVALID_HANDLE_VALUE);
					CGitStatusCache::Instance().Done();
				}
				break;
			}
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}