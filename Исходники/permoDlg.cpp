void CpermoDlg::DrawInfo(CDC* pDC)
{
	CFont font, *pOldFont;
	LOGFONT logFont;
	pDC->GetCurrentFont()->GetLogFont(&logFont);
	logFont.lfWidth = 0;
	logFont.lfHeight = nFontSize;
	logFont.lfWeight = FW_REGULAR;
	lstrcpy(logFont.lfFaceName, _T("微软雅黑"));
	font.CreateFontIndirect(&logFont);
	pOldFont = pDC->SelectObject(&font);
	COLORREF cOldTextColor;
	if (IDM_GREEN == nSkin || IDM_ORANGE == nSkin)
	{
		cOldTextColor = pDC->SetTextColor(RGB(0, 0, 0));
	}
	else
	{
		cOldTextColor = pDC->SetTextColor(RGB(255, 255, 255));
	}
	int nOldBkMode = pDC->SetBkMode(TRANSPARENT);
	CString strCPU, strMem, strNetUp, strNetDown;
	strCPU.Format(_T("%d%%"), nCPU);
	strMem.Format(_T("%d%%"), nMem);
	if (fNetUp >= 1000)
	{
		strNetUp.Format(_T("%.2fMB/S"), fNetUp/1024.0);
	}
	else
	{
		if (fNetUp < 100)
		{
			strNetUp.Format(_T("%.1fKB/S"), fNetUp);
		}
		else
		{
			strNetUp.Format(_T("%.0fKB/S"), fNetUp);
		}
	}
	if (fNetDown >= 1000)
	{
		strNetDown.Format(_T("%.2fMB/S"), fNetDown/1024.0);
	}
	else
	{
		if (fNetDown < 100)
		{
			strNetDown.Format(_T("%.1fKB/S"), fNetDown);
		}
		else
		{
			strNetDown.Format(_T("%.0fKB/S"), fNetDown);
		}
	}
	CRect rText;
	rText.left = 1;
	rText.right = 36;
	rText.top = 2;
	rText.bottom = 21;
	pDC->DrawText(strCPU, &rText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rText.left = 186;
	rText.right = 219;
	pDC->DrawText(strMem, &rText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if (IDM_BLACK == nSkin || IDM_BLUE == nSkin)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
	}
	else
	{
		pDC->SetTextColor(RGB(0, 0, 0));
	}

	CRect rcIcon;
	rcIcon.left = 38;
	rcIcon.right = 50;
	rcIcon.top = 5;
	rcIcon.bottom = 17;
	DrawIconEx(pDC->GetSafeHdc(), rcIcon.left, rcIcon.top, LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DOWN)), rcIcon.Width(), rcIcon.Height(), 0, NULL, DI_NORMAL);
	rText.left = 52;
	rText.right = 110;
	pDC->DrawText(strNetDown, &rText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rcIcon.left = 112;
	rcIcon.right = 124;
	DrawIconEx(pDC->GetSafeHdc(), rcIcon.left, rcIcon.top, LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_UP)), rcIcon.Width(), rcIcon.Height(), 0, NULL, DI_NORMAL);
	rText.left = 126;
	rText.right = 185;
	pDC->DrawText(strNetUp, &rText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	pDC->SetTextColor(cOldTextColor);
	pDC->SetBkMode(nOldBkMode);
	pDC->SelectObject(pOldFont);
	font.DeleteObject();
}