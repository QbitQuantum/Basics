void CBackStagePageInfo::PreparePreviewBitmap()
{
	CRect rectPreview;
	m_btnPreview.GetClientRect(rectPreview);
	
	CBitmap& bmpAppPreview = ((CMainFrame*)AfxGetMainWnd())->GetAppPreview();
	
	BITMAP bmp;
	bmpAppPreview.GetBitmap(&bmp);
	
	double dblScaleRatio = min((double)rectPreview.Width() / bmp.bmWidth, (double)rectPreview.Height() / bmp.bmHeight);
	
	CSize szDst((int)(bmp.bmWidth * dblScaleRatio), (int)(bmp.bmHeight * dblScaleRatio));
	
	HBITMAP hBitmap = CBCGPDrawManager::CreateBitmap_24(szDst, NULL);
	
	{
		CDC dcDst;
		dcDst.CreateCompatibleDC(NULL);
		
		HBITMAP hBitmapOld = (HBITMAP)dcDst.SelectObject (hBitmap);
		
		CBCGPDrawManager dm(dcDst);
		int nShadowSize = 5;
		
		szDst.cx -= 2 * nShadowSize;
		szDst.cy -= 2 * nShadowSize;
		
		CBCGPVisualManager::GetInstance()->OnFillRibbonBackstageForm(&dcDst, this, rectPreview);
		dm.DrawShadow(CRect(CPoint(nShadowSize, nShadowSize), szDst), nShadowSize);
		
		CDC dcSrc;
		dcSrc.CreateCompatibleDC(&dcDst);
		
		HBITMAP hBitmapViewOld = (HBITMAP)dcSrc.SelectObject(bmpAppPreview.GetSafeHandle());
		
		dcDst.SetStretchBltMode(HALFTONE);
		
		dcDst.StretchBlt(nShadowSize, nShadowSize, szDst.cx, szDst.cy, &dcSrc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		
		dcSrc.SelectObject (hBitmapViewOld);
		dcDst.SelectObject (hBitmapOld);
	}
	
	m_btnPreview.SetMouseCursorHand();
	m_btnPreview.SetDrawText(FALSE);
	m_btnPreview.m_bDrawFocus = FALSE;
	m_btnPreview.SetImage(hBitmap);
	m_btnPreview.m_bTransparent = TRUE;
	m_btnPreview.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_NOBORDERS;
	m_btnPreview.SizeToContent();
	
	bmpAppPreview.DeleteObject();
}