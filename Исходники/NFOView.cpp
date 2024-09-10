void NFOView::CopySelectedText(void)
{
    DWORD selStart;
    DWORD selEnd;
    SendMessage(_handle, EM_GETSEL, (WPARAM)&selStart, (LPARAM)&selEnd);

    if (selEnd > selStart)
    {
        int textLength = GetWindowTextLengthW(_handle);
        if (textLength > 0)
        {
            HGLOBAL selTextHandle;
            selTextHandle = GlobalAlloc(GHND, sizeof(wchar_t)*(selEnd - selStart + 1));

            // copy selected text to memory
            wchar_t* selText = (wchar_t*)GlobalLock(selTextHandle);
            memcpy(selText, _nfoText.c_str()+selStart, (selEnd-selStart)*sizeof(wchar_t));
            GlobalUnlock(selTextHandle);

            // copy to clipboard
            if (!OpenClipboard(_handle))
            { 
                return;
            }
            EmptyClipboard();
            SetClipboardData(CF_UNICODETEXT, selTextHandle);
            CloseClipboard();
        }
    }
    
    // deselect text after copy
    SendMessage(_handle, EM_SETSEL, (WPARAM)-1, (LPARAM)0);
}