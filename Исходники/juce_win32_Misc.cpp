String SystemClipboard::getTextFromClipboard()
{
    String result;

    if (OpenClipboard (0) != 0)
    {
        HANDLE bufH = GetClipboardData (CF_UNICODETEXT);

        if (bufH != 0)
        {
            const WCHAR* const data = (const WCHAR*) GlobalLock (bufH);

            if (data != nullptr)
            {
                result = String (data, (int) (GlobalSize (bufH) / sizeof (WCHAR)));

                GlobalUnlock (bufH);
            }
        }

        CloseClipboard();
    }

    return result;
}