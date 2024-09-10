BOOL CEdRptDoc::PrintAuto(CPrintDialog *pPntDlg)
{
	// 严禁在不使用省却打印机情况下不指定打印机
	ASSERT(m_bDefaultPrint || pPntDlg);
	
	// get default print
	CPrintDialog defaultDlg (FALSE, PD_RETURNDC );
	AfxGetApp()->GetPrinterDeviceDefaults( &defaultDlg.m_pd );	

	if (!pPntDlg)
		pPntDlg = &defaultDlg;
	
	HDC hdc = pPntDlg->CreatePrinterDC();
	ASSERT(hdc);
	CDC dc;
	dc.Attach( hdc );
	
    dc.m_bPrinting = TRUE;
	
    CString strTitle = m_szTitle;
	if (strTitle.IsEmpty())
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		
    DOCINFO di;                                 // Initialise print doc details
    memset(&di, 0, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = strTitle;
	
    BOOL bPrintingOK = dc.StartDoc(&di);        // Begin a new print job
	
    CPrintInfo Info;
    Info.m_rectDraw.SetRect(0,0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
	
    m_Grid.OnBeginPrinting(&dc, &Info);                // Initialise printing
	m_Grid.SetFocus();
    for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++)
    {
        dc.StartPage();                         // begin new page
        Info.m_nCurPage = page;
        m_Grid.OnPrint(&dc, &Info);                    // Print page
        bPrintingOK = (dc.EndPage() > 0);       // end page
    }
    m_Grid.OnEndPrinting(&dc, &Info);                  // Clean up after printing
	
    if (bPrintingOK)
        dc.EndDoc();                            // end a print job
    else
        dc.AbortDoc();                          // abort job.
	
    dc.Detach();                                // detach the printer DC
	
	DeleteDC(hdc);

	return TRUE;
}