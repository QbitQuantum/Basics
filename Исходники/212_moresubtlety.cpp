int DoModal(HWND hwnd)
{
    DIALOGSTATE ds = { 0 };
    HWND hdlg = CreateDialogParam(g_hinst, MAKEINTRESOURCE(1),
                                  hwnd, DlgProc, reinterpret_cast<LPARAM>(&ds));
    if (!hdlg) {
        return -1;
    }

    EnableWindow(hwnd, FALSE);
    MSG msg;
    msg.message = WM_NULL; // anything that isn't WM_QUIT
    while (!ds.fEnded) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            } else if (!IsDialogMessage(hdlg, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else if (!ds.fEnded) {
            WaitMessage();
        }
    }
    if (msg.message == WM_QUIT) {
        PostQuitMessage((int)msg.wParam);
    }
    EnableWindow(hwnd, TRUE);
    DestroyWindow(hdlg);
    return ds.iResult;
}