void ScheduleViewEx::OnPrintAll()
{
	CPrintDialog dlg(FALSE);
	if (IDOK == dlg.DoModal())
	{
		HDC dc = dlg.GetPrinterDC();
		
		CDC DC;
		DC.Attach(dc);

		DEVMODE *myMode = dlg.GetDevMode();//fills myMode with printer defaults 
		myMode->dmOrientation = DMORIENT_LANDSCAPE;//change default to landscape
		myMode->dmPrintQuality = DMRES_DRAFT;
		myMode->dmColor = DMCOLOR_MONOCHROME;
		DC.ResetDC(myMode);

		DC.m_bPrinting = TRUE;
		OnPrepareDC(&DC);
		DC.StartDoc(_T("myDoc"));
		
		int tmpOffset = m_offset;
		for (int i = 0;
			i< TotalPages();
			i++)
		{
			m_offset = i;
			DC.StartPage();
			OnDraw(&DC);
			DC.EndPage();
		}
		DC.EndDoc();
		m_offset = tmpOffset;
	}
}