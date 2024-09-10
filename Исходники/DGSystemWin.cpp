// This function processes the main loop
LRESULT CALLBACK _WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	WCHAR chars[2];
	static bool isDragging = false;
    BYTE keyboardState[256];

	int width = DGConfig::getInstance().displayWidth;
	int height = DGConfig::getInstance().displayHeight;

    switch(msg) {
		case WM_ACTIVATE:
			switch (wParam) {
				case WA_ACTIVE:
					if (_isMinimized) {
						LeaveCriticalSection(&csSystemThread);
						_isMinimized = false;
					}
					break;
			}
			break;
		case WM_ERASEBKGND:
			break;
		case WM_SIZE:
			switch (wParam) {
				case SIZE_MINIMIZED:
					EnterCriticalSection(&csSystemThread);
					_isMinimized = true;
					break;
				default:
					EnterCriticalSection(&csSystemThread);
					wglMakeCurrent(g_hDC, g_hRC);
					DGControl::getInstance().reshape(LOWORD(lParam), HIWORD(lParam));
					wglMakeCurrent(NULL, NULL);
					LeaveCriticalSection(&csSystemThread);
					break;
			}
			break;
		case WM_MOUSEMOVE:
			// For the fixed control mode, we reset the cursor position when it drifts out of the screen
			if (DGControl::getInstance().isDirectControlActive()) {
				if ((LOWORD(lParam) <= 1) || (LOWORD(lParam) >= (width - 1))) {
					SetCursorPos(width / 2, height / 2);
				}

				if ((HIWORD(lParam) <= 1) || (HIWORD(lParam) >= (height - 1))) {
					SetCursorPos(width / 2, height / 2);
				}
			}

			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
			if (isDragging)
				DGControl::getInstance().processMouse(LOWORD(lParam), HIWORD(lParam), DGMouseEventDrag);
			else
				DGControl::getInstance().processMouse(LOWORD(lParam), HIWORD(lParam), DGMouseEventMove);
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);

			if (GetCapture() != g_hWnd) {
				SetCapture(g_hWnd);
			}
			else {
				RECT rect;
				GetWindowRect(g_hWnd, &rect);

				POINT pt = { LOWORD(lParam), HIWORD(lParam) };
				ClientToScreen(g_hWnd, &pt);

				if (!PtInRect(&rect, pt)) {
					EnterCriticalSection(&csSystemThread);
					wglMakeCurrent(g_hDC, g_hRC);
					DGControl::getInstance().processMouse(width / 2, height / 2, DGMouseEventMove);
					wglMakeCurrent(NULL, NULL);
					LeaveCriticalSection(&csSystemThread);

					ReleaseCapture();
				}
			}
			break;
		case WM_LBUTTONDOWN:
			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
			DGControl::getInstance().processMouse(LOWORD(lParam), HIWORD(lParam), DGMouseEventDown);
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);
			isDragging = true;
			break;
		case WM_LBUTTONUP:
			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
			DGControl::getInstance().processMouse(LOWORD(lParam), HIWORD(lParam), DGMouseEventUp);
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);
			isDragging = false;
			break;
		case WM_RBUTTONDOWN:
			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
			DGControl::getInstance().processMouse(LOWORD(lParam), HIWORD(lParam), DGMouseEventRightDown);
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);
			break;
		case WM_RBUTTONUP:
			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
			DGControl::getInstance().processMouse(LOWORD(lParam), HIWORD(lParam), DGMouseEventRightUp);
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);
			break;
		case WM_KEYDOWN:
			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
            // A different switch to handle keystrokes
            switch(wParam) {
				case VK_F1:
				case VK_F2:
				case VK_F3:	
				case VK_F4:
				case VK_F5:
				case VK_F6:
				case VK_F7:
				case VK_F8:
				case VK_F9:
				case VK_F10:
				case VK_F11:
				case VK_F12:
					DGControl::getInstance().processFunctionKey(wParam);
					break;
				// Ignored keys
				case VK_SHIFT:
				case VK_CAPITAL:
				case VK_CONTROL:
				case VK_LWIN:
				case VK_RWIN:
					break;
				case VK_ESCAPE:
				case VK_TAB:
				case VK_SPACE:
				case VK_RETURN:
				case VK_BACK:	
					DGControl::getInstance().processKey(wParam, DGKeyEventDown);
					break;
				case VK_OEM_3: // Open console
					DGControl::getInstance().processKey(DGKeyTab, DGKeyEventDown);
					break;
				default:
					if (GetKeyState(VK_CONTROL) < 0) {
						ToUnicode(wParam, MapVirtualKey(wParam, 0), defKeyboardState, chars, 2, 0);
						DGControl::getInstance().processKey(chars[0], DGKeyEventModified);
					}
					else {
						GetKeyboardState(keyboardState);
						ToUnicode(wParam, MapVirtualKey(wParam, 0), keyboardState, chars, 2, 0);
						DGControl::getInstance().processKey(chars[0], DGKeyEventDown);
					}
					break;
			}
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);
			break;
		case WM_KEYUP:
			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
            GetKeyboardState(keyboardState);
            ToUnicode(wParam, MapVirtualKey(wParam, 0), keyboardState, chars, 2, 0);
            DGControl::getInstance().processKey(chars[0], DGKeyEventUp);
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);
			break;
        case WM_CLOSE:
            // Simulate the ESC key
			EnterCriticalSection(&csSystemThread);
			wglMakeCurrent(g_hDC, g_hRC);
            DGControl::getInstance().processKey(DGKeyEsc, false);
			wglMakeCurrent(NULL, NULL);
			LeaveCriticalSection(&csSystemThread);
			break;
        case WM_DESTROY:
		case WM_QUIT:			
        default:
            // Any other messages are passed to the default window process
            return DefWindowProc(hWnd, msg, wParam, lParam);
			break;
	}
	
	return 0;
}