void BufferTimeList::FlashCaption(vector<TCHAR *> messages)
{
    // save
    TCHAR title[1024];
    GetWindowText(_hwnd, title, 1024);

    for (int idx = 0; idx < messages.size(); idx++)
    {
        int count = 10;
        while (--count >= 0)
        {
            SetWindowText(_hwnd, messages[idx]);
            FlashWindow(_hwnd, TRUE);
            Sleep(500);
        }
        delete [] messages[idx];
    }

    // restore 
    SetWindowText(_hwnd, title);
    FlashWindow(_hwnd, FALSE);
}