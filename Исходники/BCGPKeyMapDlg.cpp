//*************************************************************************************
void CBCGPKeyMapDlg::PrintKeyMap ()
{
	CWaitCursor WaitCursor;
	
	int nItem = -1;
	int nFlag = (m_KeymapList.GetSelectedCount () > 0)  ?  LVNI_SELECTED : LVNI_ALL;
	
	CPrintDialog dlgPrint (FALSE, PD_ALLPAGES | PD_RETURNDC | PD_NOSELECTION, NULL);
	if (dlgPrint.DoModal() != IDOK)
	{
		return;
	}
	
	// Obtain a handle to the device context.
	HDC hdcPrn = dlgPrint.GetPrinterDC ();
	if (hdcPrn == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	CDC dc;
	dc.Attach (hdcPrn);

	CSize szPage (dc.GetDeviceCaps (HORZRES), dc.GetDeviceCaps (VERTRES));

	dc.StartDoc(_T("BCGKeyMapDlg"));  // begin a new print job
	dc.StartPage ();
	
	int nPage = 1;
	int y = OnPrintHeader (dc, nPage, szPage.cx);

	while ((nItem = m_KeymapList.GetNextItem (nItem, nFlag)) >= 0)
	{
		int nItemHeight = OnPrintItem (dc, nItem, y, szPage.cx, TRUE /* Calc height */);
		if (y + nItemHeight > szPage.cy)
		{
			dc.EndPage();

			dc.StartPage ();
			y = OnPrintHeader (dc, ++nPage, szPage.cx);
		}

		y += OnPrintItem (dc, nItem, y, szPage.cx, FALSE /* Draw */);
	}
	
	dc.EndPage();
	dc.EndDoc();
}