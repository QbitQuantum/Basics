//背景消息
BOOL CDlgOptionItem::OnEraseBkgnd(CDC * pDC)
{
    Invalidate(FALSE);
    UpdateWindow();
    return TRUE;
}