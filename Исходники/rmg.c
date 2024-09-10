// http://www.codeproject.com/Tips/76427/How-to-bring-window-to-top-with-SetForegroundWindo
void SetForegroundWindowInternal(HWND hWnd)
{
    SetWindowPos(hWnd,HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(hWnd,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(hWnd,HWND_NOTOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
    return;
    //relation time of SetForegroundWindow lock
    DWORD lockTimeOut = 0;
    HWND  hCurrWnd = GetForegroundWindow();
    DWORD dwThisTID = GetCurrentThreadId(),
        dwCurrTID = GetWindowThreadProcessId(hCurrWnd, 0);

    //we need to bypass some limitations from Microsoft :)
    if (dwThisTID != dwCurrTID)
    {
        AttachThreadInput(dwThisTID, dwCurrTID, TRUE);

        SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, &lockTimeOut, 0);
        SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, 0, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);

        AllowSetForegroundWindow(ASFW_ANY);
    }

    SetForegroundWindow(hWnd);

    if (dwThisTID != dwCurrTID)
    {
        SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, (PVOID)lockTimeOut, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
        AttachThreadInput(dwThisTID, dwCurrTID, FALSE);
    }
}