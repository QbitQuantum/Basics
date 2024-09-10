static void OnMouseMessage(LCUI_Event ev, void *arg)
{
	MSG *msg = arg;
	LCUI_SysEventRec sys_ev;
	static POINT mouse_pos = { 0, 0 };
	sys_ev.type = LCUI_NONE;
	switch (msg->message) {
	case WM_MOUSEMOVE:
	{
		POINT new_pos;
		GetCursorPos(&new_pos);
		ScreenToClient(msg->hwnd, &new_pos);
		sys_ev.motion.x = new_pos.x;
		sys_ev.motion.y = new_pos.y;
		sys_ev.motion.xrel = new_pos.x - mouse_pos.x;
		sys_ev.motion.yrel = new_pos.y - mouse_pos.y;
		mouse_pos.x = new_pos.x;
		mouse_pos.y = new_pos.y;
		sys_ev.type = LCUI_MOUSEMOVE;
		break;
	}
	case WM_LBUTTONDOWN:
		sys_ev.type = LCUI_MOUSEDOWN;
		sys_ev.button.button = LCUI_KEY_LEFTBUTTON;
		sys_ev.button.x = mouse_pos.x;
		sys_ev.button.y = mouse_pos.y;
		SetCapture(msg->hwnd);
		break;
	case WM_LBUTTONUP:
		sys_ev.type = LCUI_MOUSEUP;
		sys_ev.button.button = LCUI_KEY_LEFTBUTTON;
		sys_ev.button.x = mouse_pos.x;
		sys_ev.button.y = mouse_pos.y;
		ReleaseCapture();
		break;
	case WM_RBUTTONDOWN:
		sys_ev.type = LCUI_MOUSEDOWN;
		sys_ev.button.button = LCUI_KEY_RIGHTBUTTON;
		sys_ev.button.x = mouse_pos.x;
		sys_ev.button.y = mouse_pos.y;
		SetCapture(msg->hwnd);
		break;
	case WM_RBUTTONUP:
		sys_ev.type = LCUI_MOUSEUP;
		sys_ev.button.button = LCUI_KEY_RIGHTBUTTON;
		sys_ev.button.x = mouse_pos.x;
		sys_ev.button.y = mouse_pos.y;
		ReleaseCapture();
		break;
	case WM_MOUSEWHEEL:
		sys_ev.type = LCUI_MOUSEWHEEL;
		sys_ev.wheel.x = mouse_pos.x;
		sys_ev.wheel.y = mouse_pos.y;
		sys_ev.wheel.delta = GET_WHEEL_DELTA_WPARAM(msg->wParam);
		break;
#ifdef ENABLE_TOUCH_SUPPORT
	case WM_TOUCH:
	{
		UINT i, n = LOWORD(msg->wParam);
		PTOUCHINPUT inputs = NEW(TOUCHINPUT, n);
		HTOUCHINPUT handle = (HTOUCHINPUT)msg->lParam;
		if (inputs == NULL) {
			break;
		}
		sys_ev.type = LCUI_TOUCH;
		sys_ev.touch.n_points = n;
		sys_ev.touch.points = NEW(LCUI_TouchPointRec, n);
		if (sys_ev.touch.points == NULL) {
			free(inputs);
			break;
		}
		if (!GetTouchInputInfo(handle, n, inputs,
				       sizeof(TOUCHINPUT))) {
			free(inputs);
			break;
		}
		for (i = 0; i < n; ++i) {
			POINT pos;
			pos.x = inputs[i].x / 100;
			pos.y = inputs[i].y / 100;
			ScreenToClient(msg->hwnd, &pos);
			sys_ev.touch.points[i].x = pos.x;
			sys_ev.touch.points[i].y = pos.y;
			sys_ev.touch.points[i].id = inputs[i].dwID;
			if (inputs[i].dwFlags & TOUCHEVENTF_PRIMARY) {
				sys_ev.touch.points[i].is_primary = TRUE;
			} else {
				sys_ev.touch.points[i].is_primary = FALSE;
			}
			if (inputs[i].dwFlags & TOUCHEVENTF_DOWN) {
				sys_ev.touch.points[i].state = LCUI_TOUCHDOWN;
			} else if (inputs[i].dwFlags & TOUCHEVENTF_UP) {
				sys_ev.touch.points[i].state = LCUI_TOUCHUP;
			} else if (inputs[i].dwFlags & TOUCHEVENTF_MOVE) {
				sys_ev.touch.points[i].state = LCUI_TOUCHMOVE;
			}
		}
		free(inputs);
		if (!CloseTouchInputHandle(handle)) {
			break;
		}
		break;
	}
#endif
	default: break;
	}
	if (sys_ev.type != LCUI_NONE) {
		LCUI_TriggerEvent(&sys_ev, NULL);
		LCUI_DestroyEvent(&sys_ev);
	}
}