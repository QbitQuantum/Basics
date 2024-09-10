void CLLTDlg::UpdateView(double Alpha)
{
	CClientDC dc(this); // device context for painting

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SetBkMode(TRANSPARENT);

	CRect dcMemRect(0,0,m_IterRect.Width(), m_IterRect.Height());
	CBitmap bmb;
	bmb.CreateCompatibleBitmap(&dc,m_IterRect.Width(), m_IterRect.Height());
	CBitmap *pOldBitmap = dcMem.SelectObject(&bmb);

	CBrush FillBrush(GetSysColor(COLOR_3DFACE));
	dcMem.FillRect(&dcMemRect,&FillBrush);

	CRect BltRect(0,0,m_IterRect.Width(), m_IterRect.Height());
	m_IterGraph.DrawGraph(&dcMem, &BltRect,false);

	dcMem.SetTextAlign(TA_LEFT);
	if(IsBlackAndWhite())	dcMem.SetTextColor(0);
	else					dcMem.SetTextColor(RGB(150,150,150));

	CFont TFont;
	TFont.CreatePointFont(85, "Symbol");
	CFont* pOldFont = dcMem.SelectObject(&TFont);
	dcMem.TextOut(50,35,"(|Da|)");
	CFont MFont;
	MFont.CreatePointFont(85, "Arial");
	dcMem.SelectObject(&MFont);
	
	CString strong;
	strong.Format("max = %.4f", m_pIterCurve->y[m_pIterCurve->n-1]);

	dcMem.TextOut(80,35,strong);

	CFont CvFont;
	CvFont.CreateFont(18,0,0,0,FW_BOLD,FALSE,FALSE,0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FF_SWISS+VARIABLE_PITCH, "Arial");

	dcMem.SelectObject(&CvFont);

	dcMem.SetBkMode(TRANSPARENT);
	CString Title;

	if(!m_bType4){
		Title.Format("Alpha = %.2f°", Alpha);
	}
	else{
		Title.Format(" Iterations for QInf = %.2f m/s", Alpha);
	}
	dcMem.TextOut(200,5,Title);

	if(m_State ==1){
		if(IsBlackAndWhite()){
			dcMem.SetTextColor(0);
		}
		else{
			dcMem.SetTextColor(RGB(0,150,0));
		}
		dcMem.TextOut(200,35,"CONVERGED !");
	}
	else if (m_State ==2){
		if(IsBlackAndWhite()) 	dcMem.SetTextColor(0);
		else dcMem.SetTextColor(RGB(255,0,0));
		dcMem.TextOut(200,35,"UNCONVERGED...");
	}


	dc.BitBlt(m_IterRect.left, m_IterRect.top, m_IterRect.Width(), m_IterRect.Height(),
			  &dcMem,0, 0, SRCCOPY);
	dcMem.SelectObject(pOldFont);
	dcMem.SelectObject(pOldBitmap);
	bmb.DeleteObject();
	CvFont.DeleteObject();
	TFont.DeleteObject();
	MFont.DeleteObject();
	FillBrush.DeleteObject();
}