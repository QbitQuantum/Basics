void CScrollBarWindow::_SetScrollInfo(_In_ CScrollInfo *lpsi)
{
    _scrollInfo = *lpsi;

    BOOL isEnable = (_scrollInfo.nMax > _scrollInfo.nPage);

    _Enable(isEnable);

    _scrollDir = SCROLL_NONE_DIR;

    _SetCurPos(_scrollInfo.nPos, -1);
}