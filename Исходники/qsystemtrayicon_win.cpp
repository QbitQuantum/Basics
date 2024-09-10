/*
* This function tries to determine the icon geometry from the tray
*
* If it fails an invalid rect is returned.
*/
QRect QSystemTrayIconSys::findIconGeometry(const int iconId)
{
    static PtrShell_NotifyIconGetRect Shell_NotifyIconGetRect =
        (PtrShell_NotifyIconGetRect)QSystemLibrary::resolve(QLatin1String("shell32"), "Shell_NotifyIconGetRect");

    if (Shell_NotifyIconGetRect) {
        Q_NOTIFYICONIDENTIFIER nid;
        memset(&nid, 0, sizeof(nid));
        nid.cbSize = sizeof(nid);
        nid.hWnd = winId();
        nid.uID = iconId;

        RECT rect;
        HRESULT hr = Shell_NotifyIconGetRect(&nid, &rect);
        if (SUCCEEDED(hr)) {
            return QRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
        }
    }

    QRect ret;

    TBBUTTON buttonData;
    DWORD processID = 0;
    HWND trayHandle = FindWindow(L"Shell_TrayWnd", NULL);

    //find the toolbar used in the notification area
    if (trayHandle) {
        trayHandle = FindWindowEx(trayHandle, NULL, L"TrayNotifyWnd", NULL);
        if (trayHandle) {
            HWND hwnd = FindWindowEx(trayHandle, NULL, L"SysPager", NULL);
            if (hwnd) {
                hwnd = FindWindowEx(hwnd, NULL, L"ToolbarWindow32", NULL);
                if (hwnd)
                    trayHandle = hwnd;
            }
        }
    }

    if (!trayHandle)
        return ret;

    GetWindowThreadProcessId(trayHandle, &processID);
    if (processID <= 0)
        return ret;

    HANDLE trayProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ, 0, processID);
    if (!trayProcess)
        return ret;

    int buttonCount = SendMessage(trayHandle, TB_BUTTONCOUNT, 0, 0);
    LPVOID data = VirtualAllocEx(trayProcess, NULL, sizeof(TBBUTTON), MEM_COMMIT, PAGE_READWRITE);

    if ( buttonCount < 1 || !data ) {
        CloseHandle(trayProcess);
        return ret;
    }

    //search for our icon among all toolbar buttons
    for (int toolbarButton = 0; toolbarButton  < buttonCount; ++toolbarButton ) {
        SIZE_T numBytes = 0;
        DWORD appData[2] = { 0, 0 };
        SendMessage(trayHandle, TB_GETBUTTON, toolbarButton , (LPARAM)data);

        if (!ReadProcessMemory(trayProcess, data, &buttonData, sizeof(TBBUTTON), &numBytes))
            continue;

        if (!ReadProcessMemory(trayProcess, (LPVOID) buttonData.dwData, appData, sizeof(appData), &numBytes))
            continue;

        int currentIconId = appData[1];
        HWND currentIconHandle = (HWND) appData[0];
        bool isHidden = buttonData.fsState & TBSTATE_HIDDEN;

        if (currentIconHandle == winId() &&
                currentIconId == iconId && !isHidden) {
            SendMessage(trayHandle, TB_GETITEMRECT, toolbarButton , (LPARAM)data);
            RECT iconRect = {0, 0};
            if(ReadProcessMemory(trayProcess, data, &iconRect, sizeof(RECT), &numBytes)) {
                MapWindowPoints(trayHandle, NULL, (LPPOINT)&iconRect, 2);
                QRect geometry(iconRect.left + 1, iconRect.top + 1,
                               iconRect.right - iconRect.left - 2,
                               iconRect.bottom - iconRect.top - 2);
                if (geometry.isValid())
                    ret = geometry;
                break;
            }
        }
    }
    VirtualFreeEx(trayProcess, data, 0, MEM_RELEASE);
    CloseHandle(trayProcess);
    return ret;
}