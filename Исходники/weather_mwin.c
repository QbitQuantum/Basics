static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	MWinDataType *data = (MWinDataType*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch(msg) 
	{
	case WM_CREATE:
		data = (MWinDataType*)mir_calloc(sizeof(MWinDataType));
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);

		data->hContact = (HANDLE)((LPCREATESTRUCT)lParam)->lpCreateParams;
		data->hAvt = CreateWindow(AVATAR_CONTROL_CLASS, TEXT(""), WS_CHILD, 
			0, 0, opt.AvatarSize, opt.AvatarSize, hwnd, NULL, hInst, 0);
		if (data->hAvt) SendMessage(data->hAvt, AVATAR_SETCONTACT, 0, (LPARAM)data->hContact);
		break;

	case WM_DESTROY:
		mir_free(data);
		break;

	case WM_CONTEXTMENU:
		{
			POINT pt;
			HMENU hMenu;

			hMenu = (HMENU)CallService(MS_CLIST_MENUBUILDCONTACT, (WPARAM)data->hContact, 0);
			GetCursorPos(&pt);
			TrackPopupMenu(hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
			DestroyMenu(hMenu);
		}
		break;

	case WM_MOUSEMOVE:
		if (f_TrackMouseEvent)
		{
			TRACKMOUSEEVENT tme = {0};
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_QUERY;
			f_TrackMouseEvent(&tme);

			if (tme.dwFlags == 0)
			{
				tme.dwFlags = TME_HOVER | TME_LEAVE;
				tme.hwndTrack = hwnd;
				tme.dwHoverTime = CallService(MS_CLC_GETINFOTIPHOVERTIME, 0, 0);
				f_TrackMouseEvent(&tme);
			}
		}
		break;

	case WM_MOUSEHOVER:
		{
			POINT pt;
			CLCINFOTIP ti = {0};

			GetCursorPos(&pt);
			GetWindowRect(hwnd, &ti.rcItem);

			ti.cbSize = sizeof(ti);
			ti.hItem = data->hContact;
			ti.ptCursor = pt;
			ti.isTreeFocused = 1;
			CallService(MS_TOOLTIP_SHOWTIP, 0, (LPARAM)&ti);
		}
		break;

	case WM_LBUTTONDBLCLK:
		BriefInfo((WPARAM)data->hContact, 0);
		break;

	case WM_COMMAND:	 //Needed by the contact's context menu
		if (CallService(MS_CLIST_MENUPROCESSCOMMAND, MAKEWPARAM(LOWORD(wParam),MPCF_CONTACTMENU), (LPARAM)data->hContact))
			break;
		return FALSE;

	case WM_MEASUREITEM:	//Needed by the contact's context menu
		return CallService(MS_CLIST_MENUMEASUREITEM, wParam, lParam);

	case WM_DRAWITEM:	//Needed by the contact's context menu
		return CallService(MS_CLIST_MENUDRAWITEM, wParam, lParam);

	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == NM_AVATAR_CHANGED)
		{
			BOOL newava = CallService(MS_AV_GETAVATARBITMAP, (WPARAM)data->hContact, 0) != 0;
			if (newava != data->haveAvatar)
			{
				LONG_PTR style = GetWindowLongPtr(data->hAvt, GWL_STYLE);
				data->haveAvatar = newava;
				SetWindowLongPtr(data->hAvt, GWL_STYLE, newava ? (style | WS_VISIBLE) : (style & ~WS_VISIBLE));
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			}
		}
		break;

	case WM_REDRAWWIN:
		if (data->hAvt != NULL) MoveWindow(data->hAvt, 0, 0, opt.AvatarSize, opt.AvatarSize, TRUE);
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		break;

	case WM_PAINT:
		{
			RECT r, rc;

			if(GetUpdateRect(hwnd, &r, FALSE)) 
			{
				DBVARIANT dbv = {0};
				PAINTSTRUCT ps;
				HDC hdc;
				LOGFONT lfnt, lfnt1;
				COLORREF fntc, fntc1;
				COLORREF clr;
				int picSize = opt.AvatarSize;
				HICON hIcon = NULL;

				if (!data->haveAvatar)
				{
					int statusIcon = DBGetContactSettingWord(data->hContact, WEATHERPROTONAME, "Status", 0);

					picSize = GetSystemMetrics(SM_CXICON);
					hIcon = LoadSkinnedProtoIconBig(WEATHERPROTONAME, statusIcon);
					if ((INT_PTR)hIcon == CALLSERVICE_NOTFOUND) 
					{
						picSize = GetSystemMetrics(SM_CXSMICON);
						hIcon = LoadSkinnedProtoIcon(WEATHERPROTONAME, statusIcon);
					}
				}

				clr = DBGetContactSettingDword(NULL, WEATHERPROTONAME, "ColorMwinFrame", GetSysColor(COLOR_3DFACE));

				{
					FontID fntid = {0};
					strcpy(fntid.group, WEATHERPROTONAME);
					strcpy(fntid.name, "Frame Font");
					fntc = CallService(MS_FONT_GET, (WPARAM)&fntid, (LPARAM)&lfnt);

					strcpy(fntid.name, "Frame Title Font");
					fntc1 = CallService(MS_FONT_GET, (WPARAM)&fntid, (LPARAM)&lfnt1);
				}

				DBGetContactSettingString(data->hContact, WEATHERCONDITION, "WeatherInfo", &dbv);

				GetClientRect(hwnd, &rc);

				hdc = BeginPaint(hwnd, &ps);

				if (ServiceExists(MS_SKIN_DRAWGLYPH))
				{
					SKINDRAWREQUEST rq;
					memset(&rq, 0, sizeof(rq));
					rq.hDC = hdc;
					rq.rcDestRect = rc;
					rq.rcClipRect = rc;

					strcpy(rq.szObjectID, "Main,ID=WeatherFrame");
					CallService(MS_SKIN_DRAWGLYPH, (WPARAM)&rq, 0);
				}

				if (clr != 0xFFFFFFFF)
				{
					HBRUSH hBkgBrush = CreateSolidBrush(clr);
					FillRect(hdc, &rc, hBkgBrush);
					DeleteObject(hBkgBrush);
				}

				if (!data->haveAvatar)
					DrawIconEx(hdc, 1, 1, hIcon, 0, 0, 0, NULL, DI_NORMAL);

				SetBkMode(hdc, TRANSPARENT);

				{
					HFONT hfnt = CreateFontIndirect(&lfnt1);
					HFONT hfntold = SelectObject(hdc, hfnt);
					SIZE fontSize;

					char *nick = (char*)CallService(MS_CLIST_GETCONTACTDISPLAYNAME, (WPARAM)data->hContact, 0);

					GetTextExtentPoint32(hdc, _T("|"), 1, &fontSize);

					rc.top += 1;
					rc.left += picSize + fontSize.cx;

					SetTextColor(hdc, fntc1);
					DrawText(hdc, nick, -1, &rc, DT_LEFT | DT_EXPANDTABS);

					rc.top += fontSize.cy;

					SelectObject(hdc, hfntold);
					DeleteObject(hfnt);
				}

				if (dbv.pszVal) 
				{
					HFONT hfnt = CreateFontIndirect(&lfnt);
					HFONT hfntold = SelectObject(hdc, hfnt);

					SetTextColor(hdc, fntc);
					DrawText(hdc, dbv.pszVal, -1, &rc, DT_LEFT | DT_EXPANDTABS);

					SelectObject(hdc, hfntold);
					DeleteObject(hfnt);
				}
				EndPaint(hwnd, &ps);
				CallService(MS_SKIN2_RELEASEICON, (WPARAM)hIcon, 0);
				DBFreeVariant(&dbv);
			}
			break;
		}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return(TRUE);
}