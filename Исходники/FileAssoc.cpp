UINT CFileAssoc::RunCheckIconsAssocThread(LPVOID pParam)
{
    const CMediaFormats& mf = *(const CMediaFormats*)pParam;

    UINT nLastVersion = AfxGetApp()->GetProfileInt(IDS_R_SETTINGS, IDS_RS_ICON_LIB_VERSION, 0);

    if (LoadIconLib()) {
        UINT nCurrentVersion = GetIconLibVersion();
        SaveIconLibVersion(); // Ensure we don't try to fix the icons more than once

        CAtlList<CString> registeredExts;

        if (nCurrentVersion != nLastVersion && GetAssociatedExtensions(mf, registeredExts)) {
            if (SysVersion::IsVistaOrLater() && !IsUserAnAdmin()) {
                TASKDIALOGCONFIG config = {0};
                config.cbSize = sizeof(config);
                config.hInstance = AfxGetInstanceHandle();
                config.hwndParent = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
                config.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON;
                config.pszMainIcon = TD_SHIELD_ICON;
                config.pszWindowTitle = MAKEINTRESOURCE(IDS_ICONS_REASSOC_DLG_TITLE);
                config.pszMainInstruction = MAKEINTRESOURCE(IDS_ICONS_REASSOC_DLG_INSTR);
                config.pszContent = MAKEINTRESOURCE(IDS_ICONS_REASSOC_DLG_CONTENT);
                config.pfCallback = TaskDialogCallbackProc;

                typedef HRESULT(_stdcall * pfTaskDialogIndirect)(const TASKDIALOGCONFIG*, int*, int*, BOOL*);

                HMODULE hModule = ::LoadLibrary(_T("comctl32.dll"));
                if (hModule) {
                    pfTaskDialogIndirect TaskDialogIndirect = (pfTaskDialogIndirect)(::GetProcAddress(hModule, "TaskDialogIndirect"));

                    if (TaskDialogIndirect) {
                        int nButtonPressed = 0;
                        TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);

                        if (IDYES == nButtonPressed) {
                            AfxGetMyApp()->RunAsAdministrator(GetProgramPath(true), _T("/iconsassoc"), true);
                        }
                    }

                    ::FreeLibrary(hModule);
                }
            } else {
                ReAssocIcons(registeredExts);

                SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
            }
        }

        FreeIconLib();
    }

    return 0;
}