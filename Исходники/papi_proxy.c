BOOL SkypeAttach(HWND hwnd)
{
    LRESULT result;
    _hwndSkype = NULL;

    result = SendMessageTimeoutA(HWND_BROADCAST, _msgDiscover,
            (WPARAM)hwnd, (LPARAM)NULL, 2, 5000, NULL);

    if (!result)
    {
        MessageBox(hwnd, "cannot send message discover", "error",
                MB_OK | MB_ICONSTOP | MB_APPLMODAL);

        return TRUE;
    }

    return FALSE;
}