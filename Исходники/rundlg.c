void BrowsePushed(LPRUNDLG_DATA lprd)
{
    HWND hDlg = lprd->hDlg;
    TCHAR szText[MAX_PATH];

    // Get out of the "synchronized input queues" state
    if (lprd->dwThreadId)
    {
        AttachThreadInput(GetCurrentThreadId(), lprd->dwThreadId, FALSE);
        lprd->dwThreadId = 0;
    }

    GetDlgItemText(hDlg, IDD_COMMAND, szText, ARRAYSIZE(szText));
    PathUnquoteSpaces(szText);

    if (GetFileNameFromBrowse(hDlg, szText, ARRAYSIZE(szText), lprd->lpszWorkingDir,
            MAKEINTRESOURCE(IDS_EXE), MAKEINTRESOURCE(IDS_PROGRAMSFILTER),
            MAKEINTRESOURCE(IDS_BROWSE)))
    {
        PathQuoteSpaces(szText);
        SetDlgItemText(hDlg, IDD_COMMAND, szText);
        EnableOKButton(hDlg, szText);
        // place the focus on OK
        // SetFocus(GetDlgItem(hDlg, IDOK));
        SendMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)GetDlgItem(hDlg, IDOK), TRUE);
    }
}