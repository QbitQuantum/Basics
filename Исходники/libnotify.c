LRESULT CALLBACK notificationWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rc = {0};
	UINT notify_duration = 0;
	static BOOL is_fading_out = FALSE;
	static HHOOK hook_mouse_over = NULL;
	static NotifyNotification notification_data_copy = {L"", L"", ICON_INFO};

	switch (message)
	{
	case WM_LIBNOTIFYSHOW:
		/* close if already running */
		if(IsWindowVisible(hWnd))
		{
			SendMessage(hWnd, WM_LIBNOTIFYCLOSE, 0, 0);
		}
		/* guarded by CS to make sure notification_data doesn't get corrupted
		   when this code and notify_notification_update is running in parallel */
		{
			EnterCriticalSection(&thread_guard);
			NotifyNotification *notification_data = (NotifyNotification*) lParam;
			if(notification_data &&
			   notification_data->body &&
			   notification_data->summary)
			{
				notification_data_copy = *notification_data;
			}
			else
			{
				LeaveCriticalSection(&thread_guard);
				break;
			}
			LeaveCriticalSection(&thread_guard);
		}

		/* deduce the allowed text width from the max width; see geometry for rationale */
		rc.right = notification_window_width_max - (icon_size + (icon_padding * 3));

		hdc = GetDC(hWnd);
		if(hdc)
		{
			HRGN hRgn = NULL;
			HGDIOBJ hOldFont = SelectObject(hdc, (HGDIOBJ) font_body);
			if(hOldFont)
			{
				DrawText(hdc,
						 notification_data_copy.body,
						 -1,
						 &rc,
						 DT_CALCRECT | DT_WORDBREAK |
						 DT_EDITCONTROL | DT_NOCLIP |
						 DT_NOPREFIX | DT_EXTERNALLEADING);

				SelectObject(hdc, hOldFont);
			}

			ReleaseDC(hWnd, hdc);
			if(!hOldFont) return 0;	/* exit if font selection failed */

			/* calculate the actual bounding rectangle from the DrawText output */
			notify_wnd.notification_window_height = notify_wnd.summary_body_divider +
													rc.bottom +
													(icon_padding * 3);
			notify_wnd.notification_window_width = rc.right + icon_size + (icon_padding * 3);

			/* word count * milliseconds per word */
			notify_duration = word_count(notification_data_copy.body) * milliseconds_per_word;

			/* in case the calculation renders too low a value, replace it with a de facto minimum */
			notify_duration = MAX(notify_duration, min_notification_timeout);

			/* get the screen area uncluttered by the taskbar */
			if(SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0))
			{
				LONG window_x = 0, window_y = 0;

				/* system tray @ right bottom */
				if((rc.bottom != GetSystemMetrics(SM_CYSCREEN)) ||
					(rc.right != GetSystemMetrics(SM_CXSCREEN)))
				{
					window_x = rc.right -
							   (GetSystemMetrics(SM_CXSCREEN) / window_offset_factor) -
							   notify_wnd.notification_window_width;
					window_y = rc.bottom -
							   (GetSystemMetrics(SM_CYSCREEN) / window_offset_factor) -
							   notify_wnd.notification_window_height;
				}
				else if(rc.left != 0)	/* left bottom */
				{
					window_x = rc.left +
							   (GetSystemMetrics(SM_CXSCREEN) / window_offset_factor);
					window_y = rc.bottom -
							   (GetSystemMetrics(SM_CYSCREEN) / window_offset_factor) -
							   notify_wnd.notification_window_height;
				}
				else					/* right top */
				{
					window_x = rc.right -
							   (GetSystemMetrics(SM_CXSCREEN) / window_offset_factor) -
							   notify_wnd.notification_window_width;
					window_y = rc.top +
							   (GetSystemMetrics(SM_CYSCREEN) / window_offset_factor);
				}

				/* resize and reposition the window */
				MoveWindow(hWnd,
						   window_x,
						   window_y,
						   notify_wnd.notification_window_width,
						   notify_wnd.notification_window_height,
						   TRUE);

				/* set the new positions to be used by the mouse over hook */
				notify_wnd.notification_window_rect.left = window_x;
				notify_wnd.notification_window_rect.top = window_y;
				notify_wnd.notification_window_rect.right = window_x + notify_wnd.notification_window_width;
				notify_wnd.notification_window_rect.bottom = window_y + notify_wnd.notification_window_height;

				/* make it as a rounded rect. */
				hRgn = CreateRoundRectRgn(0,
										  0,
										  notify_wnd.notification_window_width,
										  notify_wnd.notification_window_height,
										  rounded_rect_edge,
										  rounded_rect_edge);
				SetWindowRgn(hWnd, hRgn, TRUE);

				/* since bRedraw is set to TRUE in SetWindowRgn invalidation isn't required */
				/*InvalidateRect(hWnd, NULL, TRUE);*/

				/* show the window and set the timers for animation and overall visibility */
				ShowWindow(hWnd, SW_SHOWNOACTIVATE);

				SetTimer(hWnd, TIMER_ANIMATION, fade_duration, NULL);
				SetTimer(hWnd, TIMER_NOTIFICATION, notify_duration, NULL);
			}
		}
		break;
	case WM_LIBNOTIFYCLOSE:
		/* clean up and reset flags */
		{
			if(hook_mouse_over)
			{
				UnhookWindowsHookEx(hook_mouse_over);
				hook_mouse_over = NULL;
			}

			KillTimer(hWnd, TIMER_ANIMATION);
			KillTimer(hWnd, TIMER_NOTIFICATION);
			is_fading_out = FALSE;

			ShowWindow(hWnd, SW_HIDE);
		}
		break;
	case WM_PAINT:
		if((L'\0' != notification_data_copy.body[0]) &&
		   (L'\0' != notification_data_copy.summary[0]))
		{
			hdc = BeginPaint(hWnd, &ps);

			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);

			HGDIOBJ hOldFont = SelectObject(hdc, (HGDIOBJ) font_summary);

			if(hOldFont)
			{
				/* set the padding as left offset and center the icon horizontally */
				DrawIcon(hdc,
						 icon_padding,
						 (notify_wnd.notification_window_height / 2) - (icon_size / 2),
						 notification_icons[notification_data_copy.icon_req]);

				/* calculate and DrawText for both summary and body
				   based on the geometry given above */
				rc.left = icon_size + (icon_padding * 2);
				rc.right = notify_wnd.notification_window_width - icon_padding;
				rc.top = icon_padding;
				rc.bottom = notify_wnd.summary_body_divider + (icon_padding * 2);

				DrawText(hdc,
						 notification_data_copy.summary,
						 -1,
						 &rc,
						 DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX);

				if(SelectObject(hdc, (HGDIOBJ) font_body))
				{
					rc.top = rc.bottom;
					rc.bottom = notify_wnd.notification_window_height - icon_padding;

					DrawText(hdc,
							 notification_data_copy.body,
							 -1,
							 &rc,
							 DT_WORDBREAK | DT_EDITCONTROL |
							 DT_NOCLIP | DT_NOPREFIX |
							 DT_EXTERNALLEADING);
				}

				SelectObject(hdc, hOldFont);
			}

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_LIBNOTIFYEXIT:
		if(hook_mouse_over)
		{
			UnhookWindowsHookEx(hook_mouse_over);
			hook_mouse_over = NULL;
		}

		KillTimer(notify_wnd.notification_window, TIMER_ANIMATION);
		KillTimer(notify_wnd.notification_window, TIMER_NOTIFICATION);
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		if(IsWindowVisible(hWnd))
		{
			if(wParam == TIMER_ANIMATION)	/* notification animation timer */
			{
				if(is_fading_out)
				{
					if(notify_wnd.notification_window_alpha > 5)
					{
						notify_wnd.notification_window_alpha -= 25;
					}
					else
					{
						/* once fully faded out, self destroy and reset the flags */
						KillTimer(hWnd, TIMER_ANIMATION);
						is_fading_out = FALSE;
						notify_wnd.notification_window_alpha = 0;
						SendMessage(hWnd, WM_LIBNOTIFYCLOSE, 0, 0);
					}
				}
				else
				{
					if(notify_wnd.notification_window_alpha < 250)
					{
						notify_wnd.notification_window_alpha += 25;
					}
					else
					{
						/* self destory as alpha reaches the maximum */
						KillTimer(hWnd, TIMER_ANIMATION);
						notify_wnd.notification_window_alpha = 255;

						/* set the mouse over hook once the window is fully visible */
						hook_mouse_over = SetWindowsHookEx(WH_MOUSE_LL,
														   mouse_over_hook_proc,
														   (HINSTANCE) GetModuleHandle(NULL),
														   0);
					}
				}
				/* for all the above cases set the newly calculated alpha */
				SetLayeredWindowAttributes(notify_wnd.notification_window,
										   0,
										   notify_wnd.notification_window_alpha,
										   LWA_ALPHA);
			}
			else	/* notification duration timer */
			{
				/* self destruct once timed out */
				KillTimer(hWnd, TIMER_NOTIFICATION);

				/* kill the hook set by animation timer */
				if(hook_mouse_over)
				{
					UnhookWindowsHookEx(hook_mouse_over);
					hook_mouse_over = NULL;
				}

				/* start fading out sequence */
				is_fading_out = TRUE;
				SetTimer(hWnd, TIMER_ANIMATION, fade_duration, NULL);
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}