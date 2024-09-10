int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int nCmdShow)
{
    UNREFERENCED_PARAMETER(nCmdShow);
    UNREFERENCED_PARAMETER(hPrevInstance);

    PROPSHEETPAGE   psp;					//defines the property sheet pages
    HPROPSHEETPAGE  rhpsp[MAXPAGES];		//an array to hold the page's HPROPSHEETPAGE handles
    SHAREDWIZDATA   wizdata;				//the shared data structure
    UINT            cPages          = 0;    //number of pages being added
    BOOL            fPagesCreated   = FALSE;//were all of the pages created successfully?

    ZeroMemory(&psp, sizeof(psp));
    ZeroMemory(&wizdata, sizeof(wizdata));
    ZeroMemory(&rhpsp, sizeof(HPROPSHEETPAGE)*MAXPAGES);

    //
    // Create the Wizard pages
    //

    // First interior page

    psp.dwSize              = sizeof(psp);
    psp.dwFlags             = PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
    psp.hInstance           = hInstance;
    psp.lParam              = (LPARAM) &wizdata; //The shared data structure
    psp.pszHeaderTitle      = MAKEINTRESOURCE(IDS_TITLE1);
    psp.pszHeaderSubTitle	= MAKEINTRESOURCE(IDS_SUBTITLE1);
    psp.pszTemplate         = MAKEINTRESOURCE(IDD_INTERIOR1);
    psp.pfnDlgProc          = (DLGPROC)IntPage1DlgProc;

    rhpsp[cPages]           = CreatePropertySheetPage(&psp);

    if (rhpsp[cPages])
    {
        ++cPages;

        // Second interior page

        psp.dwFlags             = PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
        psp.pszHeaderTitle      = MAKEINTRESOURCE(IDS_TITLE2);
        psp.pszHeaderSubTitle   = MAKEINTRESOURCE(IDS_SUBTITLE2);
        psp.pszTemplate         = MAKEINTRESOURCE(IDD_INTERIOR2);
        psp.pfnDlgProc          = (DLGPROC)IntPage2DlgProc;

        rhpsp[cPages]           = CreatePropertySheetPage(&psp);

        if (rhpsp[cPages])
        {
            ++cPages;

            //Third interior page

            psp.dwFlags             = PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
            psp.pszHeaderTitle      = MAKEINTRESOURCE(IDS_TITLE3);
            psp.pszHeaderSubTitle   = MAKEINTRESOURCE(IDS_SUBTITLE3);
            psp.pszTemplate         = MAKEINTRESOURCE(IDD_INTERIOR3);
            psp.pfnDlgProc          = (DLGPROC)IntPage3DlgProc;

            rhpsp[cPages]           = CreatePropertySheetPage(&psp);

            if (rhpsp[cPages])
            {
                ++cPages;
                fPagesCreated = TRUE;
            }
        }
    }

    if (fPagesCreated)
    {
        // Create the property sheet
        PROPSHEETHEADER psh;  //defines the property sheet
        ZeroMemory(&psh, sizeof(psh));

        psh.dwSize          = sizeof(psh);
        psh.hInstance       = hInstance;
        psh.hwndParent      = NULL;
        psh.phpage          = rhpsp;
        psh.dwFlags         = PSH_AEROWIZARD | PSH_USEICONID;
        psh.pszCaption      = MAKEINTRESOURCE(IDS_WIZTITLE);
        psh.pszIcon         = MAKEINTRESOURCE(IDI_WIZICON);
        psh.nStartPage      = 0;
        psh.nPages          = cPages;

        //Display the wizard
        if (PropertySheet(&psh) == -1)
        {
            // an error occurred, call GetLastError() to retrieve it here.
        }
    }
    else
    {
        // error creating pages -- clean up any we did create
        for (UINT iPage = 0; iPage < cPages; ++iPage)
        {
            DestroyPropertySheetPage(rhpsp[iPage]);
        }
    }

    return 0;
}