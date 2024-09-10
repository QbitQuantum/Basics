void CDrawButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	
	//判断控件类型是否为按钮类型
	if (lpDrawItemStruct->CtlType == ODT_BUTTON)
	{
		CDC dc;

		
		dc.Attach(lpDrawItemStruct->hDC);	//附加设备上下文句柄
		//获取按钮状态
		int nState = lpDrawItemStruct->itemState;
		//获取按钮区域
		CRect btnRC = lpDrawItemStruct->rcItem;
		CString szBtnText;
		GetWindowText(szBtnText);	//获取按钮文本

		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		
		COLORREF clrText;	//文本颜色
		clrText = RGB(0, 0, 0);
		COLORREF clrBK = RGB(220, 220, 220);		//背景颜色

		if (nState & ODS_SELECTED || nState & ODS_FOCUS)
		{
			clrBK = RGB(222, 231, 239);
		}
		if (m_nBtnState == 1)
		{
			clrText = RGB(255, 0, 255);
		}
		
		dc.SetTextColor(clrText);

		dc.FillRect(btnRC, &CBrush(clrBK));
		dc.FrameRect(btnRC, &CBrush(RGB(140, 158, 176)));


		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(szBtnText, btnRC, DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_WORD_ELLIPSIS);
		dc.Detach();	//分离句柄
	}	
}