LRESULT CALLBACK TipMsgWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TipMsgWindow *pThis = NULL;

	switch (message)
	{
	case WM_TIMER:
		BringWindowToTop(hWnd);
		break;
	case WM_GETMINMAXINFO:
		MINMAXINFO* mmi;
		mmi = (MINMAXINFO*)lParam;
		mmi->ptMinTrackSize.x = 1;
		mmi->ptMinTrackSize.y = 1;
		mmi->ptMaxTrackSize.x = 200;
		mmi->ptMaxTrackSize.y = 200;
		break;
	case WM_CREATE:
		SetTimer(hWnd,0, 1000, NULL);
		break;
	case WM_PAINT:
		RECT rc;
		pThis = (TipMsgWindow*)GetWindowLong(hWnd, GWL_USERDATA);
		if (pThis == NULL)
		{
			DOLOG("have not right TipMsgWindow instance£¡");
			break;
		}
		
		hdc = BeginPaint(hWnd, &ps);
		//hbr = CreateSolidBrush(RGB(0, 0, 0));
		rc.top = 0;
		rc.left = 0;
		rc.right = pThis->m_size.x;
		rc.bottom = pThis->m_size.y;
		//assert(FillRect(hdc, &rc, hbr));
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		DrawTextA(hdc, pThis->m_Msg, strlen(pThis->m_Msg), &rc, DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}