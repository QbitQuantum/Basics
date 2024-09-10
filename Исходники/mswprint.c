wBool_t wPrintDocStart( const char * title, int fpageCount, int * copiesP )
{
	printStatus = FALSE;
	pageCount = fpageCount;
	pageNumber = 0;
	print_d.hDc = mswGetPrinterDC();
	if (print_d.hDc == (HDC)0) {
		return FALSE;
	}
		printStatus = TRUE;
		docInfo.cbSize = sizeof docInfo;
		docInfo.lpszDocName = title;
		docInfo.lpszOutput = NULL;
		lpAbortDlg = MakeProcInstance( (FARPROC)mswAbortDlg, mswHInst );
		lpAbortProc = MakeProcInstance( (FARPROC)mswAbortProc, mswHInst );
		SetAbortProc( print_d.hDc, (ABORTPROC)lpAbortProc );
		if (StartDoc( print_d.hDc, &docInfo ) < 0) {
			MessageBox( mswHWnd, "Unable to start print job",
						NULL, MB_OK|MB_ICONHAND );
			FreeProcInstance( lpAbortDlg );
			FreeProcInstance( lpAbortProc );
			DeleteDC( print_d.hDc );
			return FALSE;
		}
		printAbort = FALSE;
		hAbortDlgWnd = CreateDialog( mswHInst, "MswAbortDlg", mswHWnd,
						(DLGPROC)lpAbortDlg );
		/*SetDlgItemText( hAbortDlgWnd, IDM_PRINTAPP, title );*/
		SetWindowText( hAbortDlgWnd, title );
		ShowWindow( hAbortDlgWnd, SW_NORMAL );
		UpdateWindow( hAbortDlgWnd );
		EnableWindow( mswHWnd, FALSE );
		if (copiesP)
			*copiesP = printDlg.nCopies;
		if (printDlg.nCopies>1)
			pageCount *= printDlg.nCopies;
		if ( (GetDeviceCaps( printDlg.hDC, RASTERCAPS ) & RC_PALETTE) ) {
			newPrintPalette = mswCreatePalette();
			oldPrintPalette = SelectPalette( printDlg.hDC, newPrintPalette, 0 );
			RealizePalette( printDlg.hDC );
		}
		return TRUE;
}