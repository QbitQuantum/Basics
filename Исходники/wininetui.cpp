/*
Routine Description:
    Supports Yes/No,Ok/Cancel decisions for the authentication UI.

Arguments:
    hwnd    - standard dialog params
    msg     - "
    wparam  - "
    lparam  - "

Return Value:
    BOOL
        TRUE    - we handled message
        FALSE   - Windows should handle message
*/
INT_PTR CALLBACK OkCancelDialogProc(HWND hwnd,
                                    UINT msg,
                                    WPARAM wparam,
                                    LPARAM lparam)
{
    BOOL              fRet = FALSE;
    PERRORINFODLGTYPE pDlgInfo;

    if ( msg != WM_INITDIALOG )
    {
        pDlgInfo = (PERRORINFODLGTYPE) GetWindowLongW(hwnd,DWL_USER);
        fRet = SHRCMLDialogProc( HINST_RESDLL, MAKEINTRESOURCE(pDlgInfo->dwDlgId),
                                     hwnd, msg, wparam, lparam );
    }

    switch(msg)
    {
    case WM_INITDIALOG:
        ASSERT(lparam);

        SetWindowLongW(hwnd,DWL_USER,lparam);

        pDlgInfo = (PERRORINFODLGTYPE)lparam;

        SHRCMLDialogProc( HINST_RESDLL, MAKEINTRESOURCE(pDlgInfo->dwDlgId),
                              hwnd, msg, wparam, lparam );

        SHINITDLGINFO shidi;
        SHMENUBARINFO   mbi;

        // Some of these dialogs need a scrollbar
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_WANTSCROLLBAR;
        shidi.hDlg = hwnd;
        SHInitDialog(&shidi);

        // softkeys
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hwnd;
        mbi.nToolBarId = IDR_INETUI_DIALOGYESNO;
        mbi.hInstRes = HINST_RESDLL;
        SHCreateMenuBar(&mbi);

        SHSetWindowBits(hwnd, GWL_STYLE, WS_NONAVDONEBUTTON,   WS_NONAVDONEBUTTON);

        if(IDD_SEC_CERT_ERRORS == pDlgInfo->dwDlgId)
        {
            InitSecCertErrorsDlg(hwnd,pDlgInfo);
        }
        else if(IDD_REVOCATION_PROBLEM == pDlgInfo->dwDlgId)
        {
            DWORD dwFlags = 0, dwSize = sizeof(dwFlags);

            if(pDlgInfo->hInternetMapped)
            {
                InternetQueryOption(pDlgInfo->hInternetMapped,
                                 INTERNET_OPTION_SECURITY_FLAGS,
                                 &dwFlags, 
                                 &dwSize);
            }
            
            if(dwFlags & DLG_FLAGS_SEC_CERT_REV_FAILED)
                pDlgInfo->dwDlgFlags |= DLG_FLAGS_IGNORE_FAILED_REVOCATION;
        }

        fRet = TRUE;

        // set this dialog as foreground if necessary
        if(pDlgInfo->dwDlgFlags & DLG_FLAGS_BRING_TO_FOREGROUND)
            SetForegroundWindow(hwnd);

        break;

    case WM_COMMAND:
        {
            WORD    wID = LOWORD(wparam);

            pDlgInfo = (PERRORINFODLGTYPE) GetWindowLongW(hwnd,DWL_USER);
            switch(wID)
            {
            case IDOK:
            case IDYES:
                ASSERT(pDlgInfo);
                ASSERT(pDlgInfo->dwDlgId != 0);

                //  Save flags,and change any global vars,and registry values if needed.
                if(pDlgInfo->hInternetMapped)
                {
                    VERIFY(InternetSetOptionW(pDlgInfo->hInternetMapped,
                                             INTERNET_OPTION_SECURITY_FLAGS,
                                             &(pDlgInfo->dwDlgFlags), 
                                             sizeof(pDlgInfo->dwDlgFlags)));
                }


                // If the user checked the "overide" check-box
                //  let us map it,and force a general
                //  override of all errors of this type.

                if(SendDlgItemMessageW(hwnd,IDC_DONT_WANT_WARNING,BM_GETCHECK,(WPARAM)0,(LPARAM)0)==BST_CHECKED)
                    UpdateGlobalSecuritySettings(pDlgInfo->dwDlgId,pDlgInfo->dwDlgFlags);

                EndDialog(hwnd,TRUE);
                break;

            case IDCANCEL:
            case IDNO:
                EndDialog(hwnd,FALSE);
                break;
            }
            fRet = TRUE;
            break;
        }
    }
    return fRet;
}