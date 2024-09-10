static LRESULT CALLBACK
win_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WINWINDOW *win = (WINWINDOW *) GetWindowLong(hwnd, GWL_USERDATA);
	WINDISPLAY *mod = win ? win->fbv_Display : TNULL;
	if (mod)
	{
		TIMSG *imsg;
		switch (uMsg)
		{
			default:
				TDBPRINTF(TDB_TRACE,("uMsg: %08x\n", uMsg));
				break;

			case WM_CLOSE:
				if ((win->fbv_InputMask & TITYPE_CLOSE) &&
					(fb_getimsg(mod, win, &imsg, TITYPE_CLOSE)))
					fb_sendimsg(mod, win, imsg);
				return 0;

			case WM_ERASEBKGND:
				return 0;

			case WM_GETMINMAXINFO:
			{
				LPMINMAXINFO mm = (LPMINMAXINFO) lParam;
				TINT m1, m2, m3, m4;
				win_getminmax(win, &m1, &m2, &m3, &m4, TTRUE);
				mm->ptMinTrackSize.x = m1;
				mm->ptMinTrackSize.y = m2;
				mm->ptMaxTrackSize.x = m3;
				mm->ptMaxTrackSize.y = m4;
				return 0;
			}

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				if (BeginPaint(win->fbv_HWnd, &ps))
				{
					if ((win->fbv_InputMask & TITYPE_REFRESH) &&
						(fb_getimsg(mod, win, &imsg, TITYPE_REFRESH)))
					{
						imsg->timsg_X = ps.rcPaint.left;
						imsg->timsg_Y = ps.rcPaint.top;
						imsg->timsg_Width = ps.rcPaint.right - ps.rcPaint.left;
						imsg->timsg_Height = ps.rcPaint.bottom - ps.rcPaint.top;
						TDBPRINTF(TDB_TRACE,("dirty: %d %d %d %d\n",
							imsg->timsg_X, imsg->timsg_Y, imsg->timsg_Width,
							imsg->timsg_Height));
						fb_sendimsg(mod, win, imsg);
					}
					EndPaint(win->fbv_HWnd, &ps);
				}
				return 0;
			}

			case WM_ACTIVATE:
				#if 0
				TDBPRINTF(TDB_INFO,("Window %p - Focus: %d\n", win, (LOWORD(wParam) != WA_INACTIVE)));
				if (!win->fbv_Borderless && (win->fbv_InputMask & TITYPE_FOCUS) &&
					(fb_getimsg(mod, win, &imsg, TITYPE_FOCUS)))
				{
					imsg->timsg_Code = (LOWORD(wParam) != WA_INACTIVE);
					fb_sendimsg(mod, win, imsg);
				}
				#endif
				return 0;

			case WM_SIZE:
				win->fbv_Width = LOWORD(lParam);
				win->fbv_Height = HIWORD(lParam);
				if ((win->fbv_InputMask & TITYPE_NEWSIZE) &&
					(fb_getimsg(mod, win, &imsg, TITYPE_NEWSIZE)))
				{
					imsg->timsg_Width = win->fbv_Width;
					imsg->timsg_Height = win->fbv_Height;
					fb_sendimsg(mod, win, imsg);
				}
				return 0;

			case WM_CAPTURECHANGED:
				TDBPRINTF(TDB_INFO,("Capture changed\n"));
				break;

			case WM_MOUSEMOVE:
			{
				TINT x = LOWORD(lParam);
				TINT y = HIWORD(lParam);
				win->fbv_MouseX = x;
				win->fbv_MouseY = y;
				if ((win->fbv_InputMask & TITYPE_MOUSEMOVE) &&
					(fb_getimsg(mod, win, &imsg, TITYPE_MOUSEMOVE)))
				{
					imsg->timsg_MouseX = x;
					imsg->timsg_MouseY = y;
					fb_sendimsg(mod, win, imsg);
				}

				if (win->fbv_InputMask & TITYPE_MOUSEOVER)
				{
					POINT scrpos;
					GetCursorPos(&scrpos);
	// 				TDBPRINTF(20,("in window: %d\n",
	// 					(WindowFromPoint(scrpos) == win->fbv_HWnd)));
					#if 0
					POINT scrpos;
					if (GetCapture() != win->fbv_HWnd)
					{
						SetCapture(win->fbv_HWnd);
						if (fb_getimsg(mod, win, &imsg, TITYPE_MOUSEOVER))
						{
							imsg->timsg_Code = 1;
							TDBPRINTF(20,("Mouseover=true\n"));
							fb_sendimsg(mod, win, imsg);
						}
					}
					else
					{
						POINT scrpos;
						GetCursorPos(&scrpos);
						if ((WindowFromPoint(scrpos) != win->fbv_HWnd) ||
							(x < 0) || (y < 0) || (x >= win->fbv_Width) ||
							(y >= win->fbv_Height))
						{
							ReleaseCapture();
							if (fb_getimsg(mod, win, &imsg, TITYPE_MOUSEOVER))
							{
								imsg->timsg_Code = 0;
								TDBPRINTF(20,("Mouseover=false\n"));
								fb_sendimsg(mod, win, imsg);
							}
						}
					}
					#endif
				}
				return 0;
			}

			case WM_LBUTTONDOWN:
				if ((win->fbv_InputMask & TITYPE_MOUSEBUTTON) &&
					fb_getimsg(mod, win, &imsg, TITYPE_MOUSEBUTTON))
				{
					imsg->timsg_Code = TMBCODE_LEFTDOWN;
					fb_sendimsg(mod, win, imsg);
				}
				return 0;
			case WM_LBUTTONUP:
				if ((win->fbv_InputMask & TITYPE_MOUSEBUTTON) &&
					fb_getimsg(mod, win, &imsg, TITYPE_MOUSEBUTTON))
				{
					imsg->timsg_Code = TMBCODE_LEFTUP;
					fb_sendimsg(mod, win, imsg);
				}
				return 0;
			case WM_RBUTTONDOWN:
				if ((win->fbv_InputMask & TITYPE_MOUSEBUTTON) &&
					fb_getimsg(mod, win, &imsg, TITYPE_MOUSEBUTTON))
				{
					imsg->timsg_Code = TMBCODE_RIGHTDOWN;
					fb_sendimsg(mod, win, imsg);
				}
				return 0;
			case WM_RBUTTONUP:
				if ((win->fbv_InputMask & TITYPE_MOUSEBUTTON) &&
					fb_getimsg(mod, win, &imsg, TITYPE_MOUSEBUTTON))
				{
					imsg->timsg_Code = TMBCODE_RIGHTUP;
					fb_sendimsg(mod, win, imsg);
				}
				return 0;
			case WM_MBUTTONDOWN:
				if ((win->fbv_InputMask & TITYPE_MOUSEBUTTON) &&
					fb_getimsg(mod, win, &imsg, TITYPE_MOUSEBUTTON))
				{
					imsg->timsg_Code = TMBCODE_MIDDLEDOWN;
					fb_sendimsg(mod, win, imsg);
				}
				return 0;
			case WM_MBUTTONUP:
				if ((win->fbv_InputMask & TITYPE_MOUSEBUTTON) &&
					fb_getimsg(mod, win, &imsg, TITYPE_MOUSEBUTTON))
				{
					imsg->timsg_Code = TMBCODE_MIDDLEUP;
					fb_sendimsg(mod, win, imsg);
				}
				return 0;

			case WM_SYSKEYDOWN:
				processkey(mod, win, TITYPE_KEYDOWN, 0);
				return 0;

			case WM_SYSKEYUP:
				processkey(mod, win, TITYPE_KEYUP, 0);
				return 0;

			case WM_KEYDOWN:
				processkey(mod, win, TITYPE_KEYDOWN, wParam);
				return 0;

			case WM_KEYUP:
				processkey(mod, win, TITYPE_KEYUP, wParam);
				return 0;

			case 0x020a:
				if (win->fbv_InputMask & TITYPE_MOUSEBUTTON)
				{
					TINT16 zdelta = (TINT16) HIWORD(wParam);
					if (zdelta != 0 &&
						fb_getimsg(mod, win, &imsg, TITYPE_MOUSEBUTTON))
					{
						imsg->timsg_Code = zdelta > 0 ?
							TMBCODE_WHEELUP : TMBCODE_WHEELDOWN;
						fb_sendimsg(mod, win, imsg);
					}
				}
				return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}