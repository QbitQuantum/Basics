void CChatBkDlg::DrawBackground(CDC &dc)
{
	if(m_bInitDlg == FALSE)	return;

	CRect rcClient;
	GetClientRect(&rcClient);

	CPoint ptCur;
	GetCursorPos(&ptCur);
	ScreenToClient(&ptCur);

	CDC			memDC;
	CBitmap		memBmp;
	memDC.CreateCompatibleDC(&dc);
	memBmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	memDC.SelectObject(&memBmp);
	memDC.SelectObject(m_textFont);

	memDC.SetBkMode(TRANSPARENT);

	if(m_pCurrentUser->state == 0)
		memDC.SetTextColor(RGB(128, 128, 128));
	else
		memDC.SetTextColor(RGB(255, 255, 255));

	/////画背景

	Graphics graphics(memDC.GetSafeHdc());

	RectF rcClientF = RectF(float(rcClient.left), float(rcClient.top), float(rcClient.Width()), float(rcClient.Height()));
	LinearGradientBrush lineargradientbrush(rcClientF, Color(255, 49,110,140), Color(255,84,186,178), LinearGradientModeVertical);

	graphics.FillRectangle(&lineargradientbrush, rcClientF);
	//m_ImageBk.Draw(memDC.GetSafeHdc(), rcClient);
	//MemPaintPng(memDC, CRect(rcClient.Width() - m_ImageBk->GetWidth(), 0, rcClient.right, m_ImageBk->GetHeight()), m_ImageBk);

	//memDC.FillSolidRect(rcClient, RGB(75, 75, 75));
	//HBITMAP hBitmap = NULL;
	//((Bitmap*)m_ImageBkTemp)->GetHBITMAP(RGB(0, 0, 0), &hBitmap);
	//memDC.DrawState(CPoint(rcClient.Width() - m_ImageBkTemp->GetWidth(),0), CSize(m_ImageBkTemp->GetWidth(), m_ImageBkTemp->GetHeight()),
	//				hBitmap, DST_BITMAP);

	MemPaintPng(memDC, CRect(rcClient.Width() - m_ImageBkTemp->GetWidth(), 0, rcClient.right, m_ImageBkTemp->GetHeight()), m_ImageBkTemp);


	/////画标题
	if (m_pCurrentUser)
	{
		TCHAR ch[MAX_PATH] ={ 0 };
		_stprintf_s(ch, MAX_PATH, _T(": %d (ID: %d)"), m_pCurrentUser->userUdpPortTemp, m_pCurrentUser->userTypeID);
		tstring str = m_pCurrentUser->UserID + _T(" ") + m_curUserIP + ch;

		CString strWndText;
		GetWindowText(strWndText);
		if(strWndText.GetLength() == 0)
			SetWindowText(str.c_str());

		memDC.TextOut(m_selBtnRect.right, 5, str.c_str());
	}

	MemPaintPng(memDC, m_selBtnRect, m_ImageUserSelTemp);
	//m_ImageUserSel.Draw(memDC.GetSafeHdc(), m_selBtnRect);

	if (m_minBtnRect.PtInRect(ptCur))	//最小化
		MemPaintPng(memDC, m_minBtnRect, m_ImageMinPushTemp);
	else
		MemPaintPng(memDC, m_minBtnRect, m_ImageMinNormalTemp);

	if (m_maxBtnRect.PtInRect(ptCur))	//最大化
	{
		if (IsZoomed())
			MemPaintPng(memDC, m_maxBtnRect, m_ImageRestorePushTemp);
		else
			MemPaintPng(memDC, m_maxBtnRect, m_ImageMaxPushTemp);
	}
	else
	{
		if (IsZoomed())
			MemPaintPng(memDC, m_maxBtnRect, m_ImageRestoreNormalTemp);
		else
			MemPaintPng(memDC, m_maxBtnRect, m_ImageMaxNormalTemp);
	}

	if (m_closeBtnRect.PtInRect(ptCur))	//关闭按钮
		MemPaintPng(memDC, m_closeBtnRect, m_ImageClosePushTemp);
	else
		MemPaintPng(memDC, m_closeBtnRect, m_ImageCloseNormalTemp);

	if (m_sendBtnRect.PtInRect(ptCur))	//发送
		MemPaintPng(memDC, m_sendBtnRect, m_ImageSendPushTemp);
	else
		MemPaintPng(memDC, m_sendBtnRect, m_ImageSendNormalTemp);
	memDC.DrawText(_T("发送"), m_sendBtnRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	if (m_close1BtnRect.PtInRect(ptCur))	//关闭
		MemPaintPng(memDC, m_close1BtnRect, m_ImageClose1PushTemp);
	else
		MemPaintPng(memDC, m_close1BtnRect, m_ImageClose1NormalTemp);
	memDC.DrawText(_T("关闭"), m_close1BtnRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


	if (m_sendFileRc.PtInRect(ptCur))	///发送文件
		MemPaintPng(memDC, m_sendFileRc, m_FilePushTemp);
	else
		MemPaintPng(memDC, m_sendFileRc, m_FileNormalTemp);

	if (m_sendDicRc.PtInRect(ptCur))	//发送文件夹
		MemPaintPng(memDC, m_sendDicRc, m_DicPushTemp);
	else
		MemPaintPng(memDC, m_sendDicRc, m_DicNormalTemp);

	if (m_sendPictureRc.PtInRect(ptCur))	//发送图片
		MemPaintPng(memDC, m_sendPictureRc, m_PicturePushTemp);
	else
		MemPaintPng(memDC, m_sendPictureRc, m_PictureNormalTemp);

	dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), &memDC, 0, 0, SRCCOPY);

	graphics.ReleaseHDC(memDC.GetSafeHdc());
	memDC.DeleteDC();
	memBmp.DeleteObject();
}