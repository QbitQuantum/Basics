CSizingControlBar* CSCBMiniDockFrameWnd::GetSizingControlBar()
{
    CWnd* pWnd = GetWindow(GW_CHILD); // get the dockbar
    if (pWnd == NULL)
        return NULL;
    
    pWnd = pWnd->GetWindow(GW_CHILD); // get the controlbar
    if (pWnd == NULL)
        return NULL;

    if (!pWnd->IsKindOf(RUNTIME_CLASS(CSizingControlBar)))
        return NULL;

    return (CSizingControlBar*) pWnd;
}