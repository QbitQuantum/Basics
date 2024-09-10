void CSummaryView::OnContextMenu(HWND /*hWnd*/, CPoint pt)
{
    WTL::CMenu m;
    m.LoadMenu(IDR_POPUP_RESULTS_SUMMARY);
    CResultContext context(this, m,pt);
    if ( !m_resultSlot || !m_resultSlot->OnContextResult(context) )
    {
        //if nobody handled it, then do it ourselves
        BOOL id = m.GetSubMenu(0).TrackPopupMenuEx(TPM_RETURNCMD, pt.x, pt.y, m_hWnd, NULL);
        if (id)
            PostMessage(WM_COMMAND, id);
    }
}