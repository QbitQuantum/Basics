void SendKeyHelper(HANDLE hIn, WORD vk)
{
    INPUT_RECORD irPause = { 0 };
    irPause.EventType = KEY_EVENT;
    irPause.Event.KeyEvent.bKeyDown = TRUE;
    irPause.Event.KeyEvent.wVirtualKeyCode = vk;

    DWORD dwWritten = 0;
    VERIFY_WIN32_BOOL_SUCCEEDED(WriteConsoleInputW(hIn, &irPause, 1u, &dwWritten), L"Key event sent.");
}