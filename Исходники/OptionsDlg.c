LRESULT CALLBACK
DlgOptions(
    HWND   hDlg,
    UINT   message,
    WPARAM wParam,
    LPARAM lParam
    )
{
    static LPCWSTR szExeName;
    SHIM_SETTINGS ShimSettingsTemp;
    LPSHIM_SETTINGS pShimSettings = & gShimSettings;
    DWORD cbSize;

    switch (message) {
    case WM_INITDIALOG:
        {
            //
            // find out what exe we're handling settings for
            //
            szExeName = ExeNameFromLParam(lParam);

            GetShimSettings (szExeName, & pShimSettings, & cbSize);

            RefreshDlgData (hDlg);

            return TRUE;
        }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_DEFAULT:
            {
                // Save off the globals
                memcpy (& ShimSettingsTemp, & gShimSettings, sizeof (SHIM_SETTINGS));

                // Set the default values
                gShimSettings.dwFoo = 0;

                // Update the UI to reflect the default values.
                RefreshDlgData (hDlg);

                // Restore the globals (in case this isn't 'applied')
                memcpy (& gShimSettings, & ShimSettingsTemp, sizeof (SHIM_SETTINGS));

                break;
            }
        }
        break;

    case WM_NOTIFY:
        switch (((NMHDR FAR *) lParam)->code) {

        case PSN_KILLACTIVE:
            {
                break;
            }

        case PSN_APPLY:
            {
                NKDbgPrintfW (_T("Applying settings for %s\r\n"), szExeName);

                // Retrieve settings from the UI.
                gShimSettings.dwFoo = GetDlgItemInt (
                    hDlg,
                    IDC_EDIT_FOO,
                    NULL,
                    FALSE
                    );

                SetShimSettings (szExeName, & gShimSettings, sizeof (SHIM_SETTINGS));

                break;
            }
        }
        break;
    }

    return FALSE;
}