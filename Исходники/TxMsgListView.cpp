CWnd* CTxMsgListView::pomGetParentWindow() const
{
    CWnd* pWnd = nullptr;
    // Get Splitter window pointer
    pWnd = GetParent();
    // Get Tx Msg Child Window pointer from Splitter window pointer
    // At fourth Level
    // Splitter 3 -> Splitter 2 -> Splitter 1 -> Child Frame
    if( pWnd != nullptr )
    {
        pWnd = pWnd->GetParent();
    }
    if( pWnd != nullptr )
    {
        pWnd = pWnd->GetParent();
    }

    if( pWnd != nullptr )
    {
        pWnd = pWnd->GetParent();
    }

    // Return Tx Msg Child window pointer or nullptr incase of failure
    return pWnd;
}