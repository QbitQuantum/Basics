HRESULT CFileTimeShlExt::AddPages ( LPFNADDPROPSHEETPAGE lpfnAddPageProc,
                                    LPARAM lParam )
{
PROPSHEETPAGE  psp;
HPROPSHEETPAGE hPage;
TCHAR          szPageTitle [MAX_PATH];
string_list::const_iterator it, itEnd;
                                  
    for ( it = m_lsFiles.begin(), itEnd = m_lsFiles.end();
          it != itEnd;
          it++ )
        {
        // 'it' points at the next filename.  Allocate a new copy of the string
        // that the page will own.
        LPCTSTR szFile = _tcsdup ( it->c_str() );

        if ( NULL == szFile )
            return E_OUTOFMEMORY;

        // Strip the path and extension from the filename - this will be the
        // page title.  The name is truncated at 24 chars so it fits on the tab.

        lstrcpy ( szPageTitle, it->c_str() );
        PathStripPath ( szPageTitle );
        PathRemoveExtension ( szPageTitle );
        szPageTitle[24] = '\0';

        // Set up the PROPSHEETPAGE struct.

        ZeroMemory ( &psp, sizeof(PROPSHEETPAGE) );

        psp.dwSize      = sizeof(PROPSHEETPAGE);
        psp.dwFlags     = PSP_USEREFPARENT | PSP_USETITLE | PSP_DEFAULT |
                            PSP_USEICONID | PSP_USECALLBACK;
        psp.hInstance   = _Module.GetModuleInstance();
        psp.pszTemplate = MAKEINTRESOURCE(IDD_FILETIME_PROPPAGE);
        psp.pszIcon     = MAKEINTRESOURCE(IDI_ICON);
        psp.pszTitle    = szPageTitle;
        psp.pfnDlgProc  = PropPageDlgProc;
        psp.lParam      = (LPARAM) szFile;
        psp.pfnCallback = PropPageCallbackProc;
        psp.pcRefParent = (UINT*) &_Module.m_nLockCnt;

        // Create the page & get a handle.

        hPage = CreatePropertySheetPage ( &psp );

        if ( NULL != hPage )
            {
            // Call the shell's callback function, so it adds the page to
            // the property sheet.

            if ( !lpfnAddPageProc ( hPage, lParam ))
                {
                DestroyPropertySheetPage ( hPage );
                }
            }
        }   // end for

    return S_OK;
}