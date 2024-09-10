BOOL CDlgIBAFastlane::OnEraseBkgnd(CDC* pDC)
{
	CRect rcRect;
	GetClientRect( rcRect );

	CDC memDC;  // Paint的内存DC
	CBitmap bmp;

	bmp.CreateCompatibleBitmap( pDC,rcRect.Width(),rcRect.Height() );
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);

	CBCGPToolBar* pParent = (CBCGPToolBar*)GetParent();
	if( pParent )
	{
		
		WINDOWPLACEMENT wp;
		this->GetWindowPlacement(&wp);

		CRect rcParent;
		pParent->GetClientRect(rcParent);

		// 绘制背景
		CDC memParentDC;
		CBitmap bmpParent;
		bmpParent.CreateCompatibleBitmap(pDC,rcParent.Width(),rcParent.Height());
		memParentDC.CreateCompatibleDC(NULL);
		memParentDC.SelectObject(&bmpParent);

		CDC* pParentDC = pParent->GetDC();
		CBCGPVisualManager::GetInstance ()->OnFillBarBackground (&memParentDC, pParent,
			rcParent,rcParent);
		pParent->ReleaseDC(pParentDC);

		CRect rt = wp.rcNormalPosition;

		memDC.BitBlt(0,0,rcRect.Width(),rcRect.Height(),&memParentDC,wp.rcNormalPosition.left,wp.rcNormalPosition.top,
			SRCCOPY);

		pDC->BitBlt(0,0,rt.Width(),rt.Height(),&memDC,0,0,SRCCOPY);
	}

	CBitmap bmpImg;
	BOOL bRes = 0;
	if (m_bBugleActive)
	{
		bRes = bmpImg.LoadBitmap(IDB_BUGLE2);
	}
	else
	{
		bRes = bmpImg.LoadBitmap(IDB_BUGLE1);
	}
	if (bRes)
	{
		BITMAP bt;
		bmpImg.GetBitmap(&bt);

		CStatic *pStc = (CStatic*)GetDlgItem(IDC_PIC_BUGLE);

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		memDC.SelectObject(&bmpImg);

		CRect rc;
		pStc->GetClientRect(rc);
		WINDOWPLACEMENT wp;
		pStc->GetWindowPlacement(&wp);

		CRect rcClient;
		GetClientRect(rcClient);

		rc.left = wp.rcNormalPosition.left;
		rc.top = rcClient.top + (rcClient.Height()-bt.bmHeight)/2;
		rc.right = rc.left + bt.bmWidth;
		rc.bottom = rc.top + bt.bmHeight;

		pDC->TransparentBlt(rc.left,rc.top,rc.Width(),rc.Height(),&memDC,0,0,rc.Width(),rc.Height(),RGB(255,255,255));
	}
	else
	{
		IBA_ASSERT2(0,"喇叭image 问题");
	}

	{
		WINDOWPLACEMENT pm;
		m_stcPicStatus.GetWindowPlacement(&pm);

		int nWidth = 85;
		int nHeight = 21;
		int nStatus = m_nIBAStatus;

		int nX = pm.rcNormalPosition.left;
		int nY = pm.rcNormalPosition.top;
		int nImgX = nStatus * nWidth;
		int nImgY = 0;
		
		BOOL bRes = m_imgStatus.Draw(pDC->GetSafeHdc(), nX, nY, nWidth, nHeight, nImgX, nImgY, nWidth, nHeight);
		pDC->SetBkMode(TRANSPARENT);
		CFont* pOldFont = (CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT);
		CStringArray strArr;
		CIBAHelpper::SplitLine(LOAD_STRING(IDS_IBA_NET_STATUS),strArr);
		CRect rcTest(0,0,0,0);
		CString strText = strArr.GetAt(nStatus);
		pDC->DrawText(strText,rcTest,DT_CALCRECT);
		CRect rcTxt;
		rcTxt.left = nX;
		rcTxt.right = nX + nWidth;
		rcTxt.top = nY + (nHeight - rcTest.Height())/2;
		rcTxt.bottom = rcTxt.top + rcTest.Height();
		pDC->DrawText(strText,rcTxt,DT_CENTER);
		bRes = bRes;
		pDC->SelectObject(pOldFont);
	}
	//return CBCGPDialog::OnEraseBkgnd(pDC);
	return TRUE;
}