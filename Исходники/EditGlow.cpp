void CEditGlow::ShowSearchEditFrame(CDC *pdc, bool bUse)
{
	CRect rectEdit;  // ËÑË÷¿òÎ»ÖÃ
	CWnd *pWnd = GetParent();
	this->GetWindowRect(rectEdit);
	pWnd->ScreenToClient(&rectEdit);

	//CDC* pdc = pWnd->GetDC();
	Gdiplus::Graphics graph(pdc->m_hDC);
	graph.SetSmoothingMode(Gdiplus::SmoothingModeNone);

	if(m_pImgBorder && m_pImgBorderGlow)
	{
		if(m_bMouseOn || m_bFocus)
		{
			Rect rr(rectEdit.left-2 , rectEdit.top-2 , m_pImgBorderGlow->GetWidth(), m_pImgBorderGlow->GetHeight());

			graph.DrawImage(m_pImgBorderGlow,
				rr,
				(int)0, 
				(int)0,
				(int)m_pImgBorderGlow->GetWidth(), 
				(int)m_pImgBorderGlow->GetHeight(),
				UnitPixel );
		}
		else
		{
			Rect rr(rectEdit.left-2 , rectEdit.top-2 , m_pImgBorder->GetWidth(), m_pImgBorder->GetHeight());

			graph.DrawImage(m_pImgBorder,
				rr,
				(int)0, 
				(int)0,
				(int)m_pImgBorder->GetWidth(), 
				(int)m_pImgBorder->GetHeight(),
				UnitPixel );

		}

	} 

	return;




	ISkinMgr*	pSkinMgr = AfxGetUIManager()->UIGetSkinMgr();

	CDibBitmap*	m_bmpEditLeft = pSkinMgr->GetDibBmp("LoginEditLeftBorder");
	CDibBitmap*	m_bmpEditTop = pSkinMgr->GetDibBmp("LoginEditTopBorder");
	CDibBitmap*	m_bmpEditRight = pSkinMgr->GetDibBmp("LoginEditRightBorder");
	CDibBitmap*	m_bmpEditBottom = pSkinMgr->GetDibBmp("LoginEditBottomBorder");

	CDibBitmap*	m_bmpEditLiftGray = pSkinMgr->GetDibBmp("AuthorListPanelSearchLeftGray");
	CDibBitmap*	m_bmpEditCenterGray = pSkinMgr->GetDibBmp("AuthorListPanelSearchCenterGray");
	CDibBitmap*	m_bmpEditRightGray = pSkinMgr->GetDibBmp("AuthorListPanelSearchRightGray");



	int nTop = rectEdit.top - m_bmpEditTop->GetHeight();
	int nLeft = rectEdit.left-m_bmpEditLeft->GetWidth();

	if( bUse )
	{
		CDC* pdc = pWnd->GetDC();

		m_bmpEditLeft->SetCDibRect(  CRect(nLeft,nTop, nLeft+m_bmpEditLeft->GetWidth(), nTop+m_bmpEditLeft->GetHeight()) );
		m_bmpEditLeft->Draw( pdc, FALSE );

		m_bmpEditRight->SetCDibRect( CRect(rectEdit.right,nTop, rectEdit.right+m_bmpEditRight->GetWidth(), nTop+m_bmpEditRight->GetHeight()) );
		m_bmpEditRight->Draw( pdc, FALSE );

		m_bmpEditTop->SetCDibRect( CRect(rectEdit.left,nTop, rectEdit.left+rectEdit.Width(), nTop+m_bmpEditTop->GetHeight()) );
		m_bmpEditTop->Draw( pdc, FALSE );

		ReleaseDC(pdc);
	}
	else
	{
		CDC* pdc = pWnd->GetDC();

		m_bmpEditLiftGray->SetCDibRect(  CRect(nLeft,nTop, nLeft+m_bmpEditLiftGray->GetWidth(), nTop+m_bmpEditLiftGray->GetHeight()) );
		m_bmpEditLiftGray->Draw( pdc, FALSE );

		m_bmpEditRightGray->SetCDibRect( CRect(rectEdit.right,nTop, rectEdit.right+m_bmpEditRightGray->GetWidth(), nTop+m_bmpEditRightGray->GetHeight()) );
		m_bmpEditRightGray->Draw( pdc, FALSE );

		//m_bmpEditCenterGray->SetCDibRect( CRect(rectEdit.left,nTop, rectEdit.left+rectEdit.Width(), nTop+m_bmpEditCenter->GetHeight()) );
		//m_bmpEditCenter->Draw( pdc, FALSE );

		ReleaseDC(pdc);
	}
}