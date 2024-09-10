/////////////////////////////////////////////////////////////////////////////
// LaunchUrlmonDialog
/////////////////////////////////////////////////////////////////////////////
int LaunchUrlmonDialog
(
    IN HWND     hWnd,
    IN DWORD    dwAction,
    IN DWORD    dwPermissions,
    IN LPCTSTR  lpszText
)
{
    int iRet = ERROR_CALL_NOT_IMPLEMENTED;

    UMDLGPARAMS umparams;
    
    umparams.eDlgType   = GetDialogType(dwAction, dwPermissions);
    umparams.pszMsg     = lpszText;

    iRet = DialogBoxIndirectParamW(HINST_RESDLL,
                                   (LPCDLGTEMPLATEW)LoadResource(HINST_RESDLL,
                                                    FindResourceW(HINST_RESDLL,
                                                        MAKEINTRESOURCEW(IDD_URLMON),
                                                        RT_DIALOG)),
                                   SHGetLastActiveWindow(hWnd), 
                                   (DLGPROC)UrlmonDialogProc, 
                                   (LPARAM)&umparams);

    return iRet;
}