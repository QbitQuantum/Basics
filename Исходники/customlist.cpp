// helper function to loop through and enable / disable all child windows
void EnableDescendants(HWND hWnd, BOOL enable)
{
    // walk through HWNDs to avoid creating temporary CWnd objects
    // unless we need to call this function recursively
    for (HWND hWndChild = ::GetTopWindow(hWnd); hWndChild != NULL;
            hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
    {
        CWnd* pWnd = CWnd::FromHandlePermanent(hWndChild);
        if (pWnd != NULL)
        {
            pWnd->EnableWindow(enable);
            pWnd->RedrawWindow();
        }
        if (::GetTopWindow(hWndChild) != NULL)
        {
            // send to child windows after parent
            EnableDescendants(hWndChild,enable);
        }
    }
}