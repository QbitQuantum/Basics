void CTEditCtrlWnd::OnPaint() 

{
	CPaintDC dc(this);
	
	CString strWindow, strCurreny;
	CRect	rcClient;
	
	GetClientRect(rcClient);

	dc.FillSolidRect(rcClient, m_clrFace);
	dc.SetBkMode(TRANSPARENT);
	/*dc.Draw3dRect(rcClient, m_clrBottomRight, m_clrTopLeft);*/
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
	CPen* pOldPen = (CPen*)dc.SelectObject(&pen);
	dc.Rectangle(rcClient);
	dc.SelectObject(pOldPen);
	pen.DeleteObject();
	
	
	rcClient.DeflateRect(2, 2, 2, 2);
	GetWindowText(strWindow);
	strCurreny = GetCurrencyText(strWindow);
	strCurreny = strWindow;
	
	CFont *pOldFont = dc.SelectObject(&m_fontDefault);
	dc.DrawText(strCurreny, rcClient, DT_VCENTER | DT_SINGLELINE | DT_RIGHT);
	dc.SelectObject(pOldFont);
}