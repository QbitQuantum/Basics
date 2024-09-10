void CLightDlg::ColorButtons() {
	CRect r;

	CClientDC dc(this);
	
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_COLOR);
	pBtn->GetClientRect(&r);
	colorBitmap.DeleteObject();
	colorBitmap.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBmp = MemDC.SelectObject(&colorBitmap);
	{
		CBrush br(RGB(color[0], color[1], color[2])); 
		MemDC.FillRect(r,&br);
	}
	dc.SelectObject(pOldBmp);
	pBtn->SetBitmap(HBITMAP(colorBitmap)); 
}