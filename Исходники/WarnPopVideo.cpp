void CWarnPopVideo::FullScreenPopVideo(void)
{
	if (m_bFullScreen==false) //full screen
	{
		//Hide OK Button
		CButton *pBtnOK = (CButton *)GetDlgItem(IDOK);
		if (pBtnOK)
			pBtnOK->ShowWindow(SW_HIDE);
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_TIMEOUT);
		if (pEdit)
			pEdit->ShowWindow(SW_HIDE);
		CButton *pBtnPause = (CButton*)GetDlgItem(IDC_PAUSE_ALARM);
		if (pBtnPause)
			pBtnPause->ShowWindow(SW_HIDE);

		//Full Video Screen
		GetWindowPlacement(&m_struOldPlacement);

		//Remove WS_SIZEBOX windows style. or not the window can't be full-creen.
		ModifyStyle(WS_SIZEBOX,0,0);
		
		CRect WindowRect, ClientRect;
		RECT m_FullScreenRect;

		//ReDraw the window. Get the correct edge value.
		GetWindowRect(&WindowRect);
		WindowRect.left+=1;
		WindowRect.right+=1;
		MoveWindow(CRect(0,0,352,288),TRUE);
		
		GetWindowRect(&WindowRect);
		GetClientRect(&ClientRect);
		ClientToScreen(&ClientRect);
	
		//get the dest window rect.
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		m_FullScreenRect.left = WindowRect.left - ClientRect.left;
		m_FullScreenRect.top = WindowRect.top - ClientRect.top;
		m_FullScreenRect.right = WindowRect.right - ClientRect.right + x;
		m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + y;

//		m_FullScreenRect.left = 0;
//		m_FullScreenRect.top = 0; 
//		m_FullScreenRect.right = GetSystemMetrics(SM_CXSCREEN);
//		m_FullScreenRect.bottom = GetSystemMetrics(SM_CYSCREEN);

		//Move the main window to the dest rect.
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		wndpl.flags = 0;
		wndpl.showCmd = SW_SHOWNORMAL;
		wndpl.rcNormalPosition = m_FullScreenRect;
		SetWindowPlacement(&wndpl);

		//Move the view winow to full-screen.
		RECT rc;
		GetClientRect(&rc);
		m_pPopView->MoveWindow(&rc,TRUE);

		//
		m_bFullScreen = true;

	}
	else //Restore normal screen
	{
		//Show OK Button
		CRect btnRect;
		CButton *pBtnOK = (CButton *)GetDlgItem(IDOK);
		if (pBtnOK)
		{
			pBtnOK->ShowWindow(SW_SHOW);
			pBtnOK->GetClientRect(&btnRect);
		}
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_TIMEOUT);
		if (pEdit)
			pEdit->ShowWindow(SW_SHOW);
		CButton *pBtnPause = (CButton*)GetDlgItem(IDC_PAUSE_ALARM);
		if (pBtnPause)
			pBtnPause->ShowWindow(SW_SHOW);
		
		//Restore old position
		ModifyStyle(0,WS_SIZEBOX,0);
				
		SetWindowPlacement(&m_struOldPlacement);
		RECT rc;
		GetClientRect(&rc);
 		rc.bottom -= (btnRect.Height()+3);
		m_pPopView->MoveWindow(&rc,TRUE);

		//SetWindowSize();

		//
		m_bFullScreen = false;

	}

}