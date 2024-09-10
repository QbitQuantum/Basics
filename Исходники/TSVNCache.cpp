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
                sInfoTip.Format(L"Cached Directories : %Id\nWatched paths : %d",
                    CSVNStatusCache::Instance().GetCacheSize(),
                    CSVNStatusCache::Instance().GetNumberOfWatchedPaths());

                NOTIFYICONDATA SystemTray = {};
                SystemTray.cbSize = sizeof(NOTIFYICONDATA);
                SystemTray.hWnd   = hTrayWnd;
                SystemTray.uID    = TRAY_ID;
                SystemTray.uFlags = NIF_TIP;
                wcscpy_s(SystemTray.szTip, sInfoTip);
                Shell_NotifyIcon(NIM_MODIFY, &SystemTray);
            }
            break;
        case WM_RBUTTONUP:
        case WM_CONTEXTMENU:
            {
                POINT pt;
                GetCursorPos(&pt);
                HMENU hMenu = CreatePopupMenu();
                if(hMenu)
                {
                    InsertMenu(hMenu, (UINT)-1, MF_BYPOSITION, TRAYPOP_EXIT, L"Exit");
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
            GetTextExtentPoint32( hdc, szCurrentCrawledPath[0], (int)wcslen(szCurrentCrawledPath[0]), &fontsize );
            for (int i=nCurrentCrawledpathIndex; i<MAX_CRAWLEDPATHS; ++i)
            {
                TextOut(hdc, 0, line*fontsize.cy, szCurrentCrawledPath[i], (int)wcslen(szCurrentCrawledPath[i]));
                ++line;
            }
            for (int i=0; i<nCurrentCrawledpathIndex; ++i)
            {
                TextOut(hdc, 0, line*fontsize.cy, szCurrentCrawledPath[i], (int)wcslen(szCurrentCrawledPath[i]));
                ++line;
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
            bRun = false;
            CAutoWriteWeakLock writeLock(CSVNStatusCache::Instance().GetGuard(), 200);
            CSVNStatusCache::Instance().Stop();

            return TRUE;
        }
        break;
    case WM_CLOSE:
    case WM_ENDSESSION:
    case WM_DESTROY:
    case WM_QUIT:
        {
            ATLTRACE("WM_CLOSE/DESTROY/ENDSESSION/QUIT\n");
            bRun = false;
            CAutoWriteLock writeLock(CSVNStatusCache::Instance().GetGuard());
            CSVNStatusCache::Instance().Stop();
            CSVNStatusCache::Instance().SaveCache();
            if (message != WM_QUIT)
                PostQuitMessage(0);
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
                    CTraceToOutputDebugString::Instance()(__FUNCTION__ ": WM_DEVICECHANGE with DBT_CUSTOMEVENT\n");
                    if (phdr->dbch_devicetype == DBT_DEVTYP_HANDLE)
                    {
                        DEV_BROADCAST_HANDLE * phandle = (DEV_BROADCAST_HANDLE*)lParam;
                        if (IsEqualGUID(phandle->dbch_eventguid, GUID_IO_VOLUME_DISMOUNT))
                        {
                            CTraceToOutputDebugString::Instance()(__FUNCTION__ ": Device to be dismounted\n");
                            CAutoWriteLock writeLock(CSVNStatusCache::Instance().GetGuard());
                            CSVNStatusCache::Instance().CloseWatcherHandles(phandle->dbch_handle);
                        }
                        if (IsEqualGUID(phandle->dbch_eventguid, GUID_IO_VOLUME_LOCK))
                        {
                            CTraceToOutputDebugString::Instance()(__FUNCTION__ ": Device lock event\n");
                            CAutoWriteLock writeLock(CSVNStatusCache::Instance().GetGuard());
                            CSVNStatusCache::Instance().CloseWatcherHandles(phandle->dbch_handle);
                        }
                    }
                }
                break;
            case DBT_DEVICEREMOVEPENDING:
            case DBT_DEVICEQUERYREMOVE:
            case DBT_DEVICEREMOVECOMPLETE:
                CTraceToOutputDebugString::Instance()(__FUNCTION__ ": WM_DEVICECHANGE with DBT_DEVICEREMOVEPENDING/QUERYREMOVE/REMOVECOMPLETE\n");
                if (phdr->dbch_devicetype == DBT_DEVTYP_HANDLE)
                {
                    DEV_BROADCAST_HANDLE * phandle = (DEV_BROADCAST_HANDLE*)lParam;
                    CAutoWriteLock writeLock(CSVNStatusCache::Instance().GetGuard());
                    CSVNStatusCache::Instance().CloseWatcherHandles(phandle->dbch_handle);
                }
                else if (phdr->dbch_devicetype == DBT_DEVTYP_VOLUME)
                {
                    DEV_BROADCAST_VOLUME * pVolume = (DEV_BROADCAST_VOLUME*)lParam;
                    CAutoWriteLock writeLock(CSVNStatusCache::Instance().GetGuard());
                    for (BYTE i = 0; i < 26; ++i)
                    {
                        if (pVolume->dbcv_unitmask & (1 << i))
                        {
                            TCHAR driveletter = 'A' + i;
                            CString drive = CString(driveletter);
                            drive += L":\\";
                            CSVNStatusCache::Instance().CloseWatcherHandles(CTSVNPath(drive));
                        }
                    }
                }
                else
                {
                    CAutoWriteLock writeLock(CSVNStatusCache::Instance().GetGuard());
                    CSVNStatusCache::Instance().CloseWatcherHandles(0);
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