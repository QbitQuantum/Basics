void CViscDlg::UpdateView()
{
	CClientDC dc(this); // device context for painting
	int btnHeight = 50;

	CRect CltRect;
	GetClientRect(&CltRect);

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SetBkMode(TRANSPARENT);

	CRect dcMemRect(0,0,CltRect.Width(), CltRect.Height()-btnHeight);
	CBitmap bmb;
	bmb.CreateCompatibleBitmap(&dc,CltRect.Width(),  CltRect.Height()-btnHeight);
	CBitmap * pOldBmp = dcMem.SelectObject(&bmb);

	CBrush FillBrush(GetSysColor(COLOR_3DFACE));
	dcMem.FillRect(&dcMemRect,&FillBrush);
	
	m_RmsGraph.DrawGraph(&dcMem, &m_ViscRect,false);
	m_RmsGraph.DrawLegend(&dcMem, false, m_LegendPlace);

	CFont CvFont;
	CvFont.CreateFont(18,0,0,0,FW_BOLD,FALSE,FALSE,0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FF_SWISS+VARIABLE_PITCH, "Arial");
	CFont* pOldFont = dcMem.SelectObject(&CvFont);
	
	dcMem.SetTextAlign(TA_LEFT);
	dcMem.SetBkMode(TRANSPARENT);
	CString Title;
	dcMem.SetTextColor(RGB(0,0,0));

	if(!m_bType4){
		if (m_bAlpha)
			Title.Format("Alfa = %7.2f°", m_pXFoil->alfa*180.0/3.141592654);
		else
			Title.Format("Cl = %7.2f", m_pXFoil->clspec);
	}
	else{
		ReynoldsFormat(Title, m_pXFoil->reinf);
		Title = "Re = " + Title;
	}
	dcMem.TextOut(150,5,Title);

	if(m_pXFoil->lvconv){
		dcMem.SetTextColor(RGB(0,150,0));
		dcMem.TextOut(160,45,"CONVERGED !");
	}
	else {
		if(m_pIterThread->m_Iterations>=m_IterLim && !m_pXFoil->lvconv){
			dcMem.SetTextColor(RGB(255,0,0));
			dcMem.TextOut(160,45,"UNCONVERGED...");
		}
	}

	dc.BitBlt(0, CltRect.top, CltRect.Width(), m_ViscRect.Height()+42, &dcMem,0, 0, SRCCOPY);	
	dcMem.SelectObject(pOldFont);
	dcMem.SelectObject(pOldBmp);
	bmb.DeleteObject();
	CvFont.DeleteObject();
	FillBrush.DeleteObject();
}