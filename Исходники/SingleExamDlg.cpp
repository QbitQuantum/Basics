BOOL CSingleExamDlg::OnEraseBkgnd(CDC* pDC)
{
	CDialog::OnEraseBkgnd(pDC);

	CRect rcClient;
	GetClientRect(&rcClient);

	pDC->FillRect(rcClient, &CBrush(RGB(255, 255, 255)));	//225, 242, 250

	//画虚线
	if (GetDlgItem(IDC_STATIC_ExamTime)->GetSafeHwnd())
	{
		CPen *pOldPen = NULL;
		CPen pPen;
		pPen.CreatePen(PS_DASH, 1, RGB(106, 218, 239));
		pOldPen = pDC->SelectObject(&pPen);

		CRect rtTmp;
		GetDlgItem(IDC_STATIC_ExamTime)->GetWindowRect(rtTmp);
		ScreenToClient(&rtTmp);

		CPoint pt1, pt2;
		pt1.x = rtTmp.left;
		pt1.y = rtTmp.bottom + 1;
		pt2.x = pt1.x + 350;
		pt2.y = pt1.y;
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2);
		pDC->SelectObject(pOldPen);
		pPen.Detach();
	}
	DrawBorder(pDC);

	int iX, iY;
	CDC memDC;
	BITMAP bmp;
	if (memDC.CreateCompatibleDC(pDC))
	{
		CBitmap *pOldBmp = memDC.SelectObject(&m_bmpExamType);
		m_bmpExamType.GetBitmap(&bmp);
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->StretchBlt(rcClient.right - bmp.bmWidth - 10, 1, bmp.bmWidth, bmp.bmHeight, &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);


		pOldBmp = memDC.SelectObject(&m_bmpExamTypeLeft);
		m_bmpExamTypeLeft.GetBitmap(&bmp);
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->StretchBlt(rcClient.left, rcClient.top, bmp.bmWidth, rcClient.bottom, &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

		memDC.SelectObject(pOldBmp);
	}
	memDC.DeleteDC();

	return TRUE;
}