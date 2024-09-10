VOID
InitializeDxDiagDialog(HWND hwndDlg)
{
    PDXDIAG_CONTEXT pContext;
    HICON hIcon;

    pContext = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DXDIAG_CONTEXT));
    if (!pContext)
        return;

    /* store window handle */
    pContext->hMainDialog = hwndDlg;

    /* store the context */
    SetWindowLongPtr(hwndDlg, DWLP_USER, (LONG_PTR)pContext);

    /* initialize the tab ctrl */
    InitializeTabCtrl(hwndDlg, pContext);

    /* load application icon */
    hIcon = LoadImageW(hInst, MAKEINTRESOURCEW(IDI_APPICON), IMAGE_ICON, 16, 16, 0);
    if (!hIcon)
        return;
    /* display icon */
    SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
}