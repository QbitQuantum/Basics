bool UClipBoard::getFromClipboard(TCHAR *buf)
{

    if (OpenClipboard (0) != 0)
    {
        HANDLE bufH = GetClipboardData (CF_TEXT);

        if (bufH != 0)
        {
            const char* const data = (const char*) GlobalLock (bufH);

            if (data != 0)
            {
                ::memcpy(buf, data, (int) (GlobalSize (bufH) / sizeof(char)));

                GlobalUnlock (bufH);
            }
        }

        CloseClipboard();
    }



    return false;
}