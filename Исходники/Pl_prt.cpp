/*+/csubr/TOC----------------------------------------------------------------
* PlPrtClose - close a print job for a Windows printer
*
* Purpose:
*		Closes a print job for a Windows printer.  "end page" and "end
*		document" commands are sent to the printer.
*
*		After closing the print job, this routine wraps up operations
*		for the PL_CTX for the printout.
*
* Return Value:
*		PL_OK, or
*		PL_PRT_CANCEL  if bAbort is 1 or if PlPrtStatusWindow has been
*					called and the operator clicks Cancel, or
*		other codes for other errors
*
* Notes:
* 1.	If bAbort is 1 (or if pPlot->bPrintCancel is 1), then the printout
*		is aborted, so that nothing is sent to the printer.
* 2.	This routine automatically calls PlotWrapup.
*
* See Also:
*		PlPrtOpenDefault, PlPrtOpenDialog, PlPrtStatusWindow
*
*-Date     Author		Revision
* -------- ------------	--------
* 06-08-95 R. Cole		created
*--------------------------------------------------------------------------*/
int PASCAL
PlPrtClose(
PL_CTX	*pPlot,			// IO pointer to plot context struct for printing
int		bAbort)			// I 1 to abort the printout
{
	int		retStat=PL_OK;
	int		stat;
	PRINTDLG *pPd=NULL;

	if (pPlot->hDC != 0) {
		if (bAbort || pPlot->bPrintCancel)
			stat = AbortDoc(pPlot->hDC);
		else {
			stat = EndPage(pPlot->hDC);
			stat = EndDoc(pPlot->hDC);
		}
	}
	if (pPlot->pPd != NULL) {
		pPd = (PRINTDLG *)pPlot->pPd;
		if (pPd->hDevMode != 0) GlobalFree(pPd->hDevMode);
		if (pPd->hDevNames != 0) GlobalFree(pPd->hDevNames);
		GlobalUnlock(pPlot->hPD);
	}
	if (pPlot->hPD != 0) GlobalFree(pPlot->hPD);
	if (pPlot->hDC != 0) DeleteDC(pPlot->hDC);
	pPlot->hDC = 0;
	pPlot->hPD = 0;
	pPlot->pPd = NULL;

	retStat = PlPlotWrapup(pPlot);
	strcpy(pPlot->szPrintOpen, "cls");

	return retStat;
}