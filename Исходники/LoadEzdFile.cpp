void CLoadEzdFile::OnDrawPreview()
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_WND);
	if(pWnd==NULL)
		return;    	
	//	pWnd = this;
	CRect rect;
    pWnd->GetClientRect(rect);
    rect.InflateRect(-2,-2);
    
	CDC* pDC = pWnd->GetDC(); 
	CRgn pRgn;
	pRgn.CreateRectRgnIndirect(rect);
	pDC->SelectClipRgn(&pRgn);
	
	//CBrush Brsh(GetSysColor(COLOR_BTNFACE));
	CBrush Brsh(RGB(255,255,255));
	pDC->FillRect(rect,&Brsh);	
	if(m_pPrevBmp != NULL)
    {//显示预览图片	
		CDC memDC;
		CBitmap* pOld=NULL;
		memDC.CreateCompatibleDC(pDC);
		
		pOld = memDC.SelectObject(m_pPrevBmp);
		
		BITMAP bm;
		m_pPrevBmp->GetBitmap(&bm);		
		CPoint ptCen = rect.CenterPoint ();
		::SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);	
		
		pDC->BitBlt (ptCen.x - bm.bmWidth/2,ptCen.y - bm.bmHeight/2,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
		
		memDC.SelectObject(pOld);		
	}	
	
	pWnd->ReleaseDC( pDC );     
    return;

}