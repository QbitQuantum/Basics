/************************************************************************
 *           PSDRV_StartDocA
 */
INT PSDRV_StartDocA( PSDRV_PDEVICE *physDev, const DOCINFOA *doc )
{
    LPCSTR output = "LPT1:";
    BYTE buf[300];
    HANDLE hprn = INVALID_HANDLE_VALUE;
    PRINTER_INFO_5A *pi5 = (PRINTER_INFO_5A*)buf;
    DWORD needed;

    if(physDev->job.hJob) {
        FIXME("hJob != 0. Now what?\n");
	return 0;
    }

    if(doc->lpszOutput)
        output = doc->lpszOutput;
    else if(physDev->job.output)
        output = physDev->job.output;
    else {
        if(OpenPrinterA(physDev->pi->FriendlyName, &hprn, NULL) &&
           GetPrinterA(hprn, 5, buf, sizeof(buf), &needed)) {
            output = pi5->pPortName;
        }
        if(hprn != INVALID_HANDLE_VALUE)
            ClosePrinter(hprn);
    }

    physDev->job.hJob = OpenJob16(output,  doc->lpszDocName, HDC_16(physDev->hdc) );
    if(!physDev->job.hJob) {
        WARN("OpenJob failed\n");
	return 0;
    }
    physDev->job.banding = FALSE;
    physDev->job.OutOfPage = TRUE;
    physDev->job.PageNo = 0;
    physDev->job.quiet = FALSE;
    physDev->job.in_passthrough = FALSE;
    physDev->job.had_passthrough_rect = FALSE;
    if(doc->lpszDocName) {
        physDev->job.DocName = HeapAlloc(GetProcessHeap(), 0, strlen(doc->lpszDocName)+1);
        strcpy(physDev->job.DocName, doc->lpszDocName);
    } else
        physDev->job.DocName = NULL;

    return physDev->job.hJob;
}