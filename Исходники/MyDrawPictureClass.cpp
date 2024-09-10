BOOL CMyDrawPictureClass::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_LBUTTONDOWN&&m_IsPicLoaded)
	{
		CWnd * hwnd;
		POINT pointGetCtl;
		GetCursorPos(&pointGetCtl);
		hwnd= (CWnd *)WindowFromPoint(pointGetCtl);
		while (hwnd && hwnd->GetParent()!=this)
			hwnd = hwnd->GetParent();
		if(GetDlgItem(IDC_STATIC_BASECOLOR1)==hwnd)
		{
			if(!m_IsMakePic)
			{
				m_OldSursor = ::GetCursor();
				m_IsMakePic= true;
			}
			
		}
		else
		{

			if(m_IsMakePic)
			{
				::SetCursor(m_OldSursor);
				m_IsMakePic = false;

				COLORREF color;
				color = ::GetPixel(::GetDC(NULL),pMsg->pt.x,pMsg->pt.y);
				CString wndColor=_T("0");
				wndColor.Format(_T("%x"),color);
				m_BaseColor1.SetBkColor(color);
				wndColor.MakeUpper();
				this->GetDlgItem(IDC_EDIT_COLOR1)->SetWindowTextW(wndColor);

				////////设置前台色///////////////////
				m_ForegroundColor = color;

				m_IsPicLoaded = true;
				
				drawPicture();
			}
		}
	}

	return CMFCPropertyPage::PreTranslateMessage(pMsg);
}