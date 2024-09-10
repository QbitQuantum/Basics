/**
 * This is the message procedure for my nice looking message box
 *
 * @param	hDlg		- window handle
 * @param	uMsg		- message to handle
 * @param	wParam		- message specific parameter
 * @param	lParam		- message specific parameter
 *
 * @return	TRUE, FALSE, IDOK, IDYES, IDALL, IDNO or IDCANCEL
 **/
static INT_PTR CALLBACK MsgBoxProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int retOk = IDOK;
	static int retAll = IDALL;
	static int retNon = IDNONE;
	static int retCancel = IDCANCEL;

	switch (uMsg) {
	case WM_INITDIALOG:
		{
			LPMSGBOX pMsgBox = (LPMSGBOX)lParam;
			if (PtrIsValid(pMsgBox)) {
				int icoWidth = 0;
				int InfoBarHeight = 0;
				HFONT hNormalFont;

				hNormalFont = (HFONT)SendDlgItemMessage(hDlg, TXT_NAME, WM_GETFONT, 0, 0);
				if (pMsgBox->uType & MB_INFOBAR) {
					LOGFONT lf;

					// set bold font for name in description area
					GetObject(hNormalFont, sizeof(lf), &lf);
					lf.lfWeight = FW_BOLD;
					hNormalFont = CreateFontIndirect(&lf);

					// set infobar's textfont
					SendDlgItemMessage(hDlg, TXT_NAME, WM_SETFONT, (WPARAM)hNormalFont, 0);

					// set infobar's logo icon
					SendDlgItemMessage(hDlg, ICO_DLGLOGO, STM_SETIMAGE, IMAGE_ICON,
						(pMsgBox->hiLogo ? (LPARAM)pMsgBox->hiLogo : (LPARAM)IcoLib_GetIcon(ICO_DLG_DETAILS,TRUE)));

					// enable headerbar
					ShowWindow(GetDlgItem(hDlg, TXT_NAME), SW_SHOW);
					ShowWindow(GetDlgItem(hDlg, ICO_DLGLOGO), SW_SHOW);
				}
				else {
					RECT rc;
					GetClientRect(GetDlgItem(hDlg, TXT_NAME), &rc);
					InfoBarHeight = rc.bottom;

					if (pMsgBox->hiLogo)
						SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)pMsgBox->hiLogo);
				}

				// draw the desired status icon
				HICON hIcon = MsgLoadIcon(pMsgBox);
				if (hIcon)
					SendDlgItemMessage(hDlg, ICO_MSGDLG, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
				else {
					RECT ws;
					GetWindowRect(GetDlgItem(hDlg, ICO_MSGDLG), &ws);
					icoWidth = ws.right - ws.left;
					ShowWindow(GetDlgItem(hDlg, ICO_MSGDLG), SW_HIDE);
				}

				// resize the messagebox and reorganize the buttons
				if (HDC hDC = GetDC(hDlg)) {
					POINT mpt = { 0, 0 };
					RECT ws = { 0, 0, 0, 0 };
					int txtWidth=0, txtHeight=0, needX, needY;
					RECT rcDlg;
					SIZE ts;
					LPTSTR h, rs;

					SelectObject(hDC, hNormalFont);
					// get message text width and height
					if(pMsgBox->ptszMsg) for (rs=h=pMsgBox->ptszMsg; ; ++h) {
						if (*h=='\n' || !*h) {
							GetTextExtentPoint32(hDC, rs, h-rs, &ts);
							if (ts.cx > txtWidth)
								txtWidth = ts.cx;
							txtHeight += ts.cy;
							if (!*h)
								break;
							rs = h+1;
						}
					}
					// increase width if info text requires more
					if((pMsgBox->uType&MB_INFOBAR) && pMsgBox->ptszInfoText && *pMsgBox->ptszInfoText){
						//int multiline = 0;
						RECT rcico; GetClientRect(GetDlgItem(hDlg,ICO_DLGLOGO), &rcico);
						rcico.right = rcico.right*100/66; // padding
						for(rs=h=pMsgBox->ptszInfoText; ; ++h) {
							if (*h=='\n' || !*h) {
								GetTextExtentPoint32(hDC, rs, h-rs, &ts);
								ts.cx += rcico.right;
								if (ts.cx > txtWidth)
									txtWidth = ts.cx;
								if (!*h)
									break;
								rs = h+1;
								//++multiline;
							}
						}
						/* used by SendSS, disabled for UserInfoEx for now
						if(!multiline)
							SetWindowLongPtr(GetDlgItem(hDlg,TXT_NAME), GWL_STYLE, GetWindowLongPtr(GetDlgItem(hDlg,TXT_NAME), GWL_STYLE)|SS_CENTERIMAGE); */
					}
					ReleaseDC(hDlg, hDC);

					// calc new dialog size
					GetWindowRect(hDlg, &rcDlg);
					GetWindowRect(GetDlgItem(hDlg, TXT_MESSAGE), &ws);
					needX = txtWidth - (ws.right - ws.left) - icoWidth;
					needY = max(0, txtHeight - (ws.bottom - ws.top) + 5);
					rcDlg.left -= needX/2; rcDlg.right += needX/2;
					rcDlg.top -= (needY-InfoBarHeight)/2; rcDlg.bottom += (needY-InfoBarHeight)/2;

					// resize dialog window
					MoveWindow(hDlg, rcDlg.left, rcDlg.top, rcDlg.right - rcDlg.left, rcDlg.bottom - rcDlg.top, FALSE);
					ClientToScreen(hDlg, &mpt);

					MoveCtrl(hDlg, STATIC_WHITERECT, -mpt.x, -mpt.y, needX, needY - InfoBarHeight);
					MoveCtrl(hDlg, TXT_NAME, -mpt.x, -mpt.y, needX, 0);
					MoveCtrl(hDlg, ICO_DLGLOGO, -mpt.x + needX, -mpt.y, 0, 0);
					MoveCtrl(hDlg, ICO_MSGDLG, -mpt.x, -mpt.y - InfoBarHeight, 0, 0);
					MoveCtrl(hDlg, TXT_MESSAGE, -mpt.x - icoWidth, -mpt.y - InfoBarHeight, needX, needY);
					MoveCtrl(hDlg, STATIC_LINE2, -mpt.x, -mpt.y + needY - InfoBarHeight, needX, 0);

					//
					// Do pushbutton positioning
					//
					RECT rcOk, rcAll, rcNone, rcCancel;

					// get button rectangles
					GetWindowRect(GetDlgItem(hDlg, IDOK), &rcOk);
					OffsetRect(&rcOk, -mpt.x, -mpt.y + needY - InfoBarHeight);

					GetWindowRect(GetDlgItem(hDlg, IDALL), &rcAll);
					OffsetRect(&rcAll, -mpt.x, -mpt.y + needY - InfoBarHeight);

					GetWindowRect(GetDlgItem(hDlg, IDNONE), &rcNone);
					OffsetRect(&rcNone, -mpt.x, -mpt.y + needY - InfoBarHeight);

					GetWindowRect(GetDlgItem(hDlg, IDCANCEL), &rcCancel);
					OffsetRect(&rcCancel, -mpt.x, -mpt.y + needY - InfoBarHeight);

					LONG okWidth = rcOk.right - rcOk.left;
					LONG allWidth = rcAll.right - rcAll.left;
					LONG noneWidth = rcNone.right - rcNone.left;
					LONG caWidth = rcCancel.right - rcCancel.left;
					LONG dlgMid = (rcDlg.right - rcDlg.left) / 2;

					// load button configuration
					switch (MB_TYPE(pMsgBox->uType)) {
					case MB_OK:
						rcOk.left = dlgMid - (okWidth / 2);
						rcOk.right = rcOk.left + okWidth;
						ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
						break;

					case MB_OKCANCEL:
						retOk = IDRETRY;
						SetDlgItemText(hDlg, IDOK, LPGENT("OK"));
						retCancel = IDCANCEL;
						SetDlgItemText(hDlg, IDCANCEL, LPGENT("Cancel"));
						rcOk.left = dlgMid - okWidth - 10;
						rcOk.right = rcOk.left + okWidth;
						rcCancel.left = dlgMid + 10;
						rcCancel.right = rcCancel.left + caWidth;
						ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDCANCEL), SW_SHOW);
						break;

					case MB_RETRYCANCEL:
						retOk = IDRETRY;
						SetDlgItemText(hDlg, IDOK, LPGENT("Retry"));
						retCancel = IDCANCEL;
						SetDlgItemText(hDlg, IDCANCEL, LPGENT("Cancel"));
						rcOk.left = dlgMid - okWidth - 10;
						rcOk.right = rcOk.left + okWidth;
						rcCancel.left = dlgMid + 10;
						rcCancel.right = rcCancel.left + caWidth;
						ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDCANCEL), SW_SHOW);
						break;

					case MB_YESNO:
						retOk = IDYES;
						SetDlgItemText(hDlg, IDOK, LPGENT("Yes"));
						retCancel = IDNO;
						SetDlgItemText(hDlg, IDCANCEL, LPGENT("No"));
						rcOk.left = dlgMid - okWidth - 10;
						rcOk.right = rcOk.left + okWidth;
						rcCancel.left = dlgMid + 10;
						rcCancel.right = rcCancel.left + caWidth;
						ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDCANCEL), SW_SHOW);
						break;

					case MB_ABORTRETRYIGNORE:
						retOk = IDABORT;
						SetDlgItemText(hDlg, IDOK, LPGENT("Abort"));
						retAll = IDABORT;
						SetDlgItemText(hDlg, IDALL, LPGENT("Retry"));
						retCancel = IDCANCEL;
						SetDlgItemText(hDlg, IDCANCEL, LPGENT("Ignore"));
						rcAll.left = dlgMid - (allWidth / 2);
						rcAll.right = rcAll.left + allWidth;
						rcOk.left = rcAll.left - okWidth - 5;
						rcOk.right = rcOk.left + okWidth;
						rcCancel.left = rcAll.right + 5;
						rcCancel.right = rcCancel.left + caWidth;
						ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDALL), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDCANCEL), SW_SHOW);
						break;

					case MB_YESNOCANCEL:
						retOk = IDYES;
						SetDlgItemText(hDlg, IDOK, LPGENT("Yes"));
						retAll = IDNO;
						SetDlgItemText(hDlg, IDALL, LPGENT("No"));
						retCancel = IDCANCEL;
						SetDlgItemText(hDlg, IDCANCEL, LPGENT("Cancel"));
						rcAll.left = dlgMid - (allWidth / 2);
						rcAll.right = rcAll.left + allWidth;
						rcOk.left = rcAll.left - okWidth - 5;
						rcOk.right = rcOk.left + okWidth;
						rcCancel.left = rcAll.right + 5;
						rcCancel.right = rcCancel.left + caWidth;
						ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDALL), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDCANCEL), SW_SHOW);
						break;

					case MB_YESALLNO:
						retOk = IDYES;
						SetDlgItemText(hDlg, IDOK, LPGENT("Yes"));
						retAll = IDALL;
						SetDlgItemText(hDlg, IDALL, LPGENT("All"));
						//retNon = IDNONE;
						SetDlgItemText(hDlg, IDNONE, LPGENT("None"));
						retCancel = IDNO;
						SetDlgItemText(hDlg, IDCANCEL, LPGENT("No"));
						rcCancel.right = rcDlg.right - rcDlg.left - 10;
						rcCancel.left = rcCancel.right - caWidth;
						rcNone.right = rcCancel.left - 5;
						rcNone.left = rcNone.right - noneWidth;
						rcAll.right = rcNone.left - 5;
						rcAll.left = rcAll.right - allWidth;
						rcOk.right = rcAll.left - 5;
						rcOk.left = rcOk.right - okWidth;
						// show buttons
						ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDALL), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDNONE), SW_SHOW);
						ShowWindow(GetDlgItem(hDlg, IDCANCEL), SW_SHOW);
						break;

					default:
						rcOk.left = dlgMid - (okWidth / 2);
						rcOk.right = rcOk.left + okWidth;
					}

					MoveWindow(GetDlgItem(hDlg, IDOK), rcOk.left, rcOk.top, rcOk.right - rcOk.left, rcOk.bottom - rcOk.top, FALSE);
					MoveWindow(GetDlgItem(hDlg, IDALL), rcAll.left, rcAll.top, rcAll.right - rcAll.left, rcAll.bottom - rcAll.top, FALSE);
					MoveWindow(GetDlgItem(hDlg, IDNONE), rcNone.left, rcNone.top, rcNone.right - rcNone.left, rcNone.bottom - rcNone.top, FALSE);
					MoveWindow(GetDlgItem(hDlg, IDCANCEL), rcCancel.left, rcCancel.top, rcCancel.right - rcCancel.left, rcCancel.bottom - rcCancel.top, FALSE);
				}

				// set text's
				SetWindowText(hDlg, pMsgBox->ptszTitle);
				SetDlgItemText(hDlg, TXT_NAME, pMsgBox->ptszInfoText);
				SetDlgItemText(hDlg, TXT_MESSAGE, pMsgBox->ptszMsg);

				TranslateDialogDefault(hDlg);
				return TRUE;
			}
		}
		break;

	case WM_CTLCOLORSTATIC:
		switch (GetWindowLongPtr((HWND)lParam, GWLP_ID)) {
		case STATIC_WHITERECT:
		case ICO_DLGLOGO:
		case ICO_MSGDLG:
		case TXT_MESSAGE:
		case TXT_NAME:
			SetTextColor((HDC)wParam, GetSysColor(COLOR_WINDOWTEXT));
			return GetSysColor(COLOR_WINDOW);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hDlg, retOk);
			break;
		case IDCANCEL:
			EndDialog(hDlg, retCancel);
			break;
		case IDALL:
			EndDialog(hDlg, retAll);
			break;
		case IDNONE:
			EndDialog(hDlg, retNon);
		}
		break;

	case WM_DESTROY:
		DeleteObject((HFONT)SendDlgItemMessage(hDlg, TXT_NAME, WM_GETFONT, 0, 0));
		break;
	}
	return FALSE;
}