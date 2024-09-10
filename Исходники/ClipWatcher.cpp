//  clipWatcherWndProc
//
static LRESULT CALLBACK clipWatcherWndProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    //fwprintf(stderr, L"msg: %x, hWnd=%p, wParam=%p\n", uMsg, hWnd, wParam);

    switch (uMsg) {
    case WM_CREATE:
    {
        // Initialization.
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        ClipWatcher* watcher = (ClipWatcher*)(cs->lpCreateParams);
        if (watcher != NULL) {
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)watcher);
            if (logfp != NULL) {
                fwprintf(logfp, L"watcher: %s\n", watcher->name);
            }
            // Start watching the clipboard content.
            AddClipboardFormatListener(hWnd);
            SetTimer(hWnd, watcher->blink_timer_id, ICON_BLINK_INTERVAL, NULL);
            SetTimer(hWnd, watcher->check_timer_id, FILESYSTEM_INTERVAL, NULL);
            SendMessage(hWnd, WM_TASKBAR_CREATED, 0, 0);
        }
        return FALSE;
    }

    case WM_DESTROY:
    {
        // Clean up.
        LONG_PTR lp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        ClipWatcher* watcher = (ClipWatcher*)lp;
        if (watcher != NULL) {
            KillTimer(hWnd, watcher->blink_timer_id);
            KillTimer(hWnd, watcher->check_timer_id);
            // Stop watching the clipboard content.
            RemoveClipboardFormatListener(hWnd);
            // Unregister the icon.
            NOTIFYICONDATA nidata = {0};
            nidata.cbSize = sizeof(nidata);
            nidata.hWnd = hWnd;
            nidata.uID = watcher->icon_id;
            Shell_NotifyIcon(NIM_DELETE, &nidata);
        }
        PostQuitMessage(0);
        return FALSE;
    }

    case WM_CLIPBOARDUPDATE:
    {
        // Clipboard change detected.
        LONG_PTR lp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        ClipWatcher* watcher = (ClipWatcher*)lp;
        if (watcher != NULL) {
            DWORD seqno = GetClipboardSequenceNumber();
            if (watcher->seqno < seqno) {
                watcher->seqno = seqno;
                if (logfp != NULL) {
                    fwprintf(logfp, L"updated clipboard: seqno=%d\n", seqno);
                }
                for (int i = 0; i < CLIPBOARD_RETRY; i++) {
                    Sleep(CLIPBOARD_DELAY);
                    if (OpenClipboard(hWnd)) {
                        if (GetClipboardData(CF_ORIGIN) == NULL) {
                            WCHAR path[MAX_PATH];
                            StringCchPrintf(path, _countof(path), L"%s\\%s",
                                            watcher->dstdir, watcher->name);
                            exportClipFile(path);
                        }
                        WCHAR text[256];
                        int filetype = getClipboardText(text, _countof(text));
                        if (0 <= filetype) {
                            NOTIFYICONDATA nidata = {0};
                            nidata.cbSize = sizeof(nidata);
                            nidata.hWnd = hWnd;
                            nidata.uID = watcher->icon_id;
                            nidata.uFlags = NIF_INFO;
                            nidata.dwInfoFlags = NIIF_INFO;
                            nidata.uTimeout = 1;
                            StringCchCopy(nidata.szInfoTitle,
                                          _countof(nidata.szInfoTitle),
                                          MESSAGE_UPDATED);
                            StringCchCopy(nidata.szInfo,
                                          _countof(nidata.szInfo),
                                          text);
                            Shell_NotifyIcon(NIM_MODIFY, &nidata);
                            watcher->icon_blinking = HICON_FILETYPE[filetype];
                            watcher->icon_blink_count = ICON_BLINK_COUNT;
                        }
                        CloseClipboard();
                        break;
                    }
                }
            }
        }
        return FALSE;
    }

    case WM_NOTIFY_FILE:
    {
        // File change detected.
        LONG_PTR lp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        ClipWatcher* watcher = (ClipWatcher*)lp;
        if (watcher != NULL) {
            FileEntry* entry = checkFileChanges(watcher);
            if (entry != NULL) {
                if (logfp != NULL) {
                    fwprintf(logfp, L"updated file: path=%s\n", entry->path);
                }
                int index = rindex(entry->path, L'.');
                if (0 <= index) {
                    WCHAR* ext = &(entry->path[index]);
                    if (_wcsicmp(ext, FILE_EXT_TEXT) == 0) {
                        // CF_UNICODETEXT
                        int nchars;
                        LPWSTR text = readTextFile(entry->path, &nchars);
                        if (text != NULL) {
                            if (OpenClipboard(hWnd)) {
                                EmptyClipboard();
                                setClipboardOrigin(entry->path);
                                setClipboardText(text, nchars);
                                CloseClipboard();
                            }
                            free(text);
                        }
                    } else if (_wcsicmp(ext, FILE_EXT_BITMAP) == 0) {
                        // CF_DIB
                        BITMAPINFO* bmp = readBMPFile(entry->path);
                        if (bmp != NULL) {
                            if (OpenClipboard(hWnd)) {
                                EmptyClipboard();
                                setClipboardOrigin(entry->path);
                                setClipboardDIB(bmp);
                                CloseClipboard();
                            }
                            free(bmp);
                        }
                    }
                }
            }
        }
        return FALSE;
    }

    case WM_COMMAND:
    {
        // Command specified.
        LONG_PTR lp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        ClipWatcher* watcher = (ClipWatcher*)lp;
        switch (LOWORD(wParam)) {
        case IDM_OPEN:
            if (watcher != NULL) {
                if (OpenClipboard(hWnd)) {
                    openClipFile();
                    CloseClipboard();
                }
            }
            break;
        case IDM_EXIT:
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        }
        return FALSE;
    }

    case WM_TIMECHANGE:
    {
        // Filesytem/Network share change detected.
        // NOTICE: We wanted to check if wParam is DBT_DEVICEARRIVAL.
        //   But it doesn't work when the system is suspended.
        LONG_PTR lp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        ClipWatcher* watcher = (ClipWatcher*)lp;
        if (watcher != NULL) {
            // Re-initialize the watcher object.
            StopClipWatcher(watcher);
        }
        return TRUE;
    }

    case WM_NOTIFY_ICON:
    {
        // UI event handling.
        POINT pt;
        HMENU menu = GetMenu(hWnd);
        if (menu != NULL) {
            menu = GetSubMenu(menu, 0);
        }
        switch (lParam) {
        case WM_LBUTTONDBLCLK:
            if (menu != NULL) {
                UINT item = GetMenuDefaultItem(menu, FALSE, 0);
                SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(item, 1), NULL);
            }
            break;
        case WM_LBUTTONUP:
            break;
        case WM_RBUTTONUP:
            if (GetCursorPos(&pt)) {
                SetForegroundWindow(hWnd);
                if (menu != NULL) {
                    TrackPopupMenu(menu, TPM_LEFTALIGN,
                                   pt.x, pt.y, 0, hWnd, NULL);
                }
                PostMessage(hWnd, WM_NULL, 0, 0);
            }
            break;
        }
        return FALSE;
    }

    case WM_TIMER:
    {
        LONG_PTR lp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        ClipWatcher* watcher = (ClipWatcher*)lp;
        if (watcher != NULL) {
            UINT_PTR timer_id = wParam;
            if (timer_id == watcher->blink_timer_id) {
                // Blink the icon.
                if (watcher->icon_blink_count) {
                    watcher->icon_blink_count--;
                    BOOL on = (watcher->icon_blink_count % 2);
                    NOTIFYICONDATA nidata = {0};
                    nidata.cbSize = sizeof(nidata);
                    nidata.hWnd = hWnd;
                    nidata.uID = watcher->icon_id;
                    nidata.uFlags = NIF_ICON;
                    nidata.hIcon = (on? watcher->icon_blinking : HICON_EMPTY);
                    Shell_NotifyIcon(NIM_MODIFY, &nidata);
                }
            } else if (timer_id == watcher->check_timer_id) {
                // Check the filesystem.
                StartClipWatcher(watcher);
            }
        }
        return FALSE;
    }

    case WM_CLOSE:
        DestroyWindow(hWnd);
        return FALSE;

    default:
        if (uMsg == WM_TASKBAR_CREATED) {
            LONG_PTR lp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
            ClipWatcher* watcher = (ClipWatcher*)lp;
            if (watcher != NULL) {
                // Register the icon.
                NOTIFYICONDATA nidata = {0};
                nidata.cbSize = sizeof(nidata);
                nidata.hWnd = hWnd;
                nidata.uID = watcher->icon_id;
                nidata.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
                nidata.uCallbackMessage = WM_NOTIFY_ICON;
                nidata.hIcon = HICON_EMPTY;
                StringCchPrintf(nidata.szTip, _countof(nidata.szTip),
                                MESSAGE_WATCHING, watcher->srcdir);
                Shell_NotifyIcon(NIM_ADD, &nidata);
            }
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}