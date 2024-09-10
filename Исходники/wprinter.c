void
DumpPrinter(HWND hwnd, LPTSTR szAppName, LPTSTR szFileName)
{
    PRINTDLGEX pd;
    DEVNAMES * pDevNames;
    LPCTSTR szDevice;
    GP_PRINT pr;
    HANDLE printer;
    DOC_INFO_1 di;
    DWORD jobid;
    HRESULT hr;
    LPSTR buf;
    int count;
    FILE *f;
    long lsize;
    long ldone;
    TCHAR pcdone[10];

    if ((f = _tfopen(szFileName, TEXT("rb"))) == NULL)
	return;
    fseek(f, 0L, SEEK_END);
    lsize = ftell(f);
    if (lsize <= 0)
	lsize = 1;
    fseek(f, 0L, SEEK_SET);
    ldone = 0;

    /* Print Property Sheet  */
    /* See http://support.microsoft.com/kb/240082 */
    memset(&pd, 0, sizeof(pd));
    pd.lStructSize = sizeof(pd);
    pd.hwndOwner = hwnd;
    pd.Flags = PD_NOPAGENUMS | PD_NOSELECTION | PD_NOCURRENTPAGE | PD_USEDEVMODECOPIESANDCOLLATE;
    pd.hDevNames = hDevNames;
    pd.hDevMode = hDevMode;
    pd.hDevNames = NULL;
    pd.hDevMode = NULL;
    pd.nCopies = 1;
    pd.nStartPage = START_PAGE_GENERAL;

    /* Replace the additional options in the lower part of the dialog with
     * a hint to change print options via terminal options.
     */
    pd.lpPrintTemplateName = TEXT("PrintDlgExSelect");
    pd.hInstance = graphwin->hInstance;
    pd.Flags |= PD_ENABLEPRINTTEMPLATE;

    if ((hr = PrintDlgEx(&pd)) != S_OK) {
	DWORD error = CommDlgExtendedError();
	fprintf(stderr, "\nError:  Opening the print dialog failed with error code %04x (%04x).\n", hr, error);
    }

    if (pd.dwResultAction == PD_RESULT_PRINT) {
	pDevNames = (DEVNAMES *) GlobalLock(pd.hDevNames);
	szDevice = (LPCTSTR)pDevNames + pDevNames->wDeviceOffset;
	if (!OpenPrinter((LPTSTR)szDevice, &printer, NULL))
		printer = NULL;
	GlobalUnlock(pd.hDevNames);
	/* We no longer free these structures, but preserve them for the next time
	GlobalFree(pd.hDevMode);
	GlobalFree(pd.hDevNames);
	*/
	hDevNames = pd.hDevNames;
	hDevMode = pd.hDevMode;

	if (printer == NULL)
	    return;	/* abort */

	pr.hdcPrn = printer;
	PrintRegister(&pr);
	if ((buf = (LPSTR) malloc(4096)) != NULL) {
	    EnableWindow(hwnd, FALSE);
	    pr.bUserAbort = FALSE;
	    pr.szTitle = szAppName;
	    pr.hDlgPrint = CreateDialogParam(hdllInstance, TEXT("CancelDlgBox"),
						hwnd, PrintDlgProc, (LPARAM) &pr);
	    SendMessage(GetDlgItem(pr.hDlgPrint, CANCEL_PROGRESS), PBM_SETRANGE32, 0, lsize);

	    di.pDocName = szAppName;
	    di.pOutputFile = NULL;
	    di.pDatatype = TEXT("RAW");
	    if ((jobid = StartDocPrinter(printer, 1, (LPBYTE) &di)) > 0) {
		while (pr.hDlgPrint && !pr.bUserAbort &&
		       (count = fread(buf, 1, 4096, f)) != 0 ) {
		    int ret;
		    DWORD dwBytesWritten;

		    ret = WritePrinter(printer, buf, count, &dwBytesWritten);
		    ldone += count;
		    if (dwBytesWritten > 0) {
			wsprintf(pcdone, TEXT("%d%% done"), (int)(ldone * 100 / lsize));
			SetWindowText(GetDlgItem(pr.hDlgPrint, CANCEL_PCDONE), pcdone);
			SendMessage(GetDlgItem(pr.hDlgPrint, CANCEL_PROGRESS), PBM_SETPOS, ldone, 0);
		    } else if (ret == 0) {
			SetWindowText(GetDlgItem(pr.hDlgPrint, CANCEL_PCDONE), TEXT("Error writing to printer!"));
			pr.bUserAbort  = TRUE;
		    }

		    /* handle window messages */
		    PrintAbortProc(printer, 0);
		}
		if (pr.bUserAbort) {
		    if (SetJob(printer, jobid, 0, NULL, JOB_CONTROL_DELETE) == 0) {
			SetWindowText(GetDlgItem(pr.hDlgPrint, CANCEL_PCDONE), TEXT("Error: Failed to cancel print job!"));
			fprintf(stderr, "Error: Failed to cancel print job!\n");
		    }
		}
		EndDocPrinter(printer);
		if (!pr.bUserAbort) {
		    EnableWindow(hwnd, TRUE);
		    DestroyWindow(pr.hDlgPrint);
		}
		free(buf);
	    }
	}
	ClosePrinter(printer);
	PrintUnregister(&pr);
    }
    fclose(f);
}