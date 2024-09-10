LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MMouse * mouse = MMouse::getInstance();
	MWindow * window = MWindow::getInstance();
	MWinEvent events;

	if(window->isActive())
	{
        switch(uMsg)
        {
        case WM_CREATE:
            {
                joySetCapture(hwnd, JOYSTICKID1, 0, FALSE);
                joySetCapture(hwnd, JOYSTICKID2, 0, FALSE);
            }
            break;

        case WM_KILLFOCUS:
            window->setFocus(false);
            break;

        case WM_SETFOCUS:
            window->setFocus(true);
            break;

        case WM_CLOSE:
            events.type = MWIN_EVENT_WINDOW_CLOSE;
            window->sendEvents(&events);
            return 0;

        case WM_DESTROY:
            {
                joyReleaseCapture(JOYSTICKID1);
                joyReleaseCapture(JOYSTICKID2);
            }
            break;

        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            events.type = MWIN_EVENT_KEY_DOWN;
			events.data[0] = (int)wParam;
            window->sendEvents(&events);
            break;

        case WM_SYSKEYUP:
        case WM_KEYUP:
            events.type = MWIN_EVENT_KEY_UP;
            events.data[0] = (int)wParam;
            window->sendEvents(&events);
            break;

        case WM_SIZE:
            events.type = MWIN_EVENT_WINDOW_RESIZE;
            events.data[0] = (int)LOWORD(lParam);
            events.data[1] = (int)HIWORD(lParam);
            window->sendEvents(&events);
            break;

        case WM_MOVE:
            events.type = MWIN_EVENT_WINDOW_MOVE;
			events.data[0] = (int)(short)LOWORD(lParam);
            events.data[1] = (int)(short)HIWORD(lParam);
            window->sendEvents(&events);
            break;

        case WM_LBUTTONDOWN:
            SetCapture(hwnd);
            events.type = MWIN_EVENT_MOUSE_BUTTON_DOWN;
            events.data[0] = (int)MMOUSE_BUTTON_LEFT;
			window->sendEvents(&events);
            break;

        case WM_LBUTTONUP:
            ReleaseCapture();
            events.type = MWIN_EVENT_MOUSE_BUTTON_UP;
            events.data[0] = (int)MMOUSE_BUTTON_LEFT;
            window->sendEvents(&events);
            break;

        case WM_CHAR:
            if(wParam == 8 || wParam == 32 || wParam == 13 || wParam == 9) // not return, space, delete etc..
				break;

            events.type = MWIN_EVENT_CHAR;
            events.data[0] = (int)(char)wParam;
            window->sendEvents(&events);
            break;

        case WM_MBUTTONDOWN:
            SetCapture(hwnd);
            events.type = MWIN_EVENT_MOUSE_BUTTON_DOWN;
            events.data[0] = (int)MMOUSE_BUTTON_MIDDLE;
            window->sendEvents(&events);
            break;

        case WM_MBUTTONUP:
            ReleaseCapture();
            events.type = MWIN_EVENT_MOUSE_BUTTON_UP;
            events.data[0] = (int)MMOUSE_BUTTON_MIDDLE;
            window->sendEvents(&events);
            break;

        case WM_RBUTTONDOWN:
            SetCapture(hwnd);
            events.type = MWIN_EVENT_MOUSE_BUTTON_DOWN;
            events.data[0] = (int)MMOUSE_BUTTON_RIGHT;
            window->sendEvents(&events);
            break;

        case WM_RBUTTONUP:
            ReleaseCapture();
            events.type = MWIN_EVENT_MOUSE_BUTTON_UP;
            events.data[0] = (int)MMOUSE_BUTTON_RIGHT;
            window->sendEvents(&events);
            break;

        case WM_MOUSEWHEEL:
            events.type = MWIN_EVENT_MOUSE_WHEEL_MOVE;
            events.data[0] = CLAMP((int)((short)HIWORD(wParam) / (int)WHEEL_DELTA), -1, 1);
            window->sendEvents(&events);
            break;
        }
    }
	else
	{
	    switch(uMsg)
        {
	    case WM_NCPAINT:
            window->swapBuffer();
            break;
        }
	}

	// Pass All unhandled Messages To DefWindowProc
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}