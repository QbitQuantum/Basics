bool CPicShowCtrl::SaveFile(CString strPath)
{
	int width=180;
	int height=180;

	CPaintDC dc(this);
	CxImage img;
	img.CreateFromHBITMAP(m_hBmp);

	CBitmap bitmapmem;          
	CBitmap *pOldBit;
	CDC m_pMemDC;
	m_pMemDC.CreateCompatibleDC(&dc); 
	bitmapmem.CreateCompatibleBitmap(&dc, width, height);
	pOldBit=m_pMemDC.SelectObject(&bitmapmem);

	CRect rect(0,0,width,height);
	HBRUSH bgBrush = ::CreateSolidBrush(RGB(255,255,255));
	FillRect(m_pMemDC,&rect,bgBrush);
	DeleteObject(bgBrush);
	img.Draw(m_pMemDC,m_iStartx,m_iStarty,img.GetWidth(),img.GetHeight(),&rect);

	CBitmap* pBmp=m_pMemDC.SelectObject(pOldBit);

	CxImage xImagebmp;
	xImagebmp.CreateFromHBITMAP((HBITMAP)bitmapmem.m_hObject);
	xImagebmp.Resample(100,100,0);  
	bitmapmem.DeleteObject();
	m_pMemDC.DeleteDC();
	if(xImagebmp.Save(common::utility::stringhelper::UnicodeToAscii(strPath.GetBuffer()).c_str(), CXIMAGE_FORMAT_JPG))
	{
		return true;
	}
	return false;
}