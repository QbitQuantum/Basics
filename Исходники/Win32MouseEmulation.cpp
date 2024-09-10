// Determine if the mouse is presently being captured. This call can be
// made outside of the GUI thread
bool isMouseCaptured(HWND hWnd, HWND &hCaptureWnd)
{
    bool bIsCaptured = false;

    DWORD processId = GetWindowThreadProcessId(hWnd, NULL);

    GUITHREADINFO threadInfo;
    threadInfo.cbSize = sizeof GUITHREADINFO;

    if (GetGUIThreadInfo(processId, &threadInfo))
    {
        bIsCaptured = bIsCaptured || (threadInfo.hwndCapture != 0);

        bIsCaptured = bIsCaptured || ((threadInfo.flags & 
            (GUI_INMENUMODE | GUI_INMOVESIZE |
            GUI_POPUPMENUMODE | GUI_SYSTEMMENUMODE)) != 0);

        hCaptureWnd = threadInfo.hwndCapture;
    }
    else
    {
        hCaptureWnd = NULL;
        //DisplayLastError("Failed to get GUITHREADINFO");
    }

    return bIsCaptured;
}