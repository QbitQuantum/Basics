// Hook procedure for WH_GETMESSAGE hook type.
//
// This function is more or less a combination of MSDN KB articles
// Q187988 and Q216503. See MSDN for additional details
LRESULT CALLBACK CDialogMessageHook::GetMessageProc(int nCode, 
                                 WPARAM wParam, LPARAM lParam)
{
    // If this is a keystrokes message, pass it to IsDialogMessage for tab
    // and accelerator processing
    LPMSG lpMsg = (LPMSG) lParam;

    // check if there is a menu active
    HWND hMenuWnd = NULL;
    EnumWindows(MyEnumProc, (LPARAM)&hMenuWnd);

    if (hMenuWnd == NULL &&
        (nCode >= 0) &&
        PM_REMOVE == wParam &&
        (lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST))
    {
        HWND hWnd, hActiveWindow = GetActiveWindow();
        THWNDCollection::iterator it = m_aWindows.begin();

        // check each window we manage to see if the message is meant for them
        while (it != m_aWindows.end())
        {
            hWnd = *it;

            if (::IsWindow(hWnd) &&
                ::IsDialogMessage(hWnd, lpMsg))
            {
                // The value returned from this hookproc is ignored, and it cannot
                // be used to tell Windows the message has been handled. To avoid
                // further processing, convert the message to WM_NULL before
                // returning.
                lpMsg->hwnd = NULL;
                lpMsg->message = WM_NULL;
                lpMsg->lParam = 0L;
                lpMsg->wParam = 0;

                break;
            }

            it++;
        }
    }

    // Passes the hook information to the next hook procedure in
    // the current hook chain.
    return ::CallNextHookEx(m_hHook, nCode, wParam, lParam);
}