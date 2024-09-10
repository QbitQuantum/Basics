BOOL CCefRealWndHandler::OnRealWndSize(SRealWnd *pRealWnd)
{
	if(!pRealWnd)
		return FALSE;
    
// return TRUE 由自己来移动窗口位置
	SWindow* pParent = pRealWnd->GetParent();
	CRect rcParent = pParent->GetClientRect();
	::SetWindowPos(pRealWnd->GetRealHwnd(FALSE),0,rcParent.left,rcParent.top,rcParent.Width(),rcParent.Height(),SWP_NOZORDER);
    return TRUE;
}