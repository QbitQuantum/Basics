LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
    {
	case WM_CREATE:
		// register interest in raw data here
		rid.dwFlags = RIDEV_INPUTSINK;
		rid.usUsagePage = 1;
		rid.usUsage = 6;
		rid.hwndTarget = hWnd;
		RegisterRawInputDevices(&rid, 1, sizeof(rid));
		return DefWindowProc(hWnd, message, wParam, lParam);

	case WM_USER_HKLISTEN:
		g_acceptHotKey = true;
		break;

	case WM_INPUT: {
			if (!g_acceptHotKey) break;
			UINT dwSize;
			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER)) == -1) {
				break;
			}
			LPBYTE lpb = new BYTE[dwSize];
			if (lpb == NULL) {
				break;
			}
			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
				delete[] lpb;
				break;
			}
			PRAWINPUT raw = (PRAWINPUT)lpb;
			if (raw->data.keyboard.Message == WM_KEYDOWN) {
				if (raw->data.keyboard.VKey == g_hotKey) {
					if (GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(VK_CONTROL)) {
						LPWSTR sName = new wchar_t[1024];
						GetWindowText(g_hComboSection, sName, 1023);
						PopupData * pD = new PopupData();
						pD->parent = hWnd;
						pD->instance = hInst;
						pD->sname = sName;
						CreateThread(NULL, // default security attributes
							0,			// default stack size
							PopupThread,// start address (in Popup.cpp)
							pD,			// pass PopupData
							0,
							&popupThreadID
							);

						g_acceptHotKey = false;
					}
				}
			}
			break;
		}

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}