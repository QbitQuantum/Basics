extern "C" BOOL CALLBACK AddPersonalTrustDBPages(
//
// Add the pages of our trust database editor to the indicated property
// sheet by using the indicated callback function. Return success or failure
//
    LPVOID lpv, 	
    LPFNADDPROPSHEETPAGE lpfnAddPage, 	
    LPARAM lParam	
   ) { 
    PROPSHEETPAGE psp; 

    CDialogTrustDB* pdlg = new CDialogTrustDB;
    if (!pdlg)
        return FALSE; 

    psp.dwSize      = sizeof(psp);   // no extra data 
    psp.dwFlags     = PSP_USECALLBACK | PSP_USETITLE;
    psp.hInstance   = hinst; 
    psp.pszTemplate = MAKEINTRESOURCE(IDD_TRUSTDIALOG);
    psp.pfnDlgProc  = TrustPropSheetDialogProc; 
    psp.pfnCallback = TrustPropSheetDialogReleaseProc;
    psp.lParam      = (LPARAM)pdlg; 
    psp.pszTitle    = MAKEINTRESOURCE(IDS_TRUSTDIALOG);

    BOOL fSuccess = TRUE;
    HPROPSHEETPAGE hpage = CreatePropertySheetPage(&psp); 
    if (hpage) 
        { 
        if (!lpfnAddPage(hpage, lParam)) 
            {
            DestroyPropertySheetPage(hpage);
            fSuccess = FALSE;
            }
        }
    else
        fSuccess = FALSE;

    return fSuccess;
    } 