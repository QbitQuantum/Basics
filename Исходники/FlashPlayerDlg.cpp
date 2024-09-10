BOOL CFlashPlayerDlg::PreTranslateMessage(MSG* pMsg)
{
	int const wmId = LOWORD(pMsg->wParam);
	if (pMsg->message == s_uTBBC)
	{
		if (!g_pTaskbarList)
		{
			HRESULT hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pTaskbarList));
			if (SUCCEEDED(hr))
			{
				hr = g_pTaskbarList->HrInit();
				if (FAILED(hr))
				{
					g_pTaskbarList->Release();
					g_pTaskbarList = NULL;
				}

				if(g_pTaskbarList) {
					hImglist = ImageList_LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_96),
						16, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
					if (hImglist)
					{
						hr = g_pTaskbarList->ThumbBarSetImageList(this->m_hWnd, hImglist);
						if (SUCCEEDED(hr))
						{
							THUMBBUTTON buttons[2] = {};

							buttons[0].dwMask = THB_BITMAP | THB_FLAGS;
							buttons[0].dwFlags = THBF_ENABLED;
							buttons[0].iId = IDTB_PLAY_PAUSE;

							if(IsFlashPlaying())
								buttons[0].iBitmap = 1;
							else
								buttons[0].iBitmap = 0;

							g_pTaskbarList->ThumbBarAddButtons(this->m_hWnd, 1, buttons);
						}
						g_pTaskbarList->SetProgressState(this->m_hWnd, TBPF_NORMAL);
						ImageList_Destroy(hImglist);
					}
				}
			}
		}
	} else if(pMsg->message == WM_COMMAND && (wmId == IDTB_PLAY_PAUSE)) {
		if(IsFlashPlaying())
			pFlashPtr->Stop();
		else
			pFlashPtr->Play();
		UpdateThumbnailToolbar(m_hWnd);
	} else {
		switch(pMsg->message)
		{
		case WM_NCRBUTTONDOWN:
			{
				if(pMsg->wParam == HTMAXBUTTON || pMsg->wParam == HTMINBUTTON || pMsg->wParam == HTCLOSE)
					break;
				m_popmenu.GetSubMenu(0).TrackPopupMenu(TPM_LEFTALIGN, LOWORD(pMsg->lParam), HIWORD(pMsg->lParam), m_hWnd);
				return TRUE;
			}
		case WM_SYSCHAR:
			if (pMsg->wParam == 13)
				FullScreen();
			break;
		case   WM_KEYDOWN:
			SendMessage(CMD_KEYDOWN, CMD_KEY, pMsg->wParam );
			if(pMsg->wParam == 13)
				return TRUE;
			break;
		case   WM_LBUTTONDOWN:
			POINT point;
			GetCursorPos(&point);
			if(m_fs && m_showctrl)
			{
				if(point.y < m_scr_height - 16)
					break;
				if(point.x < 5 || point.x > m_scr_width - 5)
					break;
				m_changing = true;
				double pos = (double)(point.x - 5) / (double) (m_scr_width - 10);
				pFlashPtr->GotoFrame((long)(m_fnumber * pos));
				pFlashPtr->Play();
				m_changing = false;
				return TRUE;
			}
			break;
		case  WM_RBUTTONDOWN:
			if(!m_rmenu)
			{
				SendMessage(CMD_KEYDOWN, CMD_KEY, WM_RBUTTONDOWN );
				return TRUE;
			}
			break;
		case  WM_MOUSEMOVE:
			{
				if(!m_fs)
					break;
				ShowCursor(TRUE);
				SetTimer(TIMER_HIDE_CURSOR, 2000, NULL);
				POINT point;
				GetCursorPos(&point);
				if(!m_showctrl && point.y >= m_scr_height - 20)
				{
					m_control.MoveWindow(0,m_scr_height - 16,m_scr_width,20);
					m_showctrl = true;
				}
				else if(m_showctrl && point.y < m_scr_height - 20)
				{
					m_control.MoveWindow(0,m_scr_height,m_scr_width,20);
					m_showctrl = false;
				}
				break;
			}
		}
	}
	return CWindow::IsDialogMessage(pMsg);
}