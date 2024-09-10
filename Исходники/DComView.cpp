BOOL CDComView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{
    SCROLLINFO info;
    if (HIBYTE(nScrollCode) == SB_THUMBTRACK)
    {
        GetScrollInfo(SB_VERT, &info);
        nPos = info.nTrackPos;
        Invalidate();
    }
    return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}