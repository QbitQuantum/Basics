/***********************************************************************
 *           PRINTDLG_WMInitDialog                      [internal]
 */
static LRESULT PRINTDLG_WMInitDialog16(HWND hDlg, WPARAM wParam, PRINT_PTRA16* ptr16)
{
    PRINT_PTRA *PrintStructures = &ptr16->print32;
    LPPRINTDLG16 lppd = ptr16->lpPrintDlg16;
    DEVNAMES *pdn;
    DEVMODEA *pdm;
    char *name = NULL;
    UINT comboID = (lppd->Flags & PD_PRINTSETUP) ? cmb1 : cmb4;

    /* load Collate ICONs */
    PrintStructures->hCollateIcon =
        LoadIconA(COMDLG32_hInstance, "PD32_COLLATE");
    PrintStructures->hNoCollateIcon =
        LoadIconA(COMDLG32_hInstance, "PD32_NOCOLLATE");
    if(PrintStructures->hCollateIcon == 0 ||
            PrintStructures->hNoCollateIcon == 0) {
        ERR("no icon in resourcefile\n");
        COMDLG32_SetCommDlgExtendedError(CDERR_LOADRESFAILURE);
        EndDialog(hDlg, FALSE);
    }

    /* load Paper Orientation ICON */
    /* FIXME: not implemented yet */

    /*
     * if lppd->Flags PD_SHOWHELP is specified, a HELPMESGSTRING message
     * must be registered and the Help button must be shown.
     */
    if (lppd->Flags & PD_SHOWHELP) {
        if((PrintStructures->HelpMessageID =
                    RegisterWindowMessageA(HELPMSGSTRINGA)) == 0) {
            COMDLG32_SetCommDlgExtendedError(CDERR_REGISTERMSGFAIL);
            return FALSE;
        }
    } else
        PrintStructures->HelpMessageID = 0;

    if (!(lppd->Flags & PD_PRINTSETUP)) {
        /* We have a print quality combo box. What shall we do? */
        if (GetDlgItem(hDlg,cmb1)) {
            char buf [20];

            FIXME("Print quality only displaying currently.\n");

            pdm = GlobalLock16(lppd->hDevMode);
            if(pdm) {
                switch (pdm->u1.s1.dmPrintQuality) {
                case DMRES_HIGH		:
                    strcpy(buf,"High");
                    break;
                case DMRES_MEDIUM	:
                    strcpy(buf,"Medium");
                    break;
                case DMRES_LOW		:
                    strcpy(buf,"Low");
                    break;
                case DMRES_DRAFT	:
                    strcpy(buf,"Draft");
                    break;
                case 0			:
                    strcpy(buf,"Default");
                    break;
                default			:
                    sprintf(buf,"%ddpi",pdm->u1.s1.dmPrintQuality);
                    break;
                }
                GlobalUnlock16(lppd->hDevMode);
            } else
                strcpy(buf,"Default");
            SendDlgItemMessageA(hDlg,cmb1,CB_ADDSTRING,0,(LPARAM)buf);
            SendDlgItemMessageA(hDlg,cmb1,CB_SETCURSEL,0,0);
            EnableWindow(GetDlgItem(hDlg,cmb1),FALSE);
        }
    }

    /* FIXME: I allow more freedom than either Win95 or WinNT,
     *        which do not agree to what errors should be thrown or not
     *        in case nToPage or nFromPage is out-of-range.
     */
    if (lppd->nMaxPage < lppd->nMinPage)
        lppd->nMaxPage = lppd->nMinPage;
    if (lppd->nMinPage == lppd->nMaxPage)
        lppd->Flags |= PD_NOPAGENUMS;
    if (lppd->nToPage < lppd->nMinPage)
        lppd->nToPage = lppd->nMinPage;
    if (lppd->nToPage > lppd->nMaxPage)
        lppd->nToPage = lppd->nMaxPage;
    if (lppd->nFromPage < lppd->nMinPage)
        lppd->nFromPage = lppd->nMinPage;
    if (lppd->nFromPage > lppd->nMaxPage)
        lppd->nFromPage = lppd->nMaxPage;

    /* If the printer combo box is in the dialog, fill it */
    if (GetDlgItem(hDlg,comboID)) {
        /* Fill Combobox
         */
        pdn = GlobalLock16(lppd->hDevNames);
        pdm = GlobalLock16(lppd->hDevMode);
        if(pdn)
            name = (char*)pdn + pdn->wDeviceOffset;
        else if(pdm)
            name = (char*)pdm->dmDeviceName;
        PRINTDLG_SetUpPrinterListComboA(hDlg, comboID, name);
        if(pdm) GlobalUnlock16(lppd->hDevMode);
        if(pdn) GlobalUnlock16(lppd->hDevNames);

        /* Now find selected printer and update rest of dlg */
        name = HeapAlloc(GetProcessHeap(),0,256);
        if (GetDlgItemTextA(hDlg, comboID, name, 255))
            PRINTDLG_ChangePrinterA(hDlg, name, PrintStructures);
    } else {
        /* else just use default printer */
        char name[200];
        DWORD dwBufLen = sizeof(name);
        BOOL ret = GetDefaultPrinterA(name, &dwBufLen);

        if (ret)
            PRINTDLG_ChangePrinterA(hDlg, name, PrintStructures);
        else
            FIXME("No default printer found, expect problems!\n");
    }
    HeapFree(GetProcessHeap(),0,name);

    return TRUE;
}