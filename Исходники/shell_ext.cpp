STDMETHODIMP CShellExt::XPropertySheetExt::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
    METHOD_PROLOGUE(CShellExt, PropertySheetExt);

    if(pThis->m_bIsPathInAFS) {
        // add the property page for files/folder/mount points/symlinks
        PROPSHEETPAGE psp;
        SecureZeroMemory(&psp, sizeof(PROPSHEETPAGE));
        HPROPSHEETPAGE hPage;
        CPropFile *filesheet = NULL;
        CPropVolume *volsheet = NULL;
        CPropACL * aclsheet = NULL;

        filesheet = new CPropFile(pThis->m_astrFileNames);

        if (filesheet == NULL)
            return E_OUTOFMEMORY;

        HINSTANCE hInst = 0;
        TaLocale_GetResource(RT_DIALOG, MAKEINTRESOURCE(IDD_PROPPAGE_FILE), LANG_USER_DEFAULT, &hInst);
        filesheet->m_hInst = hInst;
        filesheet->m_bIsMountpoint = pThis->m_bIsMountpoint;
        filesheet->m_bIsSymlink = pThis->m_bIsSymlink;
        filesheet->m_bIsDir = pThis->m_bDirSelected;
        psp.dwSize = sizeof (psp);
        psp.dwFlags = PSP_USEREFPARENT | PSP_USETITLE | PSP_USECALLBACK | PSP_USETITLE;
        psp.hInstance = hInst;
        psp.pszTemplate = MAKEINTRESOURCE(IDD_PROPPAGE_FILE);
        psp.pszIcon = NULL;
        psp.pszTitle = _T("AFS");
        psp.pfnDlgProc = (DLGPROC) PageProc;
        psp.lParam = (LPARAM) filesheet;
        psp.pfnCallback = PropPageCallbackProc;
        psp.pcRefParent = (UINT*) &nPSRefCount;

        hPage = CreatePropertySheetPage (&psp);

        if (hPage != NULL) {
            if (!lpfnAddPage (hPage, lParam)) {
                delete filesheet;
                DestroyPropertySheetPage (hPage);
            }
        }

        // add the property page for Volume Data
        SecureZeroMemory(&psp, sizeof(PROPSHEETPAGE));
        volsheet = new CPropVolume(pThis->m_astrFileNames);
        if (volsheet == NULL)
            return E_OUTOFMEMORY;

        hInst = 0;
        TaLocale_GetResource(RT_DIALOG, MAKEINTRESOURCE(IDD_PROPPAGE_VOLUME), LANG_USER_DEFAULT, &hInst);
        volsheet->m_hInst = hInst;
        volsheet->m_bIsMountpoint = pThis->m_bIsMountpoint;
        volsheet->m_bIsSymlink = pThis->m_bIsSymlink;
        volsheet->m_bIsDir = pThis->m_bDirSelected;
        psp.dwSize = sizeof (psp);
        psp.dwFlags = PSP_USEREFPARENT | PSP_USETITLE | PSP_USECALLBACK | PSP_USETITLE;
        psp.hInstance = hInst;
        psp.pszTemplate = MAKEINTRESOURCE(IDD_PROPPAGE_VOLUME);
        psp.pszIcon = NULL;
        psp.pszTitle = _T("AFS Volume");
        psp.pfnDlgProc = (DLGPROC) PageProc;
        psp.lParam = (LPARAM) volsheet;
        psp.pfnCallback = PropPageCallbackProc;
        psp.pcRefParent = (UINT*) &nPSRefCount;

        hPage = CreatePropertySheetPage (&psp);

        if (hPage != NULL) {
            if (!lpfnAddPage (hPage, lParam)) {
                delete volsheet;
                DestroyPropertySheetPage (hPage);
            }
        }

        if(pThis->m_bDirSelected) {
            // add the property page for ACLs
            SecureZeroMemory(&psp, sizeof(PROPSHEETPAGE));

            aclsheet = new CPropACL(pThis->m_astrFileNames);
            if (aclsheet == NULL)
                return E_OUTOFMEMORY;

            hInst = 0;
            TaLocale_GetResource(RT_DIALOG, MAKEINTRESOURCE(IDD_PROPPAGE_ACL), LANG_USER_DEFAULT, &hInst);
            aclsheet->m_hInst = hInst;
            aclsheet->m_bIsMountpoint = pThis->m_bIsMountpoint;
            aclsheet->m_bIsSymlink = pThis->m_bIsSymlink;
            aclsheet->m_bIsDir = pThis->m_bDirSelected;
            psp.dwSize = sizeof (psp);
            psp.dwFlags = PSP_USEREFPARENT | PSP_USETITLE | PSP_USECALLBACK | PSP_USETITLE;
            psp.hInstance = hInst;
            psp.pszTemplate = MAKEINTRESOURCE(IDD_PROPPAGE_ACL);
            psp.pszIcon = NULL;
            psp.pszTitle = _T("AFS ACL");
            psp.pfnDlgProc = (DLGPROC) PageProc;
            psp.lParam = (LPARAM) aclsheet;
            psp.pfnCallback = PropPageCallbackProc;
            psp.pcRefParent = (UINT*) &nPSRefCount;

            hPage = CreatePropertySheetPage (&psp);

            if (hPage != NULL) {
                if (!lpfnAddPage (hPage, lParam)) {
                    delete aclsheet;
                    DestroyPropertySheetPage (hPage);
                }
            }
        }
    }

    return S_OK;
}