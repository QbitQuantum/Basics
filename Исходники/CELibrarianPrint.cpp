void CELibrarianApp::OnPrintLibrary() 
{
	CString pszLibraryName, pszHeaderName;
	CPrintInfo printInfo;
    CELibrarianApp * pApp = this;

	//
	// get document
	//
	CELibrarianDoc* pDoc = (CELibrarianDoc*) GetDocument();
	pszLibraryName = pDoc->GetTitle();


	// 
	// print dialog
    // Page selection disabled
	//
    printInfo.m_pPD->m_pd.Flags |= PD_NOPAGENUMS;

	if (IDOK != pApp->DoPrintDialog(printInfo.m_pPD))
    {
		return;       // do not print
    }

    // print all pages
    printInfo.m_pPD->m_pd.nToPage = 0xffff;

	if (NULL == printInfo.m_pPD->m_pd.hDC)
    {
		return;
    }

	// gather file to print to if print-to-file selected
	CString strOutput;
	if (printInfo.m_pPD->m_pd.Flags & PD_PRINTTOFILE)
	{
		// construct CFileDialog for browsing
		CString strDef(MAKEINTRESOURCE(AFX_IDS_PRINTDEFAULTEXT));
		CString strPrintDef(MAKEINTRESOURCE(AFX_IDS_PRINTDEFAULT));
		CString strFilter(MAKEINTRESOURCE(AFX_IDS_PRINTFILTER));
		CString strCaption(MAKEINTRESOURCE(AFX_IDS_PRINTCAPTION));
		CFileDialog dlg(FALSE, strDef, strPrintDef,
			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
		dlg.m_ofn.lpstrTitle = strCaption;

		if (IDOK != dlg.DoModal())
        {
			return;
        }

		// set output device to resulting path name
		strOutput = dlg.GetPathName();
	}

	//
	// set up document info and start the document printing process
	//
	DOCINFO docInfo;
	memset(&docInfo, 0, sizeof(DOCINFO));
	docInfo.cbSize = sizeof(DOCINFO);
	docInfo.lpszDocName = pszLibraryName;
	CString strPortName;
	int nFormatID;
	if (strOutput.IsEmpty())
	{
		docInfo.lpszOutput = NULL;
		strPortName = printInfo.m_pPD->GetPortName();
		nFormatID = AFX_IDS_PRINTONPORT;
	}
	else
	{
		docInfo.lpszOutput = strOutput;
		nFormatID = AFX_IDS_PRINTTOFILE;
	}
	
	//
	// setup the printing DC
	//
	CDC dcPrint;
	dcPrint.Attach(printInfo.m_pPD->m_pd.hDC);  // attach printer dc
	dcPrint.m_bPrinting = TRUE;


	//
	// setup status dialog
	//
	dcPrint.SetAbortProc(PrjPrintAbortProc);

	// disable main window while printing & init printing status dialog
	AfxGetMainWnd()->EnableWindow(FALSE);
	CPrjPrintDialog dlgPrintStatus(m_pMainWnd);

	CString strTemp;

    dlgPrintStatus.SetDlgItemText(AFX_IDC_PRINT_DOCNAME, pszLibraryName);
	dlgPrintStatus.SetDlgItemText(AFX_IDC_PRINT_PRINTERNAME,
		printInfo.m_pPD->GetDeviceName());
	AfxFormatString1(strTemp, nFormatID, strPortName);
	dlgPrintStatus.SetDlgItemText(AFX_IDC_PRINT_PORTNAME, strTemp);

    dlgPrintStatus.ShowWindow(SW_SHOW);
    dlgPrintStatus.UpdateWindow();

	//
	// start printing
	//
	if (dcPrint.StartDoc(&docInfo) == SP_ERROR)
	{
		// enable main window before proceeding
		AfxGetMainWnd()->EnableWindow(TRUE);

		// cleanup and show error message
    	dlgPrintStatus.DestroyWindow();
		dcPrint.Detach();   // will be cleaned up by CPrintInfo destructor
		AfxMessageBox(AFX_IDP_FAILED_TO_START_PRINT);
		return;
	}


    BOOL bError = FALSE;
    CPrintUserData UserData;
    CString strBuffer;
 
    printInfo.m_lpUserData = (LPVOID)&UserData;
    UserData.SetLibraryName(pszLibraryName);

	//
    // print list of POU's
	//
  	//bError = PrintPOUList(&dcPrint, & printInfo);
	bError = FALSE;

	//
	// print all headers pf POU's
	//
	/*CELibrary* pCeLibrary = pDoc->GetCELibrary();
	int nn = pCeLibrary->GetPOUCount();
	CString pouName;
	for ( int ii=0 ; ii<nn && !bError; ii++)
	{	
		pouName = pCeLibrary->GetPOUName(ii);
		if (pouName != ".")
		{	
			UserData.SetHeaderName(pouName);
			bError = PrintPOUHeader( pouName, &dcPrint, &printInfo, &dlgPrintStatus);
		}
	}*/

	if (!bError)
		dcPrint.EndDoc();
	else
		dcPrint.AbortDoc();

	AfxGetMainWnd()->EnableWindow();    // enable main window
	dlgPrintStatus.DestroyWindow();
	dcPrint.Detach();   // will be cleaned up by CPrintInfo destructor
    return;
	
}