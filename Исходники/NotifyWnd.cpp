//纯文本式的右下角浮出窗口过程
LRESULT CALLBACK NotifyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPNOTIFYWND_DATA pInfo = NULL;
	RECT rc;
	POINT pt;

	//这是一个广播消息
	if(message == g_NotifyInfo.nMsg_ExitNow)
	{
		pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		//通知主窗口退出（即客户端主程序退出）
		if(pInfo != NULL && pInfo->mode == MODE_TEXT)
			PostMessage(g_NotifyInfo.hWndMainFrm, WM_EXITNOW, 0, 0);
		return TRUE;
	}

	switch (message)
	{
	case WM_NCCREATE:
		{
			SIZE _size = { 0 };
			LPCREATESTRUCT pCreateStruct = (LPCREATESTRUCT)lParam;

			LPCTSTR pStr = _T("啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊");
			pInfo = (LPNOTIFYWND_DATA)malloc(sizeof(NOTIFYWND_DATA));
			memset(pInfo, 0, sizeof(NOTIFYWND_DATA));
		
			pInfo->mode = (int)(pCreateStruct->lpCreateParams);
			//创建内存位图和DC
			HDC hdc = GetDC(hWnd);
			pInfo->hMemDC = CreateCompatibleDC(hdc);
			HGDIOBJ hOldFont = SelectObject(pInfo->hMemDC, g_NotifyInfo.hFontContent);
			GetTextExtentPoint32(pInfo->hMemDC, pStr, _tcslen(pStr), &_size);
			pInfo->hMemBm = CreateCompatibleBitmap(hdc, _size.cx + g_NotifyInfo.imgSize + 48, 600);
			ReleaseDC(hWnd, hdc);

			SelectObject(pInfo->hMemDC, hOldFont);
			SelectObject(pInfo->hMemDC, pInfo->hMemBm);

			pInfo->contentWidth = _size.cx + g_NotifyInfo.gap;
			pInfo->titleHeight = _size.cy;

			pInfo->rcIcon.left = 3 + g_NotifyInfo.gap;
			pInfo->rcTitle.left = pInfo->rcIcon.left + g_NotifyInfo.iconSize + g_NotifyInfo.gap;
			pInfo->rcTitle.top = 3 + g_NotifyInfo.gap;
			pInfo->rcTitle.bottom = pInfo->rcTitle.top + pInfo->titleHeight;

			pInfo->rcIcon.top = (pInfo->rcTitle.top + pInfo->rcTitle.bottom - g_NotifyInfo.iconSize)/2;
			pInfo->rcIcon.right = pInfo->rcIcon.left + g_NotifyInfo.iconSize;
			pInfo->rcIcon.bottom = pInfo->rcIcon.top + g_NotifyInfo.iconSize;
			
			pInfo->rcContentOutter.left = 3;
			pInfo->rcContentOutter.top = pInfo->rcTitle.bottom + g_NotifyInfo.gap;

			pInfo->rcImg.left = pInfo->rcContentOutter.left + g_NotifyInfo.gap;
			pInfo->rcImg.top = pInfo->rcContentOutter.top + g_NotifyInfo.gap;
			pInfo->rcImg.right = pInfo->rcImg.left + g_NotifyInfo.imgSize;
			pInfo->rcImg.bottom = pInfo->rcImg.top + g_NotifyInfo.imgSize;			

			SetWindowPos(hWnd, HWND_TOPMOST, -10000, -10000, 
				pInfo->wndWidth, pInfo->wndHeight, SWP_HIDEWINDOW);

			pInfo->tme.cbSize = sizeof(TRACKMOUSEEVENT);
			pInfo->tme.dwFlags = TME_LEAVE; //我们需要 WM_MOUSELEAVE 消息；
			pInfo->tme.hwndTrack = hWnd;

			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pInfo);
		}
		return TRUE;

	case WM_PAINT:
		{
			pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if(pInfo == NULL) return TRUE;

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			BitBlt(hdc, 0, 0, pInfo->wndWidth, pInfo->wndHeight, pInfo->hMemDC, 0, 0, SRCCOPY);

			//绘制closebtn(有进度条时，不能关闭)
			int imgIndex = IMG_NORMAL;
			if(pInfo->bMouseOnClose)
			{
				imgIndex = (pInfo->bMouseDown && pInfo->bCloseBtnPushed)? IMG_PUSHED : IMG_HOVER;
			}
			g_NotifyInfo.pImgCloseBtns->TransparentBlt(hdc,
				pInfo->rcCloseBtn.left,
				pInfo->rcCloseBtn.top,
				g_NotifyInfo.closeBtnSize,
				g_NotifyInfo.closeBtnSize,
				imgIndex * g_NotifyInfo.closeBtnSize,
				0,
				g_NotifyInfo.closeBtnSize,
				g_NotifyInfo.closeBtnSize,
				RGB(255, 0, 255));
			EndPaint(hWnd, &ps);
		}
		return TRUE;

	case WM_ERASEBKGND:
		return TRUE;

	case WM_UPDATEPROGRESS:
		pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if(pInfo == NULL) return TRUE;
		
		if(pInfo->mode == MODE_PROGRESS)
		{
			LPCTSTR pStr = (LPCTSTR)lParam;
			if(pStr != NULL)
				_tcscpy_s(pInfo->szProgressText, _ARRAYSIZE(pInfo->szProgressText), pStr);
			pInfo->progress = (int)wParam;

			//绘制进度条
			HGDIOBJ hOldFont = SelectObject(pInfo->hMemDC, g_NotifyInfo.hFontContent);
			SetTextColor(pInfo->hMemDC, g_NotifyInfo.clrContent);
				
			FillRect(pInfo->hMemDC, &pInfo->rcProgressText, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawText(pInfo->hMemDC, pInfo->szProgressText, -1,
				&pInfo->rcProgressText, DT_LEFT | DT_TOP | DT_SINGLELINE);

			SelectObject(pInfo->hMemDC, hOldFont);

			FillRect(pInfo->hMemDC, &pInfo->rcProgressBar, (HBRUSH)GetStockObject(WHITE_BRUSH));
			CopyRect(&rc, &pInfo->rcProgressBar);
			rc.right = pInfo->rcProgressBar.left + 
				(pInfo->rcProgressBar.right - pInfo->rcProgressBar.left) * pInfo->progress / 100;

			FillRect(pInfo->hMemDC, &rc, GetSysColorBrush(COLOR_ACTIVECAPTION)); //pInfo->hBrush);

			if(pInfo->progress >= 100)
			{
				//5 秒后自动隐藏
				pInfo->bDownloading = FALSE;
				SetTimer(hWnd, TIMERID_NOTIFY_HIDE, 2000, NULL);
			}
			UnionRect(&rc, &pInfo->rcProgressText, &pInfo->rcProgressBar);
			InvalidateRect(hWnd, &rc, FALSE);
		}
		return TRUE;

	case WM_MOUSEMOVE:
		{
			pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if(pInfo == NULL) return TRUE;

			pt.x = GET_X_LPARAM(lParam);
			pt.y = GET_Y_LPARAM(lParam);

			BOOL bTmp = PtInRect(&pInfo->rcCloseBtn, pt);
			if(bTmp != pInfo->bMouseOnClose)
			{
				pInfo->bMouseOnClose = bTmp;
				InvalidateRect(hWnd, &pInfo->rcCloseBtn, FALSE);
			}
			TrackMouseEvent(&pInfo->tme);
		}
		break;

	case WM_MOUSELEAVE:
		pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if(pInfo == NULL) return TRUE;
		if(pInfo->bMouseOnClose)
		{
			pInfo->bMouseOnClose = FALSE;
			InvalidateRect(hWnd, &pInfo->rcCloseBtn, FALSE);
		}
		break;

	case WM_LBUTTONDOWN:
		pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if(pInfo == NULL) return TRUE;

		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		pInfo->bMouseDown = TRUE;

		if(PtInRect(&pInfo->rcCloseBtn, pt))
		{
			pInfo->bCloseBtnPushed = TRUE;
			InvalidateRect(hWnd, &pInfo->rcCloseBtn, FALSE);
			SetCapture(hWnd);
		}
		break;

	case WM_LBUTTONUP:
		pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if(pInfo == NULL) return TRUE;

		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		pInfo->bMouseDown = FALSE;

		if(pInfo->bCloseBtnPushed)
		{
			pInfo->bCloseBtnPushed = FALSE;
			ReleaseCapture();
			if(PtInRect(&pInfo->rcCloseBtn, pt))
			{
				KillTimer(hWnd, TIMERID_NOTIFY_SHOWING);
				KillTimer(hWnd, TIMERID_NOTIFY_HIDING);
				KillTimer(hWnd, TIMERID_NOTIFY_TIMEOUT);
				KillTimer(hWnd, TIMERID_NOTIFY_HIDE);
				InvalidateRect(hWnd, &pInfo->rcCloseBtn, FALSE);
				//ShowWindow(hDlg, SW_HIDE);
				//用渐隐( AW_BLEND )的方式隐藏窗口，动画时间：200ms
				AnimateWindow(hWnd, 200, AW_HIDE | AW_BLEND);
			}
		}
		break;

	case WM_TIMER:
		pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if(pInfo == NULL) return TRUE;

		GetWindowRect(hWnd, &rc);
		switch(wParam)
		{
		case TIMERID_NOTIFY_SHOWING:
			if((rc.bottom - rc.top) >= (pInfo->wndHeight - g_NotifyInfo.dy))
			{
				KillTimer(hWnd, wParam);
				SetWindowPos(hWnd, NULL, rc.left, rc.bottom - pInfo->wndHeight,
					pInfo->wndWidth, pInfo->wndHeight, SWP_NOZORDER | SWP_NOACTIVATE);
			}
			else
			{
				SetWindowPos(hWnd, NULL, rc.left, rc.top - g_NotifyInfo.dy,
					pInfo->wndWidth, (rc.bottom - rc.top) + g_NotifyInfo.dy,
					SWP_NOZORDER | SWP_NOACTIVATE);
			}
			break;

		case TIMERID_NOTIFY_HIDING:
			{
				UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;
				if((rc.bottom - rc.top) <= 0)
				{
					KillTimer(hWnd, wParam);
					flags = flags | SWP_HIDEWINDOW;
				}
				SetWindowPos(hWnd, NULL, rc.left, rc.top + g_NotifyInfo.dy,
					pInfo->wndWidth, rc.bottom - rc.top - g_NotifyInfo.dy,
					flags);
			}
			break;

		case TIMERID_NOTIFY_TIMEOUT:
			{
				KillTimer(hWnd, TIMERID_NOTIFY_SHOWING);
				KillTimer(hWnd, TIMERID_NOTIFY_TIMEOUT);
				KillTimer(hWnd, TIMERID_NOTIFY_HIDE);
				SetTimer(hWnd, TIMERID_NOTIFY_HIDING, INTERVAL_NOTIFYWND, NULL);
			}
			break;
		case TIMERID_NOTIFY_HIDE: //立即隐藏
			{
				KillTimer(hWnd, TIMERID_NOTIFY_SHOWING);
				KillTimer(hWnd, TIMERID_NOTIFY_HIDING);
				KillTimer(hWnd, TIMERID_NOTIFY_TIMEOUT);
				KillTimer(hWnd, TIMERID_NOTIFY_HIDE);
				AnimateWindow(hWnd, 200, AW_HIDE | AW_BLEND);
			}
			break;
		}
		break;

	case WM_POWERBROADCAST:
		{
			//TCHAR szText[256];
			//PBT_APMQUERYSUSPEND
			//_stprintf_s(szText, _ARRAYSIZE(szText), _T("NotifyWnd_PowerEvent: event = %x"), wParam);
			//WriteLogLine(szText);
			pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if(pInfo != NULL && pInfo->mode == MODE_TEXT)
				return SendMessage(g_NotifyInfo.hWndMainFrm, WM_POWERBROADCAST, wParam, lParam);
		}
		break;

	case WM_NCDESTROY:
		{
			pInfo = (LPNOTIFYWND_DATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if(pInfo == NULL) return TRUE;
			//DeleteCriticalSection(&g_NotifyInfo.cs);

			DeleteObject(pInfo->hMemBm);
			DeleteDC(pInfo->hMemDC);

			free(pInfo);

			SetWindowLongPtr(hWnd, GWLP_USERDATA, NULL);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}